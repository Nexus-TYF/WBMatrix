/*
 * @Author: Weijie Li 
 * @Date: 2017-11-27 16:45:31 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-11-12 22:26:03
 */
#include <m4ri/matrix_gf2.h>

#include <stdio.h>

#include <m4ri/wrandom.h>


MatGf2 GenMatGf2(int r, int c) {
	return mzd_init(r,c);
}


MatGf2 GenRandomMatGf2(int r, int c) {
	MatGf2 t = GenMatGf2(r, c);
	RandomMatGf2(t);
	return t;
}

MatGf2 GenRandomMatGf2Custom(int r, int c, uint64_t (*rc)(void *data), void *data) {
	MatGf2 t = GenMatGf2(r, c);
	RandomMatGf2Custom(t, rc, data);
	return t;
}

MatGf2 GenIndMatrix(int size) {
	MatGf2 dst =GenMatGf2(size, size);
	int i,j;
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			MatGf2Set(dst, i, j, i==j);
		}
	}
	return dst;	
}

MatGf2 GenZeroVec(int size) {
	MatGf2 vec = GenMatGf2(size, 1);
	int i;
	for (i=0; i<size; i++) {
		MatGf2Set(vec, i, 0, 0);
	}
	return vec;	
}

MatGf2 GenInvertibleMatGf2(int r, int c) {
	MatGf2 mat = GenRandomMatGf2(r, c);
    while (IsMatGf2Invertible(mat)==0) {
        RandomMatGf2(mat);
    }    
    return mat;
}


MatGf2 GenMatGf2Stack(const MatGf2 a, const MatGf2 b) {
	return mzd_stack(NULL, a, b);
}

MatGf2 GenMatGf2Concat(const MatGf2 a, const MatGf2 b) {
	return mzd_concat(NULL, a, b);
}

MatGf2 GenMatGf2Diag(const MatGf2 a, const MatGf2 b) {
	MatGf2 t = NULL;
	MatGf2Diag(a, b, &t);
	return t;
}

MatGf2 GenMatGf2Inv(MatGf2 mat) {
	return mzd_inv_m4ri(NULL, mat, 0);
}

MatGf2 GenMatGf2Mul(const MatGf2 a, const MatGf2 b) {
	return mzd_mul_m4rm(NULL, a, b, 0);
}

MatGf2 GenMatGf2Add(const MatGf2 a, const MatGf2 b) {
	return mzd_add(NULL, a, b);
}

MatGf2 GenMatGf2Copy(const MatGf2 source) {
	return mzd_copy(NULL, source);
}

int ReAllocatedInvertibleMatGf2(int r, int c, MatGf2* dst) {
	MatGf2Free(*dst);
	*dst = GenInvertibleMatGf2(r, c);
	return 0;
}


int ReAllocatedMatGf2(int r, int c, MatGf2 *mat) {
	MatGf2Free(*mat);
	*mat = mzd_init(r,c);
    return 0;
}

int ReAllocatedRandomMatGf2(int r, int c, MatGf2 *mat) {
	MatGf2Free(*mat);
	*mat = GenRandomMatGf2(r, c);
	return 0;
}

int ReAllocatedRandomMatGf2Custom(int r, int c, MatGf2* mat, uint64_t (*rc)(void *data), void *data) {
	MatGf2Free(*mat);
	*mat = GenRandomMatGf2Custom(r, c, rc, data);
	return 0;
}


int InitMatGf2ByValueArray(int *data, MatGf2 mat) {
	int i,j,n,m;
	for(i=0, n=mat->nrows; i<n; i++){
		for(j=0, m=mat->ncols; j<m; j++){
            MatGf2Set(mat, i, j, data[n*i+j]);
		}
	}
	return 0;
}


int InitMatrixFromBitArray(unsigned long *data, MatGf2 mat) {
    long i,j,n;
	for(i=0, n=mat->nrows; i<n; i++){
		unsigned long t = *data;
		for(j=mat->ncols-1; j>=0; j--){
			MatGf2Set(mat, i, j, t%2);
			t >>= 1;
		}
		data++;
	}
	return 0;
}

int InitVecFromBit(unsigned long data, MatGf2 mat) {
    long i;
    unsigned long t = data;
	for(i=mat->nrows-1; i>=0; i--){
        MatGf2Set(mat, i, 0, t%2);
        t >>= 1;
	}
	return 0;
}


int MatGf2Set(MatGf2 mat, int row, int col, int value) {
    mzd_write_bit(mat, row, col ,value%2);
    return 0;
}

int MatGf2Get(MatGf2 mat, int row, int col) {
    return mzd_read_bit(mat, row, col);
}

uint64_t _wrand_word(void *data) {
	return wRand64();
}

int RandomMatGf2Custom(MatGf2 mat, uint64_t (*rc)(void *data), void *data) {
    mzd_randomize_custom(mat, rc, data);
    return 0;
}

int RandomMatGf2(MatGf2 mat) {
    RandomMatGf2Custom(mat, _wrand_word, NULL);
    return 0;
}

void DumpMatGf2Line(MatGf2 a, int newLine){
	int i,j, n = a->nrows, m=a->ncols;
	for (i=0; i<n; i++){
		for(j=0; j<m; j++){
			if (newLine) printf(" ");
			printf("%d", MatGf2Get(a, i, j));
			if (newLine) printf(" ");
			else printf(", ");
		}
		if (newLine) printf("\n");
		else printf(" | ");
	}
	if (newLine) printf("\n");
}

void DumpMatGf2(MatGf2 mat) {
    DumpMatGf2Line(mat, 1);
}


int MatGf2Inv(MatGf2 mat, MatGf2 *mat_inv) {
	MatGf2 to_be_free = *mat_inv;
	*mat_inv = GenMatGf2Inv(mat);
	MatGf2Free(to_be_free);
    return 0;
    // MatGf2 I = InitMatGf2(mat->nrows, mat->nrows);
    // for (int i=0; i < mat->nrows; i++) {
    //     MatGf2Set(I, i, i, 1);
    // }
    // return mzd_invert_naive(NULL, mat, I);
}


MatGf2 MatGf2Mul(const MatGf2 a, const MatGf2 b, MatGf2 *dst) {
	MatGf2 to_be_free = *dst;
	*dst = GenMatGf2Mul(a, b);
	MatGf2Free(to_be_free);
	return *dst;
}

MatGf2 MatGf2Add(const MatGf2 a, const MatGf2 b, MatGf2 *dst) {
	MatGf2 to_be_free = *dst;
	*dst = GenMatGf2Add(a, b);
	MatGf2Free(to_be_free);
	return *dst;
}


int MatGf2Copy(const MatGf2 source, MatGf2* dest) {
	MatGf2Free(*dest);
	*dest = GenMatGf2Copy(source);
	return 0;
}

int IsMatGf2Invertible(const MatGf2 mat) {
    if (mat->nrows != mat->ncols) return 0;
    MatGf2 x = NULL;
	int ret = 0;
    MatGf2Copy(mat, &x);
    mzd_echelonize_naive(x, 0);   
    if (MatGf2Get(x, x->nrows-1, x->nrows-1)==1) {
        ret = 1;
    } else {
		ret = 0;
    }
	MatGf2Free(x);
	return ret;
}

int MatGf2Transpose(const MatGf2 a, MatGf2 *dst) {
	MatGf2 to_be_free = *dst;
    *dst = mzd_transpose(NULL, a);
	MatGf2Free(to_be_free);
	return 0;
}


uint32_t get32FromVec(const MatGf2 vec) {
    if (vec->nrows!=32 )  {
        printf("[Error] nrows: %d, ncols: %d\n", vec->nrows, vec->ncols);
        return 0;
    }
	return getDigitalFromVec(vec);
}

uint32_t getDigitalFromVec(const MatGf2 vec) {
    if (vec->ncols!=1)  {
        printf("[Error] nrows: %d, ncols: %d\n", vec->nrows, vec->ncols);
        return 0;
    }
    uint32_t d = 0;
	int i, nrows = vec->nrows;
	for (i=0; i<nrows; i++) {
		d <<=1 ;
		d += ((MatGf2Get(vec, i, 0)==1)?1:0);
	}
	return d;
}


int MatGf2Stack(const MatGf2 a, const MatGf2 b, MatGf2* dst) {
	MatGf2 to_be_free = *dst;
    *dst = GenMatGf2Stack(a, b);
	MatGf2Free(to_be_free);
	return 0;
}


int MatGf2Concat(const MatGf2 a, const MatGf2 b, MatGf2* dst) {
	MatGf2 to_be_free = *dst;
    *dst = GenMatGf2Concat(a, b);
	MatGf2Free(to_be_free);
	return 0;
}

int MatGf2Diag(const MatGf2 a, const MatGf2 b, MatGf2* dst) {
    int n1 = a->ncols;
	int n2 = b->ncols;
	ReAllocatedMatGf2(n1+n2, n1+n2, dst);
	MatGf2 d = *dst;
	int i,j;
	for (i=0; i<n1; i++) {
		for (j=0; j<n1; j++) {
			MatGf2Set(d, i, j, MatGf2Get(a, i, j));
		}
		for (j=0; j<n2; j++) {
			MatGf2Set(d, i, n1+j, 0);
		}
	}
	for (i=0; i<n2; i++) {
		for (j=0; j<n1; j++) {
			MatGf2Set(d, n1+i, j, 0);
		}
		for (j=0; j<n2; j++) {
			MatGf2Set(d, n1+i, n1+j, MatGf2Get(b, i, j));
		}
	}
	return 0;
}

void MatGf2Free(MatGf2 mat) {
    if (mat!=NULL)
        mzd_free(mat);
}


// left multi, mat * data
uint8_t MatMulU8(const MatGf2 mat, uint8_t data) {
	MatGf2 a = GenMatGf2(8,1);
	InitVecFromBit(data, a);
	MatGf2Mul(mat, a, &a);
	uint8_t result = (uint8_t)getDigitalFromVec(a);
	MatGf2Free(a);
	a = NULL;
	return result;
}

uint32_t MatMulU32(const MatGf2 mat, uint32_t data) {
	MatGf2 a = GenMatGf2(32,1);
	InitVecFromBit(data, a);
	MatGf2Mul(mat, a, &a);
	uint32_t result = (uint32_t)getDigitalFromVec(a);
	MatGf2Free(a);
	a = NULL;
	return result;
}

//  multi,  data *  mat
uint8_t U8MulMat(uint8_t data, const MatGf2 mat) {
	MatGf2 a = GenMatGf2(8,1);
	InitVecFromBit(data, a);
	MatGf2Transpose(a, &a);
	MatGf2Mul(a, mat, &a);
	MatGf2Transpose(a, &a);
	uint8_t result = (uint8_t)getDigitalFromVec(a);
	MatGf2Free(a);
	a = NULL;
	return result;
}

uint32_t U32MulMat(uint32_t data, const MatGf2 mat) {
	MatGf2 a = GenMatGf2(32,1);
	InitVecFromBit(data, a);
	MatGf2Transpose(a, &a);
	MatGf2Mul(a, mat, &a);
	MatGf2Transpose(a, &a);
	uint32_t result = (uint32_t)getDigitalFromVec(a);
	MatGf2Free(a);
	a = NULL;
	return result;
}

int MatGf2Cmp(const MatGf2 a, const MatGf2 b) {
    return mzd_cmp(a, b);
}

uint8_t * ExportMatGf2ToStr(const MatGf2 a) {
	int byteSize = 2*sizeof(uint32_t) + a->nrows * a->ncols *sizeof(char);
	uint8_t *result = malloc( byteSize ); 
	uint8_t *iter = result;
	*( (uint32_t*)iter) = (uint32_t)a->nrows;
	iter = iter + sizeof(uint32_t);
	*( (uint32_t*)iter) = (uint32_t)a->ncols;
	iter = iter + sizeof(uint32_t);	

	int i,j;
	for (i=0; i<a->nrows; i++) {
		for (j=0; j<a->ncols; j++) {
			*((uint8_t*)iter++) = (MatGf2Get(a, i, j)?'1':'0');
		}
	}
	return result;
}

MatGf2 ImportMatGf2FromStr(const uint8_t *source) {
	uint32_t* sz = (uint32_t*)source;
	int nr = *(sz++);
	int nc = *sz;
	const char * str = (const char*)source + 2*sizeof(uint32_t);

	return mzd_from_str(nr, nc, str);
}
