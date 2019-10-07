#include "WBMatrix.h"
int main()
{
    Aff8 aff,aff_inv;
    uint8_t t=1;//plaintext
    affinepairM8(&aff,&aff_inv);
    printU8(t);
    affineU8(aff,&t);
    printU8(t);//ciphertext
    affineU8(aff_inv,&t);
    printU8(t);
    return 0;
}