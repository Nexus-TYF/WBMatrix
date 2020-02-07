
#include <NTL/mat_lzz_p.h>
#include <NTL/new.h>
#include <NTL/vec_long.h>


#include <NTL/BasicThreadPool.h>


#ifdef NTL_HAVE_AVX
#include <immintrin.h>
#endif


NTL_START_IMPL




  
void add(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
  
   if (B.NumRows() != n || B.NumCols() != m)   
      LogicError("matrix add: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j;  
   for (i = 1; i <= n; i++)   
      for (j = 1; j <= m; j++)  
         add(X(i,j), A(i,j), B(i,j));  
}  
  
void sub(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
  
   if (B.NumRows() != n || B.NumCols() != m)  
      LogicError("matrix sub: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j;  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= m; j++)  
         sub(X(i,j), A(i,j), B(i,j));  
}  





void diag(mat_zz_p& X, long n, zz_p d)  
{  
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= n; j++)  
         if (i == j)  
            X(i, j) = d;  
         else  
            clear(X(i, j));  
} 

long IsDiag(const mat_zz_p& A, long n, zz_p d)
{
   if (A.NumRows() != n || A.NumCols() != n)
      return 0;

   long i, j;

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i != j) {
            if (!IsZero(A(i, j))) return 0;
         }
         else {
            if (A(i, j) != d) return 0;
         }

   return 1;
}

void negate(mat_zz_p& X, const mat_zz_p& A)
{
   long n = A.NumRows();
   long m = A.NumCols();


   X.SetDims(n, m);

   long i, j;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++)
         negate(X(i,j), A(i,j));
}

long IsZero(const mat_zz_p& a)
{
   long n = a.NumRows();
   long i;

   for (i = 0; i < n; i++)
      if (!IsZero(a[i]))
         return 0;

   return 1;
}

void clear(mat_zz_p& x)
{
   long n = x.NumRows();
   long i;
   for (i = 0; i < n; i++)
      clear(x[i]);
}

  
void ident(mat_zz_p& X, long n)  
{  
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= n; j++)  
         if (i == j)  
            set(X(i, j));  
         else  
            clear(X(i, j));  
} 


long IsIdent(const mat_zz_p& A, long n)
{
   if (A.NumRows() != n || A.NumCols() != n)
      return 0;

   long i, j;

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i != j) {
            if (!IsZero(A(i, j))) return 0;
         }
         else {
            if (!IsOne(A(i, j))) return 0;
         }

   return 1;
}
            

void transpose(mat_zz_p& X, const mat_zz_p& A)
{
   long n = A.NumRows();
   long m = A.NumCols();

   long i, j;

   if (&X == & A) {
      if (n == m)
         for (i = 1; i <= n; i++)
            for (j = i+1; j <= n; j++)
               swap(X(i, j), X(j, i));
      else {
         mat_zz_p tmp;
         tmp.SetDims(m, n);
         for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
               tmp(j, i) = A(i, j);
         X.kill();
         X = tmp;
      }
   }
   else {
      X.SetDims(m, n);
      for (i = 1; i <= n; i++)
         for (j = 1; j <= m; j++)
            X(j, i) = A(i, j);
   }
}
   



void relaxed_power(mat_zz_p& X, const mat_zz_p& A, const ZZ& e, bool relax)
{
   if (A.NumRows() != A.NumCols()) LogicError("power: non-square matrix");

   if (e == 0) {
      ident(X, A.NumRows());
      return;
   }

   mat_zz_p T1, T2;
   long i, k;

   k = NumBits(e);
   T1 = A;

   for (i = k-2; i >= 0; i--) {
      sqr(T2, T1);
      if (bit(e, i))
         mul(T1, T2, A);
      else
         T1 = T2;
   }

   if (e < 0)
      relaxed_inv(X, T1, relax);
   else
      X = T1;
}



// ******************************************************************
//
// matrix-vector multiplication code
//
// ******************************************************************
  

// some local buffers

NTL_THREAD_LOCAL static vec_long mul_aux_vec;
NTL_THREAD_LOCAL static Vec<mulmod_precon_t> precon_vec;



void mul(vec_zz_p& x, const vec_zz_p& a, const mat_zz_p& B)
{
   long l = a.length();
   long m = B.NumCols();
  
   if (l != B.NumRows())  
      LogicError("matrix mul: dimension mismatch");  

   if (m == 0) { 

      x.SetLength(0);
      
   }
   else if (m == 1) {

      long p = zz_p::modulus();
      mulmod_t pinv = zz_p::ModulusInverse();

      long acc, tmp;
      long k;

      acc = 0;  
      for(k = 1; k <= l; k++) {  
         tmp = MulMod(rep(a(k)), rep(B(k,1)), p, pinv);  
         acc = AddMod(acc, tmp, p);  
      } 

      x.SetLength(1);
      x(1).LoopHole()  = acc;
          
   }
   else {  // m > 1.  precondition and EXEC_RANGE


      long p = zz_p::modulus();
      mulmod_t pinv = zz_p::ModulusInverse();

      vec_long::Watcher watch_mul_aux_vec(mul_aux_vec);
      mul_aux_vec.SetLength(m);
      long *acc = mul_aux_vec.elts();

      const zz_p* ap = a.elts();

      for (long j = 0; j < m; j++) acc[j] = 0;

      const bool seq = double(l)*double(m) < 20000;

      NTL_GEXEC_RANGE(seq, m, first, last) {

         for (long k = 0;  k < l; k++) {
            long aa = rep(ap[k]);
            if (aa != 0) {
               const zz_p* bp = B[k].elts();
               long T1;
               mulmod_precon_t aapinv = PrepMulModPrecon(aa, p, pinv);
   
               for (long j = first; j < last; j++) {
                  T1 = MulModPrecon(rep(bp[j]), aa, p, aapinv);
                  acc[j] = AddMod(acc[j], T1, p);
               }
            } 
         }

      } NTL_GEXEC_RANGE_END

      x.SetLength(m);
      zz_p *xp = x.elts();
      for (long j = 0; j < m; j++)
         xp[j].LoopHole() = acc[j];    
   }
}

  
void mul_aux(vec_zz_p& x, const mat_zz_p& A, const vec_zz_p& b)
{
   long n = A.NumRows();
   long l = A.NumCols();

   if (l != b.length())
      LogicError("matrix mul: dimension mismatch");

   x.SetLength(n);
   zz_p* xp = x.elts();

   long p = zz_p::modulus();
   const zz_p* bp = b.elts();

   const bool seq = double(n)*double(l) < 20000;


#ifdef NTL_HAVE_LL_TYPE

   if (cast_unsigned(l) <= (~(0UL))/cast_unsigned(p-1) &&
       cast_unsigned(l)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

      sp_reduce_struct red_struct = zz_p::red_struct();

      NTL_GEXEC_RANGE(seq, n, first, last) {

         for (long i = first; i < last; i++) {
            xp[i].LoopHole() = InnerProd_L(A[i].elts(), bp, l, p, red_struct);
         }

      } NTL_GEXEC_RANGE_END
   }
   else {
      sp_ll_reduce_struct ll_red_struct = zz_p::ll_red_struct();

      NTL_GEXEC_RANGE(seq, n, first, last) {

         for (long i = first; i < last; i++) {
            xp[i].LoopHole() = InnerProd_LL(A[i].elts(), bp, l, p, ll_red_struct);
         }

      } NTL_GEXEC_RANGE_END

   }

#else

   mulmod_t pinv = zz_p::ModulusInverse();

   if (n <= 1) {

      for (long i = 0; i < n; i++) {
	 long acc = 0;
	 const zz_p* ap = A[i].elts();

	 for (long k = 0; k < l; k++) {
            long tmp = MulMod(rep(ap[k]), rep(bp[k]), p, pinv);
            acc = AddMod(acc, tmp, p);
	 }

	 xp[i].LoopHole() = acc;
      }

   }
   else {

      Vec<mulmod_precon_t>::Watcher watch_precon_vec(precon_vec);
      precon_vec.SetLength(l);
      mulmod_precon_t *bpinv = precon_vec.elts();

      for (long k = 0; k < l; k++)
         bpinv[k] = PrepMulModPrecon(rep(bp[k]), p, pinv);

      
      NTL_GEXEC_RANGE(seq, n, first, last) {
         for (long i = first; i < last; i++) {
            long acc = 0;
            const zz_p* ap = A[i].elts();
           
            for (long k = 0; k < l; k++) {
               long tmp = MulModPrecon(rep(ap[k]), rep(bp[k]), p, bpinv[k]);
               acc = AddMod(acc, tmp, p);
            }
           
            xp[i].LoopHole() = acc;
         } 
      } NTL_GEXEC_RANGE_END

   }

#endif
}
  
void mul(vec_zz_p& x, const mat_zz_p& A, const vec_zz_p& b)  
{  
   if (&b == &x || A.position1(x) != -1) {
      vec_zz_p tmp;
      mul_aux(tmp, A, b);
      x = tmp;
   }
   else
      mul_aux(x, A, b);

}  


void mul(mat_zz_p& X, const mat_zz_p& A, zz_p b)
{
   long n = A.NumRows();
   long m = A.NumCols();

   X.SetDims(n, m);


   if (n == 0 || m == 0 || (n == 1 && m == 1)) {
      long i, j;

      for (i = 0; i < n; i++)
	 for (j = 0; j < m; j++)
            mul(X[i][j], A[i][j], b);

   }
   else {
      
      long p = zz_p::modulus();
      mulmod_t pinv = zz_p::ModulusInverse();
      long bb = rep(b);
      mulmod_precon_t bpinv = PrepMulModPrecon(bb, p, pinv);

      const bool seq = double(n)*double(m) < 20000;
      
      NTL_GEXEC_RANGE(seq, n, first, last) 
      long i, j;
      for (i = first; i < last; i++) {
         const zz_p *ap = A[i].elts();
         zz_p *xp = X[i].elts();

	 for (j = 0; j < m; j++)
            xp[j].LoopHole() = MulModPrecon(rep(ap[j]), bb, p, bpinv);
      }
      NTL_GEXEC_RANGE_END


   }
}

void mul(mat_zz_p& X, const mat_zz_p& A, long b_in)
{
   zz_p b;
   b = b_in;
   mul(X, A, b);
} 


// ******************************************************************
//
// Code shared by block-matrix code
//
// ******************************************************************

#define INV_BLK_SZ (32)


#ifdef NTL_HAVE_LL_TYPE

#ifdef NTL_HAVE_AVX

#define MAX_DBL_INT ((1L << NTL_DOUBLE_PRECISION)-1)
// max int representable exactly as a double
// this assumes NTL_DBL_PRECISION <= NTL_BITS_PER_LONG-2, which is
// checked in the code that tests for HAVE_AVX, but we check it here as
// well

#if (NTL_DBL_PRECISION > NTL_BITS_PER_LONG-2)
#error "NTL_DBL_PRECISION > NTL_BITS_PER_LONG-2"
#endif


// MUL_ADD(a, b, c): a += b*c
#ifdef NTL_HAVE_FMA
#define MUL_ADD(a, b, c) a = _mm256_fmadd_pd(b, c, a) 
#else
#define MUL_ADD(a, b, c) a = _mm256_add_pd(a, _mm256_mul_pd(b, c))
#endif

static
void muladd1_by_32(double *x, const double *a, const double *b, long n)
{
   __m256d avec, bvec;


   __m256d acc0=_mm256_load_pd(x + 0*4);
   __m256d acc1=_mm256_load_pd(x + 1*4);
   __m256d acc2=_mm256_load_pd(x + 2*4);
   __m256d acc3=_mm256_load_pd(x + 3*4);
   __m256d acc4=_mm256_load_pd(x + 4*4);
   __m256d acc5=_mm256_load_pd(x + 5*4);
   __m256d acc6=_mm256_load_pd(x + 6*4);
   __m256d acc7=_mm256_load_pd(x + 7*4);


   for (long i = 0; i < n; i++) {
      avec = _mm256_broadcast_sd(a); a++;


      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc0, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc1, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc2, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc3, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc4, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc5, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc6, avec, bvec);
      bvec = _mm256_load_pd(b); b += 4; MUL_ADD(acc7, avec, bvec);
   }


   _mm256_store_pd(x + 0*4, acc0);
   _mm256_store_pd(x + 1*4, acc1);
   _mm256_store_pd(x + 2*4, acc2);
   _mm256_store_pd(x + 3*4, acc3);
   _mm256_store_pd(x + 4*4, acc4);
   _mm256_store_pd(x + 5*4, acc5);
   _mm256_store_pd(x + 6*4, acc6);
   _mm256_store_pd(x + 7*4, acc7);
}



// this assumes n is a multiple of 16
static inline
void BlockMul(double * NTL_RESTRICT x, double * NTL_RESTRICT y, double c, long n)
{
   __m256d xvec0, xvec1, xvec2, xvec3;
   __m256d yvec0, yvec1, yvec2, yvec3;

   __m256d cvec = _mm256_broadcast_sd(&c);

   for (long i = 0; i < n; i += 16, x += 16, y += 16) {
      xvec0 = _mm256_load_pd(x+0*4);
      xvec1 = _mm256_load_pd(x+1*4);
      xvec2 = _mm256_load_pd(x+2*4);
      xvec3 = _mm256_load_pd(x+3*4);

      yvec0 = _mm256_load_pd(y+0*4);
      yvec1 = _mm256_load_pd(y+1*4);
      yvec2 = _mm256_load_pd(y+2*4);
      yvec3 = _mm256_load_pd(y+3*4);

      MUL_ADD(xvec0, yvec0, cvec);
      MUL_ADD(xvec1, yvec1, cvec);
      MUL_ADD(xvec2, yvec2, cvec);
      MUL_ADD(xvec3, yvec3, cvec);

      _mm256_store_pd(x + 0*4, xvec0);
      _mm256_store_pd(x + 1*4, xvec1);
      _mm256_store_pd(x + 2*4, xvec2);
      _mm256_store_pd(x + 3*4, xvec3);
   }
}

// this one is more general: does not assume that n is a
// multiple of 16
static inline
void BlockMul1(double * NTL_RESTRICT x, double * NTL_RESTRICT y, double c, long n)
{

   __m256d xvec0, xvec1, xvec2, xvec3;
   __m256d yvec0, yvec1, yvec2, yvec3;
   __m256d cvec;

   if (n >= 4)
      cvec = _mm256_broadcast_sd(&c);

   long i=0;
   for (; i <= n-16; i += 16, x += 16, y += 16) {
      xvec0 = _mm256_load_pd(x+0*4);
      xvec1 = _mm256_load_pd(x+1*4);
      xvec2 = _mm256_load_pd(x+2*4);
      xvec3 = _mm256_load_pd(x+3*4);

      yvec0 = _mm256_load_pd(y+0*4);
      yvec1 = _mm256_load_pd(y+1*4);
      yvec2 = _mm256_load_pd(y+2*4);
      yvec3 = _mm256_load_pd(y+3*4);

      MUL_ADD(xvec0, yvec0, cvec);
      MUL_ADD(xvec1, yvec1, cvec);
      MUL_ADD(xvec2, yvec2, cvec);
      MUL_ADD(xvec3, yvec3, cvec);

      _mm256_store_pd(x + 0*4, xvec0);
      _mm256_store_pd(x + 1*4, xvec1);
      _mm256_store_pd(x + 2*4, xvec2);
      _mm256_store_pd(x + 3*4, xvec3);
   }

   for (; i <= n-4; i += 4, x += 4, y += 4) {
      xvec0 = _mm256_load_pd(x+0*4);
      yvec0 = _mm256_load_pd(y+0*4);
      MUL_ADD(xvec0, yvec0, cvec);
      _mm256_store_pd(x + 0*4, xvec0);
   }

   for (; i < n; i++, x++, y++) {
      *x += (*y)*c;
   }
}


#endif


#define DO_MUL(a, b) ((unsigned long) (long(a)*long(b)))
//#define DO_MUL(a, b) ((a)*(b))

static
inline void BlockMul(unsigned long * NTL_RESTRICT x, unsigned long * NTL_RESTRICT y, 
                     unsigned long c, long n)
{
   for (long i = 0; i < n; i++)
      x[i] += DO_MUL(y[i], c);
}

static
void muladd1_by_32(unsigned long *x, const unsigned long *a, const unsigned long *b, 
                   long n)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {
      unsigned long sum = x[j];
      long i = 0;

      for (; i <= n-4; i += 4) {
	 sum += DO_MUL(a[i+0], b[i+0]);
	 sum += DO_MUL(a[i+1], b[i+1]);
	 sum += DO_MUL(a[i+2], b[i+2]);
	 sum += DO_MUL(a[i+3], b[i+3]);
      }

      for (; i < n; i++)
	 sum += DO_MUL(a[i], b[i]);

      x[j] = sum;
      b += INV_BLK_SZ;
   }
}

#if 0
static
void muladd1_by_32_full(unsigned long *x, const unsigned long *a, const unsigned long *b)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {
      unsigned long sum = x[j];
      long i = 0;

      sum += DO_MUL(a[i+0], b[i+0]);
      sum += DO_MUL(a[i+1], b[i+1]);
      sum += DO_MUL(a[i+2], b[i+2]);
      sum += DO_MUL(a[i+3], b[i+3]);
      sum += DO_MUL(a[i+4], b[i+4]);
      sum += DO_MUL(a[i+5], b[i+5]);
      sum += DO_MUL(a[i+6], b[i+6]);
      sum += DO_MUL(a[i+7], b[i+7]);
      sum += DO_MUL(a[i+8], b[i+8]);
      sum += DO_MUL(a[i+9], b[i+9]);
      sum += DO_MUL(a[i+10], b[i+10]);
      sum += DO_MUL(a[i+11], b[i+11]);
      sum += DO_MUL(a[i+12], b[i+12]);
      sum += DO_MUL(a[i+13], b[i+13]);
      sum += DO_MUL(a[i+14], b[i+14]);
      sum += DO_MUL(a[i+15], b[i+15]);
      sum += DO_MUL(a[i+16], b[i+16]);
      sum += DO_MUL(a[i+17], b[i+17]);
      sum += DO_MUL(a[i+18], b[i+18]);
      sum += DO_MUL(a[i+19], b[i+19]);
      sum += DO_MUL(a[i+20], b[i+20]);
      sum += DO_MUL(a[i+21], b[i+21]);
      sum += DO_MUL(a[i+22], b[i+22]);
      sum += DO_MUL(a[i+23], b[i+23]);
      sum += DO_MUL(a[i+24], b[i+24]);
      sum += DO_MUL(a[i+25], b[i+25]);
      sum += DO_MUL(a[i+26], b[i+26]);
      sum += DO_MUL(a[i+27], b[i+27]);
      sum += DO_MUL(a[i+28], b[i+28]);
      sum += DO_MUL(a[i+29], b[i+29]);
      sum += DO_MUL(a[i+30], b[i+30]);
      sum += DO_MUL(a[i+31], b[i+31]);

      x[j] = sum;
      b += INV_BLK_SZ;
   }
}
#else

// this version is faster (by about 25%) on a Sandybridge machine

#define ONE_STEP_L(i) \
  sum += DO_MUL(a[i],b[i]);\
  sum_1 += DO_MUL(a[i],b_1[i]);\
  sum_2 += DO_MUL(a[i],b_2[i]);\
  sum_3 += DO_MUL(a[i],b_3[i])\


static
void muladd1_by_32_full(unsigned long *x, const unsigned long *a, const unsigned long *b)
{
   for (long j = 0; j < INV_BLK_SZ; j+=4) {

      unsigned long sum = x[j];
      unsigned long sum_1 = x[j+1];
      unsigned long sum_2 = x[j+2];
      unsigned long sum_3 = x[j+3];

      const unsigned long *b_1 = b+INV_BLK_SZ;
      const unsigned long *b_2 = b+2*INV_BLK_SZ;
      const unsigned long *b_3 = b+3*INV_BLK_SZ;

      ONE_STEP_L(0);
      ONE_STEP_L(1);
      ONE_STEP_L(2);
      ONE_STEP_L(3);
      ONE_STEP_L(4);
      ONE_STEP_L(5);
      ONE_STEP_L(6);
      ONE_STEP_L(7);
      ONE_STEP_L(8);
      ONE_STEP_L(9);
      ONE_STEP_L(10);
      ONE_STEP_L(11);
      ONE_STEP_L(12);
      ONE_STEP_L(13);
      ONE_STEP_L(14);
      ONE_STEP_L(15);
      ONE_STEP_L(16);
      ONE_STEP_L(17);
      ONE_STEP_L(18);
      ONE_STEP_L(19);
      ONE_STEP_L(20);
      ONE_STEP_L(21);
      ONE_STEP_L(22);
      ONE_STEP_L(23);
      ONE_STEP_L(24);
      ONE_STEP_L(25);
      ONE_STEP_L(26);
      ONE_STEP_L(27);
      ONE_STEP_L(28);
      ONE_STEP_L(29);
      ONE_STEP_L(30);
      ONE_STEP_L(31);

      x[j]   = sum;
      x[j+1] = sum_1;
      x[j+2] = sum_2; 
      x[j+3] = sum_3; 

      b += 4*INV_BLK_SZ;
   }
}

#endif



#define NTL_CAST_ULL(x) ((NTL_ULL_TYPE) (x))
//#define NTL_CAST_ULL(x) ((NTL_ULL_TYPE)(unsigned long)(x))
#define NTL_MUL_ULL(x,y) (NTL_CAST_ULL(x)*NTL_CAST_ULL(y))
// NOTE: the following code sequence will generate imulq 
// instructions on x86_64 machines, which empirically is faster
// than using the mulq instruction or even the mulxq instruction,
// (tested on a Haswell machine).

// NOTE: the following code is hardcoded for INV_BLK_SZ == 32.
// Also, we special case NTL_BITS_PER_LONG-NTL_SP_NBITS > 2, which
// allows us to accumulate all 32 products without additional carries.

#if (NTL_BITS_PER_LONG-NTL_SP_NBITS > 2)

static
void muladd1_by_32(long *x, const long *a, const long *b, 
                   long n, long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);

#if 0
      for (long i = 0; i < n; i++)
	 sum += NTL_MUL_ULL(a[i], b[i]);
#else
      long i=0;
      for(; i <= n-8; i+= 8) {
	 sum += NTL_MUL_ULL(a[i+0], b[i+0]);
	 sum += NTL_MUL_ULL(a[i+1], b[i+1]);
	 sum += NTL_MUL_ULL(a[i+2], b[i+2]);
	 sum += NTL_MUL_ULL(a[i+3], b[i+3]);

	 sum += NTL_MUL_ULL(a[i+4], b[i+4]);
	 sum += NTL_MUL_ULL(a[i+5], b[i+5]);
	 sum += NTL_MUL_ULL(a[i+6], b[i+6]);
	 sum += NTL_MUL_ULL(a[i+7], b[i+7]);
      }

      for (; i < n; i++)
	 sum += NTL_MUL_ULL(a[i], b[i]);
      
#endif

      unsigned long sum0 = sum;
      unsigned long sum1 = sum >> NTL_BITS_PER_LONG;

      long res;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) 
	 res = sp_ll_red_31_normalized(0, sum1, sum0, p, ll_red_struct);
      else
	 res =  sp_ll_red_31(0, sum1, sum0, p, ll_red_struct);


      x[j] = res;
      b += INV_BLK_SZ;
   }
}

#if 0
static
void muladd1_by_32_full(long *x, const long *a, const long *b, 
                        long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);

      sum += NTL_MUL_ULL(a[0], b[0]);
      sum += NTL_MUL_ULL(a[1], b[1]);
      sum += NTL_MUL_ULL(a[2], b[2]);
      sum += NTL_MUL_ULL(a[3], b[3]);
      sum += NTL_MUL_ULL(a[4], b[4]);
      sum += NTL_MUL_ULL(a[5], b[5]);
      sum += NTL_MUL_ULL(a[6], b[6]);
      sum += NTL_MUL_ULL(a[7], b[7]);
      sum += NTL_MUL_ULL(a[8], b[8]);
      sum += NTL_MUL_ULL(a[9], b[9]);
      sum += NTL_MUL_ULL(a[10], b[10]);
      sum += NTL_MUL_ULL(a[11], b[11]);
      sum += NTL_MUL_ULL(a[12], b[12]);
      sum += NTL_MUL_ULL(a[13], b[13]);
      sum += NTL_MUL_ULL(a[14], b[14]);
      sum += NTL_MUL_ULL(a[15], b[15]);
      sum += NTL_MUL_ULL(a[16], b[16]);
      sum += NTL_MUL_ULL(a[17], b[17]);
      sum += NTL_MUL_ULL(a[18], b[18]);
      sum += NTL_MUL_ULL(a[19], b[19]);
      sum += NTL_MUL_ULL(a[20], b[20]);
      sum += NTL_MUL_ULL(a[21], b[21]);
      sum += NTL_MUL_ULL(a[22], b[22]);
      sum += NTL_MUL_ULL(a[23], b[23]);
      sum += NTL_MUL_ULL(a[24], b[24]);
      sum += NTL_MUL_ULL(a[25], b[25]);
      sum += NTL_MUL_ULL(a[26], b[26]);
      sum += NTL_MUL_ULL(a[27], b[27]);
      sum += NTL_MUL_ULL(a[28], b[28]);
      sum += NTL_MUL_ULL(a[29], b[29]);
      sum += NTL_MUL_ULL(a[30], b[30]);
      sum += NTL_MUL_ULL(a[31], b[31]);

      unsigned long sum0 = sum;
      unsigned long sum1 = sum >> NTL_BITS_PER_LONG;

      long res;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) 
	 res = sp_ll_red_31_normalized(0, sum1, sum0, p, ll_red_struct);
      else
	 res =  sp_ll_red_31(0, sum1, sum0, p, ll_red_struct);


      x[j] = res;
      b += INV_BLK_SZ;
   }
}

#elif 0

static
void muladd1_by_32_full(long *x, const long *a, const long *b, 
                        long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j+=2) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);
      NTL_ULL_TYPE sum_ = cast_unsigned(x[j+1]);
      const long *b_ = b+INV_BLK_SZ;

      sum_ += NTL_MUL_ULL(a[0], b_[0]);      sum += NTL_MUL_ULL(a[0], b[0]);
      sum_ += NTL_MUL_ULL(a[1], b_[1]);      sum += NTL_MUL_ULL(a[1], b[1]);
      sum_ += NTL_MUL_ULL(a[2], b_[2]);      sum += NTL_MUL_ULL(a[2], b[2]);
      sum_ += NTL_MUL_ULL(a[3], b_[3]);      sum += NTL_MUL_ULL(a[3], b[3]);
      sum_ += NTL_MUL_ULL(a[4], b_[4]);      sum += NTL_MUL_ULL(a[4], b[4]);
      sum_ += NTL_MUL_ULL(a[5], b_[5]);      sum += NTL_MUL_ULL(a[5], b[5]);
      sum_ += NTL_MUL_ULL(a[6], b_[6]);      sum += NTL_MUL_ULL(a[6], b[6]);
      sum_ += NTL_MUL_ULL(a[7], b_[7]);      sum += NTL_MUL_ULL(a[7], b[7]);
      sum_ += NTL_MUL_ULL(a[8], b_[8]);      sum += NTL_MUL_ULL(a[8], b[8]);
      sum_ += NTL_MUL_ULL(a[9], b_[9]);      sum += NTL_MUL_ULL(a[9], b[9]);
      sum_ += NTL_MUL_ULL(a[10], b_[10]);      sum += NTL_MUL_ULL(a[10], b[10]);
      sum_ += NTL_MUL_ULL(a[11], b_[11]);      sum += NTL_MUL_ULL(a[11], b[11]);
      sum_ += NTL_MUL_ULL(a[12], b_[12]);      sum += NTL_MUL_ULL(a[12], b[12]);
      sum_ += NTL_MUL_ULL(a[13], b_[13]);      sum += NTL_MUL_ULL(a[13], b[13]);
      sum_ += NTL_MUL_ULL(a[14], b_[14]);      sum += NTL_MUL_ULL(a[14], b[14]);
      sum_ += NTL_MUL_ULL(a[15], b_[15]);      sum += NTL_MUL_ULL(a[15], b[15]);
      sum_ += NTL_MUL_ULL(a[16], b_[16]);      sum += NTL_MUL_ULL(a[16], b[16]);
      sum_ += NTL_MUL_ULL(a[17], b_[17]);      sum += NTL_MUL_ULL(a[17], b[17]);
      sum_ += NTL_MUL_ULL(a[18], b_[18]);      sum += NTL_MUL_ULL(a[18], b[18]);
      sum_ += NTL_MUL_ULL(a[19], b_[19]);      sum += NTL_MUL_ULL(a[19], b[19]);
      sum_ += NTL_MUL_ULL(a[20], b_[20]);      sum += NTL_MUL_ULL(a[20], b[20]);
      sum_ += NTL_MUL_ULL(a[21], b_[21]);      sum += NTL_MUL_ULL(a[21], b[21]);
      sum_ += NTL_MUL_ULL(a[22], b_[22]);      sum += NTL_MUL_ULL(a[22], b[22]);
      sum_ += NTL_MUL_ULL(a[23], b_[23]);      sum += NTL_MUL_ULL(a[23], b[23]);
      sum_ += NTL_MUL_ULL(a[24], b_[24]);      sum += NTL_MUL_ULL(a[24], b[24]);
      sum_ += NTL_MUL_ULL(a[25], b_[25]);      sum += NTL_MUL_ULL(a[25], b[25]);
      sum_ += NTL_MUL_ULL(a[26], b_[26]);      sum += NTL_MUL_ULL(a[26], b[26]);
      sum_ += NTL_MUL_ULL(a[27], b_[27]);      sum += NTL_MUL_ULL(a[27], b[27]);
      sum_ += NTL_MUL_ULL(a[28], b_[28]);      sum += NTL_MUL_ULL(a[28], b[28]);
      sum_ += NTL_MUL_ULL(a[29], b_[29]);      sum += NTL_MUL_ULL(a[29], b[29]);
      sum_ += NTL_MUL_ULL(a[30], b_[30]);      sum += NTL_MUL_ULL(a[30], b[30]);
      sum_ += NTL_MUL_ULL(a[31], b_[31]);      sum += NTL_MUL_ULL(a[31], b[31]);

      unsigned long sum0 = sum;
      unsigned long sum1 = sum >> NTL_BITS_PER_LONG;
      long res;

      unsigned long sum0_ = sum_;
      unsigned long sum1_ = sum_ >> NTL_BITS_PER_LONG;
      long res_;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) {
	 res = sp_ll_red_31_normalized(0, sum1, sum0, p, ll_red_struct);
	 res_ = sp_ll_red_31_normalized(0, sum1_, sum0_, p, ll_red_struct);
      }
      else {
	 res =  sp_ll_red_31(0, sum1, sum0, p, ll_red_struct);
	 res_ =  sp_ll_red_31(0, sum1_, sum0_, p, ll_red_struct);
      }


      x[j] = res;
      x[j+1] = res_;
      b += 2*INV_BLK_SZ;
   }
}
#elif 1
// This version is consistently fastest on tests on Sandybridge and Haswell

#define ONE_STEP(i) \
  sum += NTL_MUL_ULL(a[i],b[i]);\
  sum_1 += NTL_MUL_ULL(a[i],b_1[i]);\
  sum_2 += NTL_MUL_ULL(a[i],b_2[i]);\
  sum_3 += NTL_MUL_ULL(a[i],b_3[i])\




static
void muladd1_by_32_full(long *x, const long *a, const long *b, 
                        long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j+=4) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);
      NTL_ULL_TYPE sum_1 = cast_unsigned(x[j+1]);
      NTL_ULL_TYPE sum_2 = cast_unsigned(x[j+2]);
      NTL_ULL_TYPE sum_3 = cast_unsigned(x[j+3]);
      const long *b_1 = b+INV_BLK_SZ;
      const long *b_2 = b+2*INV_BLK_SZ;
      const long *b_3 = b+3*INV_BLK_SZ;

      ONE_STEP(0);
      ONE_STEP(1);
      ONE_STEP(2);
      ONE_STEP(3);
      ONE_STEP(4);
      ONE_STEP(5);
      ONE_STEP(6);
      ONE_STEP(7);
      ONE_STEP(8);
      ONE_STEP(9);
      ONE_STEP(10);
      ONE_STEP(11);
      ONE_STEP(12);
      ONE_STEP(13);
      ONE_STEP(14);
      ONE_STEP(15);
      ONE_STEP(16);
      ONE_STEP(17);
      ONE_STEP(18);
      ONE_STEP(19);
      ONE_STEP(20);
      ONE_STEP(21);
      ONE_STEP(22);
      ONE_STEP(23);
      ONE_STEP(24);
      ONE_STEP(25);
      ONE_STEP(26);
      ONE_STEP(27);
      ONE_STEP(28);
      ONE_STEP(29);
      ONE_STEP(30);
      ONE_STEP(31);

      unsigned long sum0 = sum;
      unsigned long sum1 = sum >> NTL_BITS_PER_LONG;

      unsigned long sum0_1 = sum_1;
      unsigned long sum1_1 = sum_1 >> NTL_BITS_PER_LONG;

      unsigned long sum0_2 = sum_2;
      unsigned long sum1_2 = sum_2 >> NTL_BITS_PER_LONG;

      unsigned long sum0_3 = sum_3;
      unsigned long sum1_3 = sum_3 >> NTL_BITS_PER_LONG;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) {
	 x[j] = sp_ll_red_31_normalized(0, sum1, sum0, p, ll_red_struct);
	 x[j+1] = sp_ll_red_31_normalized(0, sum1_1, sum0_1, p, ll_red_struct);
	 x[j+2] = sp_ll_red_31_normalized(0, sum1_2, sum0_2, p, ll_red_struct);
	 x[j+3] = sp_ll_red_31_normalized(0, sum1_3, sum0_3, p, ll_red_struct);
      }
      else {
	 x[j] =  sp_ll_red_31(0, sum1, sum0, p, ll_red_struct);
	 x[j+1] =  sp_ll_red_31(0, sum1_1, sum0_1, p, ll_red_struct);
	 x[j+2] =  sp_ll_red_31(0, sum1_2, sum0_2, p, ll_red_struct);
	 x[j+3] =  sp_ll_red_31(0, sum1_3, sum0_3, p, ll_red_struct);
      }


      b += 4*INV_BLK_SZ;
   }
}
#else

static
void muladd1_by_32_full(long *x, const long *a, const long *b, 
                        long p, sp_ll_reduce_struct ll_red_struct)
{
   NTL_ULL_TYPE res_vec[INV_BLK_SZ];

   for (long j = 0; j < INV_BLK_SZ; j++) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);

      sum += NTL_MUL_ULL(a[0], b[0]);
      sum += NTL_MUL_ULL(a[1], b[1]);
      sum += NTL_MUL_ULL(a[2], b[2]);
      sum += NTL_MUL_ULL(a[3], b[3]);
      sum += NTL_MUL_ULL(a[4], b[4]);
      sum += NTL_MUL_ULL(a[5], b[5]);
      sum += NTL_MUL_ULL(a[6], b[6]);
      sum += NTL_MUL_ULL(a[7], b[7]);
      sum += NTL_MUL_ULL(a[8], b[8]);
      sum += NTL_MUL_ULL(a[9], b[9]);
      sum += NTL_MUL_ULL(a[10], b[10]);
      sum += NTL_MUL_ULL(a[11], b[11]);
      sum += NTL_MUL_ULL(a[12], b[12]);
      sum += NTL_MUL_ULL(a[13], b[13]);
      sum += NTL_MUL_ULL(a[14], b[14]);
      sum += NTL_MUL_ULL(a[15], b[15]);
      sum += NTL_MUL_ULL(a[16], b[16]);
      sum += NTL_MUL_ULL(a[17], b[17]);
      sum += NTL_MUL_ULL(a[18], b[18]);
      sum += NTL_MUL_ULL(a[19], b[19]);
      sum += NTL_MUL_ULL(a[20], b[20]);
      sum += NTL_MUL_ULL(a[21], b[21]);
      sum += NTL_MUL_ULL(a[22], b[22]);
      sum += NTL_MUL_ULL(a[23], b[23]);
      sum += NTL_MUL_ULL(a[24], b[24]);
      sum += NTL_MUL_ULL(a[25], b[25]);
      sum += NTL_MUL_ULL(a[26], b[26]);
      sum += NTL_MUL_ULL(a[27], b[27]);
      sum += NTL_MUL_ULL(a[28], b[28]);
      sum += NTL_MUL_ULL(a[29], b[29]);
      sum += NTL_MUL_ULL(a[30], b[30]);
      sum += NTL_MUL_ULL(a[31], b[31]);

      res_vec[j] = sum;


      b += INV_BLK_SZ;
   }

#if 0
   if (ll_red_struct.nbits == NTL_SP_NBITS) {
      for (long j = 0; j < INV_BLK_SZ; j++)
	 x[j] = sp_ll_red_31_normalized(0, res_vec[j] >> NTL_BITS_PER_LONG, res_vec[j], p, ll_red_struct);

   }
   else {
      for (long j = 0; j < INV_BLK_SZ; j++)
	 x[j] = sp_ll_red_31(0, res_vec[j] >> NTL_BITS_PER_LONG, res_vec[j], p, ll_red_struct);
   }
#else
#define ONE_STEP_redn(j) x[j] = sp_ll_red_31_normalized(0, res_vec[j] >> NTL_BITS_PER_LONG, res_vec[j], p, ll_red_struct)
#define ONE_STEP_red(j) x[j] = sp_ll_red_31(0, res_vec[j] >> NTL_BITS_PER_LONG, res_vec[j], p, ll_red_struct)
   if (ll_red_struct.nbits == NTL_SP_NBITS) {

      ONE_STEP_redn(0);
      ONE_STEP_redn(1);
      ONE_STEP_redn(2);
      ONE_STEP_redn(3);
      ONE_STEP_redn(4);
      ONE_STEP_redn(5);
      ONE_STEP_redn(6);
      ONE_STEP_redn(7);
      ONE_STEP_redn(8);
      ONE_STEP_redn(9);
      ONE_STEP_redn(10);
      ONE_STEP_redn(11);
      ONE_STEP_redn(12);
      ONE_STEP_redn(13);
      ONE_STEP_redn(14);
      ONE_STEP_redn(15);
      ONE_STEP_redn(16);
      ONE_STEP_redn(17);
      ONE_STEP_redn(18);
      ONE_STEP_redn(19);
      ONE_STEP_redn(20);
      ONE_STEP_redn(21);
      ONE_STEP_redn(22);
      ONE_STEP_redn(23);
      ONE_STEP_redn(24);
      ONE_STEP_redn(25);
      ONE_STEP_redn(26);
      ONE_STEP_redn(27);
      ONE_STEP_redn(28);
      ONE_STEP_redn(29);
      ONE_STEP_redn(30);
      ONE_STEP_redn(31);

   }
   else {
      ONE_STEP_red(0);
      ONE_STEP_red(1);
      ONE_STEP_red(2);
      ONE_STEP_red(3);
      ONE_STEP_red(4);
      ONE_STEP_red(5);
      ONE_STEP_red(6);
      ONE_STEP_red(7);
      ONE_STEP_red(8);
      ONE_STEP_red(9);
      ONE_STEP_red(10);
      ONE_STEP_red(11);
      ONE_STEP_red(12);
      ONE_STEP_red(13);
      ONE_STEP_red(14);
      ONE_STEP_red(15);
      ONE_STEP_red(16);
      ONE_STEP_red(17);
      ONE_STEP_red(18);
      ONE_STEP_red(19);
      ONE_STEP_red(20);
      ONE_STEP_red(21);
      ONE_STEP_red(22);
      ONE_STEP_red(23);
      ONE_STEP_red(24);
      ONE_STEP_red(25);
      ONE_STEP_red(26);
      ONE_STEP_red(27);
      ONE_STEP_red(28);
      ONE_STEP_red(29);
      ONE_STEP_red(30);
      ONE_STEP_red(31);
   }
#endif
}



#endif

#else

 
static
void muladd1_by_32(long *x, const long *a, const long *b, 
                   long n, long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);

      long i = 0;
      for (; i < n-16; i++)
	 sum += NTL_MUL_ULL(a[i], b[i]);

      NTL_ULL_TYPE acc21 = (unsigned long) (sum >> NTL_BITS_PER_LONG);
      unsigned long acc0 = (unsigned long) sum;
      sum = 0;

      for (; i < n; i++)
	 sum += NTL_MUL_ULL(a[i], b[i]);

      sum += acc0;
      acc0 = sum;
      acc21 += (unsigned long) (sum >> NTL_BITS_PER_LONG);

      long res;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) 
	 res = sp_ll_red_31_normalized(acc21 >> NTL_BITS_PER_LONG, acc21, acc0, p, ll_red_struct);
      else
	 res =  sp_ll_red_31(acc21 >> NTL_BITS_PER_LONG, acc21, acc0, p, ll_red_struct);

      x[j] = res;
      b += INV_BLK_SZ;
   }
}

static
void muladd1_by_32_full(long *x, const long *a, const long *b, 
                        long p, sp_ll_reduce_struct ll_red_struct)
{
   for (long j = 0; j < INV_BLK_SZ; j++) {

      NTL_ULL_TYPE sum = cast_unsigned(x[j]);

      sum += NTL_MUL_ULL(a[0], b[0]);
      sum += NTL_MUL_ULL(a[1], b[1]);
      sum += NTL_MUL_ULL(a[2], b[2]);
      sum += NTL_MUL_ULL(a[3], b[3]);
      sum += NTL_MUL_ULL(a[4], b[4]);
      sum += NTL_MUL_ULL(a[5], b[5]);
      sum += NTL_MUL_ULL(a[6], b[6]);
      sum += NTL_MUL_ULL(a[7], b[7]);
      sum += NTL_MUL_ULL(a[8], b[8]);
      sum += NTL_MUL_ULL(a[9], b[9]);
      sum += NTL_MUL_ULL(a[10], b[10]);
      sum += NTL_MUL_ULL(a[11], b[11]);
      sum += NTL_MUL_ULL(a[12], b[12]);
      sum += NTL_MUL_ULL(a[13], b[13]);
      sum += NTL_MUL_ULL(a[14], b[14]);
      sum += NTL_MUL_ULL(a[15], b[15]);

      NTL_ULL_TYPE acc21 = (unsigned long) (sum >> NTL_BITS_PER_LONG);
      unsigned long acc0 = (unsigned long) sum;
      sum = 0;

      sum += NTL_MUL_ULL(a[16], b[16]);
      sum += NTL_MUL_ULL(a[17], b[17]);
      sum += NTL_MUL_ULL(a[18], b[18]);
      sum += NTL_MUL_ULL(a[19], b[19]);
      sum += NTL_MUL_ULL(a[20], b[20]);
      sum += NTL_MUL_ULL(a[21], b[21]);
      sum += NTL_MUL_ULL(a[22], b[22]);
      sum += NTL_MUL_ULL(a[23], b[23]);
      sum += NTL_MUL_ULL(a[24], b[24]);
      sum += NTL_MUL_ULL(a[25], b[25]);
      sum += NTL_MUL_ULL(a[26], b[26]);
      sum += NTL_MUL_ULL(a[27], b[27]);
      sum += NTL_MUL_ULL(a[28], b[28]);
      sum += NTL_MUL_ULL(a[29], b[29]);
      sum += NTL_MUL_ULL(a[30], b[30]);
      sum += NTL_MUL_ULL(a[31], b[31]);

      sum += acc0;
      acc0 = sum;
      acc21 += (unsigned long) (sum >> NTL_BITS_PER_LONG);

      long res;
      
      if (ll_red_struct.nbits == NTL_SP_NBITS) 
	 res = sp_ll_red_31_normalized(acc21 >> NTL_BITS_PER_LONG, acc21, acc0, p, ll_red_struct);
      else
	 res =  sp_ll_red_31(acc21 >> NTL_BITS_PER_LONG, acc21, acc0, p, ll_red_struct);

      x[j] = res;
      b += INV_BLK_SZ;
   }
}



#endif



#endif



static
inline void BlockMul(long * NTL_RESTRICT x, long * NTL_RESTRICT y, 
                     long c, long n, long p, mulmod_t pinv)
{
   mulmod_precon_t cpinv = PrepMulModPrecon(c, p, pinv);
   for (long i = 0; i < n; i++) {
      long t = MulModPrecon(y[i], c, p, cpinv);
      x[i] = AddMod(x[i], t, p);
   }
}


// ******************************************************************
//
// General matrix multiplication code
//
// ******************************************************************





static
void basic_mul(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, n, first, last) {

      for (long i = first; i < last; i++) {
         long j, k;
         const zz_p* ap = A[i].elts();
   
         zz_p *xp = X[i].elts();
         for (j = 0; j < m; j++) xp[j].LoopHole() = 0;
   
         for (k = 0;  k < l; k++) {   
            long aa = rep(ap[k]);
            if (aa != 0) {
               const zz_p* bp = B[k].elts();
               long T1;
               mulmod_precon_t aapinv = PrepMulModPrecon(aa, p, pinv);
   
               for (j = 0; j < m; j++) {
     	          T1 = MulModPrecon(rep(bp[j]), aa, p, aapinv);
     	          xp[j].LoopHole() = AddMod(rep(xp[j]), T1, p);
               } 
            }
         }
      }

   } NTL_GEXEC_RANGE_END
}  




#ifdef NTL_HAVE_LL_TYPE

static
void alt_mul_L(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   long p = zz_p::modulus();
   sp_reduce_struct red_struct = zz_p::red_struct();

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, m, first, last) {

      Vec<long> B_col;
      B_col.SetLength(l);
      long *bp = B_col.elts();

      long i, j, k;

      for (j = first; j < last; j++) {
         for (k = 0; k < l; k++) bp[k] = rep(B[k][j]);
   
         for (i = 0; i < n; i++) {
            const zz_p *ap = A[i].elts();
            X[i][j].LoopHole() = InnerProd_L(bp, ap, l, p, red_struct);
         }
      }

   } NTL_GEXEC_RANGE_END
}  


static
void alt_mul_LL(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   long p = zz_p::modulus();
   sp_ll_reduce_struct ll_red_struct = zz_p::ll_red_struct();

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, m, first, last) {

      Vec<long> B_col;
      B_col.SetLength(l);
      long *bp = B_col.elts();

      long i, j, k;

      for (j = first; j < last; j++) {
         for (k = 0; k < l; k++) bp[k] = rep(B[k][j]);
   
         for (i = 0; i < n; i++) {
            const zz_p *ap = A[i].elts();
            X[i][j].LoopHole() = InnerProd_LL(bp, ap, l, p, ll_red_struct);
         }
      }

   } NTL_GEXEC_RANGE_END
}  


#ifdef NTL_HAVE_AVX

static
void blk_mul_DD(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  

   long p = zz_p::modulus();
   sp_reduce_struct red_struct = zz_p::red_struct();

   Vec< Vec<double> > A_buf;
   Vec<double *> abufp;
   long npanels = (l+INV_BLK_SZ-1)/INV_BLK_SZ;
   A_buf.SetLength(npanels);
   abufp.SetLength(npanels);

   for (long kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
      long k_max = min(kk+INV_BLK_SZ, l);

      A_buf[panel].SetLength(n * INV_BLK_SZ);
      double *abp = A_buf[panel].elts();
      abufp[panel] = abp;

      for (long i = 0; i < n; i++, abp += INV_BLK_SZ) {
         const zz_p *ap1 = A[i].elts();
         for (long k = kk; k < k_max; k++) {
            abp[k-kk] = rep(ap1[k]);
         }
         for (long k = k_max; k < kk+INV_BLK_SZ; k++) {
            abp[k-kk] = 0;
         }
      }
   }

   long nxpanels = (m+INV_BLK_SZ-1)/INV_BLK_SZ;

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, nxpanels, first, last) 
   NTL_IMPORT(n)
   NTL_IMPORT(l)
   NTL_IMPORT(m)
   NTL_IMPORT(p)
   NTL_IMPORT(red_struct)

   AlignedArray<double>::AVX B_rec;
   B_rec.SetLength(INV_BLK_SZ*INV_BLK_SZ);
   double *brec = B_rec.get();

   AlignedArray<double>::AVX X_buf;
   X_buf.SetLength(n*INV_BLK_SZ);
   double *xbp = X_buf.get();

   long jj, kk;
   long i, j, k;
   long panel;
   long xpanel;

   for (xpanel = first, jj = first*INV_BLK_SZ; xpanel < last; 
	xpanel++, jj += INV_BLK_SZ) {

      long j_max = min(jj+INV_BLK_SZ, m);

      for (i = 0; i < n*INV_BLK_SZ; i++) xbp[i] = 0;

      long red_trigger = (MAX_DBL_INT-(p-1))/((p-1)*(p-1));
      long red_count = red_trigger;

      for (kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
	 long k_max = min(kk+INV_BLK_SZ, l);

	 for (k = kk; k < k_max; k++) {
	    const zz_p *bp = B[k].elts();
	    for (j = jj; j < j_max; j++) 
	       brec[(k-kk)*INV_BLK_SZ+(j-jj)] = rep(bp[j]);
	    for (j = j_max; j < jj+INV_BLK_SZ; j++) 
	       brec[(k-kk)*INV_BLK_SZ+(j-jj)] = 0;
	 }


	 if (red_count-INV_BLK_SZ < 0) {
	    red_count = red_trigger;
	    for (i = 0; i < n*INV_BLK_SZ; i++) 
	       xbp[i] = rem((unsigned long)(long)xbp[i], p, red_struct);
	 }

	 red_count = red_count-INV_BLK_SZ;

	 const double *abp = abufp[panel];

	 for (i = 0; i < n; i++) 
	    muladd1_by_32(xbp + i*INV_BLK_SZ, abp + i*INV_BLK_SZ, brec, k_max-kk);
      }

      
      for (i = 0; i < n; i++) {
	 zz_p *xp = X[i].elts();
	 for (j = jj; j < j_max; j++)
	    xp[j].LoopHole() = 
	      rem((unsigned long)(long)xbp[i*INV_BLK_SZ + (j-jj)], p, red_struct);
      }
   }

   NTL_GEXEC_RANGE_END
}  

#endif


static
void blk_mul_LL(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  

   long p = zz_p::modulus();
   sp_ll_reduce_struct ll_red_struct = zz_p::ll_red_struct();

   Vec< Vec<long> > A_buf;
   Vec<long *> abufp;
   long npanels = (l+INV_BLK_SZ-1)/INV_BLK_SZ;
   A_buf.SetLength(npanels);
   abufp.SetLength(npanels);

   for (long kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
      long k_max = min(kk+INV_BLK_SZ, l);

      A_buf[panel].SetLength(n * INV_BLK_SZ);
      long *abp = A_buf[panel].elts();
      abufp[panel] = abp;

      for (long i = 0; i < n; i++, abp += INV_BLK_SZ) {
         const zz_p *ap1 = A[i].elts();
         for (long k = kk; k < k_max; k++) {
            abp[k-kk] = rep(ap1[k]);
         }
         for (long k = k_max; k < kk+INV_BLK_SZ; k++) {
            abp[k-kk] = 0;
         }
      }
   }

   long nxpanels = (m+INV_BLK_SZ-1)/INV_BLK_SZ;

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, nxpanels, first, last) 
   NTL_IMPORT(n)
   NTL_IMPORT(l)
   NTL_IMPORT(m)
   NTL_IMPORT(p)
   NTL_IMPORT(ll_red_struct)

   UniqueArray<long> B_rec;
   B_rec.SetLength(INV_BLK_SZ*INV_BLK_SZ);
   long *brec = B_rec.get();

   UniqueArray<long> X_buf;
   X_buf.SetLength(n*INV_BLK_SZ);
   long *xbp = X_buf.get();

   long jj, kk;
   long i, j, k;
   long panel;
   long xpanel;

   for (xpanel = first, jj = first*INV_BLK_SZ; xpanel < last; 
	xpanel++, jj += INV_BLK_SZ) {

      long j_max = min(jj+INV_BLK_SZ, m);

      for (i = 0; i < n*INV_BLK_SZ; i++) xbp[i] = 0;

      for (kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
	 long k_max = min(kk+INV_BLK_SZ, l);

         // fill brec, transposed

	 for (k = kk; k < k_max; k++) {
	    const zz_p *bp = B[k].elts();
	    for (j = jj; j < j_max; j++) 
	       brec[(k-kk)+(j-jj)*INV_BLK_SZ] = rep(bp[j]);
	    for (j = j_max; j < jj+INV_BLK_SZ; j++) 
	       brec[(k-kk)+(j-jj)*INV_BLK_SZ] = 0;
	 }

	 const long *abp = abufp[panel];

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32_full(xbp + i*INV_BLK_SZ, abp + i*INV_BLK_SZ, brec, 
                                  p, ll_red_struct);
         }
         else {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32(xbp + i*INV_BLK_SZ, abp + i*INV_BLK_SZ, brec, k_max-kk,
                                  p, ll_red_struct);
         }
      }

      
      for (i = 0; i < n; i++) {
	 zz_p *xp = X[i].elts();
	 for (j = jj; j < j_max; j++)
	    xp[j].LoopHole() =  xbp[i*INV_BLK_SZ + (j-jj)];
      }
   }

   NTL_GEXEC_RANGE_END
}  


static
void blk_mul_L(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  

   long p = zz_p::modulus();
   sp_reduce_struct red_struct = zz_p::red_struct();

   Vec< Vec<unsigned long> > A_buf;
   Vec<unsigned long *> abufp;
   long npanels = (l+INV_BLK_SZ-1)/INV_BLK_SZ;
   A_buf.SetLength(npanels);
   abufp.SetLength(npanels);

   for (long kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
      long k_max = min(kk+INV_BLK_SZ, l);

      A_buf[panel].SetLength(n * INV_BLK_SZ);
      unsigned long *abp = A_buf[panel].elts();
      abufp[panel] = abp;

      for (long i = 0; i < n; i++, abp += INV_BLK_SZ) {
         const zz_p *ap1 = A[i].elts();
         for (long k = kk; k < k_max; k++) {
            abp[k-kk] = rep(ap1[k]);
         }
         for (long k = k_max; k < kk+INV_BLK_SZ; k++) {
            abp[k-kk] = 0;
         }
      }
   }

   long nxpanels = (m+INV_BLK_SZ-1)/INV_BLK_SZ;

   const bool seq = double(n)*double(l)*double(m) < 20000;

   NTL_GEXEC_RANGE(seq, nxpanels, first, last) 
   NTL_IMPORT(n)
   NTL_IMPORT(l)
   NTL_IMPORT(m)
   NTL_IMPORT(p)
   NTL_IMPORT(red_struct)

   UniqueArray<unsigned long> B_rec;
   B_rec.SetLength(INV_BLK_SZ*INV_BLK_SZ);
   unsigned long *brec = B_rec.get();

   UniqueArray<unsigned long> X_buf;
   X_buf.SetLength(n*INV_BLK_SZ);
   unsigned long *xbp = X_buf.get();

   long jj, kk;
   long i, j, k;
   long panel;
   long xpanel;

   for (xpanel = first, jj = first*INV_BLK_SZ; xpanel < last; 
	xpanel++, jj += INV_BLK_SZ) {

      long j_max = min(jj+INV_BLK_SZ, m);

      for (i = 0; i < n*INV_BLK_SZ; i++) xbp[i] = 0;

      unsigned long ured_trigger = 
         (~(0UL)-cast_unsigned(p-1))/(cast_unsigned(p-1)*cast_unsigned(p-1));
      // NOTE: corner case at p == 2: need unsigned long to prevent overflow

      long red_trigger = min(cast_unsigned(NTL_MAX_LONG), ured_trigger);

      long red_count = red_trigger;

      for (kk = 0, panel = 0; kk < l; kk += INV_BLK_SZ, panel++) {
	 long k_max = min(kk+INV_BLK_SZ, l);

         // fill brec, transposed

	 for (k = kk; k < k_max; k++) {
	    const zz_p *bp = B[k].elts();
	    for (j = jj; j < j_max; j++) 
	       brec[(k-kk)+(j-jj)*INV_BLK_SZ] = rep(bp[j]);
	    for (j = j_max; j < jj+INV_BLK_SZ; j++) 
	       brec[(k-kk)+(j-jj)*INV_BLK_SZ] = 0;
	 }

	 if (red_count-INV_BLK_SZ < 0) {
	    red_count = red_trigger;
	    for (i = 0; i < n*INV_BLK_SZ; i++) 
	       xbp[i] = rem(xbp[i], p, red_struct);
	 }

	 red_count = red_count-INV_BLK_SZ;

	 const unsigned long *abp = abufp[panel];

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32_full(xbp + i*INV_BLK_SZ, abp + i*INV_BLK_SZ, brec);
         }
         else {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32(xbp + i*INV_BLK_SZ, abp + i*INV_BLK_SZ, brec, k_max-kk);
         }
      }

      
      for (i = 0; i < n; i++) {
	 zz_p *xp = X[i].elts();
	 for (j = jj; j < j_max; j++)
	    xp[j].LoopHole() = 
	      rem(xbp[i*INV_BLK_SZ + (j-jj)], p, red_struct);
      }
   }

   NTL_GEXEC_RANGE_END
}  


#endif





static
void mul_aux(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)
{
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   if (l != B.NumRows())  
      LogicError("matrix mul: dimension mismatch");  

   X.SetDims(n, m); 

   if (n == 0 || l == 0 || m == 0) {
      clear(X);
      return;
   }


#ifndef NTL_HAVE_LL_TYPE

   basic_mul(X, A, B);

#else

   if (l < 32) {
      //cerr << "basic_mul\n";
      basic_mul(X, A, B);
      return;
   }

   long p = zz_p::modulus();
   
   if (n/INV_BLK_SZ < 4 || l/INV_BLK_SZ < 4 || m/INV_BLK_SZ < 4) {
      if (cast_unsigned(l) <= (~(0UL))/cast_unsigned(p-1) &&
          cast_unsigned(l)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1)) {
         //cerr << "alt_mul_L\n";
         alt_mul_L(X, A, B);
      }
      else {
         //cerr << "alt_mul_LL\n";
         alt_mul_LL(X, A, B);
      }

      return;
   }

   {
      if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("number too big");
      if (NTL_OVERFLOW(l, INV_BLK_SZ, 0)) ResourceError("number too big");
      if (NTL_OVERFLOW(m, INV_BLK_SZ, 0)) ResourceError("number too big");

      long V = INV_BLK_SZ*4;

#ifdef NTL_HAVE_AVX
      if (p-1 <= MAX_DBL_INT &&
          V <= (MAX_DBL_INT-(p-1))/(p-1) &&
          V*(p-1) <= (MAX_DBL_INT-(p-1))/(p-1)) {

         // cerr << "block_mul_DD\n";
         blk_mul_DD(X, A, B);
      }
      else 
#endif
           if (cast_unsigned(V) <= (~(0UL)-cast_unsigned(p-1))/cast_unsigned(p-1) &&
               cast_unsigned(V)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

         //cerr << "blk_mul_L\n";
         blk_mul_L(X, A, B);

      }
      else {
  
         //cerr << "blk_mul_LL\n";
         blk_mul_LL(X, A, B);
      }
   }

#endif


}

void mul(mat_zz_p& X, const mat_zz_p& A, const mat_zz_p& B)
{
   if (&X == &A || &X == &B) {  
      mat_zz_p tmp;  
      mul_aux(tmp, A, B);  
      X = tmp;  
   }  
   else  
      mul_aux(X, A, B);  
}


// ******************************************************************
//
// Matrix inversion code
//
// ******************************************************************

static
long relaxed_InvModStatus(long& x, long a, long n, bool relax)
{
   if (relax) {
      return InvModStatus(x, a, n);
   }
   else {
      x = InvMod(a, n);
      return 0;
   }
}

static
void basic_inv(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }


   Mat<long> M;
   conv(M, A);
   // scratch space

   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();

   bool seq = n < 150;

   bool pivoting = false;

   for (long k = 0; k < n; k++) {
      long pos = -1;
      long pivot_inv;
      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         long pivot = M[i][k];
         if (M[i][k] != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, M[k][k], p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            long * NTL_RESTRICT y = &M[k][0];
            for (long j = 0; j < n; j++) 
               y[j] = MulModPrecon(y[j], t1, p, t1pinv);

            y[k] = pivot_inv;
         }



         NTL_GEXEC_RANGE(seq, n, first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         long * NTL_RESTRICT y = &M[k][0]; 
         for (long i = first; i < last; i++) {
            if (i == k) continue; // skip row k

            long * NTL_RESTRICT x = &M[i][0]; 
            long t1 = x[k];
            t1 = NegateMod(t1, p);
            x[k] = 0;
            if (t1 == 0) continue;

            // add t1 * row k to row i
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 

            for (long j = 0; j < n; j++) {
               long t2 = MulModPrecon(y[j], t1, p, t1pinv);
               x[j] = AddMod(x[j], t2, p);
            }
         }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }

   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long i = 0; i < n; i++) {
	 long * NTL_RESTRICT x = &M[i][0]; 

	 for (long k = n-1; k >= 0; k--) {
	    long pos = P[k];
	    if (pos != k) _ntl_swap(x[pos], x[k]);
	 }
      }
   }
   
   X.SetDims(n, n);
   for (long i = 0; i < n; i++)
      for (long j = 0; j < n; j++)
         X[i][j].LoopHole() = M[i][j];

   d.LoopHole() = det;
}



#ifdef NTL_HAVE_LL_TYPE



static
void alt_inv_L(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }


   Mat<unsigned long> M;
   conv(M, A);
   // scractch space

   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();

   

   bool seq = n < 150;

   bool pivoting = false;

   unsigned long ured_trigger = 
      (~(0UL)-cast_unsigned(p-1))/(cast_unsigned(p-1)*cast_unsigned(p-1));
   // NOTE: corner case at p == 2: need unsigned long to prevent overflow

   long red_trigger = min(cast_unsigned(NTL_MAX_LONG), ured_trigger);

   long red_count = red_trigger;


   for (long k = 0; k < n; k++) {
      bool cleanup = false;

      if (red_count-1 < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-1;

      long pos = -1;
      long pivot;
      long pivot_inv;

      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         pivot = rem(M[i][k], p, red_struct);
         if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); // t1*pinv;
            unsigned long * NTL_RESTRICT y = &M[k][0];
            for (long j = 0; j < n; j++) {
               long t2 = rem(y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k] = pivot_inv;
         }


         NTL_GEXEC_RANGE(seq, n, first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         NTL_IMPORT(red_struct)
         unsigned long * NTL_RESTRICT y = &M[k][0]; 
         if (cleanup) {
	    for (long i = first; i < last; i++) {
               if (i == k) continue;
               // skip row k: the data won't change, but it
               // technically is a race condition in a multi-theaded
               // execution, and it would violate the "restrict"
               // contract

	       unsigned long * NTL_RESTRICT x = &M[i][0]; 
	       for (long j = 0; j < n; j++) {
		  x[j] = rem(x[j], p, red_struct);
	       }
            }
         }


	 for (long i = first; i < last; i++) {
            if (i == k) continue; // skip row k

	    unsigned long * NTL_RESTRICT x = &M[i][0]; 
	    long t1 = rem(x[k], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    unsigned long ut1 = t1;
	    long j;
	    for (j = 0; j <= n-4; j+=4) {
	       unsigned long xj0 = x[j+0] + DO_MUL(y[j+0], ut1);
	       unsigned long xj1 = x[j+1] + DO_MUL(y[j+1], ut1);
	       unsigned long xj2 = x[j+2] + DO_MUL(y[j+2], ut1);
	       unsigned long xj3 = x[j+3] + DO_MUL(y[j+3], ut1);
	       x[j+0] = xj0;
	       x[j+1] = xj1;
	       x[j+2] = xj2;
	       x[j+3] = xj3;
	    }
	    for (; j < n; j++) {
	       x[j] += DO_MUL(y[j], ut1);
	    }
	 }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }

   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long i = 0; i < n; i++) {
	 unsigned long * NTL_RESTRICT x = &M[i][0]; 

	 for (long k = n-1; k >= 0; k--) {
	    long pos = P[k];
	    if (pos != k) _ntl_swap(x[pos], x[k]);
	 }
      }
   }

   X.SetDims(n, n);
   for (long i = 0; i < n; i++)
      for (long j = 0; j < n; j++)
         X[i][j].LoopHole() = rem(M[i][j], p, red_struct);

   d.LoopHole() = det;
}





#ifdef NTL_HAVE_AVX

static
void alt_inv_DD(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }

   Vec< AlignedArray<double>::AVX > M;
   M.SetLength(n);
   for (long i = 0; i < n; i++) M[i].SetLength(n);

   for (long i = 0; i < n; i++) {
      for (long j = 0; j < n; j++) 
         M[i][j] = rep(A[i][j]);
   }


   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();

   

   bool seq = n < 150;

   bool pivoting = false;

   long red_trigger = (MAX_DBL_INT-(p-1))/((p-1)*(p-1));
   long red_count = red_trigger;

   for (long k = 0; k < n; k++) {
      bool cleanup = false;

      if (red_count-1 < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-1;

      long pos = -1;
      long pivot;
      long pivot_inv;



      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         pivot = rem((unsigned long)(long)M[i][k], p, red_struct);
         if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); // t1*pinv;
            double * NTL_RESTRICT y = &M[k][0];
            for (long j = 0; j < n; j++) {
               long t2 = rem((unsigned long)(long)y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k] = pivot_inv;
         }


         NTL_GEXEC_RANGE(seq, n, first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         NTL_IMPORT(red_struct)
         double * NTL_RESTRICT y = &M[k][0]; 
         if (cleanup) {
	    for (long i = first; i < last; i++) {
               if (i == k) continue;
               // skip row k: the data won't change, but it
               // technically is a race condition in a multi-theaded
               // execution, and it would violate the "restrict"
               // contract

	       double * NTL_RESTRICT x = &M[i][0]; 
	       for (long j = 0; j < n; j++) {
		  x[j] = rem((unsigned long)(long)x[j], p, red_struct);
	       }
            }
         }


	 for (long i = first; i < last; i++) {
            if (i == k) continue; // skip row k

	    double * NTL_RESTRICT x = &M[i][0]; 
	    long t1 = rem((unsigned long)(long)x[k], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    double ut1 = t1;
            BlockMul1(x, y, ut1, n);
	 }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }


   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long i = 0; i < n; i++) {
	 double * NTL_RESTRICT x = &M[i][0]; 

	 for (long k = n-1; k >= 0; k--) {
	    long pos = P[k];
	    if (pos != k) _ntl_swap(x[pos], x[k]);
	 }
      }
   }


   X.SetDims(n, n);
   for (long i = 0; i < n; i++)
      for (long j = 0; j < n; j++)
         X[i][j].LoopHole() = rem((unsigned long)(long)M[i][j], p, red_struct);

   d.LoopHole() = det;
}

#endif





#ifdef NTL_HAVE_AVX

static
void blk_inv_DD(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too large");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;
   

   Vec< AlignedArray<double>::AVX > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      double *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }

   // copy A into panels
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      double *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         const zz_p *ap = A[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            panelp[j-jj] = rep(ap[j-jj]);
      }
   }
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();


   bool seq = n < 150;

   bool pivoting = false;

   long red_trigger = (MAX_DBL_INT-(p-1))/((p-1)*(p-1));
   long red_count = red_trigger;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      bool cleanup = false;

      if (red_count-INV_BLK_SZ < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-INV_BLK_SZ;
      double * NTL_RESTRICT kpanelp = &M[kpanel][0];

      if (cleanup) {
         for (long r = 0; r < n*INV_BLK_SZ; r++) 
            kpanelp[r] = rem((unsigned long)(long)kpanelp[r], p, red_struct);
      }

      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = rem((unsigned long)(long)kpanelp[i*INV_BLK_SZ+(k-kk)], p, red_struct);
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         double * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            double * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               long t2 = rem((unsigned long)(long)y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;
         }

	 for (long i = 0; i < n; i++) {
            if (i == k) continue; // skip row k

	    double * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = rem((unsigned long)(long)x[k-kk], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    double ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ);
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      for (long r = 0; r < n*INV_BLK_SZ; r++) 
	 kpanelp[r] = rem((unsigned long)(long)kpanelp[r], p, red_struct);

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      NTL_GEXEC_RANGE(seq, npanels, first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      AlignedArray<double>::AVX buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      double *buf = &buf_store[0];

      for (long jpanel = first; jpanel < last; jpanel++) {
	 if (jpanel == kpanel) continue;

	 double * NTL_RESTRICT jpanelp = &M[jpanel][0];

	 if (cleanup) {
	    for (long r = 0; r < n*INV_BLK_SZ; r++) 
	       jpanelp[r] = rem((unsigned long)(long)jpanelp[r], p, red_struct);
	 }

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               double * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               double * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf

         for (long i = 0; i < (k_max-kk)*INV_BLK_SZ; i++)
            buf[i] = rem((unsigned long)(long)jpanelp[kk*INV_BLK_SZ+i], p, red_struct);

	 // jpanel += kpanel*buf

	 for (long i = 0; i < n; i++) 
            muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk);
      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long k = n-1; k >= 0; k--) {
	 long pos = P[k];
	 if (pos != k) { 
            // swap columns pos and k

            double * NTL_RESTRICT x = &M[pos / INV_BLK_SZ][pos % INV_BLK_SZ];
            double * NTL_RESTRICT y = &M[k / INV_BLK_SZ][k % INV_BLK_SZ];
            for (long i = 0; i < n; i++) {
               _ntl_swap(x[i*INV_BLK_SZ], y[i*INV_BLK_SZ]);
            }
         }
      }
   }


   // copy panels into X
   X.SetDims(n, n);
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      double *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         zz_p *xp = X[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            xp[j-jj].LoopHole() = rem((unsigned long)(long)panelp[j-jj], p, red_struct);
      }
   }

   d.LoopHole() = det;

}

#endif



static
void blk_inv_L(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too large");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;

   Vec< UniqueArray<unsigned long> > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      unsigned long *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }
   
   // copy A into panels
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      unsigned long *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         const zz_p *ap = A[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            panelp[j-jj] = rep(ap[j-jj]);
      }
   }
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();


   bool seq = n < 150;

   bool pivoting = false;

   unsigned long ured_trigger = 
      (~(0UL)-cast_unsigned(p-1))/(cast_unsigned(p-1)*cast_unsigned(p-1));
   // NOTE: corner case at p == 2: need unsigned long to prevent overflow

   long red_trigger = min(cast_unsigned(NTL_MAX_LONG), ured_trigger);

   long red_count = red_trigger;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      bool cleanup = false;

      if (red_count-INV_BLK_SZ < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-INV_BLK_SZ;
      unsigned long * NTL_RESTRICT kpanelp = &M[kpanel][0];

      if (cleanup) {
         for (long r = 0; r < n*INV_BLK_SZ; r++) 
            kpanelp[r] = rem(kpanelp[r], p, red_struct);
      }

      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = rem(kpanelp[i*INV_BLK_SZ+(k-kk)], p, red_struct);
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         unsigned long * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            unsigned long * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               long t2 = rem(y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;
         }

	 for (long i = 0; i < n; i++) {
            if (i == k) continue; // skip row k

	    unsigned long * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = rem(x[k-kk], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    unsigned long ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ);
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      for (long r = 0; r < n*INV_BLK_SZ; r++) 
	 kpanelp[r] = rem(kpanelp[r], p, red_struct);

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      NTL_GEXEC_RANGE(seq, npanels, first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      UniqueArray<unsigned long> buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      unsigned long *buf = &buf_store[0];

      for (long jpanel = first; jpanel < last; jpanel++) {
	 if (jpanel == kpanel) continue;

	 unsigned long * NTL_RESTRICT jpanelp = &M[jpanel][0];

	 if (cleanup) {
	    for (long r = 0; r < n*INV_BLK_SZ; r++) 
	       jpanelp[r] = rem(jpanelp[r], p, red_struct);
	 }

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               unsigned long * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               unsigned long * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf
         // here, we transpose it

         for (long k = kk; k < k_max; k++) 
            for (long j = 0; j < INV_BLK_SZ; j++)
               buf[j*INV_BLK_SZ + (k-kk)] = 
                  rem(jpanelp[k*INV_BLK_SZ+j], p, red_struct);

	 // jpanel += kpanel*buf

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32_full(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf);
         }
         else {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk);
         }
      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long k = n-1; k >= 0; k--) {
	 long pos = P[k];
	 if (pos != k) { 
            // swap columns pos and k

            unsigned long * NTL_RESTRICT x = &M[pos / INV_BLK_SZ][pos % INV_BLK_SZ];
            unsigned long * NTL_RESTRICT y = &M[k / INV_BLK_SZ][k % INV_BLK_SZ];
            for (long i = 0; i < n; i++) {
               _ntl_swap(x[i*INV_BLK_SZ], y[i*INV_BLK_SZ]);
            }
         }
      }
   }

   // copy panels into X
   X.SetDims(n, n);
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      unsigned long *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         zz_p *xp = X[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            xp[j-jj].LoopHole() = rem(panelp[j-jj], p, red_struct);
      }
   }

   d.LoopHole() = det;

}








static
void blk_inv_LL(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (n == 0) {
      set(d);
      X.SetDims(0, 0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too big");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;

   Vec< UniqueArray<long> > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      long *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }
   

   // copy A into panels
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      long *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         const zz_p *ap = A[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            panelp[j-jj] = rep(ap[j-jj]);
      }
   }
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_ll_reduce_struct ll_red_struct = zz_p::ll_red_struct();


   bool seq = n < 150;

   bool pivoting = false;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      long * NTL_RESTRICT kpanelp = &M[kpanel][0];


      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = kpanelp[i*INV_BLK_SZ+(k-kk)];
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         long * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            long * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               y[j] = MulModPrecon(y[j], t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;
         }

	 for (long i = 0; i < n; i++) {
            if (i == k) continue; // skip row k

	    long * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = x[k-kk];
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    long ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ, p, pinv);
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod(kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      NTL_GEXEC_RANGE(seq, npanels, first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(ll_red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      UniqueArray<long> buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      long *buf = &buf_store[0];

      for (long jpanel = first; jpanel < last; jpanel++) {
	 if (jpanel == kpanel) continue;

	 long * NTL_RESTRICT jpanelp = &M[jpanel][0];

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               long * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               long * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf
         // here, we transpose it

         for (long k = kk; k < k_max; k++) 
            for (long j = 0; j < INV_BLK_SZ; j++)
               buf[j*INV_BLK_SZ + (k-kk)] = 
                  jpanelp[k*INV_BLK_SZ+j];


	 // jpanel += kpanel*buf

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32_full(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, 
			     p, ll_red_struct);
         }
         else {
	    for (long i = 0; i < n; i++) 
	       muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk,
			     p, ll_red_struct);
         }
      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod(kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (pivoting) {
      // pivot colums, using reverse swap sequence

      for (long k = n-1; k >= 0; k--) {
	 long pos = P[k];
	 if (pos != k) { 
            // swap columns pos and k

            long * NTL_RESTRICT x = &M[pos / INV_BLK_SZ][pos % INV_BLK_SZ];
            long * NTL_RESTRICT y = &M[k / INV_BLK_SZ][k % INV_BLK_SZ];
            for (long i = 0; i < n; i++) {
               _ntl_swap(x[i*INV_BLK_SZ], y[i*INV_BLK_SZ]);
            }
         }
      }
   }

   // copy panels into X
   X.SetDims(n, n);
   for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
      long j_max = min(jj+INV_BLK_SZ, n);
      long *panelp = &M[panel][0];

      for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
         zz_p *xp = X[i].elts() + jj;

         for (long j = jj; j < j_max; j++)
            xp[j-jj].LoopHole() = panelp[j-jj];
      }
   }

   d.LoopHole() = det;

}



#endif



void relaxed_inv(zz_p& d, mat_zz_p& X, const mat_zz_p& A, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

#ifndef NTL_HAVE_LL_TYPE

   basic_inv(d, X, A, (bool) relax);

#else

   long p = zz_p::modulus();

   if (n < 16) {
      //cerr << "basic_inv\n";
      basic_inv(d, X, A, relax);
   }
   else if (n/INV_BLK_SZ < 4) {
      long V = 64;

#ifdef NTL_HAVE_AVX
      if (p-1 <= MAX_DBL_INT &&
          V <= (MAX_DBL_INT-(p-1))/(p-1) &&
          V*(p-1) <= (MAX_DBL_INT-(p-1))/(p-1)) {

         //cerr << "alt_inv_DD\n";
         alt_inv_DD(d, X, A, relax);
      }
      else 
#endif
           if (cast_unsigned(V) <= (~(0UL)-cast_unsigned(p-1))/cast_unsigned(p-1) &&
               cast_unsigned(V)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

         //cerr << "alt_inv_L\n";
         alt_inv_L(d, X, A, relax);

      }
      else {
  
         //cerr << "basic_inv\n";
         basic_inv(d, X, A, relax);
      }
   }
   else {
      long V = 4*INV_BLK_SZ;

#ifdef NTL_HAVE_AVX
      if (p-1 <= MAX_DBL_INT &&
          V <= (MAX_DBL_INT-(p-1))/(p-1) &&
          V*(p-1) <= (MAX_DBL_INT-(p-1))/(p-1)) {

         //cerr << "blk_inv_DD\n";
         blk_inv_DD(d, X, A, relax);
      }
      else 
#endif
           if (cast_unsigned(V) <= (~(0UL)-cast_unsigned(p-1))/cast_unsigned(p-1) &&
               cast_unsigned(V)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

         //cerr << "blk_inv_L\n";
         blk_inv_L(d, X, A, relax);

      }
      else {
  
         //cerr << "blk_inv_LL\n";
         blk_inv_LL(d, X, A, relax);
      }
   
   }

#endif



}



// ******************************************************************
//
// Triangularizing square matrices, with applications
// to solving linear systems and computing determinants.
// Should be about 3x faster than the matrix inverse
// algorithms.
//
// ******************************************************************


static
void basic_tri(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   // adjust
   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   // adjust
   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   // adjust
   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      // adjust
      if (xp) xp->SetLength(0);
      return;
   }

   // adjust (several lines)
   // scratch space
   Mat<long> M;
   if (!trans) {
      conv(M, A);
   }
   else {
      M.SetDims(n, n);
      for (long i = 0; i < n; i++)
         for (long j = 0; j < n; j++)
            M[i][j] = rep(A[j][i]); 
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);
   // end adjust


   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();

   // adjust // bool seq = n < 150;

   bool pivoting = false;

   for (long k = 0; k < n; k++) {
      long pos = -1;
      long pivot_inv;
      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         long pivot = M[i][k];
         if (M[i][k] != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            // adjust
            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, M[k][k], p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            long * NTL_RESTRICT y = &M[k][0];
            // adjust
            for (long j = k+1; j < n; j++) 
               y[j] = MulModPrecon(y[j], t1, p, t1pinv);

            // adjust // y[k] = pivot_inv;

            // adjust
            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }



         // adjust
         bool seq = n-(k+1) < 150;
         NTL_GEXEC_RANGE(seq, n-(k+1), first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         long * NTL_RESTRICT y = &M[k][0]; 

         // adjust
         for (long ii = first; ii < last; ii++) {
            long i = ii + k+1;

            long * NTL_RESTRICT x = &M[i][0]; 
            long t1 = x[k];
            t1 = NegateMod(t1, p);
            // adjust // x[k] = 0;
            if (t1 == 0) continue;

            // add t1 * row k to row i
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 

            // adjust
            for (long j = k+1; j < n; j++) {
               long t2 = MulModPrecon(y[j], t1, p, t1pinv);
               x[j] = AddMod(x[j], t2, p);
            }

            // adjust
            if (bp)
            {
               long t2 = MulModPrecon(bv[k], t1, p, t1pinv);
               bv[i] = AddMod(bv[i], t2, p);
            }
         }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }


   // adjust
   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
	 for (long j = i+1; j < n; j++) {
            long t2 = MulMod(rep(X[j]), M[i][j], p);
            t1 = AddMod(t1, t2, p);
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;
}




#ifdef NTL_HAVE_LL_TYPE



static
void alt_tri_L(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   // adjust
   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   // adjust
   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      if (xp) xp->SetLength(0);
      return;
   }


   // scratch space
   Mat<unsigned long> M;
   if (!trans) {
      conv(M, A);
   }
   else {
      M.SetDims(n, n);
      for (long i = 0; i < n; i++)
         for (long j = 0; j < n; j++)
            M[i][j] = rep(A[j][i]); 
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);

   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();

   

   bool pivoting = false;

   unsigned long ured_trigger = 
      (~(0UL)-cast_unsigned(p-1))/(cast_unsigned(p-1)*cast_unsigned(p-1));
   // NOTE: corner case at p == 2: need unsigned long to prevent overflow

   long red_trigger = min(cast_unsigned(NTL_MAX_LONG), ured_trigger);

   long red_count = red_trigger;


   for (long k = 0; k < n; k++) {
      bool cleanup = false;

      if (red_count-1 < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-1;

      long pos = -1;
      long pivot;
      long pivot_inv;

      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         pivot = rem(M[i][k], p, red_struct);
         if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); // t1*pinv;
            unsigned long * NTL_RESTRICT y = &M[k][0];
            for (long j = k+1; j < n; j++) {
               long t2 = rem(y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }


    
         bool seq = n-(k+1) < 150;
         NTL_GEXEC_RANGE(seq, n-(k+1), first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         NTL_IMPORT(red_struct)
         unsigned long * NTL_RESTRICT y = &M[k][0]; 
         if (cleanup) {
	    for (long ii = first; ii < last; ii++) {
               long i = ii + k+1;

	       unsigned long * NTL_RESTRICT x = &M[i][0]; 
	       for (long j = k+1; j < n; j++) {
		  x[j] = rem(x[j], p, red_struct);
	       }
            }
         }


	 for (long ii = first; ii < last; ii++) {
            long i = ii + k+1;

	    unsigned long * NTL_RESTRICT x = &M[i][0]; 
	    long t1 = rem(x[k], p, red_struct);
	    t1 = NegateMod(t1, p);
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    unsigned long ut1 = t1;
	    long j;
	    for (j = k+1; j <= n-4; j+=4) {
	       unsigned long xj0 = x[j+0] + DO_MUL(y[j+0], ut1);
	       unsigned long xj1 = x[j+1] + DO_MUL(y[j+1], ut1);
	       unsigned long xj2 = x[j+2] + DO_MUL(y[j+2], ut1);
	       unsigned long xj3 = x[j+3] + DO_MUL(y[j+3], ut1);
	       x[j+0] = xj0;
	       x[j+1] = xj1;
	       x[j+2] = xj2;
	       x[j+3] = xj3;
	    }
	    for (; j < n; j++) {
	       x[j] += DO_MUL(y[j], ut1);
	    }

            if (bp)
            {
               long t2 = MulMod(bv[k], t1, p);
               bv[i] = AddMod(bv[i], t2, p);
            }
	 }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }



   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
	 for (long j = i+1; j < n; j++) {
            long t0 = rem(M[i][j], p, red_struct);
            long t2 = MulMod(rep(X[j]), t0, p);
            t1 = AddMod(t1, t2, p);
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;
}




#ifdef NTL_HAVE_AVX

static
void alt_tri_DD(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   // adjust
   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   // adjust
   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      if (xp) xp->SetLength(0);
      return;
   }


   // scratch space

   Vec< AlignedArray<double>::AVX > M;
   M.SetLength(n);
   for (long i = 0; i < n; i++) M[i].SetLength(n);
   if (!trans) {
      for (long i = 0; i < n; i++)
         for (long j = 0; j < n; j++)
            M[i][j] = rep(A[i][j]); 
   }
   else {
      for (long i = 0; i < n; i++)
         for (long j = 0; j < n; j++)
            M[i][j] = rep(A[j][i]); 
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);

   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations

   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();

   

   bool pivoting = false;

   long red_trigger = (MAX_DBL_INT-(p-1))/((p-1)*(p-1));
   long red_count = red_trigger;

   for (long k = 0; k < n; k++) {
      bool cleanup = false;

      if (red_count-1 < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-1;

      long pos = -1;
      long pivot;
      long pivot_inv;

      for (long i = k; i < n; i++) {
         // NOTE: by using InvModStatus, this code will work
         // for prime-powers as well as primes
         pivot = rem((unsigned long)(long)M[i][k], p, red_struct);
         if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         if (k != pos) {
            swap(M[pos], M[k]);
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); // t1*pinv;
            double * NTL_RESTRICT y = &M[k][0];
            for (long j = k+1; j < n; j++) {
               long t2 = rem((unsigned long)(long)y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }


    
         bool seq = n-(k+1) < 150;
         NTL_GEXEC_RANGE(seq, n-(k+1), first, last)  
         NTL_IMPORT(p)
         NTL_IMPORT(n)
         NTL_IMPORT(k)
         NTL_IMPORT(red_struct)
         double * NTL_RESTRICT y = &M[k][0]; 
         if (cleanup) {
	    for (long ii = first; ii < last; ii++) {
               long i = ii + k+1;

	       double * NTL_RESTRICT x = &M[i][0]; 
	       for (long j = k+1; j < n; j++) {
		  x[j] = rem((unsigned long)(long)x[j], p, red_struct);
	       }
            }
         }

         long align_boundary = 
            min((((k+1)+(NTL_AVX_DBL_ALIGN-1))/NTL_AVX_DBL_ALIGN)*NTL_AVX_DBL_ALIGN, n);


	 for (long ii = first; ii < last; ii++) {
            long i = ii + k+1;

	    double * NTL_RESTRICT x = &M[i][0]; 
	    long t1 = rem((unsigned long)(long)x[k], p, red_struct);
	    t1 = NegateMod(t1, p);
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    double ut1 = t1;
            for (long j = k+1; j < align_boundary; j++) x[j] += y[j]*ut1;
            BlockMul1(x+align_boundary, y+align_boundary, ut1, n-align_boundary);

            if (bp)
            {
               long t2 = MulMod(bv[k], t1, p);
               bv[i] = AddMod(bv[i], t2, p);
            }
	 }
         NTL_GEXEC_RANGE_END
      }
      else {
         clear(d);
         return;
      }
   }



   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
	 for (long j = i+1; j < n; j++) {
            long t0 = rem((unsigned long)(long)M[i][j], p, red_struct);
            long t2 = MulMod(rep(X[j]), t0, p);
            t1 = AddMod(t1, t2, p);
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;
}


#endif




#ifdef NTL_HAVE_AVX

static
void blk_tri_DD(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      if (xp) xp->SetLength(0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too large");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;
   
   Vec< AlignedArray<double>::AVX > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      double *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }

   if (trans) {
      // copy A transposed into panels
      for (long i = 0; i < n; i++) {
         const zz_p *row = &A[i][0];
         double *col = &M[i/INV_BLK_SZ][i%INV_BLK_SZ];
         for (long j = 0; j < n; j++) 
            col[j*INV_BLK_SZ] = rep(row[j]);
      }
   }
   else {
      // copy A into panels
      for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
	 long j_max = min(jj+INV_BLK_SZ, n);
	 double *panelp = &M[panel][0];

	 for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
	    const zz_p *ap = A[i].elts() + jj;

	    for (long j = jj; j < j_max; j++)
	       panelp[j-jj] = rep(ap[j-jj]);
	 }
      }
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();


   bool pivoting = false;

   long red_trigger = (MAX_DBL_INT-(p-1))/((p-1)*(p-1));
   long red_count = red_trigger;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      bool cleanup = false;

      if (red_count-INV_BLK_SZ < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-INV_BLK_SZ;
      double * NTL_RESTRICT kpanelp = &M[kpanel][0];

      if (cleanup) {
         for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
            kpanelp[r] = rem((unsigned long)(long)kpanelp[r], p, red_struct);
      }

      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = rem((unsigned long)(long)kpanelp[i*INV_BLK_SZ+(k-kk)], p, red_struct);
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         double * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            double * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               long t2 = rem((unsigned long)(long)y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;

            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }

	 for (long i = kk; i < n; i++) {
            if (i == k) continue; // skip row k

	    double * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = rem((unsigned long)(long)x[k-kk], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    double ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ);
            if (bp)
            {
               long t2 = MulMod(bv[k], t1, p);
               bv[i] = AddMod(bv[i], t2, p);
            }
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
	 kpanelp[r] = rem((unsigned long)(long)kpanelp[r], p, red_struct);

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      bool seq = (npanels-(kpanel+1))*INV_BLK_SZ < 150;
      NTL_GEXEC_RANGE(seq, npanels-(kpanel+1), first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      AlignedArray<double>::AVX buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      double *buf = &buf_store[0];

      for (long index = first; index < last; index++) {
         long jpanel = index + kpanel+1;

	 double * NTL_RESTRICT jpanelp = &M[jpanel][0];

	 if (cleanup) {
	    for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
	       jpanelp[r] = rem((unsigned long)(long)jpanelp[r], p, red_struct);
	 }

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               double * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               double * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf

         for (long i = 0; i < (k_max-kk)*INV_BLK_SZ; i++)
            buf[i] = rem((unsigned long)(long)jpanelp[kk*INV_BLK_SZ+i], p, red_struct);

	 // jpanel += kpanel*buf

	 for (long i = kk; i < n; i++) 
            muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk);
      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
         long start_panel = ((i+1)+INV_BLK_SZ-1)/INV_BLK_SZ;
	 for (long jj = INV_BLK_SZ*start_panel, panel = start_panel; 
             jj < n; jj += INV_BLK_SZ, panel++) {
            long j_max = min(jj+INV_BLK_SZ, n);
            double *row = &M[panel][i*INV_BLK_SZ];
            for (long j = jj; j < j_max; j++) {
               long t0 = rem((unsigned long)(long)row[j-jj], p, red_struct);
               long t2 = MulMod(rep(X[j]), t0, p);
               t1 = AddMod(t1, t2, p);
            }
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;

}

#endif


static
void blk_tri_L(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      if (xp) xp->SetLength(0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too large");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;
   
   Vec< UniqueArray<unsigned long> > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      unsigned long *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }

   if (trans) {
      // copy A transposed into panels
      for (long i = 0; i < n; i++) {
         const zz_p *row = &A[i][0];
         unsigned long *col = &M[i/INV_BLK_SZ][i%INV_BLK_SZ];
         for (long j = 0; j < n; j++) 
            col[j*INV_BLK_SZ] = rep(row[j]);
      }
   }
   else {
      // copy A into panels
      for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
	 long j_max = min(jj+INV_BLK_SZ, n);
	 unsigned long *panelp = &M[panel][0];

	 for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
	    const zz_p *ap = A[i].elts() + jj;

	    for (long j = jj; j < j_max; j++)
	       panelp[j-jj] = rep(ap[j-jj]);
	 }
      }
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_reduce_struct red_struct = zz_p::red_struct();


   bool pivoting = false;

   unsigned long ured_trigger = 
      (~(0UL)-cast_unsigned(p-1))/(cast_unsigned(p-1)*cast_unsigned(p-1));
   // NOTE: corner case at p == 2: need unsigned long to prevent overflow

   long red_trigger = min(cast_unsigned(NTL_MAX_LONG), ured_trigger);

   long red_count = red_trigger;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      bool cleanup = false;

      if (red_count-INV_BLK_SZ < 0) {
         red_count = red_trigger;
         cleanup = true;
      }

      red_count = red_count-INV_BLK_SZ;
      unsigned long * NTL_RESTRICT kpanelp = &M[kpanel][0];

      if (cleanup) {
         for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
            kpanelp[r] = rem(kpanelp[r], p, red_struct);
      }

      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = rem(kpanelp[i*INV_BLK_SZ+(k-kk)], p, red_struct);
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         unsigned long * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            unsigned long * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               long t2 = rem(y[j], p, red_struct);
               y[j] = MulModPrecon(t2, t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;

            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }

	 for (long i = kk; i < n; i++) {
            if (i == k) continue; // skip row k

	    unsigned long * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = rem(x[k-kk], p, red_struct);
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    unsigned long ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ);
            if (bp)
            {
               long t2 = MulMod(bv[k], t1, p);
               bv[i] = AddMod(bv[i], t2, p);
            }
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
	 kpanelp[r] = rem(kpanelp[r], p, red_struct);

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      bool seq = (npanels-(kpanel+1))*INV_BLK_SZ < 150;
      NTL_GEXEC_RANGE(seq, npanels-(kpanel+1), first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      UniqueArray<unsigned long> buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      unsigned long *buf = &buf_store[0];

      for (long index = first; index < last; index++) {
         long jpanel = index + kpanel+1;

	 unsigned long * NTL_RESTRICT jpanelp = &M[jpanel][0];

	 if (cleanup) {
	    for (long r = kk*INV_BLK_SZ; r < n*INV_BLK_SZ; r++) 
	       jpanelp[r] = rem(jpanelp[r], p, red_struct);
	 }

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               unsigned long * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               unsigned long * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf
         // here, we transpose it

         for (long k = kk; k < k_max; k++) 
            for (long j = 0; j < INV_BLK_SZ; j++)
               buf[j*INV_BLK_SZ + (k-kk)] = 
                  rem(jpanelp[k*INV_BLK_SZ+j], p, red_struct);

	 // jpanel += kpanel*buf

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = kk; i < n; i++) 
	       muladd1_by_32_full(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf);
         }
         else {
	    for (long i = kk; i < n; i++) 
	       muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk);
         }

      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
         long start_panel = ((i+1)+INV_BLK_SZ-1)/INV_BLK_SZ;
	 for (long jj = INV_BLK_SZ*start_panel, panel = start_panel; 
             jj < n; jj += INV_BLK_SZ, panel++) {
            long j_max = min(jj+INV_BLK_SZ, n);
            unsigned long *row = &M[panel][i*INV_BLK_SZ];
            for (long j = jj; j < j_max; j++) {
               long t0 = rem(row[j-jj], p, red_struct);
               long t2 = MulMod(rep(X[j]), t0, p);
               t1 = AddMod(t1, t2, p);
            }
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;

}


static
void blk_tri_LL(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("tri: nonsquare matrix");

   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   if (bp && !xp)
      LogicError("tri: bad args");

   if (n == 0) {
      set(d);
      if (xp) xp->SetLength(0);
      return;
   }

   if (NTL_OVERFLOW(n, INV_BLK_SZ, 0)) ResourceError("dimension too large");

   long npanels = (n+INV_BLK_SZ-1)/INV_BLK_SZ;
   
   Vec< UniqueArray<long> > M;
   M.SetLength(npanels);
   for (long panel = 0; panel < npanels; panel++) {
      M[panel].SetLength(n*INV_BLK_SZ);
      long *panelp = &M[panel][0];

      for (long r = 0; r < n*INV_BLK_SZ; r++) panelp[r] = 0;
   }

   if (trans) {
      // copy A transposed into panels
      for (long i = 0; i < n; i++) {
         const zz_p *row = &A[i][0];
         long *col = &M[i/INV_BLK_SZ][i%INV_BLK_SZ];
         for (long j = 0; j < n; j++) 
            col[j*INV_BLK_SZ] = rep(row[j]);
      }
   }
   else {
      // copy A into panels
      for (long jj = 0, panel = 0; jj < n; jj += INV_BLK_SZ, panel++) {
	 long j_max = min(jj+INV_BLK_SZ, n);
	 long *panelp = &M[panel][0];

	 for (long i = 0; i < n; i++, panelp += INV_BLK_SZ) {
	    const zz_p *ap = A[i].elts() + jj;

	    for (long j = jj; j < j_max; j++)
	       panelp[j-jj] = rep(ap[j-jj]);
	 }
      }
   }

   Vec<long> bv;
   if (bp) conv(bv, *bp);
            
   Vec<long> P;
   P.SetLength(n);
   for (long k = 0; k < n; k++) P[k] = k;
   // records swap operations


   long det;
   det = 1;

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   sp_ll_reduce_struct ll_red_struct = zz_p::ll_red_struct();


   bool pivoting = false;

   for (long kk = 0, kpanel = 0; kk < n; kk += INV_BLK_SZ, kpanel++) {
      long k_max = min(kk+INV_BLK_SZ, n);

      long * NTL_RESTRICT kpanelp = &M[kpanel][0];

      for (long k = kk; k < k_max; k++) {

	 long pos = -1;
	 long pivot;
	 long pivot_inv;

	 for (long i = k; i < n; i++) {
	    // NOTE: by using InvModStatus, this code will work
	    // for prime-powers as well as primes
	    pivot = kpanelp[i*INV_BLK_SZ+(k-kk)];
	    if (pivot != 0 && !relaxed_InvModStatus(pivot_inv, pivot, p, relax)) {
	       pos = i;
	       break;
	    }
	 }

	 if (pos == -1) {
	    clear(d);
	    return;
	 }

         long * NTL_RESTRICT y = &kpanelp[k*INV_BLK_SZ];
         if (k != pos) {
            // swap rows pos and k
            long * NTL_RESTRICT x = &kpanelp[pos*INV_BLK_SZ];
            for (long j = 0; j < INV_BLK_SZ; j++) _ntl_swap(x[j], y[j]);
            
            det = NegateMod(det, p);
            P[k] = pos;
            pivoting = true;

            if (bp) _ntl_swap(bv[pos], bv[k]);
         }

         det = MulMod(det, pivot, p);

         {
            // multiply row k by pivot_inv
            long t1 = pivot_inv;
            mulmod_precon_t t1pinv = PrepMulModPrecon(t1, p, pinv); 
            for (long j = 0; j < INV_BLK_SZ; j++) {
               y[j] = MulModPrecon(y[j], t1, p, t1pinv);
            }

            y[k-kk] = pivot_inv;

            if (bp) bv[k] = MulModPrecon(bv[k], t1, p, t1pinv);
         }

	 for (long i = kk; i < n; i++) {
            if (i == k) continue; // skip row k

	    long * NTL_RESTRICT x = &kpanelp[i*INV_BLK_SZ];
	    long t1 = x[k-kk];
	    t1 = NegateMod(t1, p);
            x[k-kk] = 0;
	    if (t1 == 0) continue;

            // add t1 * row k to row i
	    long ut1 = t1;
            BlockMul(x, y, ut1, INV_BLK_SZ, p, pinv);
            if (bp)
            {
               long t2 = MulMod(bv[k], t1, p);
               bv[i] = AddMod(bv[i], t2, p);
            }
         }
      }


      // finished processing current kpanel
      // next, reduce and apply to all other kpanels

      // special processing: subtract 1 off of diangonal

      for (long k = kk; k < k_max; k++)
         kpanelp[k*INV_BLK_SZ+(k-kk)] = SubMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);


      bool seq = (npanels-(kpanel+1))*INV_BLK_SZ < 150;
      NTL_GEXEC_RANGE(seq, npanels-(kpanel+1), first, last)  
      NTL_IMPORT(p)
      NTL_IMPORT(n)
      NTL_IMPORT(ll_red_struct)
      NTL_IMPORT(kpanel)
      NTL_IMPORT(kpanelp)
      NTL_IMPORT(kk)
      NTL_IMPORT(k_max)


      UniqueArray<long> buf_store;
      buf_store.SetLength(INV_BLK_SZ*INV_BLK_SZ);
      long *buf = &buf_store[0];

      for (long index = first; index < last; index++) {
         long jpanel = index + kpanel+1;

	 long * NTL_RESTRICT jpanelp = &M[jpanel][0];

         // perform swaps
         for (long k = kk; k < k_max; k++) {
            long pos = P[k];
            if (pos != k) {
               // swap rows pos and k
               long * NTL_RESTRICT pos_p = &jpanelp[pos*INV_BLK_SZ];
               long * NTL_RESTRICT k_p = &jpanelp[k*INV_BLK_SZ];
               for (long j = 0; j < INV_BLK_SZ; j++)
                  _ntl_swap(pos_p[j], k_p[j]);
            }
         }

	 // copy block number kpanel (the one on the diagonal)  into buf
         // here, we transpose it

         for (long k = kk; k < k_max; k++) 
            for (long j = 0; j < INV_BLK_SZ; j++)
               buf[j*INV_BLK_SZ + (k-kk)] = jpanelp[k*INV_BLK_SZ+j];

	 // jpanel += kpanel*buf

         if (k_max-kk == INV_BLK_SZ) {
	    for (long i = kk; i < n; i++) 
	       muladd1_by_32_full(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, 
                                  p, ll_red_struct);
         }
         else {
	    for (long i = kk; i < n; i++) 
	       muladd1_by_32(jpanelp + i*INV_BLK_SZ, kpanelp + i*INV_BLK_SZ, buf, k_max-kk,
                             p, ll_red_struct);
         }

      }
		  
      NTL_GEXEC_RANGE_END

      // special processing: add 1 back to the diangonal

      for (long k = kk; k < k_max; k++)
	 kpanelp[k*INV_BLK_SZ+(k-kk)] = AddMod((long)kpanelp[k*INV_BLK_SZ+(k-kk)], 1, p);

   }

   if (bp) {
      xp->SetLength(n);
      zz_p *X = xp->elts();

      for (long i = n-1; i >= 0; i--) {
	 long t1 = 0;
         long start_panel = ((i+1)+INV_BLK_SZ-1)/INV_BLK_SZ;
	 for (long jj = INV_BLK_SZ*start_panel, panel = start_panel; 
             jj < n; jj += INV_BLK_SZ, panel++) {
            long j_max = min(jj+INV_BLK_SZ, n);
            long *row = &M[panel][i*INV_BLK_SZ];
            for (long j = jj; j < j_max; j++) {
               long t0 = row[j-jj];
               long t2 = MulMod(rep(X[j]), t0, p);
               t1 = AddMod(t1, t2, p);
            }
	 }
         X[i].LoopHole() = SubMod(bv[i], t1, p);
      }
   }

   d.LoopHole() = det;

}



#endif



static
void tri(zz_p& d, const mat_zz_p& A, const vec_zz_p *bp, 
               vec_zz_p *xp, bool trans, bool relax)
{
   long n = A.NumRows();

   if (A.NumCols() != n)
      LogicError("inv: nonsquare matrix");

   if (bp && bp->length() != n)
      LogicError("tri: dimension mismatch");

   if (bp && !xp)
      LogicError("tri: bad args");

#ifndef NTL_HAVE_LL_TYPE

   basic_tri(d, A, bp, xp, trans, relax);

#else

   long p = zz_p::modulus();

   if (n < 16) {
      //cerr << "basic_tri\n";
      basic_tri(d, A, bp, xp, trans, relax);
   }
   else if (n/INV_BLK_SZ < 4) {
      long V = 64;

#ifdef NTL_HAVE_AVX
      if (p-1 <= MAX_DBL_INT &&
          V <= (MAX_DBL_INT-(p-1))/(p-1) &&
          V*(p-1) <= (MAX_DBL_INT-(p-1))/(p-1)) {

         //cerr << "alt_tri_DD\n";
         alt_tri_DD(d, A, bp, xp, trans, relax);
      }
      else 
#endif
           if (cast_unsigned(V) <= (~(0UL)-cast_unsigned(p-1))/cast_unsigned(p-1) &&
               cast_unsigned(V)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

         //cerr << "alt_tri_L\n";
         alt_tri_L(d, A, bp, xp, trans, relax);

      }
      else {
  
         //cerr << "basic_tri\n";
         basic_tri(d, A, bp, xp, trans, relax);
      }
   }
   else {
      long V = 4*INV_BLK_SZ;

#ifdef NTL_HAVE_AVX
      if (p-1 <= MAX_DBL_INT &&
          V <= (MAX_DBL_INT-(p-1))/(p-1) &&
          V*(p-1) <= (MAX_DBL_INT-(p-1))/(p-1)) {

         //cerr << "blk_tri_DD\n";
         blk_tri_DD(d, A, bp, xp, trans, relax);
      }
      else 
#endif
           if (cast_unsigned(V) <= (~(0UL)-cast_unsigned(p-1))/cast_unsigned(p-1) &&
               cast_unsigned(V)*cast_unsigned(p-1) <= (~(0UL))/cast_unsigned(p-1))  {

         //cerr << "blk_tri_L\n";
         blk_tri_L(d, A, bp, xp, trans, relax);

      }
      else {
  
         //cerr << "blk_tri_LL\n";
         blk_tri_LL(d, A, bp, xp, trans, relax);
      }
   
   }

#endif



}



void relaxed_determinant(zz_p& d, const mat_zz_p& A, bool relax)
{
   tri(d, A, 0, 0, false, relax);
}


void relaxed_solve(zz_p& d, vec_zz_p& x, 
           const mat_zz_p& A, const vec_zz_p& b, bool relax)
{
   tri(d, A, &b, &x, true, relax);
}

void relaxed_solve(zz_p& d, const mat_zz_p& A, vec_zz_p& x, const vec_zz_p& b, bool relax)
{
   tri(d, A, &b, &x, false, relax);
}

// ******************************************************************
//
// Other gaussian elimination code
//
// FIXME: these routines still need work
//   * The image and kernel routines could be turned into
//     more efficient versions modeled along the lines of the 
//     tri routines above.  The main difference would be that 
//     we need to swap columns in addition to rows to things
//     aligned into panels and blocks...but that should not be
//     too difficult.
//
//   * Unfortunately, the documentation for image() states that the
//     is in row-echelon form, which is hard to maintain with
//     column swapping.  So this means I'll have to provide a separate
//     interface for a faster algorithm....grrrrr....
//
//   * The gauss routine has a difficult interface, since row echelon
//     form cannot be maintained with column swapping.
//     Not sure what to do: perhaps nothing for the foreseeable furure.
//
//   * If and when I do write a better kernel routine, I could
//     consider re-working the Berlekamp null-space code in
//     lzz_pXFactoring.c.  Currently, that code has gaussian elimination
//     hard-coded.  It may be faster and cleaner to jsut use the kernel
//     routine from here.  That said, I don't think working on Berlekamp
//     is a worthwhile investment right now.
//
// ******************************************************************



long gauss(mat_zz_p& M, long w)
{
   long k, l;
   long i, j;
   long pos;
   zz_p t1, t2, t3;
   zz_p *x, *y;

   long n = M.NumRows();
   long m = M.NumCols();

   if (w < 0 || w > m)
      LogicError("gauss: bad args");

   long p = zz_p::modulus();
   mulmod_t pinv = zz_p::ModulusInverse();
   long T1, T2;

   l = 0;
   for (k = 0; k < w && l < n; k++) {

      pos = -1;
      for (i = l; i < n; i++) {
         if (!IsZero(M[i][k])) {
            pos = i;
            break;
         }
      }

      if (pos != -1) {
         swap(M[pos], M[l]);

         inv(t3, M[l][k]);
         negate(t3, t3);

         for (i = l+1; i < n; i++) {
            // M[i] = M[i] + M[l]*M[i,k]*t3

            mul(t1, M[i][k], t3);

            T1 = rep(t1);
            mulmod_precon_t T1pinv = PrepMulModPrecon(T1, p, pinv); 

            clear(M[i][k]);

            x = M[i].elts() + (k+1);
            y = M[l].elts() + (k+1);

            for (j = k+1; j < m; j++, x++, y++) {
               // *x = *x + (*y)*t1

               T2 = MulModPrecon(rep(*y), T1, p, T1pinv);
               T2 = AddMod(T2, rep(*x), p);
               (*x).LoopHole() = T2;
            }
         }

         l++;
      }
   }

   return l;
}

long gauss(mat_zz_p& M)
{
   return gauss(M, M.NumCols());
}

void image(mat_zz_p& X, const mat_zz_p& A)
{
   mat_zz_p M;
   M = A;
   long r = gauss(M);
   M.SetDims(r, M.NumCols());
   X = M;
}

void kernel(mat_zz_p& X, const mat_zz_p& A)
{
   long m = A.NumRows();
   long n = A.NumCols();

   mat_zz_p M;
   long r;

   transpose(M, A);
   r = gauss(M);

   X.SetDims(m-r, m);

   long i, j, k, s;
   zz_p t1, t2;

   vec_long D;
   D.SetLength(m);
   for (j = 0; j < m; j++) D[j] = -1;

   vec_zz_p inverses;
   inverses.SetLength(m);

   j = -1;
   for (i = 0; i < r; i++) {
      do {
         j++;
      } while (IsZero(M[i][j]));

      D[j] = i;
      inv(inverses[j], M[i][j]); 
   }

   for (k = 0; k < m-r; k++) {
      vec_zz_p& v = X[k];
      long pos = 0;
      for (j = m-1; j >= 0; j--) {
         if (D[j] == -1) {
            if (pos == k)
               set(v[j]);
            else
               clear(v[j]);
            pos++;
         }
         else {
            i = D[j];

            clear(t1);

            for (s = j+1; s < m; s++) {
               mul(t2, v[s], M[i][s]);
               add(t1, t1, t2);
            }

            mul(t1, t1, inverses[j]);
            negate(v[j], t1);
         }
      }
   }
}
   


// ******************************************************************
//
// Operator/functional notation
//
// ******************************************************************




mat_zz_p operator+(const mat_zz_p& a, const mat_zz_p& b)
{
   mat_zz_p res;
   add(res, a, b);
   NTL_OPT_RETURN(mat_zz_p, res);
}

mat_zz_p operator*(const mat_zz_p& a, const mat_zz_p& b)
{
   mat_zz_p res;
   mul_aux(res, a, b);
   NTL_OPT_RETURN(mat_zz_p, res);
}

mat_zz_p operator-(const mat_zz_p& a, const mat_zz_p& b)
{
   mat_zz_p res;
   sub(res, a, b);
   NTL_OPT_RETURN(mat_zz_p, res);
}


mat_zz_p operator-(const mat_zz_p& a)
{
   mat_zz_p res;
   negate(res, a);
   NTL_OPT_RETURN(mat_zz_p, res);
}


vec_zz_p operator*(const mat_zz_p& a, const vec_zz_p& b)
{
   vec_zz_p res;
   mul_aux(res, a, b);
   NTL_OPT_RETURN(vec_zz_p, res);
}

vec_zz_p operator*(const vec_zz_p& a, const mat_zz_p& b)
{
   vec_zz_p res;
   mul(res, a, b);
   NTL_OPT_RETURN(vec_zz_p, res);
}


NTL_END_IMPL
