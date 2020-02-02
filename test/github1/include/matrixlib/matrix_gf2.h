#ifndef _MATH_MATRIX_GF2_H_
#define _MATH_MATRIX_GF2_H_

#include <stdlib.h>
#include <m4ri/m4ri.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef mzd_t *MatGf2;

MatGf2 GenMatGf2(int r, int c);//

MatGf2 GenRandomMatGf2(int r, int c);//

MatGf2 GenInvertibleMatGf2(int r, int c);//

int TimesInveribleMatGf2(int r, int c);//

int MatGf2Inv(MatGf2 mat, MatGf2 *mat_inv);

MatGf2 GenMatGf2Inv(MatGf2 mat);//

MatGf2 GenMatGf2Copy(const MatGf2 source);//

int MatGf2Copy(const MatGf2 source, MatGf2 *dest);

int MatGf2Get(MatGf2 mat, int row, int col);//

int RandomMatGf2(MatGf2 mat);//

int IsMatGf2Invertible(const MatGf2 mat);//

void MatGf2Free(MatGf2 mat);//

#ifdef __cplusplus
}
#endif

#endif /* _MATH_MATRIX_GF2_H_ */