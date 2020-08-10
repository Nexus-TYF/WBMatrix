//LowMC Method
#include "WBMatrix/WBMatrix.h"
#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)
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

#include <vector>
#include <bitset>
// Uses the Grain LSFR as self-shrinking generator to create pseudorandom bits
// Is initialized with the all 1s state
// The first 160 bits are thrown away
bool getrandbit () {
    static std::bitset<80> state; //Keeps the 80 bit LSFR state
    bool tmp = 0;
    //If state has not been initialized yet
    if (state.none ()) {
        state.set (); //Initialize with all bits set
        //Throw the first 160 bits away
        for (unsigned i = 0; i < 160; ++i) {
            //Update the state
            tmp =  state[0] ^ state[13] ^ state[23]
                       ^ state[38] ^ state[51] ^ state[62];
            state >>= 1;
            state[79] = tmp;
        }
    }
    //choice records whether the first bit is 1 or 0.
    //The second bit is produced if the first bit is 1.
    bool choice = false;
    do {
        //Update the state
        tmp =  state[0] ^ state[13] ^ state[23]
                   ^ state[38] ^ state[51] ^ state[62];
        state >>= 1;
        state[79] = tmp;
        choice = tmp;
        tmp =  state[0] ^ state[13] ^ state[23]
                   ^ state[38] ^ state[51] ^ state[62];
        state >>= 1;
        state[79] = tmp;
    } while (! choice);
    return tmp;
}

uint8_t identM4[4] = {0x08,0x04,0x02,0x01};
uint8_t identM8[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint16_t identM16[16] = {0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint32_t identM32[32] = {0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint64_t identM64[64] = {0x8000000000000000,0x4000000000000000,0x2000000000000000,0x1000000000000000,0x800000000000000,0x400000000000000,0x200000000000000,0x100000000000000,0x80000000000000,0x40000000000000,0x20000000000000,0x10000000000000,0x8000000000000,0x4000000000000,0x2000000000000,0x1000000000000,0x800000000000,0x400000000000,0x200000000000,0x100000000000,0x80000000000,0x40000000000,0x20000000000,0x10000000000,0x8000000000,0x4000000000,0x2000000000,0x1000000000,0x800000000,0x400000000,0x200000000,0x100000000,\
                        0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};

void RandbitMatM4(M4 *Mat)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(getrandbit()) (*Mat).M[i] ^= identM4[j];
        }
    }
}
void InvTMatM4(M4 *Mat)//generate 4*4 invertible matrix
{
    M4 temp;
    RandbitMatM4(&temp);
    while(!isinvertM4(temp))
    {
        RandbitMatM4(&temp);
    }
    copyM4(temp, Mat);
}
void RandbitMatM8(M8 *Mat)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(getrandbit()) (*Mat).M[i] ^= identM8[j];
        }
    }
}
void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 temp;
    RandbitMatM8(&temp);
    while(!isinvertM8(temp))
    {
        RandbitMatM8(&temp);
    }
    copyM8(temp, Mat);
}
void RandbitMatM16(M16 *Mat)
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(getrandbit()) (*Mat).M[i] ^= identM16[j];
        }
    }
}
void InvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    M16 temp;
    RandbitMatM16(&temp);
    while(!isinvertM16(temp))
    {
        RandbitMatM16(&temp);
    }
    copyM16(temp, Mat);
}
void RandbitMatM32(M32 *Mat)
{
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            if(getrandbit()) (*Mat).M[i] ^= identM32[j];
        }
    }
}
void InvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    M32 temp;
    RandbitMatM32(&temp);
    while(!isinvertM32(temp))
    {
        RandbitMatM32(&temp);
    }
    copyM32(temp, Mat);
}
void RandbitMatM64(M64 *Mat)
{
    for(int i = 0; i < 64; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            if(getrandbit()) (*Mat).M[i] ^= identM64[j];
        }
    }
}
void InvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    M64 temp;
    RandbitMatM64(&temp);
    while(!isinvertM64(temp))
    {
        RandbitMatM64(&temp);
    }
    copyM64(temp, Mat);
}
void RandbitMatM128(M128 *Mat)
{
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            if(getrandbit()) (*Mat).M[i][0] ^= identM64[j];
            if(getrandbit()) (*Mat).M[i][1] ^= identM64[j];
        }
    }
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    M128 temp;
    RandbitMatM128(&temp);
    while(!isinvertM128(temp))
    {
        RandbitMatM128(&temp);
    }
    copyM128(temp, Mat);
}

int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;
    printf("\nInvertible and Inverse\n");
    M4 m4, m4_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM4(&m4);
        invsM4(m4, &m4_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 4*4 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M8 m8, m8_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&m8);
        invsM8(m8, &m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    
    M16 m16, m16_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&m16);
        invsM16(m16, &m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    
    M32 m32, m32_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&m32);
        invsM32(m32, &m32_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    
    M64 m64, m64_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&m64);
        invsM64(m64, &m64_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    
    M128 m128, m128_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&m128);
        invsM128(m128, &m128_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}