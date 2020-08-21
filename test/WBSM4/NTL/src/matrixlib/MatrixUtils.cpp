#include <matrixlib/MatrixUtils.h>
#include <NTL/vec_GF2.h>

void random(NTL::mat_GF2 &L, int n1, int n2)
{
	L.SetDims(n1,n2);
	int hw;
	for (int i = 0; i < n1; i++)
	{
		do
	    	{
	    		hw = 0;
				for (int j = 0; j < n2; j++)
				{
					L[i][j] = NTL::random_GF2();
					if (L[i][j] == 1)
			            hw += 1;
				}
			} while (hw == 1);
	}
}
int initMatrixFromBit(NTL::mat_GF2 &M, long *data) {
    long i,j,n,m;
	for(i=0, n=M.NumRows(); i<n; i++){
		long t = *data;
		for(j=M.NumCols()-1; j>=0; j--){
			M.put(i,j,t%2);
			t >>= 1;
		}
		data++;
	}

	return 0;
}

int initVecFromBit(NTL::vec_GF2 &M, long data, int len) {
	M.SetLength(len);
    long i,j,n,m;
	for(i=len-1; i>=0; i--){
		M.put(i, data%2);
		data >>=1;
	}
	return 0;
}
int genRandomAffineAugmentedMatrix(NTL::mat_GF2 &X,  NTL::mat_GF2 &Y, int n) {
	NTL::mat_GF2 L;
	random(L, n, n);
	while(determinant(L)==0) {
		random(L, n, n);
	}
	NTL::mat_GF2 LINV = inv(L);
	NTL::vec_GF2 tran;
	// tran.SetLength(m);
	random(tran, n);
	NTL::mat_GF2 AugmentedMatrix;

	X.SetDims(n+1, n+1);
	int i,j;
	for (i=0; i<n; i++) {
		for ( j=0; j<n; j++) {
			X.put(i,j, L.get(i, j));
		}
	}

	for (j=0; j<n; j++) {
		X.put(n, j, 0);
	}
	X.put(n, n, 1);

	for (i=0; i<n; i++) {
		X.put(i, n, tran.get(i));
	}

	NTL::GF2 d;
	
	inv(d, Y, X);

	return 0;

}

int genRandomAffineMatrix(NTL::mat_GF2 &X,  NTL::mat_GF2 &Y, NTL::vec_GF2 &V, int n) {
	random(X, n, n);
	while(determinant(X)==0) {
		random(X, n, n);
	}
	NTL::GF2 d;
	inv(d, Y, X);
	random(V, n);
	return 0;
}

int genRandomAffineMatrix(NTL::mat_GF2 &x,  NTL::mat_GF2 &inv_x, NTL::vec_GF2 &v, NTL::vec_GF2 &inv_v, int n) {
	random(x, n, n);
	while(determinant(x)==0) {
		random(x, n, n);
	}
	NTL::GF2 d;
	inv(d, inv_x, x);
	random(v, n);
	mul(inv_v, inv_x, v);
	return 0;
}

int genRandomInvMatrix(NTL::mat_GF2 &x,  NTL::mat_GF2 &inv_x, int n) {
	random(x, n, n);
	while(determinant(x)==0) {
		random(x, n, n);
	}
	NTL::GF2 d;
	inv(d, inv_x, x);
	return 0;
}


uint32_t getDigitalFromVec(NTL::vec_GF2 &s) {
	uint32_t d = 0;
	int i;
	int m = s.length();
	for (i=0; i<m; i++) {
		d <<=1 ;
		d += ((s.get(i)==1)?1:0);
	}
	return d;
}


uint32_t get32FromVec(NTL::vec_GF2 &s) {
	uint32_t d = 0;
	int i;
	for (i=0; i<32; i++) {
		d <<=1 ;
		d += ((s.get(i)==1)?1:0);
	}
	return d;
}

uint8_t get8FromVec(const vector_transform_t &s) {
	uint8_t d = 0;
	int i;
	for (i=0; i<8; i++) {
		d <<=1 ;
		d += ((s.get(i)==1)?1:0);
	}
	return d;
}


int getVecFrom32(NTL::vec_GF2 &d,uint32_t s) {
	d.SetLength(32);
	int i;
	for (i=31; i>=0; i--) {
		d.put(i, s%2);
		s>>=1;
	}
	return 0;
}

int getAugmentedVecFrom32(NTL::vec_GF2 &d, uint32_t s) {
	d.SetLength(33);
	int i;
	for (i=31; i>=0; i--) {
		d.put(i, s%2);
		s>>=1;
	}
	d.put(32, 1);
	return 0;
}

int combineDiagMat(NTL::mat_GF2 &d, NTL::mat_GF2 &s1, NTL::mat_GF2 &s2) {
	long n1 = s1.NumCols();
	long n2 = s2.NumCols();
	d.SetDims(n1+n2, n1+n2);
	int i,j;
	for (i=0; i<n1; i++) {
		for (j=0; j<n1; j++) {
			d.put(i, j, s1.get(i,j));
		}
		for (j=0; j<n2; j++) {
			d.put(i, n1+j, 0);
		}
	}
	for (i=0; i<n2; i++) {
		for (j=0; j<n1; j++) {
			d.put(n1+i, j, 0);
		}
		for (j=0; j<n2; j++) {
			d.put(n1+i, n1+j, s2.get(i,j));
		}
	}
	return 0;
}

uint32_t applyAffineToU32(const affine_transform_t &aff, uint32_t data ) {
	NTL::vec_GF2 a,b;
	initVecFromBit(a, data, 32);
	// dumpVector(a);
	// dumpMatrix(aff.linearMap);
	b = aff.linearMap * a + aff.vectorTranslation;
	return get32FromVec(b);
}

uint8_t applyAffineToU8(const affine_transform_t &aff, uint8_t data) {
	NTL::vec_GF2 a,b;
	initVecFromBit(a, data, 8);
	// dumpVector(a);
	// dumpMatrix(aff.linearMap);
	b = aff.linearMap * a + aff.vectorTranslation;
	return (uint8_t)getDigitalFromVec(b);
}

uint8_t applyMatToU8(const NTL::mat_GF2 &mat, uint8_t data) {
	NTL::vec_GF2 a,b;
	initVecFromBit(a, data, 8);
	b = mat*a;
	return (uint8_t)getDigitalFromVec(b);
}

uint32_t applyMatToU32(const matrix_transform_t &mat, uint32_t data) {
	vector_transform_t a,b;
	initVecFromBit(a, data, 32);
	b = mat*a;
	return (uint32_t)getDigitalFromVec(b);
}

uint32_t addVecToU32(NTL::vec_GF2 &vec, uint32_t data) {
	NTL::vec_GF2 a,b;
	initVecFromBit(a, data, 32);
	b = vec+a;
	return (uint32_t)getDigitalFromVec(b);
}

uint8_t addVecToU8(NTL::vec_GF2 &vec, uint8_t data) {
	NTL::vec_GF2 a,b;
	initVecFromBit(a, data, 8);
	b = vec+a;
	return (uint8_t)getDigitalFromVec(b);
}


int genIndMatrix(NTL::mat_GF2 &mat, int size) {
	mat.SetDims(size, size);
	int i,j;
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			mat.put(i, j, i==j);
		}
	}
	return 0;	
}

int genZeroVec(NTL::vec_GF2 &vec, int size) {
	vec.SetLength(size);
	int i;
	for (i=0; i<size; i++) {
		vec.put(i, 0);
	}
	return 0;	
}
