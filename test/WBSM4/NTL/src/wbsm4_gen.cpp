#include "matrixlib/wbsm4.h"
#include "matrixlib/sbox.h"

//operation matrix
affine_transform_t P[SM4_NUM_ROUNDS+4][2];
affine_transform_t E[SM4_NUM_ROUNDS+4][5][2];
affine_transform_t Q[SM4_NUM_ROUNDS+4][2];

uint8_t skbox_enc[SM4_NUM_ROUNDS][4][256];

long sm4_csl_xor_matrix[32] = {(long)0xA0202080, (long)0x50101040, (long)0x28080820, (long)0x14040410, (long)0xA020208, (long)0x5010104, (long)0x2808082, (long)0x1404041, (long)0x80A02020, (long)0x40501010, (long)0x20280808, (long)0x10140404, (long)0x80A0202, (long)0x4050101, (long)0x82028080, (long)0x41014040, (long)0x2080A020, (long)0x10405010, (long)0x8202808, (long)0x4101404, (long)0x2080A02, (long)0x1040501, (long)0x80820280, (long)0x40410140, (long)0x202080A0, (long)0x10104050, (long)0x8082028, (long)0x4041014, (long)0x202080A, (long)0x1010405, (long)0x80808202, (long)0x40404101};
void initMatrixL(NTL::mat_GF2 &csl_matrix)
{
    csl_matrix.SetDims(32, 32);
    initMatrixFromBit(csl_matrix, sm4_csl_xor_matrix);
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
#define RANDOM_AFFINE_MAT(x, xi, y, yi, d)   genRandomAffineMatrix(x, xi, y, d);\
        yi = xi*y

void sm4_wb_gen_affine(Sm4Whitebox* sm4_wb_ctx)
{
    int i,j;
    int rounds = 32 + 4;
    for (i=0; i<rounds; i++) {
        //gen P affine matrix
        RANDOM_AFFINE_MAT(P[i][0].linearMap, P[i][1].linearMap, P[i][0].vectorTranslation, P[i][1].vectorTranslation, 32);
        //gen E affine matrix
        for (j=0; j<4; j++) {
            RANDOM_AFFINE_MAT(E[i][j][0].linearMap, E[i][j][1].linearMap, E[i][j][0].vectorTranslation, E[i][j][1].vectorTranslation, 8);
        }
        NTL::mat_GF2 T,S;
        combineDiagMat(T, E[i][0][0].linearMap, E[i][1][0].linearMap);
        combineDiagMat(S, T, E[i][2][0].linearMap);
        combineDiagMat(E[i][4][0].linearMap, S, E[i][3][0].linearMap);
        inv(E[i][4][1].linearMap, E[i][4][0].linearMap);
        E[i][4][0].vectorTranslation.SetLength(32);
        for (j=0; j<32; j++) {
            E[i][4][0].vectorTranslation.put(j, E[i][j/8][0].vectorTranslation.get(j%8));
        }
        E[i][4][1].vectorTranslation = E[i][4][1].linearMap * E[i][4][0].vectorTranslation;

        //gen Q affine matrix
        RANDOM_AFFINE_MAT(Q[i][0].linearMap, Q[i][1].linearMap, Q[i][0].vectorTranslation, Q[i][1].vectorTranslation, 32);
    }
}
void sm4_wb_combine_tables(Sm4Whitebox* sm4_wb_ctx,NTL::mat_GF2 csl_matrix)
{
    int i,j;
    int rounds = 32;
    for (i=0; i<rounds; i++) {

        //part 1. gen M affine matrix
        sm4_wb_ctx->M[i][0].linearMap = E[i][4][1].linearMap * P[i + 1][1].linearMap;
        sm4_wb_ctx->M[i][0].vectorTranslation =    E[i][4][1].linearMap * (P[i + 1][1].vectorTranslation) + \
                                                    E[i][4][1].vectorTranslation ;

        sm4_wb_ctx->M[i][1].linearMap = E[i][4][1].linearMap * P[i + 2][1].linearMap;
        sm4_wb_ctx->M[i][1].vectorTranslation =    E[i][4][1].linearMap * (P[i + 2][1].vectorTranslation) + \
                                                    E[i][4][1].vectorTranslation ;

        sm4_wb_ctx->M[i][2].linearMap = E[i][4][1].linearMap * P[i + 3][1].linearMap;
        sm4_wb_ctx->M[i][2].vectorTranslation =    E[i][4][1].linearMap * (P[i + 3][1].vectorTranslation) + \
                                                    E[i][4][1].vectorTranslation ;


        //part 2. gen Q combine L into 4 matrix
        NTL::mat_GF2 QL;

        QL = Q[i][0].linearMap * csl_matrix;
        NTL::mat_GF2 QLi[4];
        for (j=0; j<4; j++) {
            QLi[j].SetDims(32, 8);
            for (int ii=0; ii<32; ii++) {
                for (int jj=0; jj<8; jj++) {
                    QLi[j].put(ii, jj, QL.get(ii, j*8+jj));
                }
            }
        }

        int k,d;
        uint32_t r = get32FromVec(Q[i][0].vectorTranslation);

        for (k=0; k<256; k++) {

            for (int d=0; d<4; d++) {
                NTL::vec_GF2 kv;
                int kd; 
                initVecFromBit(kv, k, 8);
                kv = E[i][d][0].linearMap * kv + E[i][d][0].vectorTranslation;
                kd = skbox_enc[i][d][getDigitalFromVec(kv)];
                initVecFromBit(kv, kd, 8);
                
                NTL::vec_GF2 dest;
                dest = QLi[d]*kv;
                uint32_t result = get32FromVec(dest);
                
                sm4_wb_ctx->Table[i][d][k] = result;
            }
            sm4_wb_ctx->Table[i][3][k] = sm4_wb_ctx->Table[i][3][k] ^ r;
            
        }

        //part 3. gen C D matrix, C for Xi0, D for T(Xi1+Xi2+Xi3+rk)
        
        sm4_wb_ctx->C[i].linearMap =   P[i+4][0].linearMap * \
                                        P[i][1].linearMap;
        sm4_wb_ctx->C[i].vectorTranslation =   P[i+4][0].vectorTranslation + \
                                                P[i+4][0].linearMap * \
                                                P[i][1].vectorTranslation;

        sm4_wb_ctx->D[i].linearMap =   P[i+4][0].linearMap * \
                                        Q[i][1].linearMap;
        sm4_wb_ctx->D[i].vectorTranslation =   P[i+4][0].vectorTranslation + \
                                                P[i+4][0].linearMap * \
                                                Q[i][1].vectorTranslation;

        sm4_wb_ctx->D[i].vectorTranslation =   P[i+4][0].vectorTranslation + \
                                                sm4_wb_ctx->D[i].vectorTranslation;

    }
    //external encoding

    for (int i=0; i<4; i++) {
        sm4_wb_ctx->SE[i].linearMap = P[i][0].linearMap;
        sm4_wb_ctx->SE[i].vectorTranslation = P[i][0].vectorTranslation;

        sm4_wb_ctx->FE[i].linearMap = P[rounds+i][1].linearMap;
        sm4_wb_ctx->FE[i].vectorTranslation = P[rounds+i][1].vectorTranslation;
    }

}
void sm4_wb_gen_tables(uint8_t *key, Sm4Whitebox *sm4_wb_ctx)
{
    sm4_context ctx;
    sm4_setkey_enc(&ctx, key);
    sm4_wb_gen_secrect_sbox(&ctx);
    sm4_wb_gen_affine(sm4_wb_ctx);
    NTL::mat_GF2 csl_matrix;
    initMatrixL(csl_matrix);
    sm4_wb_combine_tables(sm4_wb_ctx,csl_matrix);
}