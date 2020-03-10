#include "matrixlib/wbsm4.h"
#include "matrixlib/affine_transform.h"
#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)

//Repeat test times and calculate on average for accuracy
#define TEST 100000

//CPU cycles set start;
uint64_t start_rdtsc()
{
    return __rdtsc();
}

//CPU cycles set end;
uint64_t end_rdtsc()
{
    return __rdtsc();
}

#define GET32(pc)  (					\
	((uint32_t)(pc)[0] << 24) ^			\
	((uint32_t)(pc)[1] << 16) ^			\
	((uint32_t)(pc)[2] <<  8) ^			\
	((uint32_t)(pc)[3]))

#define PUT32(st, ct)					\
(ct)[0] = (uint8_t)((st) >> 24);		\
(ct)[1] = (uint8_t)((st) >> 16);		\
(ct)[2] = (uint8_t)((st) >>  8);		\
(ct)[3] = (uint8_t)(st)

#define SK32(A)						\
    ((skbox[0   +  (((A) >> 24) & 0xff)]) ^		\
    (skbox[256 +  (((A) >> 16) & 0xff)]) ^		\
    (skbox[512 +  (((A) >>  8) & 0xff)]) ^		\
    (skbox[768 +  (((A))       & 0xff)]      ))


#define sm4round(x0, x1, x2, x3, x4, i)	\
xt1 = ApplyAffineToU32(sm4_wb_ctx->M[i][0], x1); \
xt2 = ApplyAffineToU32(sm4_wb_ctx->M[i][1], x2); \
xt3 = ApplyAffineToU32(sm4_wb_ctx->M[i][2], x3); \
x4 = xt1 ^ xt2 ^ xt3;			\
x4 = SK32(x4);					        \
skbox += 1024;                         \
xt0 = ApplyAffineToU32(sm4_wb_ctx->C[i], x0); \
xt4 = ApplyAffineToU32(sm4_wb_ctx->D[i], x4); \
x4 = xt0 ^ xt4


void sm4_wb_enc(unsigned char IN[],unsigned char OUT[], Sm4Whitebox *sm4_wb_ctx)
{
    uint32_t x0,x1,x2,x3,x4;
    uint32_t xt0, xt1, xt2, xt3, xt4;
    
    x0 = GET32(IN     );
	x1 = GET32(IN +  4);
	x2 = GET32(IN +  8);
    x3 = GET32(IN + 12);

    uint32_t *skbox;
    x0 = ApplyAffineToU32(sm4_wb_ctx->SE[0], x0);
    x1 = ApplyAffineToU32(sm4_wb_ctx->SE[1], x1);
    x2 = ApplyAffineToU32(sm4_wb_ctx->SE[2], x2);
    x3 = ApplyAffineToU32(sm4_wb_ctx->SE[3], x3);

    skbox = (uint32_t*)sm4_wb_ctx->Table;
    for(int i=0;i<32;i++)
    {
        sm4round(x0, x1, x2, x3, x4, i);
        x0=x1;
        x1=x2;
        x2=x3;
        x3=x4;
    }
    x4 = x2;
    x2 = x0;
    x0 = x3;
    x3 = x1;

    x0 = ApplyAffineToU32(sm4_wb_ctx->FE[3], x0);
    x4 = ApplyAffineToU32(sm4_wb_ctx->FE[2], x4);
    x3 = ApplyAffineToU32(sm4_wb_ctx->FE[1], x3);
    x2 = ApplyAffineToU32(sm4_wb_ctx->FE[0], x2);

    PUT32(x0, OUT     );
	PUT32(x4, OUT +  4);
	PUT32(x3, OUT +  8);
	PUT32(x2, OUT + 12);
}
void printstate(unsigned char * in){
        for(int i = 0; i < 16; i++) {
                printf("%.2X", in[i]);

        }
        printf("\n");

        return;
}
int main()
{
    unsigned char IN[16] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};
    unsigned char key[16] = {0};
    unsigned char OUT[16];
    unsigned char OOUT[16];

    int i;
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;

    Sm4Whitebox sm4_wb_ctx;
    printf("WBSM4-M4RI performance test:\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        sm4_wb_gen_tables(key,&sm4_wb_ctx);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("WBSM4 generate tables cost %llu CPU cycles\n", ans/TEST);
    //printstate(IN);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        sm4_wb_enc(IN,OUT,&sm4_wb_ctx);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("WBSM4 encrypt cost %llu CPU cycles\n", ans/TEST);
    //printstate(OUT);
    ////sm4_context ctx;
    //sm4_setkey_enc(&ctx, key);
    //sm4_crypt_ecb(&ctx, 1, 16, IN, OOUT);
    //printstate(OOUT);
    return 0;
}