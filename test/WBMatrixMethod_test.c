//pairwise invertible matrices test of WBMatrix
#include "WBMatrix.h"
#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)

//Repeat test times and calculate on average for accuracy
#define TEST 100000
int randseed;

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

uint8_t TM8[TEST][M8N][3];
uint8_t TM16[TEST][M16N][3];
uint8_t TM32[TEST][M32N][3];
uint8_t TM64[TEST][M64N][3];
uint8_t TM128[TEST][M128N][3];

void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    int p,q;
    uint8_t temp;
    identityM8(Mat);//identity matrix
    srand((randseed++)^time(NULL));
    for(int i=0;i<M8N;i++)//generate reversible matrix
    {
        p=rand()%8;
        q=rand()%8;
        while(p==q)
        {
            p=rand()%8;
            q=rand()%8;
        }
        if(p>q)//add
        {
            (*Mat).M[p]^=(*Mat).M[q];
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
        }   
    }
}
void InvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    int p,q;
    uint16_t temp;
    identityM16(Mat);//identity matrix
    srand((randseed++)^time(NULL));
    for(int i=0;i<M16N;i++)//generate reversible matrix
    {
        p=rand()%16;
        q=rand()%16;
        while(p==q)
        {
            p=rand()%16;
            q=rand()%16;
        }
        if(p>q)//add
        {
            (*Mat).M[p]^=(*Mat).M[q];
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
        }   
    }
}
void InvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    int p,q;
    uint32_t temp;
    identityM32(Mat);//identity matrix
    srand((randseed++)^time(NULL));
    for(int i=0;i<M32N;i++)//generate reversible matrix
    {
        p=rand()%32;
        q=rand()%32;
        while(p==q)
        {
            p=rand()%32;
            q=rand()%32;
        }
        if(p>q)//add
        {
            (*Mat).M[p]^=(*Mat).M[q];
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
        }   
    }
}
void InvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    int p,q;
    uint64_t temp;
    identityM64(Mat);//identity matrix
    srand((randseed++)^time(NULL));
    for(int i=0;i<M64N;i++)//generate reversible matrix
    {
        p=rand()%64;
        q=rand()%64;
        while(p==q)
        {
            p=rand()%64;
            q=rand()%64;
        }
        if(p>q)//add
        {
            (*Mat).M[p]^=(*Mat).M[q];
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
        }   
    }
}
void InvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    int p,q;
    uint64_t temp[2];
    identityM128(Mat);//identity matrix
    srand((randseed++)^time(NULL));
    for(int i=0;i<M128N;i++)//generate reversible matrix
    {
        p=rand()%128;
        q=rand()%128;
        while(p==q)
        {
            p=rand()%128;
            q=rand()%128;
        }
        if(p>q)//add
        {
            (*Mat).M[p][0]^=(*Mat).M[q][0];
            (*Mat).M[p][1]^=(*Mat).M[q][1];
        }
        else//swap
        {
            temp[0]=(*Mat).M[p][0];
            temp[1]=(*Mat).M[p][1];
            (*Mat).M[p][0]=(*Mat).M[q][0];
            (*Mat).M[p][1]=(*Mat).M[q][1];
            (*Mat).M[q][0]=temp[0];
            (*Mat).M[q][1]=temp[1];
        }   
    }
}

void TrailM8(int k)//generate trail of 8*8 matrix
{
    int p,q;
    srand((randseed++)^time(NULL));
    for(int i=0;i<M8N;i++)
    {
        p=rand()%8;
        q=rand()%8;
        while(p==q)
        {
            p=rand()%8;
            q=rand()%8;
        }
        if(p>q)//add
        {
            TM8[k][i][0]=1;
            TM8[k][i][1]=p;
            TM8[k][i][2]=q;
        }
        else//swap
        {
            TM8[k][i][0]=0;
            TM8[k][i][1]=p;
            TM8[k][i][2]=q;
        }   
    }
}
void TrailM16(int k)//generate trail of 16*16 matrix
{
    int p,q;
    srand((randseed++)^time(NULL));
    for(int i=0;i<M16N;i++)
    {
        p=rand()%16;
        q=rand()%16;
        while(p==q)
        {
            p=rand()%16;
            q=rand()%16;
        }
        if(p>q)//add
        {
            TM16[k][i][0]=1;
            TM16[k][i][1]=p;
            TM16[k][i][2]=q;
        }
        else//swap
        {
            TM16[k][i][0]=0;
            TM16[k][i][1]=p;
            TM16[k][i][2]=q;
        }   
    }
}
void TrailM32(int k)//generate trail of 32*32 matrix
{
    int p,q;
    srand((randseed++)^time(NULL));
    for(int i=0;i<M32N;i++)
    {
        p=rand()%32;
        q=rand()%32;
        while(p==q)
        {
            p=rand()%32;
            q=rand()%32;
        }
        if(p>q)//add
        {
            TM32[k][i][0]=1;
            TM32[k][i][1]=p;
            TM32[k][i][2]=q;
        }
        else//swap
        {
            TM32[k][i][0]=0;
            TM32[k][i][1]=p;
            TM32[k][i][2]=q;
        }   
    }
}
void TrailM64(int k)//generate trail of 64*64 matrix
{
    int p,q;
    srand((randseed++)^time(NULL));
    for(int i=0;i<M64N;i++)
    {
        p=rand()%64;
        q=rand()%64;
        while(p==q)
        {
            p=rand()%64;
            q=rand()%64;
        }
        if(p>q)//add
        {
            TM64[k][i][0]=1;
            TM64[k][i][1]=p;
            TM64[k][i][2]=q;
        }
        else//swap
        {
            TM64[k][i][0]=0;
            TM64[k][i][1]=p;
            TM64[k][i][2]=q;
        }   
    }
}
void TrailM128(int k)//generate trail of 128*128 matrix
{
    int p,q;
    srand((randseed++)^time(NULL));
    for(int i=0;i<M128N;i++)
    {
        p=rand()%128;
        q=rand()%128;
        while(p==q)
        {
            p=rand()%128;
            q=rand()%128;
        }
        if(p>q)//add
        {
            TM128[k][i][0]=1;
            TM128[k][i][1]=p;
            TM128[k][i][2]=q;
        }
        else//swap
        {
            TM128[k][i][0]=0;
            TM128[k][i][1]=p;
            TM128[k][i][2]=q;
        }   
    }
}

void InvSMatM8(M8 *Mat_inv,int k)//generate 8*8 inverse matrix
{
    uint8_t temp;
    identityM8(Mat_inv);
    for(int j=M8N-1;j>=0;j--)//generate inverse matrix
    {
        if(TM8[k][j][0])//add
        {
            (*Mat_inv).M[TM8[k][j][1]]^= (*Mat_inv).M[TM8[k][j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[TM8[k][j][1]];
            (*Mat_inv).M[TM8[k][j][1]]= (*Mat_inv).M[TM8[k][j][2]];
            (*Mat_inv).M[TM8[k][j][2]]=temp;
        }   
    }
}
void InvSMatM16(M16 *Mat_inv,int k)//generate 16*16 inverse matrix
{
    uint16_t temp;
    identityM16(Mat_inv);
    for(int j=M16N-1;j>=0;j--)//generate inverse matrix
    {
        if(TM16[k][j][0])//add
        {
            (*Mat_inv).M[TM16[k][j][1]]^= (*Mat_inv).M[TM16[k][j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[TM16[k][j][1]];
            (*Mat_inv).M[TM16[k][j][1]]= (*Mat_inv).M[TM16[k][j][2]];
            (*Mat_inv).M[TM16[k][j][2]]=temp;
        }   
    }
}
void InvSMatM32(M32 *Mat_inv,int k)//generate 32*32 inverse matrix
{
    uint32_t temp;
    identityM32(Mat_inv);
    for(int j=M32N-1;j>=0;j--)//generate inverse matrix
    {
        if(TM32[k][j][0])//add
        {
            (*Mat_inv).M[TM32[k][j][1]]^= (*Mat_inv).M[TM32[k][j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[TM32[k][j][1]];
            (*Mat_inv).M[TM32[k][j][1]]= (*Mat_inv).M[TM32[k][j][2]];
            (*Mat_inv).M[TM32[k][j][2]]=temp;
        }   
    }
}
void InvSMatM64(M64 *Mat_inv,int k)//generate 64*64 inverse matrix
{
    uint64_t temp;
    identityM64(Mat_inv);
    for(int j=M64N-1;j>=0;j--)//generate inverse matrix
    {
        if(TM64[k][j][0])//add
        {
            (*Mat_inv).M[TM64[k][j][1]]^= (*Mat_inv).M[TM64[k][j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[TM64[k][j][1]];
            (*Mat_inv).M[TM64[k][j][1]]= (*Mat_inv).M[TM64[k][j][2]];
            (*Mat_inv).M[TM64[k][j][2]]=temp;
        }   
    }
}
void InvSMatM128(M128 *Mat_inv,int k)//generate 128*128 inverse matrix
{
    uint64_t temp[2];
    identityM128(Mat_inv);
    for(int j=M128N-1;j>=0;j--)//generate inverse matrix
    {
        if(TM128[k][j][0])//add
        {
            (*Mat_inv).M[TM128[k][j][1]][0]^= (*Mat_inv).M[TM128[k][j][2]][0];
            (*Mat_inv).M[TM128[k][j][1]][1]^= (*Mat_inv).M[TM128[k][j][2]][1];
        }
        else//swap
        {
            temp[0]= (*Mat_inv).M[TM128[k][j][1]][0];
            temp[1]= (*Mat_inv).M[TM128[k][j][1]][1];
            (*Mat_inv).M[TM128[k][j][1]][0]= (*Mat_inv).M[TM128[k][j][2]][0];
            (*Mat_inv).M[TM128[k][j][1]][1]= (*Mat_inv).M[TM128[k][j][2]][1];
            (*Mat_inv).M[TM128[k][j][2]][0]=temp[0];
            (*Mat_inv).M[TM128[k][j][2]][1]=temp[1];
        }   
    }
}

int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;

    printf("WBMatrix method performance test\n");
    printf("Invertible\n");
    M8 Tm8;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM8(&Tm8);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M16 Tm16;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM16(&Tm16);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M32 Tm32;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM32(&Tm32);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M64 Tm64;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM64(&Tm64);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    M128 Tm128;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvTMatM128(&Tm128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 invertible matrix cost %llu CPU cycles\n", (ans) / TEST);

    printf("\nInverse\n");
    M8 Sm8;
    for (i = 0; i < TEST; i++)
    {
        TrailM8(i);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM8(&Sm8,i);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 8*8 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M16 Sm16;
    for (i = 0; i < TEST; i++)
    {
        TrailM16(i);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM16(&Sm16,i);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 16*16 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M32 Sm32;
    for (i = 0; i < TEST; i++)
    {
        TrailM32(i);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM32(&Sm32,i);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 32*32 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M64 Sm64;
    for (i = 0; i < TEST; i++)
    {
        TrailM64(i);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM64(&Sm64,i);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 64*64 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);

    M128 Sm128;
    for (i = 0; i < TEST; i++)
    {
        TrailM128(i);
    }
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        InvSMatM128(&Sm128,i);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("compute 128*128 inverse matrix cost %llu CPU cycles\n", (ans) / TEST);


    printf("\nInvertible and Inverse\n");
    M8 m8,m8_inv;
    //initinvbaseM8(initM8_max);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM8(&m8,&m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M16 m16,m16_inv;
    //initinvbaseM16(initM16_max);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM16(&m16,&m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M32 m32,m32_inv;
    //initinvbaseM32(initM32_max);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM32(&m32,&m32_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 32*32 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M64 m64,m64_inv;
    //initinvbaseM64(initM64_max);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM64(&m64,&m64_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 64*64 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    M128 m128,m128_inv;
    //initinvbaseM128(initM128_max);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        genMatpairM128(&m128,&m128_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("generate 128*128 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);

    return 0;
}