#include "inverseMatrix.h"
#include <stdio.h>
#include "stdint.h"
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
//https://github.com/braindrillmd/inverseMatrix.git
int main ()
{
  int dimension;
  QMatrix matrix;
  QMatrix rMatrix;
  uint64_t begin;
  uint64_t end;
  uint64_t ans = 0;
  int i;

  dimension=32;
  initQMatrix(&matrix, dimension);
  qMatrixScanf(&matrix);

  printf("InverseMatrix Method performance test:\n");
  begin = start_rdtsc();
  for (i = 0; i < TEST; i++)
  {
      rMatrix = reverseMatrix(matrix);
  }
  end = end_rdtsc();
  ans = (end - begin);
  printf("compute 32*32 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

  return 0;
}

//TODO: create kinda 'QMatrix' destructor-thing
//TODO: same for the constructor-thing
