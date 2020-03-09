#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "stdint.h"

unsigned int permuteQPR(unsigned int x);
void InitRandom(unsigned int seedBase);
unsigned int random();

#endif // __RANDOM_SEQUENCE_H__