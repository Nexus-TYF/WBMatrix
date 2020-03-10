#ifndef WBSM4_H
#define WBSM4_H

#include "matrixlib/MatrixUtils.h"
#include "matrixlib/sm4.h"
#define SM4_NUM_ROUNDS 32

typedef struct Sm4Whitebox{
    //Affine
    affine_transform_t M[SM4_NUM_ROUNDS][3];
    affine_transform_t C[SM4_NUM_ROUNDS];
    affine_transform_t D[SM4_NUM_ROUNDS];

    affine_transform_t SE[4];
    affine_transform_t FE[4];

    //lookup table
    uint32_t Table[SM4_NUM_ROUNDS][4][256];
}Sm4Whitebox;

void initMatrixL(NTL::mat_GF2 &csl_matrix);
void sm4_wb_gen_secrect_sbox(sm4_context *sm4_key);
void sm4_wb_gen_affine(Sm4Whitebox* sm4_wb_ctx);
void sm4_wb_combine_tables(Sm4Whitebox* sm4_wb_ctx,NTL::mat_GF2 csl_matrix);
void sm4_wb_gen_tables(uint8_t *key, Sm4Whitebox *sm4_wb_ctx);

#endif