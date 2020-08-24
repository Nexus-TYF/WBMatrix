//Accuarcy test for all functions of WBMatrix Library
#include "WBMatrix/WBMatrix.h"
#define TEST 100000
int main()
{
    int flag = 1, i;
    printf("-----bitwise operation (read/set/flip) test-----\n");
    M4 bom4_1, bom4_2, bom4_3;
    int flag_bom4_1 = 1;
    int flag_bom4_2 = 1;
    int flag_bom4_3 = 1;
    initM4(&bom4_1);
    identityM4(&bom4_2);
    initM4(&bom4_3);
    for (i = 0; i < 4; i++)
    {
        setbitM4(&bom4_1, i, i, 1);
    }
    if(!isequalM4(bom4_1, bom4_2)) flag_bom4_1 = 0;
    for (i = 0; i < 4; i++)
    {
        if(readbitM4(bom4_1, i, i) == 0) 
        {
            flag_bom4_2 = 0;
            break;
        }
    }
    for (i = 0; i < 4; i++)
    {
        flipbitM4(&bom4_1, i, i);
    }
    if(!isequalM4(bom4_1, bom4_3)) flag_bom4_1 = 0;
    if(flag_bom4_1 && flag_bom4_2 && flag_bom4_3) printf("4bit: PASS\n");
    else {printf("4bit: ERROR\n"); flag = 0;}
    
    M8 bom8_1, bom8_2, bom8_3;
    int flag_bom8_1 = 1;
    int flag_bom8_2 = 1;
    int flag_bom8_3 = 1;
    initM8(&bom8_1);
    identityM8(&bom8_2);
    initM8(&bom8_3);
    for (i = 0; i < 8; i++)
    {
        setbitM8(&bom8_1, i, i, 1);
    }
    if(!isequalM8(bom8_1, bom8_2)) flag_bom8_1 = 0;
    for (i = 0; i < 8; i++)
    {
        if(readbitM8(bom8_1, i, i) == 0) 
        {
            flag_bom8_2 = 0;
            break;
        }
    }
    for (i = 0; i < 8; i++)
    {
        flipbitM8(&bom8_1, i, i);
    }
    if(!isequalM8(bom8_1, bom8_3)) flag_bom8_1 = 0;
    if(flag_bom8_1 && flag_bom8_2 && flag_bom8_3) printf("8bit: PASS\n");
    else {printf("8bit: ERROR\n"); flag = 0;}

    M16 bom16_1, bom16_2, bom16_3;
    int flag_bom16_1 = 1;
    int flag_bom16_2 = 1;
    int flag_bom16_3 = 1;
    initM16(&bom16_1);
    identityM16(&bom16_2);
    initM16(&bom16_3);
    for (i = 0; i < 16; i++)
    {
        setbitM16(&bom16_1, i, i, 1);
    }
    if(!isequalM16(bom16_1, bom16_2)) flag_bom16_1 = 0;
    for (i = 0; i < 16; i++)
    {
        if(readbitM16(bom16_1, i, i) == 0) 
        {
            flag_bom16_2 = 0;
            break;
        }
    }
    for (i = 0; i < 16; i++)
    {
        flipbitM16(&bom16_1, i, i);
    }
    if(!isequalM16(bom16_1, bom16_3)) flag_bom16_1 = 0;
    if(flag_bom16_1 && flag_bom16_2 && flag_bom16_3) printf("16bit: PASS\n");
    else {printf("16bit: ERROR\n"); flag = 0;}

    M32 bom32_1, bom32_2, bom32_3;
    int flag_bom32_1 = 1;
    int flag_bom32_2 = 1;
    int flag_bom32_3 = 1;
    initM32(&bom32_1);
    identityM32(&bom32_2);
    initM32(&bom32_3);
    for (i = 0; i < 32; i++)
    {
        setbitM32(&bom32_1, i, i, 1);
    }
    if(!isequalM32(bom32_1, bom32_2)) flag_bom32_1 = 0;
    for (i = 0; i < 32; i++)
    {
        if(readbitM32(bom32_1, i, i) == 0) 
        {
            flag_bom32_2 = 0;
            break;
        }
    }
    for (i = 0; i < 32; i++)
    {
        flipbitM32(&bom32_1, i, i);
    }
    if(!isequalM32(bom32_1, bom32_3)) flag_bom32_1 = 0;
    if(flag_bom32_1 && flag_bom32_2 && flag_bom32_3) printf("32bit: PASS\n");
    else {printf("32bit: ERROR\n"); flag = 0;}

    M64 bom64_1, bom64_2, bom64_3;
    int flag_bom64_1 = 1;
    int flag_bom64_2 = 1;
    int flag_bom64_3 = 1;
    initM64(&bom64_1);
    identityM64(&bom64_2);
    initM64(&bom64_3);
    for (i = 0; i < 64; i++)
    {
        setbitM64(&bom64_1, i, i, 1);
    }
    if(!isequalM64(bom64_1, bom64_2)) flag_bom64_1 = 0;
    for (i = 0; i < 64; i++)
    {
        if(readbitM64(bom64_1, i, i) == 0) 
        {
            flag_bom64_2 = 0;
            break;
        }
    }
    for (i = 0; i < 64; i++)
    {
        flipbitM64(&bom64_1, i, i);
    }
    if(!isequalM64(bom64_1, bom64_3)) flag_bom64_1 = 0;
    if(flag_bom64_1 && flag_bom64_2 && flag_bom64_3) printf("64bit: PASS\n");
    else {printf("64bit: ERROR\n"); flag = 0;}

    M128 bom128_1, bom128_2, bom128_3;
    int flag_bom128_1 = 1;
    int flag_bom128_2 = 1;
    int flag_bom128_3 = 1;
    initM128(&bom128_1);
    identityM128(&bom128_2);
    initM128(&bom128_3);
    for (i = 0; i < 128; i++)
    {
        setbitM128(&bom128_1, i, i, 1);
    }
    if(!isequalM128(bom128_1, bom128_2)) flag_bom128_1 = 0;
    for (i = 0; i < 128; i++)
    {
        if(readbitM128(bom128_1, i, i) == 0) 
        {
            flag_bom128_2 = 0;
            break;
        }
    }
    for (i = 0; i < 128; i++)
    {
        flipbitM128(&bom128_1, i, i);
    }
    if(!isequalM128(bom128_1, bom128_3)) flag_bom128_1 = 0;
    if(flag_bom128_1 && flag_bom128_2 && flag_bom128_3) printf("128bit: PASS\n");
    else {printf("128bit: ERROR\n"); flag = 0;}

    printf("-----mat mul num test-----\n");
    M4 mmnm4_1, mmnm4_2;
    uint8_t mmnn4_1 = 0x0c, mmnn4_2;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM4(&mmnm4_1, &mmnm4_2);
        mmnn4_2=MatMulNumM4(mmnm4_2, MatMulNumM4(mmnm4_1, mmnn4_1));
        if(mmnn4_1 != mmnn4_2) break;
    }
    if(i < TEST) {printf("4bit: ERROR\n"); flag = 0;}
    else printf("4bit: PASS\n");

    M8 mmnm8_1, mmnm8_2;
    uint8_t mmnn8_1 = 0x87, mmnn8_2;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM8(&mmnm8_1, &mmnm8_2);
        mmnn8_2=MatMulNumM8(mmnm8_2, MatMulNumM8(mmnm8_1, mmnn8_1));
        if(mmnn8_1 != mmnn8_2) break;
    }
    if(i < TEST) {printf("8bit: ERROR\n"); flag = 0;}
    else printf("8bit: PASS\n");

    M16 mmnm16_1, mmnm16_2;
    uint16_t mmnn16_1=0x8778, mmnn16_2;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM16(&mmnm16_1, &mmnm16_2);
        mmnn16_2 = MatMulNumM16(mmnm16_2, MatMulNumM16(mmnm16_1, mmnn16_1));
        if(mmnn16_1 != mmnn16_2) break;
    }
    if(i < TEST) {printf("16bit: ERROR\n"); flag = 0;}
    else printf("16bit: PASS\n");

    M32 mmnm32_1, mmnm32_2;
    uint32_t mmnn32_1=0x87788778, mmnn32_2;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM32(&mmnm32_1, &mmnm32_2);
        mmnn32_2 = MatMulNumM32(mmnm32_2, MatMulNumM32(mmnm32_1, mmnn32_1));
        if(mmnn32_1 != mmnn32_2) break;
    }
    if(i < TEST) {printf("32bit: ERROR\n"); flag = 0;}
    else printf("32bit: PASS\n");

    M64 mmnm64_1, mmnm64_2;
    uint64_t mmnn64_1=0x8778877887788778, mmnn64_2;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM64(&mmnm64_1, &mmnm64_2);
        mmnn64_2 = MatMulNumM64(mmnm64_2, MatMulNumM64(mmnm64_1, mmnn64_1));
        if(mmnn64_1 != mmnn64_2)  break;
    }
    if(i < TEST) {printf("64bit: ERROR\n"); flag = 0;}
    else printf("64bit: PASS\n");

    printf("-----mat mul vec test-----\n");
    M4 mmvm4_1, mmvm4_2;
    V4 mmvv4_1, mmvv4_2, mmvv4_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM4(&mmvm4_1, &mmvm4_2);
        randV4(&mmvv4_1);
        MatMulVecM4(mmvm4_1, mmvv4_1, &mmvv4_2);
        MatMulVecM4(mmvm4_2, mmvv4_2, &mmvv4_3);
        if(!isequalV4(mmvv4_1, mmvv4_3)) break;
    }
    if(i < TEST) {printf("4bit: ERROR\n"); flag = 0;}
    else printf("4bit: PASS\n");

    M8 mmvm8_1, mmvm8_2;
    V8 mmvv8_1, mmvv8_2, mmvv8_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM8(&mmvm8_1, &mmvm8_2);
        randV8(&mmvv8_1);
        MatMulVecM8(mmvm8_1, mmvv8_1, &mmvv8_2);
        MatMulVecM8(mmvm8_2, mmvv8_2, &mmvv8_3);
        if(!isequalV8(mmvv8_1, mmvv8_3)) break;
    }
    if(i < TEST) {printf("8bit: ERROR\n"); flag = 0;}
    else printf("8bit: PASS\n");

    M16 mmvm16_1, mmvm16_2;
    V16 mmvv16_1, mmvv16_2, mmvv16_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM16(&mmvm16_1, &mmvm16_2);
        randV16(&mmvv16_1);
        MatMulVecM16(mmvm16_1, mmvv16_1, &mmvv16_2);
        MatMulVecM16(mmvm16_2, mmvv16_2, &mmvv16_3);
        if(!isequalV16(mmvv16_1, mmvv16_3)) break;
    } 
    if(i < TEST) {printf("16bit: ERROR\n"); flag = 0;}
    else printf("16bit: PASS\n");

    M32 mmvm32_1, mmvm32_2;
    V32 mmvv32_1, mmvv32_2, mmvv32_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM32(&mmvm32_1, &mmvm32_2);
        randV32(&mmvv32_1);
        MatMulVecM32(mmvm32_1, mmvv32_1, &mmvv32_2);
        MatMulVecM32(mmvm32_2, mmvv32_2, &mmvv32_3);
        if(!isequalV32(mmvv32_1, mmvv32_3)) break;
    }
    if(i < TEST) {printf("32bit: ERROR\n"); flag = 0;}
    else printf("32bit: PASS\n");

    M64 mmvm64_1, mmvm64_2;
    V64 mmvv64_1, mmvv64_2, mmvv64_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM64(&mmvm64_1, &mmvm64_2);
        randV64(&mmvv64_1);
        MatMulVecM64(mmvm64_1, mmvv64_1, &mmvv64_2);
        MatMulVecM64(mmvm64_2, mmvv64_2, &mmvv64_3);
        if(!isequalV64(mmvv64_1, mmvv64_3)) break;
    } 
    if(i < TEST) {printf("64bit: ERROR\n"); flag = 0;}
    else printf("64bit: PASS\n");

    M128 mmvm128_1, mmvm128_2;
    V128 mmvv128_1, mmvv128_2, mmvv128_3;
    for(i = 0; i < TEST; i++)
    {
        genMatpairM128(&mmvm128_1, &mmvm128_2);
        randV128(&mmvv128_1);
        MatMulVecM128(mmvm128_1, mmvv128_1, &mmvv128_2);
        MatMulVecM128(mmvm128_2, mmvv128_2, &mmvv128_3);
        if(!isequalV128(mmvv128_1, mmvv128_3)) break;
    } 
    if(i < TEST) {printf("128bit: ERROR\n"); flag = 0;}
    else printf("128bit: PASS\n");
    
    printf("-----mat mul mat (includes mat transpositon) test-----\n");
    M4 mmmm4_1, mmmm4_2, mmmm4_3;
    V4 mmmv4_1, mmmv4_2, mmmv4_3, mmmv4_4;
    for(i = 0; i < TEST; i++)
    {
        randM4(&mmmm4_1);
        randM4(&mmmm4_2);
        randV4(&mmmv4_1);
        MatMulVecM4(mmmm4_1, mmmv4_1, &mmmv4_2);
        MatMulVecM4(mmmm4_2, mmmv4_2, &mmmv4_3);
        MatMulMatM4(mmmm4_2, mmmm4_1, &mmmm4_3);
        MatMulVecM4(mmmm4_3, mmmv4_1, &mmmv4_4);
        if(!isequalV4(mmmv4_3, mmmv4_4)) break;
    }
    if(i < TEST) {printf("4bit: ERROR\n"); flag = 0;}
    else printf("4bit: PASS\n");
    
    M8 mmmm8_1, mmmm8_2, mmmm8_3;
    V8 mmmv8_1, mmmv8_2, mmmv8_3, mmmv8_4;
    for(i = 0; i < TEST; i++)
    {
        randM8(&mmmm8_1);
        randM8(&mmmm8_2);
        randV8(&mmmv8_1);
        MatMulVecM8(mmmm8_1, mmmv8_1, &mmmv8_2);
        MatMulVecM8(mmmm8_2, mmmv8_2, &mmmv8_3);
        MatMulMatM8(mmmm8_2, mmmm8_1, &mmmm8_3);
        MatMulVecM8(mmmm8_3, mmmv8_1, &mmmv8_4);
        if(!isequalV8(mmmv8_3, mmmv8_4)) break;
    }
    if(i < TEST) {printf("8bit: ERROR\n"); flag = 0;}
    else printf("8bit: PASS\n");
    
    M16 mmmm16_1, mmmm16_2, mmmm16_3;
    V16 mmmv16_1, mmmv16_2, mmmv16_3, mmmv16_4;
    for(i = 0; i < TEST; i++)
    {
        randM16(&mmmm16_1);
        randM16(&mmmm16_2);
        randV16(&mmmv16_1);
        MatMulVecM16(mmmm16_1, mmmv16_1, &mmmv16_2);
        MatMulVecM16(mmmm16_2, mmmv16_2, &mmmv16_3);
        MatMulMatM16(mmmm16_2, mmmm16_1, &mmmm16_3);
        MatMulVecM16(mmmm16_3, mmmv16_1, &mmmv16_4);
        if(!isequalV16(mmmv16_3, mmmv16_4)) break;
    }
    if(i < TEST) {printf("16bit: ERROR\n"); flag = 0;}
    else printf("16bit: PASS\n");

    M32 mmmm32_1, mmmm32_2, mmmm32_3;
    V32 mmmv32_1, mmmv32_2, mmmv32_3, mmmv32_4;
    for(i = 0; i < TEST; i++)
    {
        randM32(&mmmm32_1);
        randM32(&mmmm32_2);
        randV32(&mmmv32_1);
        MatMulVecM32(mmmm32_1, mmmv32_1, &mmmv32_2);
        MatMulVecM32(mmmm32_2, mmmv32_2, &mmmv32_3);
        MatMulMatM32(mmmm32_2, mmmm32_1, &mmmm32_3);
        MatMulVecM32(mmmm32_3, mmmv32_1, &mmmv32_4);
        if(!isequalV32(mmmv32_3, mmmv32_4)) break;
    }
    if(i < TEST) {printf("32bit: ERROR\n"); flag = 0;}
    else printf("32bit: PASS\n");

    M64 mmmm64_1, mmmm64_2, mmmm64_3;
    V64 mmmv64_1, mmmv64_2, mmmv64_3, mmmv64_4;
    for(i = 0; i < TEST; i++)
    {
        randM64(&mmmm64_1);
        randM64(&mmmm64_2);
        randV64(&mmmv64_1);
        MatMulVecM64(mmmm64_1, mmmv64_1, &mmmv64_2);
        MatMulVecM64(mmmm64_2, mmmv64_2, &mmmv64_3);
        MatMulMatM64(mmmm64_2, mmmm64_1, &mmmm64_3);
        MatMulVecM64(mmmm64_3, mmmv64_1, &mmmv64_4);
        if(!isequalV64(mmmv64_3, mmmv64_4)) break;
    }
    if(i < TEST) {printf("64bit: ERROR\n"); flag = 0;}
    else printf("64bit: PASS\n");

    M128 mmmm128_1, mmmm128_2, mmmm128_3;
    V128 mmmv128_1, mmmv128_2, mmmv128_3, mmmv128_4;
    for(i = 0; i < TEST; i++)
    {
        randM128(&mmmm128_1);
        randM128(&mmmm128_2);
        randV128(&mmmv128_1);
        MatMulVecM128(mmmm128_1, mmmv128_1, &mmmv128_2);
        MatMulVecM128(mmmm128_2, mmmv128_2, &mmmv128_3);
        MatMulMatM128(mmmm128_2, mmmm128_1, &mmmm128_3);
        MatMulVecM128(mmmm128_3, mmmv128_1, &mmmv128_4);
        if(!isequalV128(mmmv128_3, mmmv128_4)) break;
    }
    if(i < TEST) {printf("128bit: ERROR\n"); flag = 0;}
    else printf("128bit: PASS\n");

    printf("-----invertible and inverse test-----\n");
    M4 iim4_1, iim4_2, iim4_3, iim4_4, iim4_5;
    identityM4(&iim4_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM4(&iim4_1, &iim4_2);
        if(!isinvertM4(iim4_1)) break;
        if(!isinvertM4(iim4_2)) break;
        MatMulMatM4(iim4_1, iim4_2, &iim4_3);
        if(!isequalM4(iim4_3, iim4_4)) break;
        invsM4(iim4_1, &iim4_5);
        if(!isequalM4(iim4_2, iim4_5)) break;
    }
    if(i < TEST) {printf("4bit: ERROR\n"); flag = 0;}
    else printf("4bit: PASS\n");

    M8 iim8_1, iim8_2, iim8_3, iim8_4, iim8_5;
    identityM8(&iim8_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM8(&iim8_1, &iim8_2);
        if(!isinvertM8(iim8_1)) break;
        if(!isinvertM8(iim8_2)) break;
        MatMulMatM8(iim8_1, iim8_2, &iim8_3);
        if(!isequalM8(iim8_3, iim8_4)) break;
        invsM8(iim8_1, &iim8_5);
        if(!isequalM8(iim8_2, iim8_5)) break;
    }
    if(i < TEST) {printf("8bit: ERROR\n"); flag = 0;}
    else printf("8bit: PASS\n");

    M16 iim16_1, iim16_2, iim16_3, iim16_4, iim16_5;
    identityM16(&iim16_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM16(&iim16_1, &iim16_2);
        if(!isinvertM16(iim16_1)) break;
        if(!isinvertM16(iim16_2)) break;
        MatMulMatM16(iim16_1, iim16_2, &iim16_3);
        if(!isequalM16(iim16_3, iim16_4)) break;
        invsM16(iim16_1, &iim16_5);
        if(!isequalM16(iim16_2, iim16_5)) break;
    }
    if(i < TEST) {printf("16bit: ERROR\n"); flag = 0;}
    else printf("16bit: PASS\n");

    M32 iim32_1, iim32_2, iim32_3, iim32_4, iim32_5;
    identityM32(&iim32_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM32(&iim32_1, &iim32_2);
        if(!isinvertM32(iim32_1)) break;
        if(!isinvertM32(iim32_2)) break;
        MatMulMatM32(iim32_1, iim32_2, &iim32_3);
        if(!isequalM32(iim32_3, iim32_4)) break;
        invsM32(iim32_1, &iim32_5);
        if(!isequalM32(iim32_2, iim32_5)) break;
    }
    if(i < TEST) {printf("32bit: ERROR\n"); flag = 0;}
    else printf("32bit: PASS\n");

    M64 iim64_1, iim64_2, iim64_3, iim64_4, iim64_5;
    identityM64(&iim64_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM64(&iim64_1, &iim64_2);
        if(!isinvertM64(iim64_1)) break;
        if(!isinvertM64(iim64_2)) break;
        MatMulMatM64(iim64_1, iim64_2, &iim64_3);
        if(!isequalM64(iim64_3, iim64_4)) break;
        invsM64(iim64_1, &iim64_5);
        if(!isequalM64(iim64_2, iim64_5)) break;
    }
    if(i < TEST) {printf("64bit: ERROR\n"); flag = 0;}
    else printf("64bit: PASS\n");

    M128 iim128_1, iim128_2, iim128_3, iim128_4, iim128_5;
    identityM128(&iim128_4);
    for(i = 0; i < TEST; i++)
    {
        genMatpairM128(&iim128_1, &iim128_2);
        if(!isinvertM128(iim128_1)) break;
        if(!isinvertM128(iim128_2)) break;
        MatMulMatM128(iim128_1, iim128_2, &iim128_3);
        if(!isequalM128(iim128_3, iim128_4))  break;
        invsM128(iim128_1, &iim128_5);
        if(!isequalM128(iim128_2, iim128_5)) break;
    }
    if(i < TEST) {printf("128bit: ERROR\n"); flag = 0;}
    else printf("128bit: PASS\n");

    printf("-----invertible affine and affine transform test-----\n");
    Aff4 iaa4_1, iaa4_2;
    uint8_t iau4_1 = 0x0c, iau4_2, iau4_3;
    genaffinepairM4(&iaa4_1, &iaa4_2);
    iau4_2 = affineU4(iaa4_1, iau4_1);
    iau4_3 = affineU4(iaa4_2, iau4_2);
    if(iau4_1 == iau4_3) printf("4bit: PASS\n");
    else {printf("4bit: ERROR\n"); flag = 0;}

    Aff8 iaa8_1, iaa8_2;
    uint8_t iau8_1 = 0x87, iau8_2, iau8_3;
    genaffinepairM8(&iaa8_1, &iaa8_2);
    iau8_2 = affineU8(iaa8_1, iau8_1);
    iau8_3 = affineU8(iaa8_2, iau8_2);
    if(iau8_1 == iau8_3) printf("8bit: PASS\n");
    else {printf("8bit: ERROR\n"); flag = 0;}

    Aff16 iaa16_1, iaa16_2;
    uint16_t iau16_1=0x8778, iau16_2, iau16_3;
    genaffinepairM16(&iaa16_1, &iaa16_2);
    iau16_2 = affineU16(iaa16_1, iau16_1);
    iau16_3 = affineU16(iaa16_2, iau16_2);
    if(iau16_1 == iau16_3) printf("16bit: PASS\n");
    else {printf("16bit: ERROR\n"); flag = 0;}

    Aff32 iaa32_1, iaa32_2;
    uint32_t iau32_1=0x87788778, iau32_2, iau32_3;
    genaffinepairM32(&iaa32_1, &iaa32_2);
    iau32_2 = affineU32(iaa32_1, iau32_1);
    iau32_3 = affineU32(iaa32_2, iau32_2);
    if(iau32_1 == iau32_3) printf("32bit: PASS\n");
    else {printf("32bit: ERROR\n"); flag = 0;}

    Aff64 iaa64_1, iaa64_2;
    uint64_t iau64_1 = 0x8778877887788778, iau64_2, iau64_3;
    genaffinepairM64(&iaa64_1, &iaa64_2);
    iau64_2 = affineU64(iaa64_1, iau64_1);
    iau64_3 = affineU64(iaa64_2, iau64_2);
    if(iau64_1 == iau64_3) printf("64bit: PASS\n");
    else {printf("64bit: ERROR\n"); flag = 0;}

    Aff128 iaa128_1, iaa128_2;
    uint64_t iau128_1[2]={0x8778877887788778,0x8778877887788778}, iau128_2[2], iau128_3[2];
    genaffinepairM128(&iaa128_1, &iaa128_2);
    affineU128(iaa128_1, iau128_1, iau128_2);
    affineU128(iaa128_2, iau128_2, iau128_3);
    if( (iau128_1[0] == iau128_3[0]) && (iau128_1[1] == iau128_3[1]) ) printf("128bit: PASS\n");
    else {printf("128bit: ERROR\n"); flag = 0;}

    printf("-----affine mix test-----\n");
    Aff4 ama4_1, ama4_2, ama4_3, ama4_4, ama4_5;
    uint8_t amu4_1 = 0x0c, amu4_2, amu4_3, amu4_4, amu4_5;
    genaffinepairM4(&ama4_1, &ama4_2);
    genaffinepairM4(&ama4_3, &ama4_4);
    amu4_2 = affineU4(ama4_1, amu4_1);
    affinemixM4(ama4_3, ama4_2, &ama4_5);
    amu4_4 = affineU4(ama4_5, amu4_2);
    amu4_5 = affineU4(ama4_4, amu4_4);
    if(amu4_1 == amu4_5) printf("4bit: PASS\n");
    else {printf("4bit: ERROR\n"); flag = 0;}

    Aff8 ama8_1, ama8_2, ama8_3, ama8_4, ama8_5;
    uint8_t amu8_1 = 0x87, amu8_2, amu8_3, amu8_4, amu8_5;
    genaffinepairM8(&ama8_1, &ama8_2);
    genaffinepairM8(&ama8_3, &ama8_4);
    amu8_2 = affineU8(ama8_1, amu8_1);
    affinemixM8(ama8_3, ama8_2, &ama8_5);
    amu8_4 = affineU8(ama8_5, amu8_2);
    amu8_5 = affineU8(ama8_4, amu8_4);
    if(amu8_1 == amu8_5) printf("8bit: PASS\n");
    else {printf("8bit: ERROR\n"); flag = 0;}

    Aff16 ama16_1, ama16_2, ama16_3, ama16_4, ama16_5;
    uint16_t amu16_1 = 0x8778, amu16_2, amu16_3, amu16_4, amu16_5;
    genaffinepairM16(&ama16_1, &ama16_2);
    genaffinepairM16(&ama16_3, &ama16_4);
    amu16_2 = affineU16(ama16_1, amu16_1);
    affinemixM16(ama16_3, ama16_2, &ama16_5);
    amu16_4 = affineU16(ama16_5, amu16_2);
    amu16_5 = affineU16(ama16_4, amu16_4);
    if(amu16_1 == amu16_5) printf("16bit: PASS\n");
    else {printf("16bit: ERROR\n"); flag = 0;}

    Aff32 ama32_1, ama32_2, ama32_3, ama32_4, ama32_5;
    uint32_t amu32_1 = 0x87788778, amu32_2, amu32_3, amu32_4, amu32_5;
    genaffinepairM32(&ama32_1, &ama32_2);
    genaffinepairM32(&ama32_3, &ama32_4);
    amu32_2 = affineU32(ama32_1, amu32_1);
    affinemixM32(ama32_3, ama32_2, &ama32_5);
    amu32_4 = affineU32(ama32_5, amu32_2);
    amu32_5 = affineU32(ama32_4, amu32_4);
    if(amu32_1 == amu32_5) printf("32bit: PASS\n");
    else {printf("32bit: ERROR\n"); flag = 0;}

    Aff64 ama64_1, ama64_2, ama64_3, ama64_4, ama64_5;
    uint64_t amu64_1 = 0x87877887788778, amu64_2, amu64_3, amu64_4, amu64_5;
    genaffinepairM64(&ama64_1, &ama64_2);
    genaffinepairM64(&ama64_3, &ama64_4);
    amu64_2 = affineU64(ama64_1, amu64_1);
    affinemixM64(ama64_3,ama64_2, &ama64_5);
    amu64_4 = affineU64(ama64_5, amu64_2);
    amu64_5 = affineU64(ama64_4, amu64_4);
    if(amu64_1 == amu64_5) printf("64bit: PASS\n");
    else {printf("64bit: ERROR\n"); flag = 0;}

    Aff128 ama128_1, ama128_2, ama128_3, ama128_4, ama128_5;
    uint64_t amu128_1[2] = {0x8778877887788778, 0x8778877887788778}, amu128_2[2], amu128_3[2], amu128_4[2], amu128_5[2];
    genaffinepairM128(&ama128_1, &ama128_2);
    genaffinepairM128(&ama128_3, &ama128_4);
    affineU128(ama128_1, amu128_1, amu128_2);
    affinemixM128(ama128_3, ama128_2, &ama128_5);
    affineU128(ama128_5, amu128_2, amu128_4);
    affineU128(ama128_4, amu128_4, amu128_5);
    if( (amu128_1[0] == amu128_5[0]) && (amu128_1[1] == amu128_5[1]) ) printf("128bit: PASS\n");
    else {printf("128bit: ERROR\n"); flag = 0;}

    printf("-----affine concatenation test-----\n");
    Aff8 acm8[16];
    Aff32 acm32_1, acm32_2;
    Aff64 acm64_1, acm64_2;
    Aff128 acm128_1, acm128_2;
    identityM32(&acm32_2.Mat);
    identityM64(&acm64_2.Mat);
    identityM128(&acm128_2.Mat);
    for(i = 0; i < 16; i++)
    {
        identityM8(&acm8[i].Mat);
        acm8[i].Vec.V = 0xff;
    }
    affinecomM8to32(acm8[0], acm8[1], acm8[2], acm8[3], &acm32_1);
    if(isequalM32(acm32_1.Mat, acm32_2.Mat) && (acm32_1.Vec.V == 0xffffffff)) printf("8to32: PASS\n");
    else {printf("8to32: ERROR\n"); flag = 0;}

    affinecomM8to64(acm8[0], acm8[1], acm8[2], acm8[3], acm8[4], acm8[5], acm8[6], acm8[7], &acm64_1);
    if(isequalM64(acm64_1.Mat, acm64_2.Mat) && (acm64_1.Vec.V == 0xffffffffffffffff)) printf("8to64: PASS\n");
    else {printf("8to64: ERROR\n"); flag = 0;}

    affinecomM8to128(acm8[0], acm8[1], acm8[2], acm8[3], acm8[4], acm8[5], acm8[6], acm8[7], acm8[8], acm8[9], acm8[10], acm8[11], acm8[12], acm8[13], acm8[14], acm8[15], &acm128_1);
    if(isequalM128(acm128_1.Mat, acm128_2.Mat) && (acm128_1.Vec.V[0] == 0xffffffffffffffff) && (acm128_1.Vec.V[1] == 0xffffffffffffffff)) printf("8to128: PASS\n");
    else {printf("8to128: ERROR\n"); flag = 0;}

    Aff16 acm16[8];
    Aff32 acm32[4];
    for(i =0; i < 4; i++)
    {
        identityM16(&acm16[i].Mat);
        acm16[i].Vec.V = 0xffff;

        identityM32(&acm32[i].Mat);
        acm32[i].Vec.V = 0xffffffff;
    }
    for(i = 4; i < 8; i++)
    {
        identityM16(&acm16[i].Mat);
        acm16[i].Vec.V = 0xffff;
    }
    affinecomM16to64(acm16[0], acm16[1], acm16[2], acm16[3], &acm64_1);
    if(isequalM64(acm64_1.Mat, acm64_2.Mat) && (acm64_1.Vec.V == 0xffffffffffffffff)) printf("16to64: PASS\n");
    else {printf("16to64: ERROR\n"); flag = 0;}

    affinecomM32to128(acm32[0], acm32[1], acm32[2], acm32[3], &acm128_1);
    if(isequalM128(acm128_1.Mat, acm128_2.Mat) && (acm128_1.Vec.V[0] == 0xffffffffffffffff) && (acm128_1.Vec.V[1] == 0xffffffffffffffff)) printf("32to128: PASS\n");
    else {printf("32to128: ERROR\n"); flag = 0;}

    affinecomM16to128(acm16[0], acm16[1], acm16[2], acm16[3], acm16[4], acm16[5], acm16[6], acm16[7], &acm128_1);
    if(isequalM128(acm128_1.Mat, acm128_2.Mat) && (acm128_1.Vec.V[0] == 0xffffffffffffffff) && (acm128_1.Vec.V[1] == 0xffffffffffffffff)) printf("16to128: PASS\n");
    else {printf("16to128: ERROR\n"); flag = 0;}

    if(flag) printf("\nALL PASS!");
    else printf("\nERROR!");
    return 0;
}