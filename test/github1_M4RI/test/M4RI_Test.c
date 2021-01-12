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

void InvTMatM4(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(4, 4);
}
void InvTMatM8(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(8, 8);
}
void InvTMatM16(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(16, 16);
}
void InvTMatM32(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(32, 32);
}
void InvTMatM64(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(64, 64);
}
void InvTMatM128(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(128, 128);
}
void InvTMatM256(MatGf2 *Mat)
{
    *Mat = GenInvertibleMatGf2(256, 256);
}

void InvSMatM4(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM8(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM16(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM32(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM64(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM128(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}
void InvSMatM256(MatGf2 Mat, MatGf2 *Mat_inv)
{
    *Mat_inv = GenMatGf2Inv(Mat);
}

void genMatpairM4(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(4, 4);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM8(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(8, 8);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM16(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(16, 16);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM32(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(32, 32);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM64(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(64, 64);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM128(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(128, 128);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
void genMatpairM256(MatGf2 *Mat, MatGf2 *Mat_inv)
{
    *Mat = GenInvertibleMatGf2(256, 256);
    *Mat_inv = GenMatGf2Inv(*Mat);
}
int TimesInveribleMatGf2(int r, int c) 
{
	int times = 1;
    MatGf2 mat = GenMatGf2(r, c);
    RandomMatGf2(mat);
    while (IsMatGf2Invertible(mat)==0) 
    {
        RandomMatGf2(mat);
        times++;
    }
    MatGf2Free(mat);
    return times;
}
int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("M4RI Method performance test:\n");
    
    printf("Times\n");
    double times8 = 0.0;
    for (i = 0; i < TEST; i++)
    {
        times8 += TimesInveribleMatGf2(8, 8);
    }
    printf("generate 8*8 invertible matrix cost %f times\n", (times8) / TEST);

    double times16 = 0.0;
    for (i = 0; i < TEST; i++)
    {
        times16 += TimesInveribleMatGf2(16, 16);
    }
    printf("generate 16*16 invertible matrix cost %f times\n", (times16) / TEST);

    double times32 = 0.0;
    for (i = 0; i < TEST; i++)
    {
        times32 += TimesInveribleMatGf2(32, 32);
    }
    printf("generate 32*32 invertible matrix cost %f times\n", (times32) / TEST);

    double times64 = 0.0;
    for (i = 0; i < TEST; i++)
    {
        times64 += TimesInveribleMatGf2(64, 64);
    }
    printf("generate 64*64 invertible matrix cost %f times\n", (times64) / TEST);

    double times128 = 0.0;
    for (i = 0; i < TEST; i++)
    {
        times128 += TimesInveribleMatGf2(128, 128);
    }
    printf("generate 128*128 invertible matrix cost %f times\n", (times128) / TEST);

    printf("\nInverible\n");
    MatGf2 Tm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&Tm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(Tm8);

    MatGf2 Tm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&Tm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(Tm16);

    MatGf2 Tm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&Tm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(Tm32);

    MatGf2 Tm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&Tm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(Tm64);

    MatGf2 Tm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&Tm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(Tm128);
	
    printf("\nInverse\n");
    MatGf2 Im8[TEST],Sm8;
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&Im8[i]);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM8(Im8[i],&Sm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 8*8 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
    for (i = 0; i < TEST; i++)
    {
        MatGf2Free(Im8[i]);
    }
    MatGf2Free(Sm8);

    MatGf2 Im16[TEST],Sm16;
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&Im16[i]);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM16(Im16[i],&Sm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 16*16 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
    for (i = 0; i < TEST; i++)
    {
        MatGf2Free(Im16[i]);
    }
    MatGf2Free(Sm16);

    MatGf2 Im32[TEST],Sm32;
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&Im32[i]);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM32(Im32[i],&Sm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 32*32 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
    for (i = 0; i < TEST; i++)
    {
        MatGf2Free(Im32[i]);
    }
    MatGf2Free(Sm32);

    MatGf2 Im64[TEST],Sm64;
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&Im64[i]);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM64(Im64[i],&Sm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 64*64 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
    for (i = 0; i < TEST; i++)
    {
        MatGf2Free(Im64[i]);
    }
    MatGf2Free(Sm64);

    MatGf2 Im128[TEST],Sm128;
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&Im128[i]);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM128(Im128[i],&Sm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 128*128 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);
    for (i = 0; i < TEST; i++)
    {
        MatGf2Free(Im128[i]);
    }
    MatGf2Free(Sm128);

    printf("\nInvertible and Inverse\n");
    MatGf2 m4, m4_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM4(&m4, &m4_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 4*4 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m4);
    MatGf2Free(m4_inv);

    MatGf2 m8, m8_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM8(&m8, &m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m8);
    MatGf2Free(m8_inv);

    MatGf2 m16, m16_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM16(&m16, &m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m16);
    MatGf2Free(m16_inv);

    MatGf2 m32, m32_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM32(&m32, &m32_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m32);
    MatGf2Free(m32_inv);

    MatGf2 m64, m64_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM64(&m64, &m64_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m64);
    MatGf2Free(m64_inv);

    MatGf2 m128, m128_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM128(&m128, &m128_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m128);
    MatGf2Free(m128_inv);

    MatGf2 m256, m256_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM256(&m256, &m256_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 256*256 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    MatGf2Free(m256);
    MatGf2Free(m256_inv);

	return 0;
}