#include "../Variety/defs.h"
void trap(uint type)
{
    static int i = 0;
    printf("%x exception over\n\r", type & 0x7fffffff);
    return;
}