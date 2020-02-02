#include "invertiblematrix.h"
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
void InvTMatM(int n,int **array)
{
    getIdentityMatrix(n, array);
    //get invertible matrix
    getInvertibleMatrix(n, array);
    //put invertible matrix into file
    //putInvertibleMatrixIntoFile(n, array);
    //print invertible matrix
    //printInvertibleMatrix(n, array);

}

int main()
{
    int k;
    int n;

    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("InvertibleMatrix Method performance test:\n");
    n=8;
    int** a8;
    a8 = (int**)malloc(sizeof(int*)*n);
        for(k = 0; k < n; ++k)
        {
               a8[k] = (int*)malloc(sizeof(int)*n);
        }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM(n,a8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    freeMatrix(n, a8);

    n=16;
    int** a16;
    a16 = (int**)malloc(sizeof(int*)*n);
        for(k = 0; k < n; ++k)
        {
               a16[k] = (int*)malloc(sizeof(int)*n);
        }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM(n,a16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    freeMatrix(n, a16);

    n=32;
    int** a32;
    a32 = (int**)malloc(sizeof(int*)*n);
        for(k = 0; k < n; ++k)
        {
               a32[k] = (int*)malloc(sizeof(int)*n);
        }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM(n,a32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    freeMatrix(n, a32);

    n=64;
    int** a64;
    a64 = (int**)malloc(sizeof(int*)*n);
        for(k = 0; k < n; ++k)
        {
               a64[k] = (int*)malloc(sizeof(int)*n);
        }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM(n,a64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    freeMatrix(n, a64);

    n=128;
    int** a128;
    a128 = (int**)malloc(sizeof(int*)*n);
        for(k = 0; k < n; ++k)
        {
               a128[k] = (int*)malloc(sizeof(int)*n);
        }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM(n,a128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);
    freeMatrix(n, a128);

    return 0;
}