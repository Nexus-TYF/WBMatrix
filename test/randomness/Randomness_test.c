#include "WBMatrix/WBMatrix.h"
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
    M8 Mat[TEST8], Mat_inv[TEST8];
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
        rGInvTMatM8(&Mat[i]);
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
    M8 iim8_1,iim8_2,iim8_3,iim8_4;
    identityM8(&iim8_4);
    int i;
    for(i=0;i<TEST8;i++)
    {
        newmethod2_genMatpairM8(&iim8_1,&iim8_2);
        MatMulMatM8(iim8_1,iim8_2,&iim8_3);
        if(!isequalM8(iim8_3,iim8_4)) break;
    }
    if(i<TEST8) {printf("8bit: ERROR\n");}
    else printf("8bit: OK\n");
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
    M8 m8,m8_inv;
    begin = start_rdtsc();
    for (i = 0; i < TEST8; i++)
    {
        newmethod2_ReGauss_genMatpairM8(&m8,&m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2_ReGauss generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST8);
    begin = start_rdtsc();
    for (i = 0; i < TEST8; i++)
    {
        newmethod2_strict_genMatpairM8(&m8,&m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2_strict generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST8);
    begin = start_rdtsc();
    for (i = 0; i < TEST8; i++)
    {
        newmethod2_genMatpairM8(&m8,&m8_inv);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("newmethod2 generate 8*8 matrix and its inverse matirx cost %llu CPU cycles\n", (ans) / TEST8);
}
int main()
{
    // m8_test();
    // m16_test();
    // m32_test();
    // m64_test();
    // m128_test();
    // RandMat_m8_test();
    // ReGauss_m8_test();
    // newmethod_m8_test();
    // RandbitMat_m8_test();
    // newmethod2_m8_test();
    newmethod2_strict_m8_test();
    newmethod2_ReGauss_m8_test();
    newmethod2_m8_test();
    //performance();
    //accuracy();
    return 0;
}