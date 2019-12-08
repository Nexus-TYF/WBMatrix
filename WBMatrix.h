#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int randseed;
//8bits
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
//16bits
typedef struct M16
{
    uint16_t M[16];
}M16;

typedef struct V16
{
    uint16_t V;
}V16;

typedef struct Aff16
{
    M16 Mat;
    V16 Vec;
}Aff16;
//32bits
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
//64bits
typedef struct M64
{
    uint64_t M[64];
}M64;

typedef struct V64
{
    uint64_t V;
}V64;

typedef struct Aff64
{
    M64 Mat;
    V64 Vec;
}Aff64;
//128bits
typedef struct M128
{
    uint64_t M[128][2];
}M128;

typedef struct V128
{
    uint64_t V[2];
}V128;

typedef struct Aff128
{
    M128 Mat;
    V128 Vec;
}Aff128;

/*
* 8bit Matrix operation
*/
void initM8(M8 *Mat);
void randM8(M8 *Mat);
void identityM8(M8 *Mat);
void printM8(M8 Mat);
void printbitM8(M8 Mat);

void initV8(V8 *Vec);
void randV8(V8 *Vec);
void printV8(V8 Vec);

uint8_t affineU8(Aff8 aff,uint8_t arr);
int xorU8(uint8_t n);
void printU8(uint8_t n);

void MatMulVecM8(M8 Mat,V8 Vec,V8 *ans);
void MatMulMatM8(M8 Mat1,M8 Mat2,M8 *Mat);
void MattransM8(M8 Mat,M8 *Mat_trans);

void genMatpairM8(M8 *Mat,M8 *Mat_inv);
void genaffinepairM8(Aff8 *aff,Aff8 *aff_inv);
void affinemixM8(Aff8 preaff_inv,Aff8 aff,Aff8 *mixaff);
/*
* 16bit Matrix operation
*/
void initM16(M16 *Mat);
void randM16(M16 *Mat);
void identityM16(M16 *Mat);
void printM16(M16 Mat);
void printbitM16(M16 Mat);

void initV16(V16 *Vec);
void randV16(V16 *Vec);
void printV16(V16 Vec);

int xorU16(uint16_t n);
void printU16(uint16_t n);

void MatMulVecM16(M16 Mat,V16 Vec,V16 *ans);
void MatMulMatM16(M16 Mat1,M16 Mat2,M16 *Mat);
void MattransM16(M16 Mat,M16 *Mat_trans);

void genMatpairM16(M16 *Mat,M16 *Mat_inv);
/*
* 32bit Matrix operation
*/
void initM32(M32 *Mat);
void randM32(M32 *Mat);
void identityM32(M32 *Mat);
void printM32(M32 Mat);
void printbitM32(M32 Mat);

void initV32(V32 *Vec);
void randV32(V32 *Vec);
void printV32(V32 Vec);

uint32_t affineU32(Aff32 aff,uint32_t arr);
int xorU32(uint32_t n);
void printU32(uint32_t n);

void MatMulVecM32(M32 Mat,V32 Vec,V32 *ans);
void MatMulMatM32(M32 Mat1,M32 Mat2,M32 *Mat);
void MattransM32(M32 Mat,M32 *Mat_trans);

void genMatpairM32(M32 *Mat,M32 *Mat_inv);
void genaffinepairM32(Aff32 *aff,Aff32 *aff_inv);
void affinemixM32(Aff32 preaff_inv,Aff32 aff,Aff32 *mixaff);
void MatrixcomM8to32(M8 m1,M8 m2,M8 m3,M8 m4,M32 *mat);
void VectorcomV8to32(V8 v1,V8 v2,V8 v3,V8 v4,V32 *vec);
void affinecomM8to32(Aff8 aff1,Aff8 aff2,Aff8 aff3,Aff8 aff4,Aff32 *aff);
/*
* 64bit Matrix operation
*/
void initM64(M64 *Mat);
void randM64(M64 *Mat);
void identityM64(M64 *Mat);
void printM64(M64 Mat);
void printbitM64(M64 Mat);

void initV64(V64 *Vec);
void randV64(V64 *Vec);
void printV64(V64 Vec);

int xorU64(uint64_t n);
void printU64(uint64_t n);

void MatMulVecM64(M64 Mat,V64 Vec,V64 *ans);
void MatMulMatM64(M64 Mat1,M64 Mat2,M64 *Mat);
void MattransM64(M64 Mat,M64 *Mat_trans);

void genMatpairM64(M64 *Mat,M64 *Mat_inv);
/*
* 128bit Matrix operation
*/
void initM128(M128 *Mat);
void randM128(M128 *Mat);
void identityM128(M128 *Mat);
void printM128(M128 Mat);
void printbitM128(M128 Mat);

void initV128(V128 *Vec);
void randV128(V128 *Vec);
void printV128(V128 Vec);

int xorU128(uint64_t n[]);
void printU128(uint64_t n[]);

void MatMulVecM128(M128 Mat,V128 Vec,V128 *ans);
void MatMulMatM128(M128 Mat1,M128 Mat2,M128 *Mat);
void MattransM128(M128 Mat,M128 *Mat_trans);

void genMatpairM128(M128 *Mat,M128 *Mat_inv);