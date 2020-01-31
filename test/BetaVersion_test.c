#include "WBMatrix.h"

uint8_t identM8[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
int numxor(uint8_t num)
{
    int n=0;
    for(int i=0;i<8;i++)
    {
        if(num&0x01) n++;
        num=num>>1;
    }
    return n;
}
void diagdominM8(M8 *Mat)
{
    uint8_t temp;
    int flag;
    srand((randseed++)^time(NULL));
    for(int i=0;i<8;i++)
    {
        flag=1;
        while(flag)
        {
            flag=0;
            temp=rand()%256;
            while(!( ((temp&identM8[i])==identM8[i]) &&  xorU8(temp) ) )
            {
                temp=rand()%256;
            }
            for(int j=0;j<i;j++)
            {
                if((*Mat).M[j]==temp) 
                {
                    flag=1;
                    break;
                }
            }
        }
        (*Mat).M[i]=temp;
    }
}

void lowtoupM8(M8 *Mat)
{
    M8 temp;
    srand((randseed++)^time(NULL));
    for(int i=0;i<8;i++)
    {
        temp.M[i]=identM8[i];
        for(int j=0;j<i;j++)
        {
            if(rand()%2) temp.M[i]^=identM8[j];//1
            else//0
            {
                //if(rand()%2) 
                temp.M[j]^=identM8[i];
            }
        }
    }
    //printbitM8(temp);
    copyM8(temp,Mat);
}