#include "matrixlib/wbsm4.h"
#include "matrixlib/sbox.h"

unsigned long sm4_csl_xor_matrix[32] = {0xA0202080, 0x50101040, 0x28080820, 0x14040410, 0xA020208, 0x5010104, 0x2808082, 0x1404041, 0x80A02020, 0x40501010, 0x20280808, 0x10140404, 0x80A0202, 0x4050101, 0x82028080, 0x41014040, 0x2080A020, 0x10405010, 0x8202808, 0x4101404, 0x2080A02, 0x1040501, 0x80820280, 0x40410140, 0x202080A0, 0x10104050, 0x8082028, 0x4041014, 0x202080A, 0x1010405, 0x80808202, 0x40404101};
void initMatrixL(MatGf2 csl_matrix)
{
    InitMatrixFromBitArray(sm4_csl_xor_matrix, csl_matrix);
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
    MatGf2 temp = NULL;
    int rounds = 32 + 4;
    for (i=0; i<rounds; i++) {
        //gen P affine matrix
        GenRandomAffineTransform(&P[i][0], &P[i][1], 32);///pi及pi逆

        //gen E affine matrix
        for (j=0; j<4; j++) {
            GenRandomAffineTransform(&E[i][j][0], &E[i][j][1], 8);///Ei[0~3]及逆

        }
        MatGf2 T,S;
        T = S = NULL;
        MatGf2Diag(E[i][0][0].linear_map, E[i][1][0].linear_map, &T);
        MatGf2Diag(T, E[i][2][0].linear_map, &S);
        E[i][4][0].linear_map = GenMatGf2Diag(S, E[i][3][0].linear_map);
        E[i][4][1].linear_map = GenMatGf2Inv(E[i][4][0].linear_map);
        E[i][4][0].vector_translation = GenMatGf2(32, 1);
        for (j=0; j<32; j++) {
            MatGf2Set(E[i][4][0].vector_translation, j, 0, MatGf2Get(E[i][j/8][0].vector_translation, j%8, 0));
        }
        E[i][4][1].vector_translation = NULL;
        MatGf2Mul( E[i][4][1].linear_map, E[i][4][0].vector_translation, &E[i][4][1].vector_translation);

        //gen Q affine matrix
        GenRandomAffineTransform(&Q[i][0], &Q[i][1], 32);///Qi[0~3]及逆
        MatGf2Free(T);
        MatGf2Free(S);
        T = S = NULL;
    }
    MatGf2Free(temp);
    temp = NULL;
}
void sm4_wb_combine_tables(Sm4Whitebox* sm4_wb_ctx,MatGf2 csl_matrix)
{
    int i,j;
    MatGf2 temp = NULL;
    MatGf2 kv = NULL;
    MatGf2 dest = NULL;
    int rounds = 32;
    for (i=0; i<rounds; i++) {

        //part 1. gen M affine matrix
        sm4_wb_ctx->M[i][0].linear_map = GenMatGf2Mul( E[i][4][1].linear_map, P[i + 1][1].linear_map);
        sm4_wb_ctx->M[i][0].vector_translation =   GenMatGf2Add( MatGf2Mul( E[i][4][1].linear_map, P[i + 1][1].vector_translation, &temp), \
                                                    E[i][4][1].vector_translation) ;

        sm4_wb_ctx->M[i][1].linear_map = GenMatGf2Mul( E[i][4][1].linear_map, P[i + 2][1].linear_map);
        sm4_wb_ctx->M[i][1].vector_translation =    GenMatGf2Add( MatGf2Mul( E[i][4][1].linear_map, P[i + 2][1].vector_translation, &temp), \
                                                    E[i][4][1].vector_translation) ;

        sm4_wb_ctx->M[i][2].linear_map = GenMatGf2Mul( E[i][4][1].linear_map, P[i + 3][1].linear_map);
        sm4_wb_ctx->M[i][2].vector_translation =    GenMatGf2Add( MatGf2Mul( E[i][4][1].linear_map, P[i + 3][1].vector_translation, &temp), \
                                                    E[i][4][1].vector_translation) ;


        //part 2. gen Q combine L into 4 matrix
        MatGf2 QL;

        QL = GenMatGf2Mul( Q[i][0].linear_map, csl_matrix);
        MatGf2 QLi[4];
        for (j=0; j<4; j++) {
            QLi[j] = GenMatGf2(32, 8);
            for (int ii=0; ii<32; ii++) {
                for (int jj=0; jj<8; jj++) {
                    MatGf2Set( QLi[j], ii, jj, MatGf2Get(QL, ii, j*8+jj));
                }
            }
        }

        int k;
        uint32_t r = get32FromVec(Q[i][0].vector_translation);

        for (k=0; k<256; k++) {

            for (int d=0; d<4; d++) {
                int kd;
                ReAllocatedMatGf2(8,1, &kv);///8*1矩阵
                InitVecFromBit(k, kv);///k转化成矩阵
                ///Ei操作
                MatGf2Add( MatGf2Mul( E[i][d][0].linear_map, kv, &temp), E[i][d][0].vector_translation, &kv);
                ///进s盒
                kd = skbox_enc[i][d][getDigitalFromVec(kv)];
                InitVecFromBit(kd, kv);
                
                MatGf2Mul( QLi[d], kv, &dest);///L
                uint32_t result = get32FromVec(dest);
                
                sm4_wb_ctx->Table[i][d][k] = result;
            }
            sm4_wb_ctx->Table[i][3][k] = sm4_wb_ctx->Table[i][3][k] ^ r;///Q
            
        }
        MatGf2Free(QL);
        MatGf2Free(QLi[0]);
        MatGf2Free(QLi[1]);
        MatGf2Free(QLi[2]);
        MatGf2Free(QLi[3]);
        QL = QLi[0] = QLi[1] = QLi[2] = QLi[3] = NULL;

        //part 3. gen C D matrix, C for Xi0, D for T(Xi1+Xi2+Xi3+rk)
        
        sm4_wb_ctx->C[i].linear_map =   GenMatGf2Mul( P[i+4][0].linear_map, \
                                        P[i][1].linear_map);
        sm4_wb_ctx->C[i].vector_translation =   GenMatGf2Add( P[i+4][0].vector_translation, \
                                                MatGf2Mul(P[i+4][0].linear_map, \
                                                P[i][1].vector_translation, &temp));

        sm4_wb_ctx->D[i].linear_map =   GenMatGf2Mul( P[i+4][0].linear_map, \
                                        Q[i][1].linear_map);
        sm4_wb_ctx->D[i].vector_translation =   GenMatGf2Add( P[i+4][0].vector_translation, \
                                                MatGf2Mul(P[i+4][0].linear_map, \
                                                Q[i][1].vector_translation, &temp));

        sm4_wb_ctx->D[i].vector_translation =   MatGf2Add( P[i+4][0].vector_translation, \
                                                sm4_wb_ctx->D[i].vector_translation, &sm4_wb_ctx->D[i].vector_translation);
//        sm4_wb_ctx->D[i].vector_translation =   GenMatGf2Add( P[i+4][0].vector_translation, \
                                                          sm4_wb_ctx->D[i].vector_translation);

    }


    //external encoding

    for (int i=0; i<4; i++) {
        sm4_wb_ctx->SE[i].linear_map = GenMatGf2Copy(P[i][0].linear_map);
        sm4_wb_ctx->SE[i].vector_translation = GenMatGf2Copy(P[i][0].vector_translation);

        sm4_wb_ctx->FE[i].linear_map = GenMatGf2Copy(P[rounds+i][1].linear_map);
        sm4_wb_ctx->FE[i].vector_translation = GenMatGf2Copy(P[rounds+i][1].vector_translation);
    }

    MatGf2Free(temp);
    MatGf2Free(kv);
    MatGf2Free(dest);
    temp = kv = dest = NULL;
}
void sm4_wb_gen_tables(uint8_t *key, Sm4Whitebox *sm4_wb_ctx)
{
    sm4_context ctx;
    sm4_setkey_enc(&ctx, key);
    sm4_wb_gen_secrect_sbox(&ctx);
    sm4_wb_gen_affine(sm4_wb_ctx);
    MatGf2 csl_matrix;
    csl_matrix = GenMatGf2(32, 32);
    initMatrixL(csl_matrix);
    sm4_wb_combine_tables(sm4_wb_ctx,csl_matrix);
    MatGf2Free(csl_matrix);
}