/*
 * @Author: Weijie Li 
 * @Date: 2018-11-12 19:05:34 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-11-12 20:47:01
 */
#ifndef _W_RANDOM_W_H_
#define _W_RANDOM_W_H_

#include<stdint.h>

// // Rand a list of Number
// int random_rand(unsigned char *output, size_t size);

// // Rand a list of int32
// int random_rand_int_array(int *output, int count);

char* wRandFuncVersion();

// Rand a list of int32 (if ctx==NULL, then init a global ctx)
int wRandomList(int *list, int len);

int wRandomShuffleU8(uint8_t *list, int len);

uint32_t wRand31();
uint32_t wRand32();
uint64_t wRand64();


#endif // _W_RANDOM_W_H_