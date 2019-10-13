/*
 * @Author: Weijie Li 
 * @Date: 2018-11-12 19:16:04 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-11-12 20:49:44
 */

#include <m4ri/wrandom.h>
#include <stdlib.h>


#ifdef AISINO_RAND_FUNC

#include "AisinoRand/rand.h"

char* wRandFuncVersion()
{
    return "aisino_rand";
}

int wRandomList(int *list, int len){
    return aisino_rand_list(NULL, list, len);
}

uint32_t wRand31() {
    int tmp;
    wRandomList(&tmp, 1);
    return tmp;
}

uint32_t wRand32() {
    int tmp[2];
    wRandomList(tmp, 2);
    uint32_t res = tmp[0] ^ (tmp[1] << 1);
    return res;
}

uint64_t wRand64() {
    int tmp[3];
    wRandomList(tmp, 3);
    uint64_t a,b,c;
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];
    uint64_t res= a ^ (b<<21) ^ (c<<42) ;
    return res;
}

#elif defined CUSTOM_RAND_FUNC

char* wRandFuncVersion()
{
    return "custom random function";
}

// please set the <Custom random function> in here
uint32_t wRand31()=0;

#else

#include<time.h> 
#include <stdlib.h>

char* wRandFuncVersion()
{
    return "default rand() function";
}

static int inited = 0;

uint32_t wRand31() {
    if (inited==0) {
        inited = 1;
        srand(time(0)); 
    }
    return rand();
}

uint32_t wRand32() {
    uint32_t res = wRand31() ^ (wRand31() << 1);
    return res;
}

uint64_t wRand64() {
    uint64_t a,b,c;
    a = wRand31();
    b = wRand31();
    c = wRand31();
    uint64_t res= a ^ (b<<21) ^ (c<<42) ;
    return res;
}

// // Rand a list of Number
// static int random_rand(unsigned char *output, size_t size);

// // Rand a list of int32
// static int random_rand_int_array(int *output, int count);

// Rand a list of int32 (if ctx==NULL, then init a global ctx)
int wRandomList(int *list, int len){
    if (list == NULL)
        return -1;
    while(len--) {
        *list = wRand31();
    }
    return 0;
}

#endif

int wRandomShuffleU8(uint8_t *list, int len) {
    int t, roundCnt, ret;
    unsigned int *randNumbers;
    randNumbers = (unsigned int *)malloc((len + 10) * sizeof(unsigned int));
    wRandomList((int*) randNumbers, len);
    while (len > 0) {
        int r = randNumbers[len] % len;
        len--;
        uint8_t tmp = *(list + len);
        *(list + len) = *(list + r);
        *(list + r) = tmp;
    }
    free(randNumbers);
    return 0;
}


