//Accuarcy test for all functions of WBMatrix Library
#include "WBMatrix/WBMatrix.h"
#define TEST 10000
int main()
{
    int flag=1,i;
    printf("-----mat mul num test-----\n");
    M8 mmnm8_1,mmnm8_2;
    uint8_t mmnn8_1=0x87,mmnn8_2;
    for(i=0;i<TEST;i++)
    {
        genMatpairM8(&mmnm8_1,&mmnm8_2);
        mmnn8_2=MatMulNumM8(mmnm8_2,MatMulNumM8(mmnm8_1,mmnn8_1));
        if(mmnn8_1!=mmnn8_2) break;
    }
    if(i<TEST) {printf("8bit: ERROR\n"); flag=0;}
    else printf("8bit: OK\n");

    M16 mmnm16_1,mmnm16_2;
    uint16_t mmnn16_1=0x8778,mmnn16_2;
    for(i=0;i<TEST;i++)
    {
        genMatpairM16(&mmnm16_1,&mmnm16_2);
        mmnn16_2=MatMulNumM16(mmnm16_2,MatMulNumM16(mmnm16_1,mmnn16_1));
        if(mmnn16_1!=mmnn16_2) break;
    }
    if(i<TEST) {printf("16bit: ERROR\n"); flag=0;}
    else printf("16bit: OK\n");

    M32 mmnm32_1,mmnm32_2;
    uint32_t mmnn32_1=0x87788778,mmnn32_2;
    for(i=0;i<TEST;i++)
    {
        genMatpairM32(&mmnm32_1,&mmnm32_2);
        mmnn32_2=MatMulNumM32(mmnm32_2,MatMulNumM32(mmnm32_1,mmnn32_1));
        if(mmnn32_1!=mmnn32_2) break;
    }
    if(i<TEST) {printf("32bit: ERROR\n"); flag=0;}
    else printf("32bit: OK\n");

    M64 mmnm64_1,mmnm64_2;
    uint64_t mmnn64_1=0x8778877887788778,mmnn64_2;
    for(i=0;i<TEST;i++)
    {
        genMatpairM64(&mmnm64_1,&mmnm64_2);
        mmnn64_2=MatMulNumM64(mmnm64_2,MatMulNumM64(mmnm64_1,mmnn64_1));
        if(mmnn64_1!=mmnn64_2)  break;
    }
    if(i<TEST) {printf("64bit: ERROR\n"); flag=0;}
    else printf("64bit: OK\n");

    printf("-----mat mul vec test-----\n");
    M8 mmvm8_1,mmvm8_2;
    V8 mmvv8_1,mmvv8_2,mmvv8_3;
    for(i=0;i<TEST;i++)
    {
        genMatpairM8(&mmvm8_1,&mmvm8_2);
        randV8(&mmvv8_1);
        MatMulVecM8(mmvm8_1,mmvv8_1,&mmvv8_2);
        MatMulVecM8(mmvm8_2,mmvv8_2,&mmvv8_3);
        if(!isequalV8(mmvv8_1,mmvv8_3)) break;
    }
    if(i<TEST) {printf("8bit: ERROR\n"); flag=0;}
    else printf("8bit: OK\n");

    M16 mmvm16_1,mmvm16_2;
    V16 mmvv16_1,mmvv16_2,mmvv16_3;
    for(i=0;i<TEST;i++)
    {
        genMatpairM16(&mmvm16_1,&mmvm16_2);
        randV16(&mmvv16_1);
        MatMulVecM16(mmvm16_1,mmvv16_1,&mmvv16_2);
        MatMulVecM16(mmvm16_2,mmvv16_2,&mmvv16_3);
        if(!isequalV16(mmvv16_1,mmvv16_3)) break;
    } 
    if(i<TEST) {printf("16bit: ERROR\n"); flag=0;}
    else printf("16bit: OK\n");

    M32 mmvm32_1,mmvm32_2;
    V32 mmvv32_1,mmvv32_2,mmvv32_3;
    for(i=0;i<TEST;i++)
    {
        genMatpairM32(&mmvm32_1,&mmvm32_2);
        randV32(&mmvv32_1);
        MatMulVecM32(mmvm32_1,mmvv32_1,&mmvv32_2);
        MatMulVecM32(mmvm32_2,mmvv32_2,&mmvv32_3);
        if(!isequalV32(mmvv32_1,mmvv32_3)) break;
    }
    if(i<TEST) {printf("32bit: ERROR\n"); flag=0;}
    else printf("32bit: OK\n");

    M64 mmvm64_1,mmvm64_2;
    V64 mmvv64_1,mmvv64_2,mmvv64_3;
    for(i=0;i<TEST;i++)
    {
        genMatpairM64(&mmvm64_1,&mmvm64_2);
        randV64(&mmvv64_1);
        MatMulVecM64(mmvm64_1,mmvv64_1,&mmvv64_2);
        MatMulVecM64(mmvm64_2,mmvv64_2,&mmvv64_3);
        if(!isequalV64(mmvv64_1,mmvv64_3)) break;
    } 
    if(i<TEST) {printf("64bit: ERROR\n"); flag=0;}
    else printf("64bit: OK\n");

    M128 mmvm128_1,mmvm128_2;
    V128 mmvv128_1,mmvv128_2,mmvv128_3;
    for(i=0;i<TEST;i++)
    {
        genMatpairM128(&mmvm128_1,&mmvm128_2);
        randV128(&mmvv128_1);
        MatMulVecM128(mmvm128_1,mmvv128_1,&mmvv128_2);
        MatMulVecM128(mmvm128_2,mmvv128_2,&mmvv128_3);
        if(!isequalV128(mmvv128_1,mmvv128_3)) break;
    } 
    if(i<TEST) {printf("128bit: ERROR\n"); flag=0;}
    else printf("128bit: OK\n");
    
    printf("-----mat mul mat (includes mat transpositon) test-----\n");
    M8 mmmm8_1,mmmm8_2,mmmm8_3;
    V8 mmmv8_1,mmmv8_2,mmmv8_3,mmmv8_4;
    for(i=0;i<TEST;i++)
    {
        randM8(&mmmm8_1);
        randM8(&mmmm8_2);
        randV8(&mmmv8_1);
        MatMulVecM8(mmmm8_1,mmmv8_1,&mmmv8_2);
        MatMulVecM8(mmmm8_2,mmmv8_2,&mmmv8_3);
        MatMulMatM8(mmmm8_2,mmmm8_1,&mmmm8_3);
        MatMulVecM8(mmmm8_3,mmmv8_1,&mmmv8_4);
        if(!isequalV8(mmmv8_3,mmmv8_4)) break;
    }
    if(i<TEST) {printf("8bit: ERROR\n"); flag=0;}
    else printf("8bit: OK\n");
    
    M16 mmmm16_1,mmmm16_2,mmmm16_3;
    V16 mmmv16_1,mmmv16_2,mmmv16_3,mmmv16_4;
    for(i=0;i<TEST;i++)
    {
        randM16(&mmmm16_1);
        randM16(&mmmm16_2);
        randV16(&mmmv16_1);
        MatMulVecM16(mmmm16_1,mmmv16_1,&mmmv16_2);
        MatMulVecM16(mmmm16_2,mmmv16_2,&mmmv16_3);
        MatMulMatM16(mmmm16_2,mmmm16_1,&mmmm16_3);
        MatMulVecM16(mmmm16_3,mmmv16_1,&mmmv16_4);
        if(!isequalV16(mmmv16_3,mmmv16_4)) break;
    }
    if(i<TEST) {printf("16bit: ERROR\n"); flag=0;}
    else printf("16bit: OK\n");

    M32 mmmm32_1,mmmm32_2,mmmm32_3;
    V32 mmmv32_1,mmmv32_2,mmmv32_3,mmmv32_4;
    for(i=0;i<TEST;i++)
    {
        randM32(&mmmm32_1);
        randM32(&mmmm32_2);
        randV32(&mmmv32_1);
        MatMulVecM32(mmmm32_1,mmmv32_1,&mmmv32_2);
        MatMulVecM32(mmmm32_2,mmmv32_2,&mmmv32_3);
        MatMulMatM32(mmmm32_2,mmmm32_1,&mmmm32_3);
        MatMulVecM32(mmmm32_3,mmmv32_1,&mmmv32_4);
        if(!isequalV32(mmmv32_3,mmmv32_4)) break;
    }
    if(i<TEST) {printf("32bit: ERROR\n"); flag=0;}
    else printf("32bit: OK\n");

    M64 mmmm64_1,mmmm64_2,mmmm64_3;
    V64 mmmv64_1,mmmv64_2,mmmv64_3,mmmv64_4;
    for(i=0;i<TEST;i++)
    {
        randM64(&mmmm64_1);
        randM64(&mmmm64_2);
        randV64(&mmmv64_1);
        MatMulVecM64(mmmm64_1,mmmv64_1,&mmmv64_2);
        MatMulVecM64(mmmm64_2,mmmv64_2,&mmmv64_3);
        MatMulMatM64(mmmm64_2,mmmm64_1,&mmmm64_3);
        MatMulVecM64(mmmm64_3,mmmv64_1,&mmmv64_4);
        if(!isequalV64(mmmv64_3,mmmv64_4)) break;
    }
    if(i<TEST) {printf("64bit: ERROR\n"); flag=0;}
    else printf("64bit: OK\n");

    M128 mmmm128_1,mmmm128_2,mmmm128_3;
    V128 mmmv128_1,mmmv128_2,mmmv128_3,mmmv128_4;
    for(i=0;i<TEST;i++)
    {
        randM128(&mmmm128_1);
        randM128(&mmmm128_2);
        randV128(&mmmv128_1);
        MatMulVecM128(mmmm128_1,mmmv128_1,&mmmv128_2);
        MatMulVecM128(mmmm128_2,mmmv128_2,&mmmv128_3);
        MatMulMatM128(mmmm128_2,mmmm128_1,&mmmm128_3);
        MatMulVecM128(mmmm128_3,mmmv128_1,&mmmv128_4);
        if(!isequalV128(mmmv128_3,mmmv128_4)) break;
    }
    if(i<TEST) {printf("128bit: ERROR\n"); flag=0;}
    else printf("128bit: OK\n");

    printf("-----invertible and inverse test-----\n");
    printf("nomal mode:\n");
    M8 iim8_1,iim8_2,iim8_3,iim8_4;
    identityM8(&iim8_4);
    for(i=0;i<TEST;i++)
    {
        genMatpairM8(&iim8_1,&iim8_2);
        MatMulMatM8(iim8_1,iim8_2,&iim8_3);
        if(!isequalM8(iim8_3,iim8_4)) break;
    }
    if(i<TEST) {printf("8bit: ERROR\n"); flag=0;}
    else printf("8bit: OK\n");

    M16 iim16_1,iim16_2,iim16_3,iim16_4;
    identityM16(&iim16_4);
    for(i=0;i<TEST;i++)
    {
        genMatpairM16(&iim16_1,&iim16_2);
        MatMulMatM16(iim16_1,iim16_2,&iim16_3);
        if(!isequalM16(iim16_3,iim16_4)) break;
    }
    if(i<TEST) {printf("16bit: ERROR\n"); flag=0;}
    else printf("16bit: OK\n");

    M32 iim32_1,iim32_2,iim32_3,iim32_4;
    identityM32(&iim32_4);
    for(i=0;i<TEST;i++)
    {
        genMatpairM32(&iim32_1,&iim32_2);
        MatMulMatM32(iim32_1,iim32_2,&iim32_3);
        if(!isequalM32(iim32_3,iim32_4)) break;
    }
    if(i<TEST) {printf("32bit: ERROR\n"); flag=0;}
    else printf("32bit: OK\n");

    M64 iim64_1,iim64_2,iim64_3,iim64_4;
    identityM64(&iim64_4);
    for(i=0;i<TEST;i++)
    {
        genMatpairM64(&iim64_1,&iim64_2);
        MatMulMatM64(iim64_1,iim64_2,&iim64_3);
        if(!isequalM64(iim64_3,iim64_4)) break;
    }
    if(i<TEST) {printf("64bit: ERROR\n"); flag=0;}
    else printf("64bit: OK\n");

    M128 iim128_1,iim128_2,iim128_3,iim128_4;
    identityM128(&iim128_4);
    for(i=0;i<TEST;i++)
    {
        genMatpairM128(&iim128_1,&iim128_2);
        MatMulMatM128(iim128_1,iim128_2,&iim128_3);
        if(!isequalM128(iim128_3,iim128_4))  break;
    }
    if(i<TEST) {printf("128bit: ERROR\n"); flag=0;}
    else printf("128bit: OK\n");

    printf("min mode:\n");
    M8 iiminm8_1,iiminm8_2,iiminm8_3,iiminm8_4;
    initinvbaseM8(initM8_min);
    genMatpairM8(&iiminm8_1,&iiminm8_2);
    MatMulMatM8(iiminm8_1,iiminm8_2,&iiminm8_3);
    identityM8(&iiminm8_4);
    if(isequalM8(iiminm8_3,iiminm8_4)) printf("8bit: OK\n");
    else {printf("8bit: ERROR\n"); flag=0;}

    M16 iiminm16_1,iiminm16_2,iiminm16_3,iiminm16_4;
    initinvbaseM16(initM16_min);
    genMatpairM16(&iiminm16_1,&iiminm16_2);
    MatMulMatM16(iiminm16_1,iiminm16_2,&iiminm16_3);
    identityM16(&iiminm16_4);
    if(isequalM16(iiminm16_3,iiminm16_4)) printf("16bit: OK\n");
    else {printf("16bit: ERROR\n"); flag=0;}

    M32 iiminm32_1,iiminm32_2,iiminm32_3,iiminm32_4;
    initinvbaseM32(initM32_min);
    genMatpairM32(&iiminm32_1,&iiminm32_2);
    MatMulMatM32(iiminm32_1,iiminm32_2,&iiminm32_3);
    identityM32(&iiminm32_4);
    if(isequalM32(iiminm32_3,iiminm32_4)) printf("32bit: OK\n");
    else {printf("32bit: ERROR\n"); flag=0;}

    M64 iiminm64_1,iiminm64_2,iiminm64_3,iiminm64_4;
    initinvbaseM64(initM64_min);
    genMatpairM64(&iiminm64_1,&iiminm64_2);
    MatMulMatM64(iiminm64_1,iiminm64_2,&iiminm64_3);
    identityM64(&iiminm64_4);
    if(isequalM64(iiminm64_3,iiminm64_4)) printf("64bit: OK\n");
    else {printf("64bit: ERROR\n"); flag=0;}

    M128 iiminm128_1,iiminm128_2,iiminm128_3,iiminm128_4;
    initinvbaseM128(initM128_min);
    genMatpairM128(&iiminm128_1,&iiminm128_2);
    MatMulMatM128(iiminm128_1,iiminm128_2,&iiminm128_3);
    identityM128(&iiminm128_4);
    if(isequalM128(iiminm128_3,iiminm128_4)) printf("128bit: OK\n");
    else {printf("128bit: ERROR\n"); flag=0;}

    freebaseM8();
    freebaseM16();
    freebaseM32();
    freebaseM64();
    freebaseM128();

    printf("max mode:\n");
    M8 iimaxm8_1,iimaxm8_2,iimaxm8_3,iimaxm8_4;
    initinvbaseM8(initM8_max);
    genMatpairM8(&iimaxm8_1,&iimaxm8_2);
    MatMulMatM8(iimaxm8_1,iimaxm8_2,&iimaxm8_3);
    identityM8(&iimaxm8_4);
    if(isequalM8(iimaxm8_3,iimaxm8_4)) printf("8bit: OK\n");
    else {printf("8bit: ERROR\n"); flag=0;}

    M16 iimaxm16_1,iimaxm16_2,iimaxm16_3,iimaxm16_4;
    initinvbaseM16(initM16_max);
    genMatpairM16(&iimaxm16_1,&iimaxm16_2);
    MatMulMatM16(iimaxm16_1,iimaxm16_2,&iimaxm16_3);
    identityM16(&iimaxm16_4);
    if(isequalM16(iimaxm16_3,iimaxm16_4)) printf("16bit: OK\n");
    else {printf("16bit: ERROR\n"); flag=0;}

    M32 iimaxm32_1,iimaxm32_2,iimaxm32_3,iimaxm32_4;
    initinvbaseM32(initM32_max);
    genMatpairM32(&iimaxm32_1,&iimaxm32_2);
    MatMulMatM32(iimaxm32_1,iimaxm32_2,&iimaxm32_3);
    identityM32(&iimaxm32_4);
    if(isequalM32(iimaxm32_3,iimaxm32_4)) printf("32bit: OK\n");
    else {printf("32bit: ERROR\n"); flag=0;}

    M64 iimaxm64_1,iimaxm64_2,iimaxm64_3,iimaxm64_4;
    initinvbaseM64(initM64_max);
    genMatpairM64(&iimaxm64_1,&iimaxm64_2);
    MatMulMatM64(iimaxm64_1,iimaxm64_2,&iimaxm64_3);
    identityM64(&iimaxm64_4);
    if(isequalM64(iimaxm64_3,iimaxm64_4)) printf("64bit: OK\n");
    else {printf("64bit: ERROR\n"); flag=0;}

    M128 iimaxm128_1,iimaxm128_2,iimaxm128_3,iimaxm128_4;
    initinvbaseM128(initM128_max);
    genMatpairM128(&iimaxm128_1,&iimaxm128_2);
    MatMulMatM128(iimaxm128_1,iimaxm128_2,&iimaxm128_3);
    identityM128(&iimaxm128_4);
    if(isequalM128(iimaxm128_3,iimaxm128_4)) printf("128bit: OK\n");
    else {printf("128bit: ERROR\n"); flag=0;}

    printf("-----invertible affine and affine transform test-----\n");
    Aff8 iaa8_1,iaa8_2;
    uint8_t iau8_1=0x87,iau8_2,iau8_3;
    genaffinepairM8(&iaa8_1,&iaa8_2);
    iau8_2=affineU8(iaa8_1,iau8_1);
    iau8_3=affineU8(iaa8_2,iau8_2);
    if(iau8_1==iau8_3) printf("8bit: OK\n");
    else {printf("8bit: ERROR\n"); flag=0;}

    Aff16 iaa16_1,iaa16_2;
    uint16_t iau16_1=0x8778,iau16_2,iau16_3;
    genaffinepairM16(&iaa16_1,&iaa16_2);
    iau16_2=affineU16(iaa16_1,iau16_1);
    iau16_3=affineU16(iaa16_2,iau16_2);
    if(iau16_1==iau16_3) printf("16bit: OK\n");
    else {printf("16bit: ERROR\n"); flag=0;}

    Aff32 iaa32_1,iaa32_2;
    uint32_t iau32_1=0x87788778,iau32_2,iau32_3;
    genaffinepairM32(&iaa32_1,&iaa32_2);
    iau32_2=affineU32(iaa32_1,iau32_1);
    iau32_3=affineU32(iaa32_2,iau32_2);
    if(iau32_1==iau32_3) printf("32bit: OK\n");
    else {printf("32bit: ERROR\n"); flag=0;}

    Aff64 iaa64_1,iaa64_2;
    uint64_t iau64_1=0x8778877887788778,iau64_2,iau64_3;
    genaffinepairM64(&iaa64_1,&iaa64_2);
    iau64_2=affineU64(iaa64_1,iau64_1);
    iau64_3=affineU64(iaa64_2,iau64_2);
    if(iau64_1==iau64_3) printf("64bit: OK\n");
    else {printf("64bit: ERROR\n"); flag=0;}

    Aff128 iaa128_1,iaa128_2;
    uint64_t iau128_1[2]={0x8778877887788778,0x8778877887788778},iau128_2[2],iau128_3[2];
    genaffinepairM128(&iaa128_1,&iaa128_2);
    affineU128(iaa128_1,iau128_1,iau128_2);
    affineU128(iaa128_2,iau128_2,iau128_3);
    if( (iau128_1[0]==iau128_3[0]) && (iau128_1[1]==iau128_3[1]) ) printf("128bit: OK\n");
    else {printf("128bit: ERROR\n"); flag=0;}

    printf("-----affine mix test-----\n");
    Aff8 ama8_1,ama8_2,ama8_3,ama8_4,ama8_5;
    uint8_t amu8_1=0x87,amu8_2,amu8_3,amu8_4,amu8_5;
    genaffinepairM8(&ama8_1,&ama8_2);
    genaffinepairM8(&ama8_3,&ama8_4);
    amu8_2=affineU8(ama8_1,amu8_1);
    affinemixM8(ama8_3,ama8_2,&ama8_5);
    amu8_4=affineU8(ama8_5,amu8_2);
    amu8_5=affineU8(ama8_4,amu8_4);
    if(amu8_1==amu8_5) printf("8bit: OK\n");
    else {printf("8bit: ERROR\n"); flag=0;}

    Aff16 ama16_1,ama16_2,ama16_3,ama16_4,ama16_5;
    uint16_t amu16_1=0x8778,amu16_2,amu16_3,amu16_4,amu16_5;
    genaffinepairM16(&ama16_1,&ama16_2);
    genaffinepairM16(&ama16_3,&ama16_4);
    amu16_2=affineU16(ama16_1,amu16_1);
    affinemixM16(ama16_3,ama16_2,&ama16_5);
    amu16_4=affineU16(ama16_5,amu16_2);
    amu16_5=affineU16(ama16_4,amu16_4);
    if(amu16_1==amu16_5) printf("16bit: OK\n");
    else {printf("16bit: ERROR\n"); flag=0;}

    Aff32 ama32_1,ama32_2,ama32_3,ama32_4,ama32_5;
    uint32_t amu32_1=0x87788778,amu32_2,amu32_3,amu32_4,amu32_5;
    genaffinepairM32(&ama32_1,&ama32_2);
    genaffinepairM32(&ama32_3,&ama32_4);
    amu32_2=affineU32(ama32_1,amu32_1);
    affinemixM32(ama32_3,ama32_2,&ama32_5);
    amu32_4=affineU32(ama32_5,amu32_2);
    amu32_5=affineU32(ama32_4,amu32_4);
    if(amu32_1==amu32_5) printf("32bit: OK\n");
    else {printf("32bit: ERROR\n"); flag=0;}

    Aff64 ama64_1,ama64_2,ama64_3,ama64_4,ama64_5;
    uint64_t amu64_1=0x87877887788778,amu64_2,amu64_3,amu64_4,amu64_5;
    genaffinepairM64(&ama64_1,&ama64_2);
    genaffinepairM64(&ama64_3,&ama64_4);
    amu64_2=affineU64(ama64_1,amu64_1);
    affinemixM64(ama64_3,ama64_2,&ama64_5);
    amu64_4=affineU64(ama64_5,amu64_2);
    amu64_5=affineU64(ama64_4,amu64_4);
    if(amu64_1==amu64_5) printf("64bit: OK\n");
    else {printf("64bit: ERROR\n"); flag=0;}

    Aff128 ama128_1,ama128_2,ama128_3,ama128_4,ama128_5;
    uint64_t amu128_1[2]={0x8778877887788778,0x8778877887788778},amu128_2[2],amu128_3[2],amu128_4[2],amu128_5[2];
    genaffinepairM128(&ama128_1,&ama128_2);
    genaffinepairM128(&ama128_3,&ama128_4);
    affineU128(ama128_1,amu128_1,amu128_2);
    affinemixM128(ama128_3,ama128_2,&ama128_5);
    affineU128(ama128_5,amu128_2,amu128_4);
    affineU128(ama128_4,amu128_4,amu128_5);
    if( (amu128_1[0]==amu128_5[0]) && (amu128_1[1]==amu128_5[1]) )printf("128bit: OK\n");
    else {printf("128bit: ERROR\n"); flag=0;}

    if(flag) printf("\nALL PASS!");
    else printf("\nERROR!");
    return 0;
}