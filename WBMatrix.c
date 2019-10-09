#include "WBMatrix.h"
int initM8(M8 *Mat)//initial Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=0;
    }
}
int initM32(M32 *Mat)//initial Matrix 32*32
{
    for(int i=0;i<32;i++)
    {
        (*Mat).M[i]=0;
    }
}
int initV8(V8 *Vec)//initial Vector 8*1
{
    (*Vec).V=0;
}
int initV32(V32 *Vec)//initial Vector 32*1
{
    (*Vec).V=0;
}
int randM8(M8 *Mat)//randomize Matrix 8*8 
{
    srand((randseed++)^time(NULL));
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
int identityM32(M32 *Mat)//identity matrix 32*32
{
    (*Mat).M[31]=1;
    for(int i=30;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
int randV8(V8 *Vec)//randomize Vector 8*1
{
    srand((randseed++)^time(NULL));
    (*Vec).V=rand()%256;
}
int randV32(V32 *Vec)//randomize Vector 32*1
{
    uint16_t *v=(uint16_t*)&((*Vec).V);
    srand((randseed++)^time(NULL));
    *(v+1)=rand()%65536;
    *v=rand()%65536;
}
int printM8(M8 Mat)//printf Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        printf("0x%x\n",Mat.M[i]);
    }
}
int printM32(M32 Mat)//printf Matrix 32*32
{
    for(int i=0;i<32;i++)
    {
        printf("0x%x\n",Mat.M[i]);
    }
}
int printV8(V8 Vec)//printf Vector 8*1
{
    printf("0x%x\n",Vec.V);
}
int printV32(V32 Vec)//printf Vector 32*1
{
    printf("0x%x\n",Vec.V);
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
int affineU32(Aff32 aff,uint32_t *arr)//32bits affine transformation
{
    uint32_t temp=0;
    if(xorU32(aff.Mat.M[0]&(*arr))) temp^=0x00000001;
    for(int i=1;i<32;i++)
    {
        temp=temp<<1;
        if(xorU32(aff.Mat.M[i]&(*arr))) temp^=0x00000001;//mul,add are equal to and,xor 
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
int xorU32(uint32_t n)// uint32_t internal xor
{
    uint8_t temp=0;
    uint8_t* u=(uint8_t*)&n;
    temp=(*u)^(*(u+1))^(*(u+2))^(*(u+3));
    if(xorU8(temp)) return 1;
    else return 0;
}
int printU8(uint8_t n)//printf uint8_t
{
    printf("0x%x\n",n);
}
int printU32(uint32_t n)//printf uint32_t
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
    printf("\n");
}
int printbitM32(M32 Mat)//printf Matrix 32*32 in the form of bits 
{
    uint32_t temp;
    for(int i=0;i<32;i++)
    {
        temp=Mat.M[i];
        for(int j=0;j<32;j++)
        {
            if(temp&0x80000000) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        printf("\n");
    }
    printf("\n");
}
int MatMulVecM8(M8 Mat,V8 Vec,V8 *ans)//matrix * vector -> vector 8*1
{
    (*ans).V=0;
    if(xorU8(Mat.M[0]&Vec.V)) (*ans).V^=0x01;
    for(int i=1;i<8;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU8(Mat.M[i]&Vec.V)) (*ans).V^=0x01;
    }
}
int MatMulVecM32(M32 Mat,V32 Vec,V32 *ans)//matrix * vector -> vector 32*1
{
    (*ans).V=0;
    if(xorU32(Mat.M[0]&Vec.V)) (*ans).V^=0x00000001;
    for(int i=1;i<32;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU32(Mat.M[i]&Vec.V)) (*ans).V^=0x00000001;
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
    srand((randseed++)^time(NULL));
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
    MatMulVecM8((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
int affinepairM32(Aff32 *aff,Aff32 *aff_inv)//generate a pair of affine
{
    int n=100;//generate times
    int p,q;
    uint32_t temp;
    int swaporadd[3]={1,0,1};
    int trail[n][3];
    identityM32(&(aff->Mat));
    identityM32(&(aff_inv->Mat));
    randV32(&(aff->Vec));
    srand((randseed++)^time(NULL));
    for(int i=0;i<n;i++)//generate reversible matrix
    {
        if(swaporadd[rand()%3])//add
        {
            p=rand()%32;
            q=rand()%32;
            while(p==q)
            {
                p=rand()%32;
                q=rand()%32;
            }
            (*aff).Mat.M[p]^=(*aff).Mat.M[q];
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            p=rand()%32;
            q=rand()%32;
            while(p==q)
            {
                p=rand()%32;
                q=rand()%32;
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
    MatMulVecM32((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
int affinecomM8to32(Aff8 aff1,Aff8 aff2,Aff8 aff3,Aff8 aff4,Aff32 *aff)//diagonal line affine combine,four 8*8 -> 32*32
{
    int j=0;
    uint8_t* m;
    uint8_t* v;
    initM32(&(aff->Mat));

    v=(uint8_t*)&(*aff).Vec.V;
    *(v+3)=aff1.Vec.V;
    *(v+2)=aff2.Vec.V;
    *(v+1)=aff3.Vec.V;
    *v=aff4.Vec.V;

    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*aff).Mat.M[j];
        *(m+3)=aff1.Mat.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*aff).Mat.M[j];
        *(m+2)=aff2.Mat.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*aff).Mat.M[j];
        *(m+1)=aff3.Mat.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*aff).Mat.M[j];
        *m=aff4.Mat.M[i];
        j++;
    }
}
int MattransM8(M8 Mat,M8 *Mat_trans)
{
    initM8(Mat_trans);
    for(int i=0;i<8;i++)
    {
        if((Mat.M[0]<<i)&0x80) (*Mat_trans).M[i]^=0x01;
        for(int j=1;j<8;j++)
        {
            (*Mat_trans).M[i]=(*Mat_trans).M[i]<<1;
            if((Mat.M[j]<<i)&0x80) (*Mat_trans).M[i]^=0x01;
        }
    }
}
int affinemixM8(Aff8 aff1,Aff8 aff2,Aff8 *aff)
{

}