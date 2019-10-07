#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct M8
{
    uint8_t M[8];
}M8;

typedef struct V8
{
    uint8_t V;
}V8;

typedef struct Aff8
{
    M8 Mat;
    V8 Vec;
}Aff8;

typedef struct M32
{
    uint32_t M[32];
}M32;

typedef struct V32
{
    uint32_t V;
}V32;

typedef struct Aff32
{
    M32 Mat;
    V32 Vec;
}Aff32;

int initM8(M8 *Mat);
int randM8(M8 *Mat);
int identityM8(M8 *Mat);
int printM8(M8 Mat);
int printbitM8(M8 Mat);

int initM32(M32 *Mat);
int printbitM32(M32 Mat);

int initV8(V8 *Vec);
int randV8(V8 *Vec);
int printV8(V8 Vec);

int initV32(V32 *Vec);
int printV32(V32 Vec);

int affineU8(Aff8 aff,uint8_t *arr);
int xorU8(uint8_t n);
int printU8(uint8_t n);

int MatMulVec(M8 Mat,V8 Vec,V8 *ans);

int affinepairM8(Aff8 *aff,Aff8 *aff_inv);
int affinecomM8to32(Aff8 aff1,Aff8 aff2,Aff8 aff3,Aff8 aff4,Aff32 *aff);