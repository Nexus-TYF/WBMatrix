#include "matrixlib/affine_transform.h"
#include "sm4.h"
#define SM4_NUM_ROUNDS 32
//operation matrix
AffineTransform P[SM4_NUM_ROUNDS+4][2];
AffineTransform E[SM4_NUM_ROUNDS+4][5][2];
AffineTransform Q[SM4_NUM_ROUNDS+4][2];

uint8_t skbox_enc[SM4_NUM_ROUNDS][4][256];

typedef struct Sm4Whitebox{
    //Affine
    AffineTransform M[SM4_NUM_ROUNDS][3];
    AffineTransform C[SM4_NUM_ROUNDS];
    AffineTransform D[SM4_NUM_ROUNDS];

    AffineTransform SE[4];
    AffineTransform FE[4];

    //lookup table
    uint32_t Table[SM4_NUM_ROUNDS][4][256];
}Sm4Whitebox;

void initMatrixL(MatGf2 csl_matrix);
void sm4_wb_gen_secrect_sbox(sm4_context *sm4_key);
void sm4_wb_gen_affine(Sm4Whitebox* sm4_wb_ctx);
void sm4_wb_combine_tables(Sm4Whitebox* sm4_wb_ctx,MatGf2 csl_matrix);
void sm4_wb_gen_tables(uint8_t *key, Sm4Whitebox *sm4_wb_ctx);