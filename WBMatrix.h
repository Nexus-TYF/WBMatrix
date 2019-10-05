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
    uint16_t M[32][2];
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
    uint16_t V[2];
};
int initM8(struct M8 *Mat);
int randM8(struct M8 *Mat);
int printM8(struct M8 Mat);
int initV8(struct V8 *Vec);
int randV8(struct V8 *Vec);
int printV8(struct V8 Vec);
int affineB1(struct M8 Mat,uint8_t *arr,struct V8 Vec);
int xorByte(uint8_t B);