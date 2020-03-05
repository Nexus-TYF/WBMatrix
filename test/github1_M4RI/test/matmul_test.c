#include <matrixlib/matrix_gf2.h>
#include <stdio.h>

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
    printf("M4RI Matrix performance test:\n");
    
    MatGf2 M8,V8,V8_ans;
    V8 = GenMatGf2(8, 1);
    V8_ans = GenMatGf2(8, 1);
    RandomMatGf2(V8);
    M8 = GenMatGf2(8, 8);
    RandomMatGf2(M8);
    printf("matrix-vector mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(M8,V8,&V8_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - 8*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    MatGf2 M16,V16,V16_ans;
    V16 = GenMatGf2(16, 1);
    V16_ans = GenMatGf2(16, 1);
    RandomMatGf2(V16);
    M16 = GenMatGf2(16, 16);
    RandomMatGf2(M16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(M16,V16,&V16_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - 16*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    MatGf2 M32,V32,V32_ans;
    V32 = GenMatGf2(32, 1);
    V32_ans = GenMatGf2(32, 1);
    RandomMatGf2(V32);
    M32 = GenMatGf2(32, 32);
    RandomMatGf2(M32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(M32,V32,&V32_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - 32*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    MatGf2 M64,V64,V64_ans;
    V64 = GenMatGf2(64, 1);
    V64_ans = GenMatGf2(64, 1);
    RandomMatGf2(V64);
    M64 = GenMatGf2(64, 64);
    RandomMatGf2(M64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(M64,V64,&V64_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - 64*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    MatGf2 M128,V128,V128_ans;
    V128 = GenMatGf2(128, 1);
    V128_ans = GenMatGf2(128, 1);
    RandomMatGf2(V128);
    M128 = GenMatGf2(128, 128);
    RandomMatGf2(M128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatGf2Mul(M128,V128,&V128_ans);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - 128*1 vector multiplication cost %llu CPU cycles\n", (ans) / TEST);
    
    MatGf2 M8_1,M8_2,M8_ans;
    M8_1 = GenMatGf2(8, 8);
    M8_2 = GenMatGf2(8, 8);
    RandomMatGf2(M8_1);
    RandomMatGf2(M8_2);
    M8_ans = GenMatGf2(8, 8);
    printf("\nmatrix-matrix mul\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M8_ans = GenMatGf2Mul(M8_1,M8_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M16_1,M16_2,M16_ans;
    M16_1 = GenMatGf2(16, 16);
    M16_2 = GenMatGf2(16, 16);
    RandomMatGf2(M16_1);
    RandomMatGf2(M16_2);
    M16_ans = GenMatGf2(16, 16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M16_ans = GenMatGf2Mul(M16_1,M16_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M32_1,M32_2,M32_ans;
    M32_1 = GenMatGf2(32, 32);
    M32_2 = GenMatGf2(32, 32);
    RandomMatGf2(M32_1);
    RandomMatGf2(M32_2);
    M32_ans = GenMatGf2(32, 32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M32_ans = GenMatGf2Mul(M32_1,M32_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M64_1,M64_2,M64_ans;
    M64_1 = GenMatGf2(64, 64);
    M64_2 = GenMatGf2(64, 64);
    RandomMatGf2(M64_1);
    RandomMatGf2(M64_2);
    M64_ans = GenMatGf2(64, 64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M64_ans = GenMatGf2Mul(M64_1,M64_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M128_1,M128_2,M128_ans;
    M128_1 = GenMatGf2(128, 128);
    M128_2 = GenMatGf2(128, 128);
    RandomMatGf2(M128_1);
    RandomMatGf2(M128_2);
    M128_ans = GenMatGf2(128, 128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M128_ans = GenMatGf2Mul(M128_1,M128_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix multiplication cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 V8_1,V8_2,V8_3;
    V8_1 = GenMatGf2(8, 1);
    V8_2 = GenMatGf2(8, 1);
    RandomMatGf2(V8_1);
    RandomMatGf2(V8_2);
    V8_3 = GenMatGf2(8, 1);
    printf("\nvector-vector add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V8_3 = GenMatGf2Add(V8_1,V8_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 V16_1,V16_2,V16_3;
    V16_1 = GenMatGf2(16, 1);
    V16_2 = GenMatGf2(16, 1);
    RandomMatGf2(V16_1);
    RandomMatGf2(V16_2);
    V16_3 = GenMatGf2(16, 1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V16_3 = GenMatGf2Add(V16_1,V16_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 V32_1,V32_2,V32_3;
    V32_1 = GenMatGf2(32, 1);
    V32_2 = GenMatGf2(32, 1);
    RandomMatGf2(V32_1);
    RandomMatGf2(V32_2);
    V32_3 = GenMatGf2(32, 1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V32_3 = GenMatGf2Add(V32_1,V32_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 V64_1,V64_2,V64_3;
    V64_1 = GenMatGf2(64, 1);
    V64_2 = GenMatGf2(64, 1);
    RandomMatGf2(V64_1);
    RandomMatGf2(V64_2);
    V64_3 = GenMatGf2(64, 1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V64_3 = GenMatGf2Add(V64_1,V64_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 V128_1,V128_2,V128_3;
    V128_1 = GenMatGf2(128, 1);
    V128_2 = GenMatGf2(128, 1);
    RandomMatGf2(V128_1);
    RandomMatGf2(V128_2);
    V128_3 = GenMatGf2(128, 1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        V128_3 = GenMatGf2Add(V128_1,V128_2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*1 vector - vector addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M8_3,M8_4,M8_5;
    M8_3 = GenMatGf2(8, 8);
    M8_4 = GenMatGf2(8, 8);
    RandomMatGf2(M8_3);
    RandomMatGf2(M8_4);
    M8_5 = GenMatGf2(8, 8);
    printf("\nmatrix-matrix add\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M8_5 = GenMatGf2Add(M8_3,M8_4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M16_3,M16_4,M16_5;
    M16_3 = GenMatGf2(16, 16);
    M16_4 = GenMatGf2(16, 16);
    RandomMatGf2(M16_3);
    RandomMatGf2(M16_4);
    M16_5 = GenMatGf2(16, 16);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M16_5 = GenMatGf2Add(M16_3,M16_4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("16*16 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M32_3,M32_4,M32_5;
    M32_3 = GenMatGf2(32, 32);
    M32_4 = GenMatGf2(32, 32);
    RandomMatGf2(M32_3);
    RandomMatGf2(M32_4);
    M32_5 = GenMatGf2(32, 32);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M32_5 = GenMatGf2Add(M32_3,M32_4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("32*32 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M64_3,M64_4,M64_5;
    M64_3 = GenMatGf2(64, 64);
    M64_4 = GenMatGf2(64, 64);
    RandomMatGf2(M64_3);
    RandomMatGf2(M64_4);
    M64_5 = GenMatGf2(64, 64);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M64_5 = GenMatGf2Add(M64_3,M64_4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("64*64 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    MatGf2 M128_3,M128_4,M128_5;
    M128_3 = GenMatGf2(128, 128);
    M128_4 = GenMatGf2(128, 128);
    RandomMatGf2(M128_3);
    RandomMatGf2(M128_4);
    M128_5 = GenMatGf2(128, 128);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        M128_5 = GenMatGf2Add(M128_3,M128_4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("128*128 matrix - matrix addition cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}