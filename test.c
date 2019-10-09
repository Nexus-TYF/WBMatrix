#include "WBMatrix.h"
int main()
{
    Aff8 aff[10],aff_inv[10];
    uint8_t t;
    for(int i=0;i<10;i++)
    {
        t=3;
        affinepairM8(&aff[i],&aff_inv[i]);
        printU8(t);
        affineU8(aff[i],&t);
        printU8(t);//affine transformation
        affineU8(aff_inv[i],&t);
        printU8(t);
        printf("\n");
    }

    Aff8 aff1,aff2,aff3,aff4;
    initM8(&(aff1.Mat));
    randM8(&(aff1.Mat));
    initM8(&(aff2.Mat));
    randM8(&(aff2.Mat));
    printbitM8(aff1.Mat);
    printbitM8(aff2.Mat);
    printbitM8(aff3.Mat);
    printbitM8(aff4.Mat);

    Aff32 aff32;
    randV8(&(aff1.Vec));
    randV8(&(aff2.Vec));
    randV8(&(aff3.Vec));
    randV8(&(aff4.Vec));
    affinecomM8to32(aff1,aff2,aff3,aff4,&aff32);//affine combine
    printbitM32(aff32.Mat);

    printV8(aff1.Vec);
    printV8(aff2.Vec);
    printV8(aff3.Vec);
    printV8(aff4.Vec);
    printV32(aff32.Vec);
    printf("\n");

    initV32(&(aff32.Vec));
    printV32(aff32.Vec);
    randV32(&(aff32.Vec));
    printV32(aff32.Vec);
    printf("\n");

    Aff32 affine[10],affine_inv[10];
    uint32_t r;
    for(int i=0;i<10;i++)
    {
        r=8888;//plaintext
        affinepairM32(&affine[i],&affine_inv[i]);
        printU32(r);
        affineU32(affine[i],&r);
        printU32(r);//affine transformation
        affineU32(affine_inv[i],&r);
        printU32(r);
        printf("\n");
    }

    M8 M_trans;
    printbitM8(aff1.Mat);
    MattransM8(aff1.Mat,&M_trans);
    printbitM8(M_trans);
    return 0;
}