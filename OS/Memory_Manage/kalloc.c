#include "../Variety/defs.h"
#include "../Variety/mmu.h"
extern char Kernel_end[]; //内核的末尾的地址

struct run
{
        struct run *next;
}; //用于构建空闲页链表，空闲页的头放置于此
struct
{
        int num;
        struct run *freelist;
} kmem;                             //空闲页的链表头
void freerange(void *vs, void *ve); //用于释放vs到ve的页表地址
void kinit1(void *s, void *t)
{
        kmem.num = 0;
        freerange(s, t);
        printf("kinit1 over\n\r");
}
void kinit2(void *s, void *t)
{
        freerange(s, t);
}

void kfree(char *v)
{
        struct run *r;

        r = (struct run *)v;
        r->next = kmem.freelist;
        kmem.freelist = r;
        kmem.num++;
}
char *kalloc()
{
        struct run *r;
        if (kmem.num)
        {
                r = kmem.freelist;
                kmem.freelist = r->next;
        }
        else
        {
                r = (void *)0;
        }
        return r;
}

void freerange(void *vs, void *ve)
{
        char *p = (char *)PGROUNDUP(vs);
        for (; p + PGSIZE <= (char *)ve; p += PGSIZE)
        {
                kfree(p);
        }
}