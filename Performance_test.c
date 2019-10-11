#include "WBMatrix.h"
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
int main()
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