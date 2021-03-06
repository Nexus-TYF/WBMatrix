//matrix operation test of WBMatrix
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
    printf("WBMatrix Matrix performance test:\n");
    
    M4 Mat4;
    randM4(&Mat4);
    V4 Vec4, Vec4_ans;
    randV4(&Vec4);
    printf("matrix-vector mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM4(Mat4, Vec4, &Vec4_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - 4*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M8 Mat8;
    randM8(&Mat8);
    V8 Vec8, Vec8_ans;
    randV8(&Vec8);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM8(Mat8, Vec8, &Vec8_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - 8*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M16 Mat16;
    randM16(&Mat16);
    V16 Vec16, Vec16_ans;
    randV16(&Vec16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM16(Mat16, Vec16, &Vec16_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - 16*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M32 Mat32;
    randM32(&Mat32);
    V32 Vec32, Vec32_ans;
    randV32(&Vec32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM32(Mat32, Vec32, &Vec32_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - 32*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M64 Mat64;
    randM64(&Mat64);
    V64 Vec64, Vec64_ans;
    randV64(&Vec64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM64(Mat64, Vec64, &Vec64_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - 64*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M128 Mat128;
    randM128(&Mat128);
    V128 Vec128, Vec128_ans;
    randV128(&Vec128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM128(Mat128, Vec128, &Vec128_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - 128*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M256 Mat256;
    randM256(&Mat256);
    V256 Vec256, Vec256_ans;
    randV256(&Vec256);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM256(Mat256, Vec256, &Vec256_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("256*256 matrix - 256*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    M4 M4_1, M4_2, M4_3;
    genMatpairM4(&M4_1, &M4_2);
    printf("\nmatrix-matrix mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM4(M4_1, M4_2, &M4_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M8 M8_1, M8_2, M8_3;
    genMatpairM8(&M8_1, &M8_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM8(M8_1, M8_2, &M8_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M16 M16_1, M16_2, M16_3;
    genMatpairM16(&M16_1, &M16_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM16(M16_1, M16_2, &M16_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M32 M32_1, M32_2, M32_3;
    genMatpairM32(&M32_1, &M32_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM32(M32_1, M32_2, &M32_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M64 M64_1, M64_2, M64_3;
    genMatpairM64(&M64_1, &M64_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM64(M64_1, M64_2, &M64_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M128 M128_1, M128_2, M128_3;
    genMatpairM128(&M128_1, &M128_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM128(M128_1, M128_2, &M128_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    M256 M256_1, M256_2, M256_3;
    genMatpairM256(&M256_1, &M256_2);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulMatM256(M256_1, M256_2, &M256_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("256*256 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    V4 V4_1, V4_2, V4_3;
    printf("\nvector-vector add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV4(V4_1, V4_2, &V4_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V8 V8_1, V8_2, V8_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV8(V8_1, V8_2, &V8_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V16 V16_1, V16_2, V16_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV16(V16_1, V16_2, &V16_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V32 V32_1, V32_2, V32_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV32(V32_1, V32_2, &V32_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V64 V64_1, V64_2, V64_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV64(V64_1, V64_2, &V64_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V128 V128_1, V128_2, V128_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV128(V128_1, V128_2, &V128_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    V256 V256_1, V256_2, V256_3;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        VecAddVecV256(V256_1, V256_2, &V256_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("256*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    printf("\nmatrix-matrix add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM4(M4_1, M4_2, &M4_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("4*4 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM8(M8_1, M8_2, &M8_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM16(M16_1, M16_2, &M16_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM32(M32_1, M32_2, &M32_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM64(M64_1, M64_2, &M64_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM128(M128_1, M128_2, &M128_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatAddMatM256(M256_1, M256_2, &M256_3);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("256*256 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}