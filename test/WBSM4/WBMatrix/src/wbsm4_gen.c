#include "wbsm4.h"
#include "sbox.h"

uint32_t identM32[32]={0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
unsigned long sm4_csl_xor_matrix[32] = {0xA0202080, 0x50101040, 0x28080820, 0x14040410, 0xA020208, 0x5010104, 0x2808082, 0x1404041, 0x80A02020, 0x40501010, 0x20280808, 0x10140404, 0x80A0202, 0x4050101, 0x82028080, 0x41014040, 0x2080A020, 0x10405010, 0x8202808, 0x4101404, 0x2080A02, 0x1040501, 0x80820280, 0x40410140, 0x202080A0, 0x10104050, 0x8082028, 0x4041014, 0x202080A, 0x1010405, 0x80808202, 0x40404101};
void initMatrixL(M32 *csl_matrix)
{
    for(int i=0;i<32;i++)
    {
        (*csl_matrix).M[i]=sm4_csl_xor_matrix[i];
    }
}
void sm4_wb_gen_secrect_sbox(sm4_context *sm4_key) {
    uint8_t *sst;
    uint32_t key[32];
    for(int i=0;i<32;i++)
    {
        key[i]=sm4_key->sk[i];
    }
    uint32_t *rk = key;
    sst = (uint8_t*)skbox_enc;
    for (int i=0; i< 32; i++) {
        for (int j=0; j<256; j++) {
            sst[   0 + j ] = SBOX[ j ^ ((rk[i] >> 24) & 0xff) ];///[][0][j]
            sst[ 256 + j ] = SBOX[ j ^ ((rk[i] >> 16) & 0xff) ];///[][1][j]
            sst[ 512 + j ] = SBOX[ j ^ ((rk[i] >>  8) & 0xff) ];///[][2][j]
            sst[ 768 + j ] = SBOX[ j ^ ((rk[i]      ) & 0xff) ];///[][3][j]
        } 
        sst += 1024;///下一轮
    }
}
void sm4_wb_gen_affine(Sm4Whitebox* sm4_wb_ctx)
{
    int i,j;
    int rounds = 32 + 4;
    for (i=0; i<rounds; i++) {
        //gen P affine matrix
          genaffinepairM32(&P[i][0],&P[i][1]);

        //gen E affine matrix
        for (j=0; j<4; j++) {
            genaffinepairM8(&E[i][j][0],&E[i][j][1]);
        }

          // combine 4 E8 to 1 E32
        affinecomM8to32(E[i][0][1], E[i][1][1], E[i][2][1], E[i][3][1], &EC[i][1]);


        genaffinepairM32(&Q[i][0], &Q[i][1]);


    }
}
void sm4_wb_combine_tables(Sm4Whitebox* sm4_wb_ctx,M32 csl_matrix)
{
    int i,j;
    int rounds = 32;
    for (i=0; i<rounds; i++) {

        //part 1. gen M affine matrix

        affinemixM32(EC[i][1], P[i+1][1], &sm4_wb_ctx->M[i][0]);
        affinemixM32(EC[i][1], P[i+2][1], &sm4_wb_ctx->M[i][1]);
        affinemixM32(EC[i][1], P[i+3][1], &sm4_wb_ctx->M[i][2]);

        //part 2. gen Q combine L into 4 matrix

        M32 QL;
        MatMulMatM32(Q[i][0].Mat, csl_matrix, &QL);
        M32 QLi[4];
        for(j = 0; j<4; j++){
            for (int ii=0; ii<32; ii++) {
                    QLi[j].M[ii] = (uint8_t)(QL.M[ii] >> (8 * j));
            }
        }

        int k;
        uint32_t r = Q[i][0].Vec.V;

        for (k=0; k<256; k++) {

            for (int d=0; d<4; d++) {

               int kd =  affineU8(E[i][d][0], k);


                kd = skbox_enc[i][d][kd];

                uint32_t temp = 0;
                for(int ii = 0; ii<32;ii++){
                    if(xorU8((uint8_t)(QLi[3-d].M[ii]) & kd)) temp ^= identM32[ii];

                }

                sm4_wb_ctx->Table[i][d][k] = temp;

            }

            sm4_wb_ctx->Table[i][3][k] = sm4_wb_ctx->Table[i][3][k] ^ r;

        }

        //part 3. gen C D matrix, C for Xi0, D for T(Xi1+Xi2+Xi3+rk)

        affinemixM32(P[i+4][0], P[i][1], &sm4_wb_ctx->C[i]);

        affinemixM32(P[i+4][0], Q[i][1], &sm4_wb_ctx->D[i]);

        sm4_wb_ctx->D[i].Vec.V ^= P[i+4]->Vec.V ;


    }

    //external encoding

    for (int i=0; i<4; i++) {

        sm4_wb_ctx->SE[i].Mat = P[i][0].Mat;
        sm4_wb_ctx->SE[i].Vec = P[i][0].Vec;

        sm4_wb_ctx->FE[i].Mat = P[rounds+i][1].Mat;
        sm4_wb_ctx->FE[i].Vec = P[rounds+i][1].Vec;
    }

}
void sm4_wb_gen_tables(uint8_t *key, Sm4Whitebox *sm4_wb_ctx)
{
    sm4_context ctx;
    sm4_setkey_enc(&ctx, key);
    sm4_wb_gen_secrect_sbox(&ctx);
    sm4_wb_gen_affine(sm4_wb_ctx);
    M32 csl_matrix;
    initMatrixL(&csl_matrix);
    sm4_wb_combine_tables(sm4_wb_ctx,csl_matrix);
}