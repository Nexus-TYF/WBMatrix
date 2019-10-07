#include "WBMatrix.h"
int main()
{
    struct M8 M;
    struct V8 V;
    uint8_t t=1;//plaintext
    struct M8 M_inv;
    struct V8 V_inv;
    affinepairM8(&M,&V,&M_inv,&V_inv);
    printU8(t);
    affineU8(M,&t,V);
    printU8(t);//ciphertext
    affineU8(M_inv,&t,V_inv);
    printU8(t);
    return 0;
}