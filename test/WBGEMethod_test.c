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
                }
            }
        }
        printbitM8(Mat); 
    }
    //printbitM8(Mat);
    if(Mat.M[7]==0x01) return 1;
    else return 0;
}

int main()
{
    int ans;
    M8 mat[3][3];
    initinvbaseM8(initM8_max);
    for(int i=0;i<3;i++)
    {
        genMatpairM8(&mat[i][0],&mat[i][1]);
        MatMulMatM8(mat[i][0],mat[i][1],&mat[i][3]);
        printM8(mat[i][3]);
        initinvbaseM8(initM8_max);
    }
    //ans=isinvertM8(mat[0][0]);
    // printf("invert?: %d\n",ans);
    // ans=isinvertM8(mat[0][1]);
    // printf("invert?: %d\n",ans);
    return 0;
}
