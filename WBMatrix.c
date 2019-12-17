#include "WBMatrix.h"
#include "xor.h"
#include "inverse.h"

void initM8(M8 *Mat)//initial Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=0;
    }
}
void initM16(M16 *Mat)//initial Matrix 16*16
{
    for(int i=0;i<16;i++)
    {
        (*Mat).M[i]=0;
    }
}
void initM32(M32 *Mat)//initial Matrix 32*32
{
    for(int i=0;i<32;i++)
    {
        (*Mat).M[i]=0;
    }
}
void initM64(M64 *Mat)//initial Matrix 64*64
{
    for(int i=0;i<64;i++)
    {
        (*Mat).M[i]=0;
    }
}
void initM128(M128 *Mat)//initial Matrix 128*128
{
    for(int i=0;i<128;i++)
    {
        (*Mat).M[i][0]=0;
        (*Mat).M[i][1]=0;
    }
}
void initV8(V8 *Vec)//initial Vector 8*1
{
    (*Vec).V=0;
}
void initV16(V16 *Vec)//initial Vector 16*1
{
    (*Vec).V=0;
}
void initV32(V32 *Vec)//initial Vector 32*1
{
    (*Vec).V=0;
}
void initV64(V64 *Vec)//initial Vector 64*1
{
    (*Vec).V=0;
}
void initV128(V128 *Vec)//initial Vector 128*1
{
    (*Vec).V[0]=0;
    (*Vec).V[1]=0;
}
void randM8(M8 *Mat)//randomize Matrix 8*8 
{
    srand((randseed++)^time(NULL));
    for(int i=0;i<8;i++)
    {
        (*Mat).M[i]=rand()%256;
    }
}
void randM16(M16 *Mat)//randomize Matrix 16*16 
{
    srand((randseed++)^time(NULL));
    for(int i=0;i<16;i++)
    {
        (*Mat).M[i]=rand()%65536;
    }
}
void randM32(M32 *Mat)//randomize Matrix 32*32 
{
    uint16_t *m;
    srand((randseed++)^time(NULL));
    for(int i=0;i<32;i++)
    {
        m=(uint16_t*)&((*Mat).M[i]);
        *(m+1)=rand()%65536;
        *m=rand()%65536;
    }
}
void randM64(M64 *Mat)//randomize Matrix 64*64 
{
    uint16_t *m;
    srand((randseed++)^time(NULL));
    for(int i=0;i<64;i++)
    {
        m=(uint16_t*)&((*Mat).M[i]);
        *(m+3)=rand()%65536;
        *(m+2)=rand()%65536;
        *(m+1)=rand()%65536;
        *m=rand()%65536;
    }
}
void randM128(M128 *Mat)//randomize Matrix 128*128 
{
    uint16_t *m;
    srand((randseed++)^time(NULL));
    for(int i=0;i<128;i++)
    {
        m=(uint16_t*)&((*Mat).M[i][0]);
        *(m+3)=rand()%65536;
        *(m+2)=rand()%65536;
        *(m+1)=rand()%65536;
        *m=rand()%65536;
        m=(uint16_t*)&((*Mat).M[i][1]);
        *(m+3)=rand()%65536;
        *(m+2)=rand()%65536;
        *(m+1)=rand()%65536;
        *m=rand()%65536;
    }
}
void identityM8(M8 *Mat)//identity matrix 8*8
{
    (*Mat).M[7]=1;
    for(int i=6;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
void identityM16(M16 *Mat)//identity matrix 16*16
{
    (*Mat).M[15]=1;
    for(int i=14;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
void identityM32(M32 *Mat)//identity matrix 32*32
{
    (*Mat).M[31]=1;
    for(int i=30;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
void identityM64(M64 *Mat)//identity matrix 64*64
{
    (*Mat).M[63]=1;
    for(int i=62;i>=0;i--)
    {
        (*Mat).M[i]=(*Mat).M[i+1]<<1;
    }
}
void identityM128(M128 *Mat)//identity matrix 128*128
{
    initM128(Mat);
    (*Mat).M[127][1]=1;
    for(int i=126;i>=64;i--)
    {
        (*Mat).M[i][1]=(*Mat).M[i+1][1]<<1;
    }
    for(int i=63;i>=0;i--)
    {
        (*Mat).M[i][0]=(*Mat).M[i+64][1];
    }
}
void randV8(V8 *Vec)//randomize Vector 8*1
{
    srand((randseed++)^time(NULL));
    (*Vec).V=rand()%256;
}
void randV16(V16 *Vec)//randomize Vector 16*1
{
    srand((randseed++)^time(NULL));
    (*Vec).V=rand()%65536;
}
void randV32(V32 *Vec)//randomize Vector 32*1
{
    uint16_t *v=(uint16_t*)&((*Vec).V);
    srand((randseed++)^time(NULL));
    *(v+1)=rand()%65536;
    *v=rand()%65536;
}
void randV64(V64 *Vec)//randomize Vector 64*1
{
    uint16_t *v=(uint16_t*)&((*Vec).V);
    srand((randseed++)^time(NULL));
    *(v+3)=rand()%65536;
    *(v+2)=rand()%65536;
    *(v+1)=rand()%65536;
    *v=rand()%65536;
}
void randV128(V128 *Vec)//randomize Vector 128*1
{
    uint16_t *v=(uint16_t*)&((*Vec).V[0]);
    srand((randseed++)^time(NULL));
    *(v+3)=rand()%65536;
    *(v+2)=rand()%65536;
    *(v+1)=rand()%65536;
    *v=rand()%65536;
    v=(uint16_t*)&((*Vec).V[1]);
    *(v+3)=rand()%65536;
    *(v+2)=rand()%65536;
    *(v+1)=rand()%65536;
    *v=rand()%65536;
}
void printM8(M8 Mat)//printf Matrix 8*8
{
    for(int i=0;i<8;i++)
    {
        printf("0x%x\n",Mat.M[i]);
    }
}
void printM16(M16 Mat)//printf Matrix 16*16
{
    for(int i=0;i<16;i++)
    {
        printf("0x%x\n",Mat.M[i]);
    }
}
void printM32(M32 Mat)//printf Matrix 32*32
{
    for(int i=0;i<32;i++)
    {
        printf("0x%x\n",Mat.M[i]);
    }
}
void printM64(M64 Mat)//printf Matrix 64*64
{
    for(int i=0;i<64;i++)
    {
        printf("0x%llx\n",Mat.M[i]);
    }
}
void printM128(M128 Mat)//printf Matrix 128*128
{
    for(int i=0;i<128;i++)
    {
        printf("0x%llx ",Mat.M[i][0]);
        printf("0x%llx\n",Mat.M[i][1]);
    }
}
void printV8(V8 Vec)//printf Vector 8*1
{
    printf("0x%x\n",Vec.V);
}
void printV16(V16 Vec)//printf Vector 16*1
{
    printf("0x%x\n",Vec.V);
}
void printV32(V32 Vec)//printf Vector 32*1
{
    printf("0x%x\n",Vec.V);
}
void printV64(V64 Vec)//printf Vector 64*1
{
    printf("0x%llx\n",Vec.V);
}
void printV128(V128 Vec)//printf Vector 128*1
{
    printf("0x%llx ",Vec.V[0]);
    printf("0x%llx\n",Vec.V[1]);
}
void copyM8(M8 Mat1,M8 *Mat2)
{
    for(int i=0;i<8;i++)
    {
        (*Mat2).M[i]=Mat1.M[i];
    }
}
void copyM16(M16 Mat1,M16 *Mat2)
{
    for(int i=0;i<16;i++)
    {
        (*Mat2).M[i]=Mat1.M[i];
    }
}
void copyM32(M32 Mat1,M32 *Mat2)
{
    for(int i=0;i<32;i++)
    {
        (*Mat2).M[i]=Mat1.M[i];
    }
}
void copyM64(M64 Mat1,M64 *Mat2)
{
    for(int i=0;i<64;i++)
    {
        (*Mat2).M[i]=Mat1.M[i];
    }
}
void copyM128(M128 Mat1,M128 *Mat2)
{
    for(int i=0;i<128;i++)
    {
        (*Mat2).M[i][0]=Mat1.M[i][0];
        (*Mat2).M[i][1]=Mat1.M[i][1];
    }
}
uint8_t affineU8(Aff8 aff,uint8_t arr)//8bits affine transformation
{
    V8 mul_vec,ans_vec;
    mul_vec.V=arr;
    MatMulVecM8(aff.Mat,mul_vec,&ans_vec);//mul
    return ans_vec.V^aff.Vec.V;//add
}
uint16_t affineU16(Aff16 aff,uint16_t arr)//16bits affine transformation
{
    V16 mul_vec,ans_vec;
    mul_vec.V=arr;
    MatMulVecM16(aff.Mat,mul_vec,&ans_vec);//mul
    return ans_vec.V^aff.Vec.V;//add
}
uint32_t affineU32(Aff32 aff,uint32_t arr)//32bits affine transformation
{
    V32 mul_vec,ans_vec;
    mul_vec.V=arr;
    MatMulVecM32(aff.Mat,mul_vec,&ans_vec);//mul
    return ans_vec.V^aff.Vec.V;//add
}
uint64_t affineU64(Aff64 aff,uint64_t arr)//64bits affine transformation
{
    V64 mul_vec,ans_vec;
    mul_vec.V=arr;
    MatMulVecM64(aff.Mat,mul_vec,&ans_vec);//mul
    return ans_vec.V^aff.Vec.V;//add
}
void affineU128(Aff128 aff,uint64_t arr[],uint64_t ans[])//128bits affine transformation
{
    V128 mul_vec,ans_vec;
    mul_vec.V[0]=arr[0];
    mul_vec.V[1]=arr[1];
    MatMulVecM128(aff.Mat,mul_vec,&ans_vec);//mul
    ans[0]=ans_vec.V[0]^aff.Vec.V[0];//add
    ans[1]=ans_vec.V[1]^aff.Vec.V[1];
}
int xorU8(uint8_t n)// uint8_t internal xor
{
    if(xor[n]) return 1;
    else return 0;
}
int xorU16(uint16_t n)// uint16_t internal xor
{
    uint8_t temp=0;
    uint8_t* u=(uint8_t*)&n;
    temp=(*u)^(*(u+1));
    if(xorU8(temp)) return 1;
    else return 0;
}
int xorU32(uint32_t n)// uint32_t internal xor
{
    uint16_t temp=0;
    uint16_t* u=(uint16_t*)&n;
    temp=(*u)^(*(u+1));
    if(xorU16(temp)) return 1;
    else return 0;
}
int xorU64(uint64_t n)// uint64_t internal xor
{
    uint32_t temp=0;
    uint32_t* u=(uint32_t*)&n;
    temp=(*u)^(*(u+1));
    if(xorU32(temp)) return 1;
    else return 0;
}
int xorU128(uint64_t n[])// uint128_t internal xor
{
    uint64_t temp=0;
    temp=n[0]^n[1];
    if(xorU64(temp)) return 1;
    else return 0;
}
void printU8(uint8_t n)//printf uint8_t
{
    printf("0x%x\n",n);
}
void printU16(uint16_t n)//printf uint16_t
{
    printf("0x%x\n",n);
}
void printU32(uint32_t n)//printf uint32_t
{
    printf("0x%x\n",n);
}
void printU64(uint64_t n)//printf uint64_t
{
    printf("0x%x\n",n);
}
void printU128(uint64_t n[])//printf uint128_t
{
    printf("0x%x ",n[0]);
    printf("0x%x\n",n[1]);
}
void printbitM8(M8 Mat)//printf Matrix 8*8 in the form of bits 
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
void printbitM16(M16 Mat)//printf Matrix 16*16 in the form of bits 
{
    uint16_t temp;
    for(int i=0;i<16;i++)
    {
        temp=Mat.M[i];
        for(int j=0;j<16;j++)
        {
            if(temp&0x8000) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        printf("\n");
    }
    printf("\n");
}
void printbitM32(M32 Mat)//printf Matrix 32*32 in the form of bits 
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
void printbitM64(M64 Mat)//printf Matrix 64*64 in the form of bits 
{
    uint64_t temp;
    for(int i=0;i<64;i++)
    {
        temp=Mat.M[i];
        for(int j=0;j<64;j++)
        {
            if(temp&0x8000000000000000) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        printf("\n");
    }
    printf("\n");
}
void printbitM128(M128 Mat)//printf Matrix 128*128 in the form of bits 
{
    uint64_t temp;
    for(int i=0;i<128;i++)
    {
        temp=Mat.M[i][0];
        for(int j=0;j<64;j++)
        {
            if(temp&0x8000000000000000) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        temp=Mat.M[i][1];
        for(int j=0;j<64;j++)
        {
            if(temp&0x8000000000000000) printf("%d ",1);
            else printf("%d ",0);
            temp=temp<<1;
        }
        printf("\n");
    }
    printf("\n");
}
void MatMulVecM8(M8 Mat,V8 Vec,V8 *ans)//matrix * vector -> vector 8*1
{
    initV8(ans);
    if(xorU8(Mat.M[0]&Vec.V)) (*ans).V^=0x01;
    for(int i=1;i<8;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU8(Mat.M[i]&Vec.V)) (*ans).V^=0x01;
    }
}
void MatMulVecM16(M16 Mat,V16 Vec,V16 *ans)//matrix * vector -> vector 16*1
{
    initV16(ans);
    if(xorU16(Mat.M[0]&Vec.V)) (*ans).V^=0x0001;
    for(int i=1;i<16;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU16(Mat.M[i]&Vec.V)) (*ans).V^=0x0001;
    }
}
void MatMulVecM32(M32 Mat,V32 Vec,V32 *ans)//matrix * vector -> vector 32*1
{
    initV32(ans);
    if(xorU32(Mat.M[0]&Vec.V)) (*ans).V^=0x00000001;
    for(int i=1;i<32;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU32(Mat.M[i]&Vec.V)) (*ans).V^=0x00000001;
    }
}
void MatMulVecM64(M64 Mat,V64 Vec,V64 *ans)//matrix * vector -> vector 64*1
{
    initV64(ans);
    if(xorU64(Mat.M[0]&Vec.V)) (*ans).V^=0x0000000000000001;
    for(int i=1;i<64;i++)
    {
        (*ans).V=(*ans).V<<1;
        if(xorU64(Mat.M[i]&Vec.V)) (*ans).V^=0x0000000000000001;
    }
}
void MatMulVecM128(M128 Mat,V128 Vec,V128 *ans)//matrix * vector -> vector 128*1
{
    initV128(ans);
    uint64_t temp[2]; 
    temp[0]=Mat.M[0][0]&Vec.V[0];
    temp[1]=Mat.M[0][1]&Vec.V[1];
    if(xorU128(temp)) (*ans).V[0]^=0x0000000000000001;
    for(int i=1;i<64;i++)
    {
        (*ans).V[0]=(*ans).V[0]<<1;
        temp[0]=Mat.M[i][0]&Vec.V[0];
        temp[1]=Mat.M[i][1]&Vec.V[1];
        if(xorU128(temp)) (*ans).V[0]^=0x0000000000000001;
    }
    temp[0]=Mat.M[64][0]&Vec.V[0];
    temp[1]=Mat.M[64][1]&Vec.V[1];
    if(xorU128(temp)) (*ans).V[1]^=0x0000000000000001;
    for(int i=65;i<128;i++)
    {
        (*ans).V[1]=(*ans).V[1]<<1;
        temp[0]=Mat.M[i][0]&Vec.V[0];
        temp[1]=Mat.M[i][1]&Vec.V[1];
        if(xorU128(temp)) (*ans).V[1]^=0x0000000000000001;
    }
}
void initinvbaseM8(int N)//initial base matrix, parameter: initM8_min , initM8_max
{
    int p,q;
    uint8_t temp;
    srand((randseed++)^time(NULL));
    if(basetrailM8[0][0]!=-1) return ;
    initM8_times=N;
    for(int i=0;i<initM8_times;i++)//generate reversible base matrix
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
            
            baseM8.M[p]^=baseM8.M[q];
            basetrailM8[i][0]=1;
            basetrailM8[i][1]=p;
            basetrailM8[i][2]=q;
        }
        else//swap
        {
            temp=baseM8.M[p];
            baseM8.M[p]=baseM8.M[q];
            baseM8.M[q]=temp;
            basetrailM8[i][0]=0;
            basetrailM8[i][1]=p;
            basetrailM8[i][2]=q;
        }   
    }
}
void genMatpairM8(M8 *Mat,M8 *Mat_inv)//generate 8*8 reversible matrix and its inverse matrix
{
    int p,q;
    uint8_t temp;
    int trail[M8N][3];// generate trail
    copyM8(baseM8,Mat);//copy base matrix
    identityM8(Mat_inv);
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
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=M8N-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*Mat_inv).M[trail[j][1]]^= (*Mat_inv).M[trail[j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[trail[j][1]];
            (*Mat_inv).M[trail[j][1]]= (*Mat_inv).M[trail[j][2]];
            (*Mat_inv).M[trail[j][2]]=temp;
        }   
    }
    if(basetrailM8[0][0]!=-1)//base matrix
    {
        for(int j=initM8_times-1;j>=0;j--)//generate inverse matrix
        {
            if(basetrailM8[j][0])//add
            {
                (*Mat_inv).M[basetrailM8[j][1]]^= (*Mat_inv).M[basetrailM8[j][2]];
            }
            else//swap
            {
                temp= (*Mat_inv).M[basetrailM8[j][1]];
                (*Mat_inv).M[basetrailM8[j][1]]= (*Mat_inv).M[basetrailM8[j][2]];
                (*Mat_inv).M[basetrailM8[j][2]]=temp;
            }   
        }
    }
}
void initinvbaseM16(int N)//initial base matrix, parameter: initM16_min , initM16_max
{
    int p,q;
    uint16_t temp;
    srand((randseed++)^time(NULL));
    if(basetrailM16[0][0]!=-1) return ;
    initM16_times=N;
    for(int i=0;i<initM16_times;i++)//generate reversible base matrix
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
            
            baseM16.M[p]^=baseM16.M[q];
            basetrailM16[i][0]=1;
            basetrailM16[i][1]=p;
            basetrailM16[i][2]=q;
        }
        else//swap
        {
            temp=baseM16.M[p];
            baseM16.M[p]=baseM16.M[q];
            baseM16.M[q]=temp;
            basetrailM16[i][0]=0;
            basetrailM16[i][1]=p;
            basetrailM16[i][2]=q;
        }   
    }
}
void genMatpairM16(M16 *Mat,M16 *Mat_inv)//generate 16*16 reversible matrix and its inverse matrix
{
    int p,q;
    uint16_t temp;
    int trail[M16N][3];
    copyM16(baseM16,Mat);//copy base matrix
    identityM16(Mat_inv);
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
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            p=rand()%16;
            q=rand()%16;
            while(p==q)
            {
                p=rand()%16;
                q=rand()%16;
            }
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=M16N-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*Mat_inv).M[trail[j][1]]^= (*Mat_inv).M[trail[j][2]];
        }
        else//swap
        {
            temp= (*Mat_inv).M[trail[j][1]];
            (*Mat_inv).M[trail[j][1]]=(*Mat_inv).M[trail[j][2]];
            (*Mat_inv).M[trail[j][2]]=temp;
        }   
    }
    if(basetrailM16[0][0]!=-1)
    {
        for(int j=initM16_times-1;j>=0;j--)//generate inverse matrix for base matrix
        {
            if(basetrailM16[j][0])//add
            {
                (*Mat_inv).M[basetrailM16[j][1]]^= (*Mat_inv).M[basetrailM16[j][2]];
            }
            else//swap
            {
                temp= (*Mat_inv).M[basetrailM16[j][1]];
                (*Mat_inv).M[basetrailM16[j][1]]= (*Mat_inv).M[basetrailM16[j][2]];
                (*Mat_inv).M[basetrailM16[j][2]]=temp;
            }   
        }
    }
}
void initinvbaseM32(int N)//initial base matrix, parameter: initM32_min , initM32_max
{
    int p,q;
    uint32_t temp;
    srand((randseed++)^time(NULL));
    if(basetrailM32[0][0]!=-1) return ;
    initM32_times=N;
    for(int i=0;i<initM32_times;i++)//generate reversible base matrix
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
            
            baseM32.M[p]^=baseM32.M[q];
            basetrailM32[i][0]=1;
            basetrailM32[i][1]=p;
            basetrailM32[i][2]=q;
        }
        else//swap
        {
            temp=baseM32.M[p];
            baseM32.M[p]=baseM32.M[q];
            baseM32.M[q]=temp;
            basetrailM32[i][0]=0;
            basetrailM32[i][1]=p;
            basetrailM32[i][2]=q;
        }   
    }
}
void genMatpairM32(M32 *Mat,M32 *Mat_inv)//generate 32*32 reversible matrix and its inverse matrix
{
    int p,q;
    uint32_t temp;
    int trail[M32N][3];
    copyM32(baseM32,Mat);//copy base matrix
    identityM32(Mat_inv);
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
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=M32N-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*Mat_inv).M[trail[j][1]]^=(*Mat_inv).M[trail[j][2]];
        }
        else//swap
        {
            temp=(*Mat_inv).M[trail[j][1]];
            (*Mat_inv).M[trail[j][1]]=(*Mat_inv).M[trail[j][2]];
            (*Mat_inv).M[trail[j][2]]=temp;
        }   
    }
    if(basetrailM32[0][0]!=-1)
    {
        for(int j=initM32_times-1;j>=0;j--)//generate inverse matrix for base matrix
        {
            if(basetrailM32[j][0])//add
            {
                (*Mat_inv).M[basetrailM32[j][1]]^= (*Mat_inv).M[basetrailM32[j][2]];
            }
            else//swap
            {
                temp= (*Mat_inv).M[basetrailM32[j][1]];
                (*Mat_inv).M[basetrailM32[j][1]]= (*Mat_inv).M[basetrailM32[j][2]];
                (*Mat_inv).M[basetrailM32[j][2]]=temp;
            }   
        }
    }
}
void initinvbaseM64(int N)//initial base matrix, parameter: initM64_min , initM64_max
{
    int p,q;
    uint64_t temp;
    srand((randseed++)^time(NULL));
    if(basetrailM64[0][0]!=-1) return ;
    initM64_times=N;
    for(int i=0;i<initM64_times;i++)//generate reversible base matrix
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
            
            baseM64.M[p]^=baseM64.M[q];
            basetrailM64[i][0]=1;
            basetrailM64[i][1]=p;
            basetrailM64[i][2]=q;
        }
        else//swap
        {
            temp=baseM64.M[p];
            baseM64.M[p]=baseM64.M[q];
            baseM64.M[q]=temp;
            basetrailM64[i][0]=0;
            basetrailM64[i][1]=p;
            basetrailM64[i][2]=q;
        }   
    }
}
void genMatpairM64(M64 *Mat,M64 *Mat_inv)//generate 64*64 reversible matrix and its inverse matrix
{
    int p,q;
    uint64_t temp;
    int trail[M64N][3];
    copyM64(baseM64,Mat);//copy base matrix
    identityM64(Mat_inv);
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
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            temp=(*Mat).M[p];
            (*Mat).M[p]=(*Mat).M[q];
            (*Mat).M[q]=temp;
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=M64N-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*Mat_inv).M[trail[j][1]]^=(*Mat_inv).M[trail[j][2]];
        }
        else//swap
        {
            temp=(*Mat_inv).M[trail[j][1]];
            (*Mat_inv).M[trail[j][1]]=(*Mat_inv).M[trail[j][2]];
            (*Mat_inv).M[trail[j][2]]=temp;
        }   
    }
    if(basetrailM64[0][0]!=-1)
    {
        for(int j=initM64_times-1;j>=0;j--)//generate inverse matrix for base matrix
        {
            if(basetrailM64[j][0])//add
            {
                (*Mat_inv).M[basetrailM64[j][1]]^= (*Mat_inv).M[basetrailM64[j][2]];
            }
            else//swap
            {
                temp= (*Mat_inv).M[basetrailM64[j][1]];
                (*Mat_inv).M[basetrailM64[j][1]]= (*Mat_inv).M[basetrailM64[j][2]];
                (*Mat_inv).M[basetrailM64[j][2]]=temp;
            }   
        }
    }
}
void initinvbaseM128(int N)//initial base matrix, parameter: initM128_min , initM128_max
{
    int p,q;
    uint64_t temp[2];
    srand((randseed++)^time(NULL));
    if(basetrailM128[0][0]!=-1) return ;
    initM128_times=N;
    for(int i=0;i<initM128_times;i++)//generate reversible base matrix
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
            
            baseM128.M[p][0]^=baseM128.M[q][0];
            baseM128.M[p][1]^=baseM128.M[q][1];
            basetrailM128[i][0]=1;
            basetrailM128[i][1]=p;
            basetrailM128[i][2]=q;
        }
        else//swap
        {
            temp[0]=baseM128.M[p][0];
            temp[1]=baseM128.M[p][1];
            baseM128.M[p][0]=baseM128.M[q][0];
            baseM128.M[p][1]=baseM128.M[q][1];
            baseM128.M[q][0]=temp[0];
            baseM128.M[q][1]=temp[1];
            basetrailM128[i][0]=0;
            basetrailM128[i][1]=p;
            basetrailM128[i][2]=q;
        }   
    }
}
void genMatpairM128(M128 *Mat,M128 *Mat_inv)//generate 128*128 reversible matrix and its inverse matrix
{
    int p,q;
    uint64_t temp[2];
    int trail[M128N][3];
    copyM128(baseM128,Mat);
    identityM128(Mat_inv);
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
            trail[i][0]=1;
            trail[i][1]=p;
            trail[i][2]=q;
        }
        else//swap
        {
            temp[0]=(*Mat).M[p][0];
            (*Mat).M[p][0]=(*Mat).M[q][0];
            (*Mat).M[q][0]=temp[0];
            temp[1]=(*Mat).M[p][1];
            (*Mat).M[p][1]=(*Mat).M[q][1];
            (*Mat).M[q][1]=temp[1];
            trail[i][0]=0;
            trail[i][1]=p;
            trail[i][2]=q;
        }   
    }
    for(int j=M128N-1;j>=0;j--)//generate inverse matrix
    {
        if(trail[j][0])//add
        {
            (*Mat_inv).M[trail[j][1]][0]^=(*Mat_inv).M[trail[j][2]][0];
            (*Mat_inv).M[trail[j][1]][1]^=(*Mat_inv).M[trail[j][2]][1];
        }
        else//swap
        {
            temp[0]=(*Mat_inv).M[trail[j][1]][0];
            (*Mat_inv).M[trail[j][1]][0]=(*Mat_inv).M[trail[j][2]][0];
            (*Mat_inv).M[trail[j][2]][0]=temp[0];
            temp[1]=(*Mat_inv).M[trail[j][1]][1];
            (*Mat_inv).M[trail[j][1]][1]=(*Mat_inv).M[trail[j][2]][1];
            (*Mat_inv).M[trail[j][2]][1]=temp[1];
        }   
    }
    if(basetrailM128[0][0]!=-1)
    {
        for(int j=initM128_times-1;j>=0;j--)//generate inverse matrix for base matrix
        {
            if(basetrailM128[j][0])//add
            {
                (*Mat_inv).M[basetrailM128[j][1]][0]^= (*Mat_inv).M[basetrailM128[j][2]][0];
                (*Mat_inv).M[basetrailM128[j][1]][1]^= (*Mat_inv).M[basetrailM128[j][2]][1];
            }
            else//swap
            {
                temp[0]= (*Mat_inv).M[basetrailM128[j][1]][0];
                (*Mat_inv).M[basetrailM128[j][1]][0]= (*Mat_inv).M[basetrailM128[j][2]][0];
                (*Mat_inv).M[basetrailM128[j][2]][0]=temp[0];
                temp[1]= (*Mat_inv).M[basetrailM128[j][1]][1];
                (*Mat_inv).M[basetrailM128[j][1]][1]= (*Mat_inv).M[basetrailM128[j][2]][1];
                (*Mat_inv).M[basetrailM128[j][2]][1]=temp[1];
            }   
        }
    }
}
void genaffinepairM8(Aff8 *aff,Aff8 *aff_inv)//generate a pair of affine
{
    genMatpairM8(&(aff->Mat),&(aff_inv->Mat));
    randV8(&(aff->Vec));
    MatMulVecM8((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
void genaffinepairM16(Aff16 *aff,Aff16 *aff_inv)//generate a pair of affine
{
    genMatpairM16(&(aff->Mat),&(aff_inv->Mat));
    randV16(&(aff->Vec));
    MatMulVecM16((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
void genaffinepairM32(Aff32 *aff,Aff32 *aff_inv)//generate a pair of affine
{
    genMatpairM32(&(aff->Mat),&(aff_inv->Mat));
    randV32(&(aff->Vec));
    MatMulVecM32((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
void genaffinepairM64(Aff64 *aff,Aff64 *aff_inv)//generate a pair of affine
{
    genMatpairM64(&(aff->Mat),&(aff_inv->Mat));
    randV64(&(aff->Vec));
    MatMulVecM64((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
void genaffinepairM128(Aff128 *aff,Aff128 *aff_inv)//generate a pair of affine
{
    genMatpairM128(&(aff->Mat),&(aff_inv->Mat));
    randV128(&(aff->Vec));
    MatMulVecM128((*aff_inv).Mat,(*aff).Vec,&(aff_inv->Vec));
}
void MatrixcomM8to32(M8 m1,M8 m2,M8 m3,M8 m4,M32 *mat)//diagonal matrix combine,four 8*8 -> 32*32
{
    int j=0;
    uint8_t* m;
    initM32(mat);
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*mat).M[j];
        *(m+3)=m1.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*mat).M[j];
        *(m+2)=m2.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*mat).M[j];
        *(m+1)=m3.M[i];
        j++;
    }
    for(int i=0;i<8;i++)
    {
        m=(uint8_t*)&(*mat).M[j];
        *m=m4.M[i];
        j++;
    }
}
void VectorcomV8to32(V8 v1,V8 v2,V8 v3,V8 v4,V32 *vec)//four vectors combine
{
    uint8_t* v;
    v=(uint8_t*)&(*vec).V;
    *(v+3)=v1.V;
    *(v+2)=v2.V;
    *(v+1)=v3.V;
    *v=v4.V;
}
void affinecomM8to32(Aff8 aff1,Aff8 aff2,Aff8 aff3,Aff8 aff4,Aff32 *aff)//diagonal affine combine,four 8*8 -> 32*32
{
    MatrixcomM8to32(aff1.Mat,aff2.Mat,aff3.Mat,aff4.Mat,&(aff->Mat));
    VectorcomV8to32(aff1.Vec,aff2.Vec,aff3.Vec,aff4.Vec,&(aff->Vec));
}
void MattransM8(M8 Mat,M8 *Mat_trans)//matrix tansposition M8
{
    //initM8(Mat_trans);
    for(int i=0;i<8;i++)
    {
        if((Mat.M[0]<<i)&0x80) (*Mat_trans).M[i]=0x01;
        else (*Mat_trans).M[i]=0x00;
        for(int j=1;j<8;j++)
        {
            (*Mat_trans).M[i]=(*Mat_trans).M[i]<<1;
            if((Mat.M[j]<<i)&0x80) (*Mat_trans).M[i]^=0x01;
        }
    }
}
void MattransM16(M16 Mat,M16 *Mat_trans)//matrix tansposition M16
{
    //initM16(Mat_trans);
    for(int i=0;i<16;i++)
    {
        if((Mat.M[0]<<i)&0x8000) (*Mat_trans).M[i]=0x0001;
        else (*Mat_trans).M[i]=0x0000;
        for(int j=1;j<16;j++)
        {
            (*Mat_trans).M[i]=(*Mat_trans).M[i]<<1;
            if((Mat.M[j]<<i)&0x8000) (*Mat_trans).M[i]^=0x0001;
        }
    }
}
void MattransM32(M32 Mat,M32 *Mat_trans)//matrix tansposition M32
{
    //initM32(Mat_trans);
    for(int i=0;i<32;i++)
    {
        if((Mat.M[0]<<i)&0x80000000) (*Mat_trans).M[i]=0x00000001;
        else (*Mat_trans).M[i]=0x00000000;
        for(int j=1;j<32;j++)
        {
            (*Mat_trans).M[i]=(*Mat_trans).M[i]<<1;
            if((Mat.M[j]<<i)&0x80000000) (*Mat_trans).M[i]^=0x00000001;
        }
    }
}
void MattransM64(M64 Mat,M64 *Mat_trans)//matrix tansposition M64
{
    //initM64(Mat_trans);
    for(int i=0;i<64;i++)
    {
        if((Mat.M[0]<<i)&0x8000000000000000) (*Mat_trans).M[i]=0x0000000000000001;
        else (*Mat_trans).M[i]=0x0000000000000000;
        for(int j=1;j<64;j++)
        {
            (*Mat_trans).M[i]=(*Mat_trans).M[i]<<1;
            if((Mat.M[j]<<i)&0x8000000000000000) (*Mat_trans).M[i]^=0x0000000000000001;
        }
    }
}
void MattransM128(M128 Mat,M128 *Mat_trans)//matrix tansposition M128
{
    //initM128(Mat_trans);
    for(int i=0;i<64;i++)
    {
        if((Mat.M[0][0]<<i)&0x8000000000000000) (*Mat_trans).M[i][0]=0x0000000000000001;
        else (*Mat_trans).M[i][0]=0x0000000000000000;
        for(int j=1;j<64;j++)
        {
            (*Mat_trans).M[i][0]=(*Mat_trans).M[i][0]<<1;
            if((Mat.M[j][0]<<i)&0x8000000000000000) (*Mat_trans).M[i][0]^=0x0000000000000001;
        }
    }
    for(int i=0;i<64;i++)
    {
        if((Mat.M[64][0]<<i)&0x8000000000000000) (*Mat_trans).M[i][1]=0x0000000000000001;
        else (*Mat_trans).M[i][1]=0x0000000000000000;
        for(int j=65;j<128;j++)
        {
            (*Mat_trans).M[i][1]=(*Mat_trans).M[i][1]<<1;
            if((Mat.M[j][0]<<i)&0x8000000000000000) (*Mat_trans).M[i][1]^=0x0000000000000001;
        }
    }
    for(int i=64;i<128;i++)
    {
        if((Mat.M[0][1]<<(i-64))&0x8000000000000000) (*Mat_trans).M[i][0]=0x0000000000000001;
        else (*Mat_trans).M[i][0]=0x0000000000000000;
        for(int j=1;j<64;j++)
        {
            (*Mat_trans).M[i][0]=(*Mat_trans).M[i][0]<<1;
            if((Mat.M[j][1]<<(i-64))&0x8000000000000000) (*Mat_trans).M[i][0]^=0x0000000000000001;
        }
    }
    for(int i=64;i<128;i++)
    {
        if((Mat.M[64][1]<<(i-64))&0x8000000000000000) (*Mat_trans).M[i][1]=0x0000000000000001;
        else (*Mat_trans).M[i][1]=0x0000000000000000;
        for(int j=65;j<128;j++)
        {
            (*Mat_trans).M[i][1]=(*Mat_trans).M[i][1]<<1;
            if((Mat.M[j][1]<<(i-64))&0x8000000000000000) (*Mat_trans).M[i][1]^=0x0000000000000001;
        }
    }
}
void MatMulMatM8(M8 Mat1,M8 Mat2,M8 *Mat)//matrix multiplication 8*8 mul 8*8 -> 8*8
{
    M8 Mat2_trans;
    initM8(Mat);
    MattransM8(Mat2,&Mat2_trans);
    for(int i=0;i<8;i++)
    {
        if(xorU8(Mat1.M[i]&Mat2_trans.M[0])) (*Mat).M[i]=0x01;
        for(int j=1;j<8;j++)
        {
            (*Mat).M[i]=(*Mat).M[i]<<1;
            if(xorU8(Mat1.M[i]&Mat2_trans.M[j])) (*Mat).M[i]^=0x01;
        }       
    }
}
void MatMulMatM16(M16 Mat1,M16 Mat2,M16 *Mat)//matrix multiplication 16*16 mul 16*16 -> 16*16
{
    M16 Mat2_trans;
    initM16(Mat);
    MattransM16(Mat2,&Mat2_trans);
    for(int i=0;i<16;i++)
    {
        if(xorU16(Mat1.M[i]&Mat2_trans.M[0])) (*Mat).M[i]=0x0001;
        for(int j=1;j<16;j++)
        {
            (*Mat).M[i]=(*Mat).M[i]<<1;
            if(xorU16(Mat1.M[i]&Mat2_trans.M[j])) (*Mat).M[i]^=0x0001;
        }       
    }
}
void MatMulMatM32(M32 Mat1,M32 Mat2,M32 *Mat)//matrix multiplication 32*32 mul 32*32 -> 32*32
{
    M32 Mat2_trans;
    initM32(Mat);
    MattransM32(Mat2,&Mat2_trans);
    for(int i=0;i<32;i++)
    {
        if(xorU32(Mat1.M[i]&Mat2_trans.M[0])) (*Mat).M[i]=0x00000001;
        for(int j=1;j<32;j++)
        {
            (*Mat).M[i]=(*Mat).M[i]<<1;
            if(xorU32(Mat1.M[i]&Mat2_trans.M[j])) (*Mat).M[i]^=0x00000001;
        }       
    } 
}
void MatMulMatM64(M64 Mat1,M64 Mat2,M64 *Mat)//matrix multiplication 64*64 mul 64*64 -> 64*64
{
    M64 Mat2_trans;
    initM64(Mat);
    MattransM64(Mat2,&Mat2_trans);
    for(int i=0;i<64;i++)
    {
        if(xorU64(Mat1.M[i]&Mat2_trans.M[0])) (*Mat).M[i]=0x0000000000000001;
        for(int j=1;j<64;j++)
        {
            (*Mat).M[i]=(*Mat).M[i]<<1;
            if(xorU64(Mat1.M[i]&Mat2_trans.M[j])) (*Mat).M[i]^=0x0000000000000001;
        }       
    } 
}
void MatMulMatM128(M128 Mat1,M128 Mat2,M128 *Mat)//matrix multiplication 128*128 mul 128*128 -> 128*128
{
    M128 Mat2_trans;
    uint64_t temp[2];
    initM128(Mat);
    MattransM128(Mat2,&Mat2_trans);
    for(int i=0;i<128;i++)
    {
        temp[0]=Mat1.M[i][0]&Mat2_trans.M[0][0];
        temp[1]=Mat1.M[i][1]&Mat2_trans.M[0][1];
        if(xorU128(temp)) (*Mat).M[i][0]=0x0000000000000001;
        for(int j=1;j<64;j++)
        {
            (*Mat).M[i][0]=(*Mat).M[i][0]<<1;
            temp[0]=Mat1.M[i][0]&Mat2_trans.M[j][0];
            temp[1]=Mat1.M[i][1]&Mat2_trans.M[j][1];
            if(xorU128(temp)) (*Mat).M[i][0]^=0x0000000000000001;
        }
        temp[0]=Mat1.M[i][0]&Mat2_trans.M[64][0];
        temp[1]=Mat1.M[i][1]&Mat2_trans.M[64][1];
        if(xorU128(temp)) (*Mat).M[i][1]=0x0000000000000001;
        for(int j=65;j<128;j++)
        {
            (*Mat).M[i][1]=(*Mat).M[i][1]<<1;
            temp[0]=Mat1.M[i][0]&Mat2_trans.M[j][0];
            temp[1]=Mat1.M[i][1]&Mat2_trans.M[j][1];
            if(xorU128(temp)) (*Mat).M[i][1]^=0x0000000000000001;
        }
    } 
}
void affinemixM8(Aff8 preaff_inv,Aff8 aff,Aff8 *mixaff)//mixed transformation of (previous affine inversion) and this round affine
{
    MatMulMatM8(aff.Mat,preaff_inv.Mat,&(mixaff->Mat));
    MatMulVecM8(aff.Mat,preaff_inv.Vec,&(mixaff->Vec));
    (*mixaff).Vec.V^=aff.Vec.V;
}
void affinemixM16(Aff16 preaff_inv,Aff16 aff,Aff16 *mixaff)//mixed transformation of (previous affine inversion) and this round affine
{
    MatMulMatM16(aff.Mat,preaff_inv.Mat,&(mixaff->Mat));
    MatMulVecM16(aff.Mat,preaff_inv.Vec,&(mixaff->Vec));
    (*mixaff).Vec.V^=aff.Vec.V;
}
void affinemixM32(Aff32 preaff_inv,Aff32 aff,Aff32 *mixaff)//mixed transformation of (previous affine inversion) and this round affine
{
    MatMulMatM32(aff.Mat,preaff_inv.Mat,&(mixaff->Mat));
    MatMulVecM32(aff.Mat,preaff_inv.Vec,&(mixaff->Vec));
    (*mixaff).Vec.V^=aff.Vec.V;
}
void affinemixM64(Aff64 preaff_inv,Aff64 aff,Aff64 *mixaff)//mixed transformation of (previous affine inversion) and this round affine
{
    MatMulMatM64(aff.Mat,preaff_inv.Mat,&(mixaff->Mat));
    MatMulVecM64(aff.Mat,preaff_inv.Vec,&(mixaff->Vec));
    (*mixaff).Vec.V^=aff.Vec.V;
}
void affinemixM128(Aff128 preaff_inv,Aff128 aff,Aff128 *mixaff)//mixed transformation of (previous affine inversion) and this round affine
{
    MatMulMatM128(aff.Mat,preaff_inv.Mat,&(mixaff->Mat));
    MatMulVecM128(aff.Mat,preaff_inv.Vec,&(mixaff->Vec));
    (*mixaff).Vec.V[0]^=aff.Vec.V[0];
    (*mixaff).Vec.V[1]^=aff.Vec.V[1];
}