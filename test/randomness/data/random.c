#include "time.h"
#include "stdlib.h"
#include "stdio.h"
int main()
{
    FILE *fd = fopen("random.bin","wb");
    char s1 = 0x00;
    srand(time(NULL));
    if(fd == NULL)
    {
        perror("open failed!");
        exit(1);
    }
    for(int i = 0; i < 100000; i++)
    {
        s1 = rand();
        fwrite(&s1,sizeof(s1),1,fd);
    }
    fclose(fd);
    return 0;
}