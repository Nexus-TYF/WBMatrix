/*
 * @Author: Weijie Li 
 * @Date: 2017-11-27 16:32:03 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-11-12 22:32:46
 */
#ifndef _MATRIX_AFFINE_TRANSFORM_H_
#define _MATRIX_AFFINE_TRANSFORM_H_

#include "m4ri/matrix_gf2.h"

typedef struct AffineTransform {
    MatGf2 linear_map;
    MatGf2 vector_translation;
} AffineTransform;

int RandomAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim);
int RandomAffineTransformCustom(AffineTransform *at, AffineTransform *at_inv, int dim, uint64_t (*rc)(void * data), void* data);
int GenRandomAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim);
int GenRandomAffineTransformCustom(AffineTransform *at, AffineTransform *at_inv, int dim, uint64_t (*rc)(void * data), void* data);

int IndAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim);
int GenIndAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim);

// left mul at.linear_map * mat
int ApplyAffineTransform(const AffineTransform at, const MatGf2 mat, MatGf2* dst);

// right mul mat * at.linear_map
int ApplyAffineTransformRight(const MatGf2 mat, const AffineTransform at, MatGf2* dst);

//  affine.linear * u32 + affine.vector
uint32_t ApplyAffineToU32(const AffineTransform aff, uint32_t x);
uint16_t ApplyAffineToU16(const AffineTransform aff, uint16_t data);
uint8_t ApplyAffineToU8(const AffineTransform aff, uint8_t data);

#define AffineMulU8(a, b) ApplyAffineToU8(a, b)
#define AffineMulU16(a, b) ApplyAffineToU16(a, b)
#define AffineMulU32(a, b) ApplyAffineToU32(a, b)

//  u8 * affine.linear + affine.vector
uint8_t U8MulAffine(uint8_t data, const AffineTransform aff);
uint16_t U16MulAffine(uint16_t data, const AffineTransform aff);
uint32_t U32MulAffine(uint32_t data, const AffineTransform aff);

/**
 * @brief Obsolete, equivalent to release
 * 
 * @param aff 
 * @return int 
 */
int AffineTransformFree(AffineTransform *aff);

/**
 * @brief release source in AffineTransform
 * 
 * @param aff 
 * @return int 
 */
int AffineTransformRelease(AffineTransform *aff);

/**
 * @brief export AffineTransform to str
 * 
 * @param aff 
 * @return void* 
 */
uint8_t * ExportAffineToStr(const AffineTransform* aff);

/**
 * @brief import AffineTransform from str
 * 
 * @param source 
 * @return AffineTransform 
 */
AffineTransform ImportAffineFromStr(const uint8_t *source);

#endif /* _MATRIX_AFFINE_TRANSFORM_H_ */