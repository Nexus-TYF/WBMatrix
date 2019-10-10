#include "WBMatrix.h"

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

    M8 Mat1;
    V8 Vec1;
    V8 Vec2;
    randM8(&Mat1);
    randV8(&Vec1);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        MatMulVecM8(Mat1,Vec1,&Vec2);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("8*8 Mat mul 8*1 Vec cost %llu CPU cycles\n", (ans) / TEST);
    return 0;
}