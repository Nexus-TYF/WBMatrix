//Gaussian elimination Method Base on WBMatrix 
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

uint8_t identM8[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
int isinvertM8(M8 Mat)
{
    uint8_t temp;
    for(int i=0;i<8;i++)
    {
        if((Mat.M[i]&identM8[i])==identM8[i])
        {
            for(int j=i+1;j<8;j++)
            {
                if((Mat.M[j]&identM8[i])==identM8[i])
                {
                    Mat.M[j]^=Mat.M[i];
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
                    break;
                }
            }
            for(int k=i+1;k<8;k++)
            {
                if((Mat.M[k]&identM8[i])==identM8[i])
                {
                    Mat.M[k]^=Mat.M[i];
                }
            }
        }
    }
    printbitM8(Mat);
    if((Mat.M[7]&identM8[7])==identM8[7]) return 1;
    else return 0;
}

void diagdominM8(M8 *Mat)
{
    uint8_t temp;
    int flag;
    srand((randseed++)^time(NULL));
    for(int i=0;i<8;i++)
    {
        flag=1;
        while(flag)
        {
            flag=0;
            temp=rand()%256;
            while(!( ((temp&identM8[i])==identM8[i]) && xorU8(temp) ) )
            {
                temp=rand()%256;
            }
            for(int j=0;j<i;j++)
            {
                if((*Mat).M[j]==temp) flag=1;
            }
        }
        (*Mat).M[i]=temp;
    }
}

int main()
{
    // int ans=0;
    // M8 mat[100000];
    // for(int i=0;i<100000;i++)
    // {
    //     randM8(&mat[i]);
    // }
    // for(int j=0;j<100000;j++)
    // {
    //     ans+=isinvertM8(mat[j]);
    // }
    M8 mat;
    int ans;
    diagdominM8(&mat);
    printbitM8(mat);
    ans=isinvertM8(mat);
    //printf("invert?:%d\n",ans);
    return 0;
}
