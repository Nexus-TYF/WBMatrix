//pairwise invertible matrices test of WBMatrix
#include "WBMatrix/WBMatrix.h"
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

    printf("WBMatrix method performance test\n");
    printf("\nInvertible and Inverse\n");
    M8 m8,m8_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM8(&m8, &m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M16 m16,m16_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM16(&m16, &m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M32 m32,m32_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM32(&m32, &m32_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M64 m64,m64_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM64(&m64, &m64_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M128 m128,m128_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM128(&m128, &m128_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}