#include <matrixlib/matrix_gf2.h>
#include <stdio.h>

MatGf2 GenMatGf2(int r, int c) {//
	return mzd_init(r,c);
}

MatGf2 GenRandomMatGf2(int r, int c) {//
	MatGf2 t = GenMatGf2(r, c);
	RandomMatGf2(t);
	return t;
}

MatGf2 GenInvertibleMatGf2(int r, int c) {//
	MatGf2 mat = GenRandomMatGf2(r, c);
    while (IsMatGf2Invertible(mat)==0) {
        RandomMatGf2(mat);
    }    
    return mat;
}

int TimesInveribleMatGf2(int r, int c) {//
	int times=1;
    MatGf2 mat = GenMatGf2(r, c);
    RandomMatGf2(mat);
    while (IsMatGf2Invertible(mat)==0) {
        RandomMatGf2(mat);
        times++;
    }
    MatGf2Free(mat);
    return times;
}

MatGf2 GenMatGf2Inv(MatGf2 mat) {//
	return mzd_inv_m4ri(NULL, mat, 0);
}

int MatGf2Inv(MatGf2 mat, MatGf2 *mat_inv) {
	MatGf2 to_be_free = *mat_inv;
	*mat_inv = GenMatGf2Inv(mat);
	MatGf2Free(to_be_free);
    return 0;
}

MatGf2 GenMatGf2Copy(const MatGf2 source) {//
	return mzd_copy(NULL, source);
}

int MatGf2Get(MatGf2 mat, int row, int col) {//
    return mzd_read_bit(mat, row, col);
}

int RandomMatGf2(MatGf2 mat) {//
    mzd_randomize(mat);
    return 0;
}

int MatGf2Copy(const MatGf2 source, MatGf2* dest) {
	MatGf2Free(*dest);
	*dest = GenMatGf2Copy(source);
	return 0;
}

int IsMatGf2Invertible(const MatGf2 mat) {//
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

void MatGf2Free(MatGf2 mat) {//
    if (mat!=NULL)
        mzd_free(mat);
}