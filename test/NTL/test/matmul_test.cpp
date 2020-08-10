#include<RandMat.h>
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
    printf("NTL Matrix performance test:\n");
    
    RandMat M4;
    M4.init(4);
    vec_GF2 V4_1, V4_2;
    initVec(V4_1, 4);
    V4_2.SetLength(4);
    printf("matrix-vector mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V4_2 = M4.mat * V4_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - 4*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M8;
    M8.init(8);
    vec_GF2 V8_1, V8_2;
    initVec(V8_1, 8);
    V8_2.SetLength(8);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V8_2 = M8.mat * V8_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - 8*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    RandMat M16;
    M16.init(16);
    vec_GF2 V16_1, V16_2;
    initVec(V16_1, 16);
    V16_2.SetLength(16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V16_2 = M16.mat * V16_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - 8*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    RandMat M32;
    M32.init(32);
    vec_GF2 V32_1, V32_2;
    V32_2.SetLength(32);
    initVec(V32_1, 32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V32_2 = M32.mat * V32_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - 32*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    RandMat M64;
    M64.init(64);
    vec_GF2 V64_1, V64_2;
    initVec(V64_1, 64);
    V64_2.SetLength(64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V64_2 = M64.mat * V64_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - 64*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    RandMat M128;
    M128.init(128);
    vec_GF2 V128_1, V128_2;
    initVec(V128_1, 128);
    V128_2.SetLength(128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V128_2 = M128.mat * V128_1;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - 128*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    RandMat M4_1, M4_2;
    M4_1.init(8);
    M4_2.init(8);
    printf("\nmatrix-matrix mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M4_2.mat = M4_1.mat * M4_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M8_1, M8_2;
    M8_1.init(8);
    M8_2.init(8);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M8_2.mat = M8_1.mat * M8_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M16_1, M16_2;
    M16_1.init(16);
    M16_2.init(16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M16_2.mat = M16_1.mat * M16_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M32_1, M32_2;
    M32_1.init(32);
    M32_2.init(32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M32_2.mat = M32_1.mat * M32_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M64_1, M64_2;
    M64_1.init(64);
    M64_2.init(64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M64_2.mat = M64_1.mat * M64_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    RandMat M128_1, M128_2;
    M128_1.init(128);
    M128_2.init(128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M128_2.mat = M128_1.mat * M128_1.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V4_3;
    printf("\nvector-vector add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V4_3 = V4_1 + V4_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V8_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V8_3 = V8_1 + V8_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V16_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V16_3 = V16_1 + V16_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V32_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V32_3 = V32_1 + V32_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V64_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V64_3 = V64_1 + V64_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    vec_GF2 V128_3;
    V128_3.SetLength(128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V128_3 = V128_1 + V128_2;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    printf("\nmatrix-matrix add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M4.invMat = M4_1.invMat + M4_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M8.invMat = M8_1.invMat + M8_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M16.invMat = M16_1.invMat + M16_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M32.invMat = M32_1.invMat + M32_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M64.invMat = M64_1.invMat + M64_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M128.invMat = M128_1.invMat + M128_2.invMat;
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}