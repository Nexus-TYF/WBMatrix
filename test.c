#include "WBMatrix.h"
int main()
{
    struct M8 M;
    /*initM8(&M);
    randM8(&M);
    printM8(M);*/
    struct V8 V;
    /*initV8(&V);
    randV8(&V);
    printV8(V);*/
    uint8_t t=1;
    /*affineB1(M,&t,V);
    printf("%d",t);*/
    //printf("%d",xorU8(t));
    for(int i=0;i<8;i++)
    {
        M.M[i]=1;
    }
    V.V=0;
    affineU8(M,&t,V);
    printf("%d",t);

    return 0;
}