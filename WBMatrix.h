#include <time.h>
#include <stdlib.h>
#include <stdio.h>
typedef unsigned char byte;
struct M8
{
    byte M[8];
};
struct M16
{
    byte M[16][2];
};
struct M32
{
    byte M[32][4];
};
struct V8
{
    byte V;
};
struct V16
{
    byte V[2];
};
struct V32
{
    byte V[4];
};
int initM8(struct M8 *Mat);
int randM8(struct M8 *Mat);
int printM8(struct M8 Mat);
int initV8(struct V8 *Vec);
int randV8(struct V8 *Vec);
int printV8(struct V8 Vec);
int affineB1(struct M8 Mat,byte *arr,struct V8 Vec);
int xorByte(byte B);