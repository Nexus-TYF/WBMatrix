//Reverse LU Decomposition Method
#include "WBMatrix.h"
uint8_t identM8[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
void lowM8(M8 *Mat)
{
    M8 temp;
    srand((randseed++)^time(NULL));
    for(int i=0;i<8;i++)
    {
        temp.M[i]=identM8[i];
        for(int j=0;j<i;j++)
        {
            if(rand()%2) temp.M[i]^=identM8[j];
        }
    }
    copyM8(temp,Mat);
}