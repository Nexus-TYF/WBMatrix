//Reverse LU Decomposition Method
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
int randseed;

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

uint8_t identM4[4] = {0x08,0x04,0x02,0x01};
uint8_t identM8[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint16_t identM16[16] = {0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint32_t identM32[32] = {0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint64_t identM64[64] = {0x8000000000000000,0x4000000000000000,0x2000000000000000,0x1000000000000000,0x800000000000000,0x400000000000000,0x200000000000000,0x100000000000000,0x80000000000000,0x40000000000000,0x20000000000000,0x10000000000000,0x8000000000000,0x4000000000000,0x2000000000000,0x1000000000000,0x800000000000,0x400000000000,0x200000000000,0x100000000000,0x80000000000,0x40000000000,0x20000000000,0x10000000000,0x8000000000,0x4000000000,0x2000000000,0x1000000000,0x800000000,0x400000000,0x200000000,0x100000000,\
                        0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};

void lowM4(M4 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 4; i++)
    {
        (*Mat).M[i] = identM4[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM4[j];
        }
    }
}
void lowM8(M8 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 8; i++)
    {
        (*Mat).M[i] = identM8[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM8[j];
        }
    }
}
void lowM16(M16 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 16; i++)
    {
        (*Mat).M[i] = identM16[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM16[j];
        }
    }
}
void lowM32(M32 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 32; i++)
    {
        (*Mat).M[i] = identM32[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM32[j];
        }
    }
}
void lowM64(M64 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 64; i++)
    {
        (*Mat).M[i] = identM64[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM64[j];
        }
    }
}
void lowM128(M128 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 64; i++)
    {
        (*Mat).M[i][0] = identM64[i];
        for(int j = 0; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i][0] ^= identM64[j];
        }
        (*Mat).M[i][1] = 0;
    }
    for(int i = 64; i < 128; i++)
    {
        (*Mat).M[i][1] = identM64[i - 64];
        for(int j = 64; j < i; j++)
        {
            if(cus_random()%2) (*Mat).M[i][1] ^= identM64[j - 64];
        }
        for(int j = 0; j < 64; j++)
        {
            if(cus_random()%2) (*Mat).M[i][0] ^= identM64[j];
        }
    }
}

void upM4(M4 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 4; i++)
    {
        (*Mat).M[i] = identM4[i];
        for(int j = i + 1; j < 4; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM4[j];
        }
    }
}
void upM8(M8 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 8; i++)
    {
        (*Mat).M[i] = identM8[i];
        for(int j = i + 1; j < 8; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM8[j];
        }
    }
}
void upM16(M16 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 16; i++)
    {
        (*Mat).M[i] = identM16[i];
        for(int j = i + 1; j < 16; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM16[j];
        }
    }
}
void upM32(M32 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 32; i++)
    {
        (*Mat).M[i] = identM32[i];
        for(int j = i + 1; j < 32; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM32[j];
        }
    }
}
void upM64(M64 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 64; i++)
    {
        (*Mat).M[i] = identM64[i];
        for(int j = i + 1; j < 64; j++)
        {
            if(cus_random()%2) (*Mat).M[i] ^= identM64[j];
        }
    }
}
void upM128(M128 *Mat)
{
    InitRandom((randseed++) ^ time(NULL));
    for(int i = 0; i < 64; i++)
    {
        (*Mat).M[i][0] = identM64[i];
        for(int j = i + 1; j < 64; j++)
        {
            if(cus_random()%2) (*Mat).M[i][0] ^= identM64[j];
        }
        for(int j = 0; j < 64; j++)
        {
            if(cus_random()%2) (*Mat).M[i][1] ^= identM64[j];
        }
    }
    for(int i = 64; i < 128; i++)
    {
        (*Mat).M[i][1] = identM64[i - 64];
        for(int j = i + 1; j < 128; j++)
        {
            if(cus_random()%2) (*Mat).M[i][1] ^= identM64[j - 64];
        }
        (*Mat).M[i][0] = 0;
    }
}

void InvTMatM4(M4 *Mat)//generate 4*4 invertible matrix
{
    M4 mat1, mat2, mat3;
    int randpivot;
    uint8_t temp;
    InitRandom((randseed++) ^ time(NULL));
    lowM4(&mat1);
    upM4(&mat2);
    MatMulMatM4(mat1, mat2, &mat3);
    for(int i = 0; i < 3; i++)
    {
        randpivot = i + 1 + cus_random()%(3 - i);
        temp = mat3.M[i];
        mat3.M[i] = mat3.M[randpivot];
        mat3.M[randpivot] = temp;
    }
    copyM4(mat3, Mat);
}
void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 mat1, mat2, mat3;
    int randpivot;
    uint8_t temp;
    InitRandom((randseed++) ^ time(NULL));
    lowM8(&mat1);
    upM8(&mat2);
    MatMulMatM8(mat1, mat2, &mat3);
    for(int i = 0; i < 7; i++)
    {
        randpivot = i + 1 + cus_random()%(7 - i);
        temp = mat3.M[i];
        mat3.M[i] = mat3.M[randpivot];
        mat3.M[randpivot] = temp;
    }
    copyM8(mat3, Mat);
}
void InvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    M16 mat1, mat2, mat3;
    int randpivot;
    uint16_t temp;
    InitRandom((randseed++) ^ time(NULL));
    lowM16(&mat1);
    upM16(&mat2);
    MatMulMatM16(mat1, mat2, &mat3);
    for(int i = 0; i < 7; i++)
    {
        randpivot = i + 1 + cus_random()%(7 - i);
        temp = mat3.M[i];
        mat3.M[i] = mat3.M[randpivot];
        mat3.M[randpivot] = temp;
    }
    copyM16(mat3, Mat);
}
void InvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    M32 mat1, mat2, mat3;
    int randpivot;
    uint32_t temp;
    InitRandom((randseed++) ^ time(NULL));
    lowM32(&mat1);
    upM32(&mat2);
    MatMulMatM32(mat1, mat2, &mat3);
    for(int i = 0; i < 7; i++)
    {
        randpivot = i + 1 + cus_random()%(7 - i);
        temp = mat3.M[i];
        mat3.M[i] = mat3.M[randpivot];
        mat3.M[randpivot] = temp;
    }
    copyM32(mat3, Mat);
}
void InvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    M64 mat1, mat2, mat3;
    int randpivot;
    uint64_t temp;
    InitRandom((randseed++) ^ time(NULL));
    lowM64(&mat1);
    upM64(&mat2);
    MatMulMatM64(mat1, mat2, &mat3);
    for(int i = 0; i < 7; i++)
    {
        randpivot = i + 1 + cus_random()%(7 - i);
        temp = mat3.M[i];
        mat3.M[i] = mat3.M[randpivot];
        mat3.M[randpivot] = temp;
    }
    copyM64(mat3, Mat);
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    M128 mat1, mat2, mat3;
    int randpivot;
    uint64_t temp[2];
    InitRandom((randseed++) ^ time(NULL));
    lowM128(&mat1);
    upM128(&mat2);
    MatMulMatM128(mat1, mat2, &mat3);
    for(int i = 0; i < 7; i++)
    {
        randpivot = i + 1 + cus_random()%(7 - i);
        temp[0] = mat3.M[i][0];
        mat3.M[i][0] = mat3.M[randpivot][0];
        mat3.M[randpivot][0] = temp[0];

        temp[1] = mat3.M[i][1];
        mat3.M[i][1] = mat3.M[randpivot][1];
        mat3.M[randpivot][1] = temp[1];
    }
    copyM128(mat3, Mat);
}

int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("Reverse LU Decomposition Method performance test:\n");
    M4 Tm4, Sm4;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM4(&Tm4);
        invsM4(Tm4, &Sm4);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 4 * 4 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M8 Tm8, Sm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&Tm8);
        invsM8(Tm8, &Sm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8 * 8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M16 Tm16, Sm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&Tm16);
        invsM16(Tm16, &Sm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16 * 16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M32 Tm32, Sm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&Tm32);
        invsM32(Tm32, &Sm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32 * 32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M64 Tm64, Sm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&Tm64);
        invsM64(Tm64, &Sm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64 * 64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M128 Tm128, Sm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&Tm128);
        invsM128(Tm128, &Sm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128 * 128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}