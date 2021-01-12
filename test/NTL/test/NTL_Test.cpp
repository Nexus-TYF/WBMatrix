#include <RandMat.h>
#include <stdio.h>
#include <stdint.h>

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

    printf("NTL test:\n");
/*
    printf("Inverible\n");
    mat_GF2 Tm4;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm4, 4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 4*4 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Tm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm8, 8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Tm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm16, 16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Tm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm32, 32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Tm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm64, 64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Tm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Tm128, 128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    printf("\nInverse\n");
    mat_GF2 Im4[TEST], Sm4;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im4[i], 4);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm4 = inv(Im4[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 4*4 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Im8[TEST], Sm8;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im8[i], 8);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm8 = inv(Im8[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 8*8 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Im16[TEST], Sm16;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im16[i], 16);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm16 = inv(Im16[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 16*16 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Im32[TEST], Sm32;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im32[i], 32);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm32 = inv(Im32[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 32*32 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Im64[TEST], Sm64;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im64[i], 64);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm64 = inv(Im64[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 64*64 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    mat_GF2 Im128[TEST], Sm128;
    for (i = 0; i < TEST; i++)
    {
        InvTMat(Im128[i], 128);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Sm128 = inv(Im128[i]);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 128*128 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
*/
    printf("\nInvertible and Inverse\n");
    RandMat m4;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m4.init(4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 4*4 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m8.init(8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m16.init(16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m32.init(32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m64.init(64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m128.init(128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    RandMat m256;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        m256.init(256);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 256*256 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

	return 0;
}