//Reverse Gaussian elimination
#include "structure.h"
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

void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    int randAdd;
    int randExc;
    uint8_t temp;
    srand((randseed++)^time(NULL));
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<7)//Exchange
        {
            randExc=i+1+rand()%(7-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void InvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    int randAdd;
    int randExc;
    uint16_t temp;
    srand((randseed++)^time(NULL));
    for(int i=15;i>=0;i--)
    {
        for(int j=0;j<16;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<15)//Exchange
        {
            randExc=i+1+rand()%(15-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void InvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    int randAdd;
    int randExc;
    uint32_t temp;
    srand((randseed++)^time(NULL));
    for(int i=31;i>=0;i--)
    {
        for(int j=0;j<32;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<31)//Exchange
        {
            randExc=i+1+rand()%(31-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void InvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    int randAdd;
    int randExc;
    uint64_t temp;
    srand((randseed++)^time(NULL));
    for(int i=63;i>=0;i--)
    {
        for(int j=0;j<64;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<63)//Exchange
        {
            randExc=i+1+rand()%(63-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    int randAdd;
    int randExc;
    uint64_t temp[2];
    srand((randseed++)^time(NULL));
    for(int i=127;i>=0;i--)
    {
        for(int j=0;j<128;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) 
                {
                    (*Mat).M[j][0]^=(*Mat).M[i][0];
                    (*Mat).M[j][1]^=(*Mat).M[i][1];
                }
            }
        }
        if(i<127)//Exchange
        {
            randExc=i+1+rand()%(127-i);
            temp[0]=(*Mat).M[i][0];
            temp[1]=(*Mat).M[i][1];
            (*Mat).M[i][0]=(*Mat).M[randExc][0];
            (*Mat).M[i][1]=(*Mat).M[randExc][1];
            (*Mat).M[randExc][0]=temp[0];
            (*Mat).M[randExc][1]=temp[1];
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

    return 0;
}