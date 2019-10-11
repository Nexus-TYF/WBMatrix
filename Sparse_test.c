#include "WBMatrix.h"
#define N 10000
double quantof1M8(M8 Mat)
{
    double count=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(Mat.M[i]&0x01) count++;
            Mat.M[i]=Mat.M[i]>>1;
        }
    }
    return (count/64.0);
}
double quantof1M32(M32 Mat)
{
    double count=0;
    for(int i=0;i<32;i++)
    {
        for(int j=0;j<32;j++)
        {
            if(Mat.M[i]&0x00000001) count++;
            Mat.M[i]=Mat.M[i]>>1;
        }
    }
    return (count/1024.0);
}
int main()
{
    /*Aff8 aff1,aff1_inv;
    double scale=0.0;
    for(int i=0;i<N;i++)
    {
        affinepairM8(&aff1,&aff1_inv);
        scale+=quantof1M8(aff1.Mat);
    }
    printf("the proporton of the quantity of 1 is :%0.4f\n",(scale/N));*/

    Aff32 aff2,aff2_inv;
    double scale1=0.0;
    for(int i=0;i<N;i++)
    {
        affinepairM32(&aff2,&aff2_inv);
        scale1+=quantof1M32(aff2.Mat);
    }
    printf("the proporton of the quantity of 1 is :%0.4f\n",(scale1/N));
    return 0;
}