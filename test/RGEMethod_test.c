//Reverse Gaussian elimination
#include "WBMatrix/WBMatrix.h"
#include <time.h>
#include <stdlib.h>
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
int cus_randomseed;

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

void InvTMatM4(M4 *Mat)//generate 4 * 4 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint8_t temp;
    identityM4(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 3; i >= 0; i--)
    {
        for(int j = 0; j < 4; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) (*Mat).M[j] ^= (*Mat).M[i];
            }
        }
        if(i < 3)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(3 - i);
            temp = (*Mat).M[i];
            (*Mat).M[i] = (*Mat).M[cus_randomExc];
            (*Mat).M[cus_randomExc] = temp;
        }   
    }
}
void InvTMatM8(M8 *Mat)//generate 8 * 8 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint8_t temp;
    identityM8(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) (*Mat).M[j] ^= (*Mat).M[i];
            }
        }
        if(i < 7)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(7 - i);
            temp = (*Mat).M[i];
            (*Mat).M[i] = (*Mat).M[cus_randomExc];
            (*Mat).M[cus_randomExc] = temp;
        }   
    }
}
void InvTMatM16(M16 *Mat)//generate 16 * 16 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint16_t temp;
    identityM16(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 15; i >= 0; i--)
    {
        for(int j = 0; j < 16; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) (*Mat).M[j] ^= (*Mat).M[i];
            }
        }
        if(i < 15)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(15 - i);
            temp = (*Mat).M[i];
            (*Mat).M[i] = (*Mat).M[cus_randomExc];
            (*Mat).M[cus_randomExc] = temp;
        }   
    }
}
void InvTMatM32(M32 *Mat)//generate 32 * 32 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint32_t temp;
    identityM32(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 31; i >= 0; i--)
    {
        for(int j = 0; j < 32; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) (*Mat).M[j] ^= (*Mat).M[i];
            }
        }
        if(i < 31)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(31 - i);
            temp = (*Mat).M[i];
            (*Mat).M[i] = (*Mat).M[cus_randomExc];
            (*Mat).M[cus_randomExc] = temp;
        }   
    }
}
void InvTMatM64(M64 *Mat)//generate 64 * 64 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint64_t temp;
    identityM64(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 63; i >= 0; i--)
    {
        for(int j = 0; j < 64; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) (*Mat).M[j] ^= (*Mat).M[i];
            }
        }
        if(i < 63)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(63 - i);
            temp = (*Mat).M[i];
            (*Mat).M[i] = (*Mat).M[cus_randomExc];
            (*Mat).M[cus_randomExc] = temp;
        }   
    }
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    int cus_randomAdd;
    int cus_randomExc;
    uint64_t temp[2];
    identityM128(Mat);
    Initcus_randomom((cus_randomseed++) ^ time(NULL));
    for(int i = 127; i >= 0; i--)
    {
        for(int j = 0; j < 128; j++)//Add
        {
            if(j != i)
            {
                cus_randomAdd = cus_random()%2;
                if(cus_randomAdd) 
                {
                    (*Mat).M[j][0] ^= (*Mat).M[i][0];
                    (*Mat).M[j][1] ^= (*Mat).M[i][1];
                }
            }
        }
        if(i < 127)//Exchange
        {
            cus_randomExc = i + 1 + cus_random()%(127 - i);
            temp[0] = (*Mat).M[i][0];
            temp[1] = (*Mat).M[i][1];
            (*Mat).M[i][0] = (*Mat).M[cus_randomExc][0];
            (*Mat).M[i][1] = (*Mat).M[cus_randomExc][1];
            (*Mat).M[cus_randomExc][0] = temp[0];
            (*Mat).M[cus_randomExc][1] = temp[1];
        }   
    }
}

int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("Reverse Gussian Elimination Method performance test:\n");
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