#include "WBMatrix/WBMatrix.h"
#define TEST8 100000
#define TEST16 25000
#define TEST32 5000
#define TEST64 1400
#define TEST128 350
void InvTMatM8(M8 *Mat)//generate 8*8 invertible matrix
{
    M8 temp;
    randM8(&temp);
    while(!isinvertM8(temp))
    {
        randM8(&temp);
    }
    copyM8(temp,Mat);
}
void randMat_m8_test()
{
    M8 Mat[TEST8];
    uint8_t st;
    FILE *fd = fopen("RandMat_8bits.bin","wb");
    if(fd == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        InvTMatM8(&Mat[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat[i].M[j];
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
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
void reGauss_m8_test()
{
    M8 Mat[TEST8];
    uint8_t st;
    FILE *fd = fopen("ReGauss_8bits.bin","wb");
    if(fd == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < TEST8; i++)
    {
        rGInvTMatM8(&Mat[i]);
        for(int j = 0; j < 8; j++)
        {
            st = Mat[i].M[j];
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
void m8_test()
{
    M8 Mat1[TEST8], Mat2[TEST8];
    uint8_t st;
    FILE *fd = fopen("WBMatrix_8bits.bin","wb");
    if(fd == NULL)
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
            fwrite(&st, sizeof(st), 1, fd);
        }
    }
    fclose(fd);
}
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
int main()
{
    m8_test();
    m16_test();
    m32_test();
    m64_test();
    m128_test();
    randMat_m8_test();
    reGauss_m8_test();
    return 0;
}