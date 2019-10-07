#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
struct M8
{
    uint8_t M[8];
};
struct M16
{
    uint16_t M[16];
};
struct M32
{
    uint32_t M[32];
};
struct V8
{
    uint8_t V;
};
struct V16
{
    uint16_t V;
};
struct V32
{
    uint32_t V;
};

int initM8(struct M8 *Mat);
int randM8(struct M8 *Mat);
int identityM8(struct M8 *Mat);
int printM8(struct M8 Mat);
int printbitM8(struct M8 Mat);

int initV8(struct V8 *Vec);
int randV8(struct V8 *Vec);
int printV8(struct V8 Vec);

int affineU8(struct M8 Mat,uint8_t *arr,struct V8 Vec);
int xorU8(uint8_t n);
int printU8(uint8_t n);

int MatMulVec(struct M8 Mat,struct V8 Vec,struct V8 *ans);

int affinepairM8(struct M8 *Mat,struct V8 *Vec,struct M8 *Mat_inv,struct V8 *Vec_inv);