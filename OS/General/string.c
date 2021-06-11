#include"../Variety/defs.h"
void* memset(void* dst,int w,uint n){
        char* p = (char*)dst;
        w&=0xff;
        while(n--){
                *p = w;
                p = p+1;
        }
        return dst;
}