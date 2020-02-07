#ifndef GENTABLES_H
#define GENTABLES_H

#include "aes.h"
#include "RandMat.h"
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef union {
  u8 bytes[4];
  u32 all;
} tyi;

vec_GF2 int2vec (u32 iIn, int size);
u32 vec2int (vec_GF2 vIn, int size);
void computeTables (u8 expandedKey[176]);
void printTables();
void mixColumns_table(u8 state[16]);
void aes_128_table_encrypt (u8 input[16], u8 output[16]);

#endif // GENTABLES_H