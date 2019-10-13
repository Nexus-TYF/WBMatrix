#include <WBMatrix/WBMatrix.h>
#include <m4ri/matrix_gf2.h>
#include <m4ri/affine_transform.h>
#include <m4ri/wrandom.h>
#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)

//Repeat test times and calculate on average for accuracy
#define TEST 2000000

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
int WBM_TEST()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    M8 Mat1;
    V8 Vec1;
    V8 Vec2;
    randM8(&Mat1);
    randV8(&Vec1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM8(Mat1,Vec1,&Vec2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 Mat mul 8*1 Vec cost %llu CPU cycles\n", (ans) / TEST);

    Aff8 aff1,aff1_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        affinepairM8(&aff1,&aff1_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 Affine and its inversion Affine cost %llu CPU cycles\n", (ans) / TEST);

    M8 Mat2,Mat3,Mat4;
    randM8(&Mat2);
    randM8(&Mat3);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM8(Mat2,Mat3,&Mat4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 Mat mul 8*8 Mat cost %llu CPU cycles\n", (ans) / TEST);

    uint8_t t=222;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       affineU8(aff1,&t);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8bits affine transformation cost %llu CPU cycles\n", (ans) / TEST);

    M8 Mat5,Mat5_trans;
    randM8(&Mat5);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       MattransM8(Mat5,&Mat5_trans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 Mat tansposition cost %llu CPU cycles\n", (ans) / TEST);

    Aff8 aff2,aff2_inv,aff3;
    affinepairM8(&aff2,&aff2_inv);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       affinemixM8(aff1_inv,aff2,&aff3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8bits affine mixture cost %llu CPU cycles\n\n", (ans) / TEST);

    M32 Mat32_1;
    V32 Vec32_1;
    V32 Vec32_2;
    randM32(&Mat32_1);
    randV32(&Vec32_1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM32(Mat32_1,Vec32_1,&Vec32_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 Mat mul 32*1 Vec cost %llu CPU cycles\n", (ans) / TEST);

    Aff32 aff32_1,aff32_1_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        affinepairM32(&aff32_1,&aff32_1_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 Affine and its inversion Affine cost %llu CPU cycles\n", (ans) / TEST);

    uint32_t r=0x12345678;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       affineU32(aff32_1,&r);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32bits affine transformation cost %llu CPU cycles\n", (ans) / TEST);
    return 0;
}


int M4RI_TEST()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    MatGf2 Mat1;
    uint8_t vec1 = 22;
    uint8_t vec2;
    Mat1 = GenRandomMatGf2(8,8);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulU8(Mat1,vec1);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  8*8 Mat mul 8*1 Vec cost %llu CPU cycles\n", (ans) / TEST);

     AffineTransform aff1, aff1_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       GenIndAffineTransform(&aff1,&aff1_inv,8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  generate 8*8 Affine and its inversion Affine cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 Mat2,Mat3,Mat4;
    Mat2 = GenRandomMatGf2(8,8);

    Mat3 = GenRandomMatGf2(8,8);

    Mat4 = NULL;
    begin = start_rdtsc();


    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(Mat2,Mat3,&Mat4);
        
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  8*8 Mat mul 8*8 Mat cost %llu CPU cycles\n", (ans) / TEST);

    uint8_t t=222;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       ApplyAffineToU8(aff1,t);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  8bits affine transformation cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 Mat5,Mat5_trans;
    Mat5=GenRandomMatGf2(8,8);
    Mat5_trans = NULL;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Transpose(Mat5,&Mat5_trans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI 8*8 Mat tansposition cost %llu CPU cycles\n", (ans) / TEST);

    Aff8 aff2,aff2_inv,aff3;
    affinepairM8(&aff2,&aff2_inv);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
    //    
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf(" M4RI  ---------", (ans) / TEST);

    MatGf2 Mat32_1;
    uint32_t Vec32_1 = 222222;
    uint32_t Vec32_2;
   Mat32_1 =  GenRandomMatGf2(32,32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulU32(Mat32_1,Vec32_1);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  32*32 Mat mul 32*1 Vec cost %llu CPU cycles\n", (ans) / TEST);

    AffineTransform aff32_1,aff32_1_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        GenIndAffineTransform(&aff32_1,&aff32_1_inv,32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  generate 32*32 Affine and its inversion Affine cost %llu CPU cycles\n", (ans) / TEST);

    uint32_t r=0x12345678;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
       ApplyAffineToU32(aff32_1,&r);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("M4RI  32bits affine transformation cost %llu CPU cycles\n", (ans) / TEST);
    return 0;
}

int main(){
    WBM_TEST();
    M4RI_TEST();
}