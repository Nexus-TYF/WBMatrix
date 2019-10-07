#include "WBMatrix.h"
int initM8(M8 *Mat)//initial Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=0;
    }
}
int initV8(V8 *Vec)//initial Vector 8*1
{
    (*Vec).V=0;
}
int randM8(M8 *Mat)//randomize Matrix 8*8 
{
    srand(time(NULL));
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=rand()%256;
    }
}
int identityM8(M8 *Mat)//identity matrix 8*8
{
    (*Mat).M[7]=1;
    for(int i=6;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
int randV8(V8 *Vec)//randomize Vector 8*1
{
    srand(time(NULL));
    (*Vec).V=rand()%256;
}
int printM8(M8 Mat)//printf Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        printf("%x\n",Mat.M[i]);
    }
}
int printV8(V8 Vec)//printf Vector 8*1
{
    printf("%x\n",Vec.V);
}
int affineU8(Aff8 aff,uint8_t *arr)//8bits affine transformation
{
    uint8_t temp=0;
    if(xorU8(aff.Mat.M[0]&(*arr))) temp^=0x01;
    for(int i=1;i<8;i++)
    {
        temp=temp<<1;
        if(xorU8(aff.Mat.M[i]&(*arr))) temp^=0x01;//mul,add are equal to and,xor 
    }
    (*arr)=temp^aff.Vec.V;
}
int xorU8(uint8_t n)// uint8_t internal xor
{
    int count=0;
    for(int i=0;i<8;i++)
    {
        if(n&0x01) count++;
        n=n>>1;
    }
    if(count&0x01==1) return 1;
    else return 0;
}
int printU8(uint8_t n)//printf uint8_t
{
    printf("0x%x\n",n);
}
int printbitM8(M8 Mat)//printf Matrix 8*8 in the form of bits 
{
    uint8_t temp;
    for(int i=0;i<8;i++)
    {
        temp=Mat.M[i];
        for(int j=0;j<8;j++)
        {
            if(temp&0x80) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        printf("\n");
    }
}
int MatMulVec(M8 Mat,V8 Vec,V8 *ans)//matrix * vector -> vector 8*1
{
    (*ans).V=0;
    if(xorU8(Mat.M[0]&Vec.V)) (*ans).V^=0x01;
    for(int i=1;i<8;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU8(Mat.M[i]&Vec.V)) (*ans).V^=0x01;
    }
}
int affinepairM8(Aff8 *aff,Aff8 *aff_inv)//generate a pair of affine
{
    int n=30;//generate times
    int p,q;
    uint8_t temp;
    int swaporadd[3]={1,0,1};
    int trail[n][3];
    identityM8(&(aff->Mat));
    identityM8(&(aff_inv->Mat));
    randV8(&(aff->Vec));
    srand(time(NULL));
    for(int i=0;i<n;i++)//generate reversible matrix
    {
        if(swaporadd[rand()%3])//add
        {
            p=rand()%8;
            q=rand()%8;
            while(p==q)
            {
                p=rand()%8;
                q=rand()%8;
            }
            (*aff).Mat.M[p]^=(*aff).Mat.M[q];
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            p=rand()%8;
            q=rand()%8;
            while(p==q)
            {
                p=rand()%8;
                q=rand()%8;
            }
            temp=(*aff).Mat.M[p];
            (*aff).Mat.M[p]=(*aff).Mat.M[q];
            (*aff).Mat.M[q]=temp;
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=n-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*aff_inv).Mat.M[trail[j][1]]^=(*aff_inv).Mat.M[trail[j][2]];
        }
        else//swap
        {
            temp=(*aff_inv).Mat.M[trail[j][1]];
            (*aff_inv).Mat.M[trail[j][1]]=(*aff_inv).Mat.M[trail[j][2]];
            (*aff_inv).Mat.M[trail[j][2]]=temp;
        }   
    }
    MatMulVec((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}