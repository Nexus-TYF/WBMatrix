//Gaussian elimination Method Base on WBMatrix 
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

uint8_t identM8[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint16_t identM16[16]={0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint32_t identM32[32]={0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint64_t identM64[64]={0x8000000000000000,0x4000000000000000,0x2000000000000000,0x1000000000000000,0x800000000000000,0x400000000000000,0x200000000000000,0x100000000000000,0x80000000000000,0x40000000000000,0x20000000000000,0x10000000000000,0x8000000000000,0x4000000000000,0x2000000000000,0x1000000000000,0x800000000000,0x400000000000,0x200000000000,0x100000000000,0x80000000000,0x40000000000,0x20000000000,0x10000000000,0x8000000000,0x4000000000,0x2000000000,0x1000000000,0x800000000,0x400000000,0x200000000,0x100000000,\
                        0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};

void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 temp;
    randM8(&temp);
    while(!isinvertM8(temp))
    {
        randM8(&temp);
    }
    copyM8(temp,Mat);
}
void InvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    M16 temp;
    randM16(&temp);
    while(!isinvertM16(temp))
    {
        randM16(&temp);
    }
    copyM16(temp,Mat);
}
void InvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    M32 temp;
    randM32(&temp);
    while(!isinvertM32(temp))
    {
        randM32(&temp);
    }
    copyM32(temp,Mat);
}
void InvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    M64 temp;
    randM64(&temp);
    while(!isinvertM64(temp))
    {
        randM64(&temp);
    }
    copyM64(temp,Mat);
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    M128 temp;
    randM128(&temp);
    while(!isinvertM128(temp))
    {
        randM128(&temp);
    }
    copyM128(temp,Mat);
}

void MatrixpairM8(M8 *Mat,M8 *Mat_inv)
{
    InvTMatM8(Mat);
    invsM8(*Mat,Mat_inv);
}
void MatrixpairM16(M16 *Mat,M16 *Mat_inv)
{
    InvTMatM16(Mat);
    invsM16(*Mat,Mat_inv);
}
void MatrixpairM32(M32 *Mat,M32 *Mat_inv)
{
    InvTMatM32(Mat);
    invsM32(*Mat,Mat_inv);
}
void MatrixpairM64(M64 *Mat,M64 *Mat_inv)
{
    InvTMatM64(Mat);
    invsM64(*Mat,Mat_inv);
}
void MatrixpairM128(M128 *Mat,M128 *Mat_inv)
{
    InvTMatM128(Mat);
    invsM128(*Mat,Mat_inv);
}

int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("Gaussian elimination Method performance test:\n");
    printf("Invertible\n");
    M8 Tm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&Tm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M16 Tm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&Tm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M32 Tm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&Tm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M64 Tm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&Tm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M128 Tm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&Tm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    printf("\nInverse\n");
    M8 Sm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        invsM8(Tm8,&Sm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 8*8 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M16 Sm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        invsM16(Tm16,&Sm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 16*16 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M32 Sm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        invsM32(Tm32,&Sm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 32*32 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M64 Sm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        invsM64(Tm64,&Sm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 64*64 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M128 Sm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        invsM128(Tm128,&Sm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 128*128 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    
    printf("\nInvertible and Inverse\n");
    M8 m8,m8_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatrixpairM8(&m8,&m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M16 m16,m16_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatrixpairM16(&m16,&m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M32 m32,m32_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatrixpairM32(&m32,&m32_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M64 m64,m64_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatrixpairM64(&m64,&m64_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    
    M128 m128,m128_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatrixpairM128(&m128,&m128_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}
