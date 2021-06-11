#include "./types.h"
#include "../uart/my_printf.h"
static void change_page_addr(uint pgdir)
{
    uint i;
    __asm__ __volatile__(
        "mov %1,#0\n"
        "mcr p15,0,%1,c7,c5,0\n"
        "mcr p15,0,%1,c7,c5,6\n"
        "mcr p15,0,%1,c8,c7,0\n"
        "ISB\n"
        "mcr p15, 0, %0, c2, c0, 0\n"
        :
        : "r"(pgdir), "r"(i));
}

static void enter_trap(uint type)
{
    __asm__ __volatile__(
        "push {lr}\n"
        "mov r0,%0\n"
        "swi 0\n"
        "pop {lr}\n"
        :
        : "r"(type));
}