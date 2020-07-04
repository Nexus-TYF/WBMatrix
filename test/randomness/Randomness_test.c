#include "WBMatrix/WBMatrix.h"
#define TEST 100000
#define TEST8 100000
#define TEST16 25000
#define TEST32 5000
#define TEST64 1400
#define TEST128 350
#ifdef __GNUC__
#include <x86intrin.h>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#endif
#pragma intrinsic(__rdtsc)

int randsseed;
uint8_t identM8[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
uint16_t identM16[16]={0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint32_t identM32[32]={0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
uint64_t identM64[64]={0x8000000000000000,0x4000000000000000,0x2000000000000000,0x1000000000000000,0x800000000000000,0x400000000000000,0x200000000000000,0x100000000000000,0x80000000000000,0x40000000000000,0x20000000000000,0x10000000000000,0x8000000000000,0x4000000000000,0x2000000000000,0x1000000000000,0x800000000000,0x400000000000,0x200000000000,0x100000000000,0x80000000000,0x40000000000,0x20000000000,0x10000000000,0x8000000000,0x4000000000,0x2000000000,0x1000000000,0x800000000,0x400000000,0x200000000,0x100000000,\
                        0x80000000,0x40000000,0x20000000,0x10000000,0x8000000,0x4000000,0x2000000,0x1000000,0x800000,0x400000,0x200000,0x100000,0x80000,0x40000,0x20000,0x10000,0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};


void InvSMatM8(M8 Mat,M8 *Mat_inv)//generate 8*8 inverse matrix
{
    uint8_t temp;
    identityM8(Mat_inv);
    for(int i=0;i<8;i++)
    {
        if((Mat.M[i]&identM8[i])==identM8[i])
        {
            for(int j=i+1;j<8;j++)
            {
                if((Mat.M[j]&identM8[i])==identM8[i])
                {
                    Mat.M[j]^=Mat.M[i];
                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        else
        {
            for(int j=i+1;j<8;j++)
            {
                if((Mat.M[j]&identM8[i])==identM8[i])
                {
                    temp=Mat.M[i];
                    Mat.M[i]=Mat.M[j];
                    Mat.M[j]=temp;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;
                    break;
                }
            }
            for(int k=i+1;k<8;k++)
            {
                if((Mat.M[k]&identM8[i])==identM8[i])
                {
                    Mat.M[k]^=Mat.M[i];
                    (*Mat_inv).M[k]^=(*Mat_inv).M[i];
                }
            }
        }
    }
    for(int i=7;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j]&identM8[i])==identM8[i])
            {
                Mat.M[j]^=Mat.M[i];
                (*Mat_inv).M[j]^=(*Mat_inv).M[i];
            }
        }
    }
}
void InvSMatM16(M16 Mat,M16 *Mat_inv)//generate 16*16 inverse matrix
{
    uint16_t temp;
    identityM16(Mat_inv);
    for(int i=0;i<16;i++)
    {
        if((Mat.M[i]&identM16[i])==identM16[i])
        {
            for(int j=i+1;j<16;j++)
            {
                if((Mat.M[j]&identM16[i])==identM16[i])
                {
                    Mat.M[j]^=Mat.M[i];
                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        else
        {
            for(int j=i+1;j<16;j++)
            {
                if((Mat.M[j]&identM16[i])==identM16[i])
                {
                    temp=Mat.M[i];
                    Mat.M[i]=Mat.M[j];
                    Mat.M[j]=temp;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;
                    break;
                }
            }
            for(int k=i+1;k<16;k++)
            {
                if((Mat.M[k]&identM16[i])==identM16[i])
                {
                    Mat.M[k]^=Mat.M[i];
                    (*Mat_inv).M[k]^=(*Mat_inv).M[i];
                }
            }
        }
    }
    for(int i=15;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j]&identM16[i])==identM16[i])
            {
                Mat.M[j]^=Mat.M[i];
                (*Mat_inv).M[j]^=(*Mat_inv).M[i];
            }
        }
    }
}
void InvSMatM32(M32 Mat,M32 *Mat_inv)//generate 32*32 inverse matrix
{
    uint32_t temp;
    identityM32(Mat_inv);
    for(int i=0;i<32;i++)
    {
        if((Mat.M[i]&identM32[i])==identM32[i])
        {
            for(int j=i+1;j<32;j++)
            {
                if((Mat.M[j]&identM32[i])==identM32[i])
                {
                    Mat.M[j]^=Mat.M[i];
                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        else
        {
            for(int j=i+1;j<32;j++)
            {
                if((Mat.M[j]&identM32[i])==identM32[i])
                {
                    temp=Mat.M[i];
                    Mat.M[i]=Mat.M[j];
                    Mat.M[j]=temp;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;
                    break;
                }
            }
            for(int k=i+1;k<32;k++)
            {
                if((Mat.M[k]&identM32[i])==identM32[i])
                {
                    Mat.M[k]^=Mat.M[i];
                    (*Mat_inv).M[k]^=(*Mat_inv).M[i];
                }
            }
        }
    }
    for(int i=31;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j]&identM32[i])==identM32[i])
            {
                Mat.M[j]^=Mat.M[i];
                (*Mat_inv).M[j]^=(*Mat_inv).M[i];
            }
        }
    }
}
void InvSMatM64(M64 Mat,M64 *Mat_inv)//generate 64*64 inverse matrix
{
    uint64_t temp;
    identityM64(Mat_inv);
    for(int i=0;i<64;i++)
    {
        if((Mat.M[i]&identM64[i])==identM64[i])
        {
            for(int j=i+1;j<64;j++)
            {
                if((Mat.M[j]&identM64[i])==identM64[i])
                {
                    Mat.M[j]^=Mat.M[i];
                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        else
        {
            for(int j=i+1;j<64;j++)
            {
                if((Mat.M[j]&identM64[i])==identM64[i])
                {
                    temp=Mat.M[i];
                    Mat.M[i]=Mat.M[j];
                    Mat.M[j]=temp;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;
                    break;
                }
            }
            for(int k=i+1;k<64;k++)
            {
                if((Mat.M[k]&identM64[i])==identM64[i])
                {
                    Mat.M[k]^=Mat.M[i];
                    (*Mat_inv).M[k]^=(*Mat_inv).M[i];
                }
            }
        }
    }
    for(int i=63;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j]&identM64[i])==identM64[i])
            {
                Mat.M[j]^=Mat.M[i];
                (*Mat_inv).M[j]^=(*Mat_inv).M[i];
            }
        }
    }
}
void InvSMatM128(M128 Mat,M128 *Mat_inv)//generate 128*128 inverse matrix
{
    uint64_t temp[2];
    identityM128(Mat_inv);
    for(int i=0;i<64;i++)
    {
        if((Mat.M[i][0]&identM64[i])==identM64[i])
        {
            for(int j=i+1;j<128;j++)
            {
                if((Mat.M[j][0]&identM64[i])==identM64[i])
                {
                    Mat.M[j][0]^=Mat.M[i][0];
                    Mat.M[j][1]^=Mat.M[i][1];

                    (*Mat_inv).M[j][0]^=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[j][1]^=(*Mat_inv).M[i][1];
                }
            }
        }
        else
        {
            for(int j=i+1;j<128;j++)
            {
                if((Mat.M[j][0]&identM64[i])==identM64[i])
                {
                    temp[0]=Mat.M[i][0];
                    Mat.M[i][0]=Mat.M[j][0];
                    Mat.M[j][0]=temp[0];

                    temp[1]=Mat.M[i][1];
                    Mat.M[i][1]=Mat.M[j][1];
                    Mat.M[j][1]=temp[1];

                    temp[0]=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[i][0]=(*Mat_inv).M[j][0];
                    (*Mat_inv).M[j][0]=temp[0];

                    temp[1]=(*Mat_inv).M[i][1];
                    (*Mat_inv).M[i][1]=(*Mat_inv).M[j][1];
                    (*Mat_inv).M[j][1]=temp[1];
                    break;
                }
            }
            for(int k=i+1;k<128;k++)
            {
                if((Mat.M[k][0]&identM64[i])==identM64[i])
                {
                    Mat.M[k][0]^=Mat.M[i][0];
                    Mat.M[k][1]^=Mat.M[i][1];

                    (*Mat_inv).M[k][0]^=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[k][1]^=(*Mat_inv).M[i][1];
                }
            }
        }
    }
    for(int i=64;i<128;i++)
    {
        if((Mat.M[i][1]&identM64[i-64])==identM64[i-64])
        {
            for(int j=i+1;j<128;j++)
            {
                if((Mat.M[j][1]&identM64[i-64])==identM64[i-64])
                {
                    Mat.M[j][1]^=Mat.M[i][1];

                    (*Mat_inv).M[j][0]^=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[j][1]^=(*Mat_inv).M[i][1];
                }
            }
        }
        else
        {
            for(int j=i+1;j<128;j++)
            {
                if((Mat.M[j][1]&identM64[i-64])==identM64[i-64])
                {
                    temp[1]=Mat.M[i][1];
                    Mat.M[i][1]=Mat.M[j][1];
                    Mat.M[j][1]=temp[1];

                    temp[0]=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[i][0]=(*Mat_inv).M[j][0];
                    (*Mat_inv).M[j][0]=temp[0];

                    temp[1]=(*Mat_inv).M[i][1];
                    (*Mat_inv).M[i][1]=(*Mat_inv).M[j][1];
                    (*Mat_inv).M[j][1]=temp[1];
                    break;
                }
            }
            for(int k=i+1;k<128;k++)
            {
                if((Mat.M[k][1]&identM64[i-64])==identM64[i-64])
                {
                    Mat.M[k][1]^=Mat.M[i][1];

                    (*Mat_inv).M[k][0]^=(*Mat_inv).M[i][0];
                    (*Mat_inv).M[k][1]^=(*Mat_inv).M[i][1];
                }
            }
        }
    }
    for(int i=127;i>=64;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j][1]&identM64[i-64])==identM64[i-64])
            {
                Mat.M[j][1]^=Mat.M[i][1];
                (*Mat_inv).M[j][0]^=(*Mat_inv).M[i][0];
                (*Mat_inv).M[j][1]^=(*Mat_inv).M[i][1];
            }
        }
    }
    for(int i=63;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if((Mat.M[j][0]&identM64[i])==identM64[i])
            {
                Mat.M[j][0]^=Mat.M[i][0];
                (*Mat_inv).M[j][0]^=(*Mat_inv).M[i][0];
                (*Mat_inv).M[j][1]^=(*Mat_inv).M[i][1];
            }
        }
    }
}
//----------------------------------------------------
void RandMat_InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 temp;
    randM8(&temp);
    while(!isinvertM8(temp))
    {
        randM8(&temp);
    }
    copyM8(temp,Mat);
}
void RandMat_m8_test()
{
    M8 Mat[TEST8], Mat_inv[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("RandMat_8bits.bin","wb");
    FILE *fd1 = fopen("RandMat_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        RandMat_InvTMatM8(&Mat[i]);
        InvSMatM8(Mat[i], &Mat_inv[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//-------------------------------------------
void RandbitMat(M8 *Mat)
{
    InitRandom((randsseed++)^((unsigned int)time(NULL)));
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(cus_random()%2) (*Mat).M[i]^=identM8[j];
        }
    }
}
void RandbitMat_InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 temp;
    RandbitMat(&temp);
    while(!isinvertM8(temp))
    {
        RandbitMat(&temp);
    }
    copyM8(temp,Mat);
}
void RandbitMat_m8_test()
{
    M8 Mat[TEST8], Mat_inv[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("RandbitMat_8bits.bin","wb");
    FILE *fd1 = fopen("RandbitMat_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        RandbitMat_InvTMatM8(&Mat[i]);
        InvSMatM8(Mat[i], &Mat_inv[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//-------------------------------------------------
void rGInvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    int randAdd;
    int randExc;
    uint8_t temp;
    srand(time(NULL));
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<7)//Exchange
        {
            randExc=i+1+rand()%(7-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void ReGauss_m8_test()
{
    M8 Mat, Mat_inv;
    uint8_t st;
    FILE *fd0 = fopen("ReGauss_8bits.bin","wb");
    FILE *fd1 = fopen("ReGauss_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        rGInvTMatM8(&Mat);
        InvSMatM8(Mat, &Mat_inv);
        for(int j = 0; j < 8; j++)
        {
            st = Mat.M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv.M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
void rGInvTMatM16(M16 *Mat)//generate 16*16 invertible matrix
{
    int randAdd;
    int randExc;
    uint16_t temp;
    srand(time(NULL));
    for(int i=15;i>=0;i--)
    {
        for(int j=0;j<16;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<15)//Exchange
        {
            randExc=i+1+rand()%(15-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void ReGauss_m16_test()
{
    M16 Mat, Mat_inv;
    uint16_t st;
    FILE *fd0 = fopen("ReGauss_16bits.bin","wb");
    FILE *fd1 = fopen("ReGauss_16bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST16; i++)
    {
        rGInvTMatM16(&Mat);
        InvSMatM16(Mat, &Mat_inv);
        for(int j = 0; j < 16; j++)
        {
            st = Mat.M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv.M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//-------------------------------------------------------------
void rGInvTMatM32(M32 *Mat)//generate 32*32 invertible matrix
{
    int randAdd;
    int randExc;
    uint32_t temp;
    srand(time(NULL));
    for(int i=31;i>=0;i--)
    {
        for(int j=0;j<32;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<31)//Exchange
        {
            randExc=i+1+rand()%(31-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void ReGauss_m32_test()
{
    M32 Mat, Mat_inv;
    uint32_t st;
    FILE *fd0 = fopen("ReGauss_32bits.bin","wb");
    FILE *fd1 = fopen("ReGauss_32bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST32; i++)
    {
        rGInvTMatM32(&Mat);
        InvSMatM32(Mat, &Mat_inv);
        for(int j = 0; j < 32; j++)
        {
            st = Mat.M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv.M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//---------------------------------------------------
void rGInvTMatM64(M64 *Mat)//generate 64*64 invertible matrix
{
    int randAdd;
    int randExc;
    uint64_t temp;
    srand(time(NULL));
    for(int i=63;i>=0;i--)
    {
        for(int j=0;j<64;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) (*Mat).M[j]^=(*Mat).M[i];
            }
        }
        if(i<63)//Exchange
        {
            randExc=i+1+rand()%(63-i);
            temp=(*Mat).M[i];
            (*Mat).M[i]=(*Mat).M[randExc];
            (*Mat).M[randExc]=temp;
        }   
    }
}
void ReGauss_m64_test()
{
    M64 Mat, Mat_inv;
    uint64_t st;
    FILE *fd0 = fopen("ReGauss_64bits.bin","wb");
    FILE *fd1 = fopen("ReGauss_64bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST64; i++)
    {
        rGInvTMatM64(&Mat);
        InvSMatM64(Mat, &Mat_inv);
        for(int j = 0; j < 64; j++)
        {
            st = Mat.M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv.M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//--------------------------------------------------------
void rGInvTMatM128(M128 *Mat)//generate 128*128 invertible matrix
{
    int randAdd;
    int randExc;
    uint64_t temp[2];
    srand(time(NULL));
    for(int i=127;i>=0;i--)
    {
        for(int j=0;j<128;j++)//Add
        {
            if(j!=i)
            {
                randAdd=rand()%2;
                if(randAdd) 
                {
                    (*Mat).M[j][0]^=(*Mat).M[i][0];
                    (*Mat).M[j][1]^=(*Mat).M[i][1];
                }
            }
        }
        if(i<127)//Exchange
        {
            randExc=i+1+rand()%(127-i);
            temp[0]=(*Mat).M[i][0];
            temp[1]=(*Mat).M[i][1];
            (*Mat).M[i][0]=(*Mat).M[randExc][0];
            (*Mat).M[i][1]=(*Mat).M[randExc][1];
            (*Mat).M[randExc][0]=temp[0];
            (*Mat).M[randExc][1]=temp[1];
        }   
    }
}
void ReGauss_m128_test()
{
    M128 Mat, Mat_inv;
    uint64_t st;
    FILE *fd0 = fopen("ReGauss_128bits.bin","wb");
    FILE *fd1 = fopen("ReGauss_128bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST128; i++)
    {
        rGInvTMatM128(&Mat);
        InvSMatM128(Mat, &Mat_inv);
        for(int j = 0; j < 128; j++)
        {
            st = Mat.M[j][0];
            fwrite(&st, sizeof(st), 1, fd0);
            st = Mat.M[j][1];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat_inv.M[j][0];
            fwrite(&st, sizeof(st), 1, fd1);
            st = Mat_inv.M[j][1];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------------------
void m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("WBMatrix_8bits.bin","wb");
    FILE *fd1 = fopen("WBMatrix_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        genMatpairM8(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//-----------------------------------------------------
void newmethod_genMatpairM8(M8 *Mat, M8 *Mat_inv)//generate 8*8 reversible matrix and its inverse matrix
{
    int p, q;
    uint8_t temp;
    #define times_add 20
    #define times_add_or_swap 8
    int trail[times_add + times_add_or_swap][3];// generate trail
    identityM8(Mat);
    identityM8(Mat_inv);
    InitRandom((randsseed++)^(unsigned int)time(NULL));
    for(int i = 0; i < times_add; i++)//generate reversible matrix add
    {
        p = cus_random()%8;
        q = cus_random()%8;
        while(p == q)
        {
            p = cus_random()%8;
            q = cus_random()%8;
        }
        if(p > q)//p = p + q
        {
            (*Mat).M[p] ^= (*Mat).M[q];
            trail[i][0] = 1;// add 1
            trail[i][1] = p;
            trail[i][2] = q;
        }
        else//q = q + p
        {
            (*Mat).M[q] ^= (*Mat).M[p];
            trail[i][0] = 1;// add 1
            trail[i][1] = q;
            trail[i][2] = p;
        }
    }
    for(int i = times_add; i < times_add + times_add_or_swap; i++)//generate reversible matrix add or swap
    {
        p = cus_random()%8;
        q = cus_random()%8;
        while(p == q)
        {
            p = cus_random()%8;
            q = cus_random()%8;
        }
        if(p > q)//add
        {
            
            (*Mat).M[p] ^= (*Mat).M[q];
            trail[i][0] = 1;
            trail[i][1] = p;
            trail[i][2] = q;
        }
        else//swap
        {
            temp = (*Mat).M[p];
            (*Mat).M[p] = (*Mat).M[q];
            (*Mat).M[q] = temp;
            trail[i][0] = 0;// swap 0
            trail[i][1] = p;
            trail[i][2] = q;
        }  
    }
    for(int j = times_add + times_add_or_swap - 1; j >= 0; j--)//generate inverse matrix
    {
        if(trail[j][0])//add 1
        {
            (*Mat_inv).M[trail[j][1]] ^=  (*Mat_inv).M[trail[j][2]];
        }
        else//swap 0
        {
            temp = (*Mat_inv).M[trail[j][1]];
            (*Mat_inv).M[trail[j][1]] = (*Mat_inv).M[trail[j][2]];
            (*Mat_inv).M[trail[j][2]] = temp;
        }   
    }
}
void newmethod_m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("newmethod_8bits.bin","wb");
    FILE *fd1 = fopen("newmethod_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        newmethod_genMatpairM8(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_genMatpairM8(M8 *Mat,M8 *Mat_inv)//generate 8*8 reversible matrix and its inverse matrix
{
    int p,q;
    uint8_t temp;
    int trail[64][3];// generate trail
    identityM8(Mat);
    identityM8(Mat_inv);
    InitRandom(time(NULL));
    M8 tempMat;
    M8 resultMat;
    int row = 0;
    randM8(&tempMat);
    copyM8(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    for(int i = 0; i < 8; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM8[i]) == identM8[i])
        {
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                row = i;
                break;
            }
            else //still invertible
            {
                for(int k=i+1;k<8;k++)
                {
                    if((tempMat.M[k]&identM8[i])==identM8[i])
                    {
                        tempMat.M[k]^=tempMat.M[i];

                        (*Mat_inv).M[k]^=(*Mat_inv).M[i];

                        trail[times][0]=1;
                        trail[times][1]=k;
                        trail[times][2]=i;
                        times++;
                    }
                }
            }
        }
    }
    if(flag)//not invertible
    {
        for(int t = row; t < 7; t++)
        {
            p = t + 1 + cus_random()%(7 - t);//swap
            temp = tempMat.M[p];
            tempMat.M[p] = tempMat.M[t];
            tempMat.M[t] = temp;
            temp = (*Mat_inv).M[p];
            (*Mat_inv).M[p] = (*Mat_inv).M[t];
            (*Mat_inv).M[t] = temp;
            trail[times][0] = 0;
            trail[times][1] = p;
            trail[times][2] = t;
            times++;
    
            for(int j = t + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[t]) == identM8[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        for(int t = 7; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if((tempMat.M[j] & identM8[t]) == identM8[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=7;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM8[i])==identM8[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM8(resultMat, Mat);
    }
}
void newmethod2_m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("newmethod2_8bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        newmethod2_genMatpairM8(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_strict_genMatpairM8(M8 *Mat,M8 *Mat_inv)//generate 8*8 reversible matrix and its inverse matrix
{
    int p,q;
    uint8_t temp;
    int trail[64][3];// generate trail
    identityM8(Mat);
    identityM8(Mat_inv);
    InitRandom(time(NULL));
    M8 tempMat;
    M8 resultMat;
    randM8(&tempMat);
    copyM8(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    int invertible = 1;
    for(int i = 0; i < 8; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM8[i]) == identM8[i])
        {
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                invertible = 0;
                if (i < 7)
                {
                    p = i + 1 + cus_random()%(7 - i);//swap
                    temp = tempMat.M[p];
                    tempMat.M[p] = tempMat.M[i];
                    tempMat.M[i] = temp;
                    temp = (*Mat_inv).M[p];
                    (*Mat_inv).M[p] = (*Mat_inv).M[i];
                    (*Mat_inv).M[i] = temp;
                    trail[times][0] = 0;
                    trail[times][1] = p;
                    trail[times][2] = i;
                    times++;
                    for(int t = i + 1; t < 7; t++)
                    {
                        if(cus_random()%2)
                        {
                            tempMat.M[t] ^= tempMat.M[i];
                            (*Mat_inv).M[t] ^= (*Mat_inv).M[i];
                            trail[times][0] = 1;
                            trail[times][1] = t;
                            trail[times][2] = i;
                            times++;
                        }
                    }
                }
            }
            else //can still contiune
            {
                for(int k = i + 1; k < 8; k++)
                {
                    if((tempMat.M[k]&identM8[i]) == identM8[i])
                    {
                        tempMat.M[k] ^= tempMat.M[i];

                        (*Mat_inv).M[k] ^= (*Mat_inv).M[i];

                        trail[times][0] = 1;
                        trail[times][1] = k;
                        trail[times][2] = i;
                        times++;
                    }
                }
            }
        }
    }
    if(!invertible)//not invertible
    {
        for(int t = 7; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if((tempMat.M[j] & identM8[t]) == identM8[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=7;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM8[i])==identM8[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM8(resultMat, Mat);
    }
}
void newmethod2_strict_m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("newmethod2_strict_8bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_strict_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        newmethod2_strict_genMatpairM8(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_ReGauss_genMatpairM8(M8 *Mat,M8 *Mat_inv)//generate 8*8 reversible matrix and its inverse matrix
{
    int p,q;
    uint8_t temp;
    int trail[64][3];// generate trail
    identityM8(Mat);
    identityM8(Mat_inv);
    InitRandom(time(NULL));
    M8 tempMat;
    M8 resultMat;
    int row = 0;
    randM8(&tempMat);
    copyM8(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    for(int i = 0; i < 8; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM8[i]) == identM8[i])
        {
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 8; j++)
            {
                if((tempMat.M[j] & identM8[i]) == identM8[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                row = i;
                break;
            }
            else //still invertible
            {
                for(int k=i+1;k<8;k++)
                {
                    if((tempMat.M[k]&identM8[i])==identM8[i])
                    {
                        tempMat.M[k]^=tempMat.M[i];

                        (*Mat_inv).M[k]^=(*Mat_inv).M[i];

                        trail[times][0]=1;
                        trail[times][1]=k;
                        trail[times][2]=i;
                        times++;
                    }
                }
            }
        }
    }
    if(flag)//not invertible
    {
        for(int t = row; t < 7; t++)
        {
            p = t + 1 + cus_random()%(7 - t);//swap
            
            temp = (*Mat_inv).M[p];
            (*Mat_inv).M[p] = (*Mat_inv).M[t];
            (*Mat_inv).M[t] = temp;
            trail[times][0] = 0;
            trail[times][1] = p;
            trail[times][2] = t;
            times++;
    
            for(int j = t + 1; j < 8; j++)
            {
                if(cus_random()%2)
                {
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        for(int t = 7; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if(cus_random()%2)
                {
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=7;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM8[i])==identM8[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM8(resultMat, Mat);
    }
}
void newmethod2_ReGauss_m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd0 = fopen("newmethod2_ReGauss_8bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_ReGauss_8bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        newmethod2_ReGauss_genMatpairM8(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_genMatpairM16(M16 *Mat,M16 *Mat_inv)//generate 16*16 reversible matrix and its inverse matrix
{
    int p,q;
    uint16_t temp;
    int trail[256][3];// generate trail
    identityM16(Mat);
    identityM16(Mat_inv);
    InitRandom(time(NULL));
    M16 tempMat;
    M16 resultMat;
    int row = 0;
    randM16(&tempMat);
    copyM16(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    for(int i = 0; i < 16; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM16[i]) == identM16[i])
        {
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                row = i;
                break;
            }
            else //still invertible
            {
                for(int k=i+1;k<16;k++)
                {
                    if((tempMat.M[k]&identM16[i])==identM16[i])
                    {
                        tempMat.M[k]^=tempMat.M[i];

                        (*Mat_inv).M[k]^=(*Mat_inv).M[i];

                        trail[times][0]=1;
                        trail[times][1]=k;
                        trail[times][2]=i;
                        times++;
                    }
                }
            }
        }
    }
    if(flag)//not invertible
    {
        for(int t = row; t < 15; t++)
        {
            p = t + 1 + cus_random()%(15 - t);//swap
            temp = tempMat.M[p];
            tempMat.M[p] = tempMat.M[t];
            tempMat.M[t] = temp;
            temp = (*Mat_inv).M[p];
            (*Mat_inv).M[p] = (*Mat_inv).M[t];
            (*Mat_inv).M[t] = temp;
            trail[times][0] = 0;
            trail[times][1] = p;
            trail[times][2] = t;
            times++;
    
            for(int j = t + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[t]) == identM16[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        for(int t = 15; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if((tempMat.M[j] & identM16[t]) == identM16[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=15;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM16[i])==identM16[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM16(resultMat, Mat);
    }
}
void newmethod2_m16_test()
{
    M16 Mat1[TEST16], Mat2[TEST16];
    uint16_t st;
    FILE *fd0 = fopen("newmethod2_16bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_16bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST16; i++)
    {
        newmethod2_genMatpairM16(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 16; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_strict_genMatpairM16(M16 *Mat,M16 *Mat_inv)//generate 16*16 reversible matrix and its inverse matrix
{
    int p,q;
    uint16_t temp;
    int trail[256][3];// generate trail
    identityM16(Mat);
    identityM16(Mat_inv);
    InitRandom(time(NULL));
    M16 tempMat;
    M16 resultMat;
    randM16(&tempMat);
    copyM16(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    int invertible = 1;
    for(int i = 0; i < 16; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM16[i]) == identM16[i])
        {
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                invertible = 0;
                if (i < 15)
                {
                    p = i + 1 + cus_random()%(15 - i);//swap
                    temp = tempMat.M[p];
                    tempMat.M[p] = tempMat.M[i];
                    tempMat.M[i] = temp;
                    temp = (*Mat_inv).M[p];
                    (*Mat_inv).M[p] = (*Mat_inv).M[i];
                    (*Mat_inv).M[i] = temp;
                    trail[times][0] = 0;
                    trail[times][1] = p;
                    trail[times][2] = i;
                    times++;
                    for(int t = i + 1; t < 15; t++)
                    {
                        if(cus_random()%2)
                        {
                            tempMat.M[t] ^= tempMat.M[i];
                            (*Mat_inv).M[t] ^= (*Mat_inv).M[i];
                            trail[times][0] = 1;
                            trail[times][1] = t;
                            trail[times][2] = i;
                            times++;
                        }
                    }
                }
            }
            else //can still contiune
            {
                for(int k = i + 1; k < 16; k++)
                {
                    if((tempMat.M[k]&identM16[i]) == identM16[i])
                    {
                        tempMat.M[k] ^= tempMat.M[i];

                        (*Mat_inv).M[k] ^= (*Mat_inv).M[i];

                        trail[times][0] = 1;
                        trail[times][1] = k;
                        trail[times][2] = i;
                        times++;
                    }
                }
            }
        }
    }
    if(!invertible)//not invertible
    {
        for(int t = 15; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if((tempMat.M[j] & identM16[t]) == identM16[t])
                {
                    tempMat.M[j] ^= tempMat.M[t];
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=15;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM16[i])==identM16[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM16(resultMat, Mat);
    }
}
void newmethod2_strict_m16_test()
{
    M16 Mat1[TEST16], Mat2[TEST16];
    uint16_t st;
    FILE *fd0 = fopen("newmethod2_strict_16bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_strict_16bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST16; i++)
    {
        newmethod2_strict_genMatpairM16(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 16; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void newmethod2_ReGauss_genMatpairM16(M16 *Mat,M16 *Mat_inv)//generate 16*16 reversible matrix and its inverse matrix
{
    int p,q;
    uint16_t temp;
    int trail[256][3];// generate trail
    identityM16(Mat);
    identityM16(Mat_inv);
    InitRandom(time(NULL));
    M16 tempMat;
    M16 resultMat;
    int row = 0;
    randM16(&tempMat);
    copyM16(tempMat, &resultMat);
    int flag = 0;
    int times = 0;
    for(int i = 0; i < 16; i++)//diagonal = 1?
    {
        if((tempMat.M[i] & identM16[i]) == identM16[i])
        {
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    tempMat.M[j] ^= tempMat.M[i];

                    (*Mat_inv).M[j] ^= (*Mat_inv).M[i];

                    trail[times][0]=1;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                }
            }
        }
        else// swap to find 1
        {
            flag = 1;
            for(int j = i + 1; j < 16; j++)
            {
                if((tempMat.M[j] & identM16[i]) == identM16[i])
                {
                    temp=tempMat.M[i];
                    tempMat.M[i]=tempMat.M[j];
                    tempMat.M[j]=temp;

                    flag=0;

                    temp=(*Mat_inv).M[i];
                    (*Mat_inv).M[i]=(*Mat_inv).M[j];
                    (*Mat_inv).M[j]=temp;

                    trail[times][0]=0;
                    trail[times][1]=j;
                    trail[times][2]=i;
                    times++;
                    break;
                }
            }
            if(flag) //can not find 1 which means not invertible
            {
                row = i;
                break;
            }
            else //still invertible
            {
                for(int k=i+1;k<16;k++)
                {
                    if((tempMat.M[k]&identM16[i])==identM16[i])
                    {
                        tempMat.M[k]^=tempMat.M[i];

                        (*Mat_inv).M[k]^=(*Mat_inv).M[i];

                        trail[times][0]=1;
                        trail[times][1]=k;
                        trail[times][2]=i;
                        times++;
                    }
                }
            }
        }
    }
    if(flag)//not invertible
    {
        for(int t = row; t < 15; t++)
        {
            p = t + 1 + cus_random()%(15 - t);//swap
            
            temp = (*Mat_inv).M[p];
            (*Mat_inv).M[p] = (*Mat_inv).M[t];
            (*Mat_inv).M[t] = temp;
            trail[times][0] = 0;
            trail[times][1] = p;
            trail[times][2] = t;
            times++;
    
            for(int j = t + 1; j < 16; j++)
            {
                if(cus_random()%2)
                {
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        for(int t = 15; t >= 0; t--)
        {
            for(int j = t - 1; j >= 0; j--)
            {
                if(cus_random()%2)
                {
                    (*Mat_inv).M[j] ^= (*Mat_inv).M[t];
                    trail[times][0] = 1;
                    trail[times][1] = j;
                    trail[times][2] = t;
                    times++;
                }
            }
        }
        
        for(int j = times - 1; j >= 0; j--)//generate inverse matrix
        {
            if(trail[j][0])//add
            {
                (*Mat).M[trail[j][1]] ^= (*Mat).M[trail[j][2]];
            }
            else//swap
            {
                temp = (*Mat).M[trail[j][1]];
                (*Mat).M[trail[j][1]] = (*Mat).M[trail[j][2]];
                (*Mat).M[trail[j][2]] = temp;
            }   
        }
    }
    else//invertible 
    {
        for(int i=15;i>=0;i--)
        {
            for(int j=i-1;j>=0;j--)
            {
                if((tempMat.M[j]&identM16[i])==identM16[i])
                {
                    tempMat.M[j]^=tempMat.M[i];

                    (*Mat_inv).M[j]^=(*Mat_inv).M[i];
                }
            }
        }
        copyM16(resultMat, Mat);
    }
}
void newmethod2_ReGauss_m16_test()
{
    M16 Mat1[TEST16], Mat2[TEST16];
    uint16_t st;
    FILE *fd0 = fopen("newmethod2_ReGauss_16bits.bin","wb");
    FILE *fd1 = fopen("newmethod2_ReGauss_16bits_inv.bin","wb");
    if(fd0 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    if(fd1 == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST16; i++)
    {
        newmethod2_ReGauss_genMatpairM16(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 16; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd0);

            st = Mat2[i].M[j];
            fwrite(&st, sizeof(st), 1, fd1);
        }
    }
    fclose(fd0);
    fclose(fd1);
}
//------------------------------------------------
void m16_test()
{
    M16 Mat1[TEST16], Mat2[TEST16];
    uint16_t st;
    FILE *fd = fopen("WBMatrix_16bits.bin","wb");
    if(fd == NULL)
    {
        printf("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST16; i++)
    {
        genMatpairM16(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 16; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
void m32_test()
{
    M32 Mat1[TEST32], Mat2[TEST32];
    uint32_t st;
    FILE *fd = fopen("WBMatrix_32bits.bin","wb");
    if(fd == NULL)
    {
        printf("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST32; i++)
    {
        genMatpairM32(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 32; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
void m64_test()
{
    M64 Mat1[TEST64], Mat2[TEST64];
    uint64_t st;
    FILE *fd = fopen("WBMatrix_64bits.bin","wb");
    if(fd == NULL)
    {
        printf("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST64; i++)
    {
        genMatpairM64(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 64; j++)
        {
            st = Mat1[i].M[j];
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
void m128_test()
{
    M128 Mat1[TEST128], Mat2[TEST128];
    uint64_t st1, st2;
    FILE *fd = fopen("WBMatrix_128bits.bin","wb");
    if(fd == NULL)
    {
        printf("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST128; i++)
    {
        genMatpairM128(&Mat1[i], &Mat2[i]);
        for(int j = 0; j < 128; j++)
        {
            st1 = Mat1[i].M[j][0];
            fwrite(&st1, sizeof(st1), 1, fd);
            st2 = Mat1[i].M[j][1];
            fwrite(&st2, sizeof(st2), 1, fd);
        }
    }
    fclose(fd);
}

void accuracy()
{
    printf("-----invertible and inverse test-----\n");
    printf("nomal mode:\n");
    M16 iim16_1,iim16_2,iim16_3,iim16_4;
    identityM16(&iim16_4);
    int i;
    for(i=0;i<TEST;i++)
    {
        newmethod2_genMatpairM16(&iim16_1,&iim16_2);
        MatMulMatM16(iim16_1,iim16_2,&iim16_3);
        if(!isequalM16(iim16_3,iim16_4)) break;
    }
    if(i<TEST) {printf("newmethod2 16bit: ERROR\n");}
    else printf("newmethod2 16bit: OK\n");
    for(i=0;i<TEST;i++)
    {
        newmethod2_strict_genMatpairM16(&iim16_1,&iim16_2);
        MatMulMatM16(iim16_1,iim16_2,&iim16_3);
        if(!isequalM16(iim16_3,iim16_4)) break;
    }
    if(i<TEST) {printf("newmethod2_strict 16bit: ERROR\n");}
    else printf("newmethod2_strict 16bit: OK\n");
    for(i=0;i<TEST;i++)
    {
        newmethod2_ReGauss_genMatpairM16(&iim16_1,&iim16_2);
        MatMulMatM16(iim16_1,iim16_2,&iim16_3);
        if(!isequalM16(iim16_3,iim16_4)) break;
    }
    if(i<TEST) {printf("newmethod2_ReGauss 16bit: ERROR\n");}
    else printf("newmethod2_ReGauss 16bit: OK\n");
}

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
void performance()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;
    printf("\nInvertible and Inverse\n");
    M16 m16,m16_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        newmethod2_ReGauss_genMatpairM16(&m16,&m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2_ReGauss generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        newmethod2_strict_genMatpairM16(&m16,&m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2_strict generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        newmethod2_genMatpairM16(&m16,&m16_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2 generate 16*16 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST);
}
int main()
{
    // m8_test();
    // m16_test();
    // m32_test();
    // m64_test();
    // m128_test();
    // RandMat_m8_test();
    ReGauss_m8_test();
    ReGauss_m16_test();
    ReGauss_m32_test();
    ReGauss_m64_test();
    ReGauss_m128_test();
    // newmethod_m8_test();
    // RandbitMat_m8_test();
    // newmethod2_strict_m8_test();
    // newmethod2_ReGauss_m8_test();
    // newmethod2_m8_test();
    // newmethod2_strict_m16_test();
    // newmethod2_ReGauss_m16_test();
    // newmethod2_m16_test();
    //performance();
    //accuracy();
    return 0;
}