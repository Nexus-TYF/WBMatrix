#include "WBMatrix.h"
int initM8(struct M8 *Mat)//initial Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=0;
    }
}
int initV8(struct V8 *Vec)//initial Vector 8*1
{
    (*Vec).V=0;
}
int randM8(struct M8 *Mat)//randomize Matrix 8*8 
{
    srand(time(NULL));
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=rand()%256;
    }
}
int randV8(struct V8 *Vec)//randomize Vector 8*1
{
    srand(time(NULL));
    (*Vec).V=rand()%256;
}
int printM8(struct M8 Mat)
{
    for(int i=0;i<8;i++)
    {
        printf("%x\n",Mat.M[i]);
    }
}
int printV8(struct V8 Vec)
{
    printf("%x\n",Vec.V);
}
int affineB1(struct M8 Mat,uint8_t *arr,struct V8 Vec)//1 byte(8 bits) array affine
{
    uint8_t temp=0;
    if(xorByte(Mat.M[0]&(*arr))) temp=temp^0x01;
    for(int i=1;i<8;i++)
    {
        temp=temp<<1;
        if(xorByte(Mat.M[i]&(*arr))) temp=temp^0x01;//mul,add are equal to and,xor 
    }
    (*arr)=temp^Vec.V;
}
int xorByte(uint8_t B)
{
    int count=0;
    for(int i=0;i<8;i++)
    {
        if(B&0x01) count++;
        B=B>>1;
    }
    if(count==1||count==3||count==5||count==7) return 1;
    else return 0;
}






