#include "types.h"
//Memmory_Manage
//kalloc.c

char *kalloc();
void kfree(char *);
void kinit1(void *, void *);
void kinit2(void *, void *);
//vm.h
void kvmalloc();
pde_t *setupkvm();
void switchkvm();

//proc.c
void userinit();
//string.c
void *
memset(void *, int, uint);

#define NELEM(x) (sizeof(x) / sizeof((x)[0]))