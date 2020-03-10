#ifndef _MATH_MATRIX_GF2_H_
#define _MATH_MATRIX_GF2_H_

#include <stdlib.h>
#include <m4ri/m4ri.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef mzd_t *MatGf2;

/**
 *  Gen* means return a new pointer point to MatGf2
 *  ReAllocated* means free the old pointer and allocated new space
 *  others need to pass a existed pointer pointed to existed MatGf2
 * 
 * */


MatGf2 GenMatGf2(int r, int c);

MatGf2 GenRandomMatGf2(int r, int c);

MatGf2 GenIndMatrix(int size);

MatGf2 GenZeroVec(int size);

MatGf2 GenInvertibleMatGf2(int r, int c);

/**
 * Stack A on top of B and write the result to dst.
 * [ A ], [ B ] -> [ A ] = dst
 *                 [ B ]
 * */
MatGf2 GenMatGf2Stack(const MatGf2 a, const MatGf2 b);

/**
 * Concatenate B to A and write the result to dst.
 * [A],[B]->[A B]= dst
 * */
MatGf2 GenMatGf2Concat(const MatGf2 a, const MatGf2 b);

/**
 * Concatenate B to A in diag form and return.
 * [A],[B]->[A   ]
 *          [   B]
 * */
MatGf2 GenMatGf2Diag(const MatGf2 a, const MatGf2 b);

MatGf2 GenMatGf2Inv(MatGf2 mat);

MatGf2 GenMatGf2Mul(const MatGf2 a, const MatGf2 b);

uint32_t AddMatToU32(const MatGf2 a,const uint32_t b);

MatGf2 GenMatGf2Add(const MatGf2 a, const MatGf2 b);

MatGf2 GenMatAddU8(const MatGf2 a,const uint8_t b);

MatGf2 GenMatAddU16(const MatGf2 a, const uint16_t b);

MatGf2 GenMatGf2Copy(const MatGf2 source);

int ReAllocatedMatGf2(int r, int c, MatGf2 *mat);

int ReAllocatedRandomMatGf2(int r, int c, MatGf2* mat);


uint64_t AddMatToU64(const MatGf2 a, const uint64_t b);

int ReAllocatedInvertibleMatGf2(int r, int c, MatGf2 *dst);

/**
 * Initializes matrix from specified array.
 * Data must be at least dimension of given matrix.
 */
int InitMatGf2ByValueArray(int *data, MatGf2 mat);



/**
 * format matrix from bit, a long correspons a col
 * for example : [1,2,3,4] to a 4*4 matrix
 * [ 0 0 0 1 ]
 * [ 0 0 1 0 ]
 * [ 0 1 0 1 ]
 * [ 1 0 0 0 ]
 * */
int InitMatrixFromBitArray(unsigned long *data, MatGf2 mat);

/**
 * for example : 29 to a 4*1 matrix
 * 11101 to matrix
 * [ 1 ]
 * [ 1 ]
 * [ 0 ]
 * [ 1 ]
 * */
int InitVecFromBit(unsigned long data, MatGf2 mat);

int InitVecFromBit_64(uint64_t data, MatGf2 mat);


#ifdef WITH_UINT128
int InitVecFromBit_128(__uint128_t data, MatGf2 mat);
#endif
int MatGf2Set(MatGf2 mat, int row, int col, int value);

int MatGf2Get(MatGf2 mat, int row, int col);

int RandomMatGf2(MatGf2 mat);

void DumpMatGf2(MatGf2 mat);

int MatGf2Inv(MatGf2 mat, MatGf2 *mat_inv);

int MatGf2Copy(const MatGf2 source, MatGf2 *dest);

int IsMatGf2Invertible(const MatGf2 mat);


/**
 * MatGf2 dst: Preallocated matrix, may be NULL for automatic creation.
 * */
MatGf2 MatGf2Mul(const MatGf2 a, const MatGf2 b, MatGf2 *dst);

/**
 * MatGf2 dst: Preallocated matrix, may be NULL for automatic creation.
 * */
MatGf2 MatGf2Add(const MatGf2 a, const MatGf2 b, MatGf2 *dst);

/**
 * MatGf2 dst: Preallocated matrix, may be NULL for automatic creation.
 * */
int MatGf2Transpose(const MatGf2 a, MatGf2 *dst);

uint32_t get32FromVec(const MatGf2 vec);

uint64_t get64FromVec(const MatGf2 vec);

uint32_t getDigitalFromVec(const MatGf2 vec);

#ifdef WITH_UINT128

__uint128_t ApplyMatToU128(const MatGf2 mat, __uint128_t data);

__uint128_t AddMatToU128(const MatGf2 mat, __uint128_t x);

__uint128_t get128FromVec(const MatGf2 vec);

#endif
    /**
 * Stack A on top of B and write the result to dst.
 * [ A ], [ B ] -> [ A ] = dst
 *                 [ B ]
 * */
    int MatGf2Stack(const MatGf2 a, const MatGf2 b, MatGf2 *dst);

/**
 * Concatenate B to A and write the result to dst.
 * [A],[B]->[A B]= dst
 * */
int MatGf2Concat(const MatGf2 a, const MatGf2 b, MatGf2 *dst);

/**
 * Concatenate B to A in diag form and return.
 * [A],[B]->[A   ]
 *          [   B]
 * */
int MatGf2Diag(const MatGf2 a, const MatGf2 b, MatGf2 *dst);

void MatGf2Free(MatGf2 mat);


uint8_t ApplyMatToU8(const MatGf2 mat, uint8_t data);
uint16_t ApplyMatToU16(const MatGf2 mat, uint16_t data);
uint32_t ApplyMatToU32(const MatGf2 mat, uint32_t data);
uint64_t ApplyMatToU64(const MatGf2 mat, uint64_t data);

    /**
 * Return -1,0,1 if if A < B, A == B or A > B respectively.
 * */
    int MatGf2Cmp(const MatGf2 a, const MatGf2 b);

/**
 * @brief convert MatGf2 to a byte array
 * 
 * @param a MatGf2
 * @return void* byte array
 */
uint8_t * ExportMatGf2ToStr(const MatGf2 a);

/**
 * @brief convert a byte array to MatGf2
 * 
 * @param source byte array
 * @return MatGf2 
 */
MatGf2 ImportMatGf2FromStr(const uint8_t *source);

#ifdef __cplusplus
}
#endif

#endif /* _MATH_MATRIX_GF2_H_ */