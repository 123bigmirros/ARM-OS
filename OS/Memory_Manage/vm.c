#include "../Variety/defs.h"
#include "../uart/my_printf.h"
#include "../Variety/mmu.h"
#include "../Variety/memlayout.h"
#include "../Variety/arm.h"
extern char rodata_end[];
extern char data_start[];
pde_t *kpgdir;
//获取与va相对应的二级页表的地址
static pde_t *walkpgdir(pde_t *pgdir, const void *va, int alloc)
{
    pde_t *pde;
    pde_t *pgtab;
    pde = &pgdir[PDX(va)];
    if ((*pde) & 1)
    {
        pgtab = (pde_t *)PTE_ADDR(*pde);
    }
    else
    {
        static int cnt = 4;
        static pde_t *nowpg;
        if (cnt == 4)
        {
            if ((nowpg = kalloc()) == 0)
            {
                printf("空间不足\n\r");
                return 0;
            }
            memset(nowpg, 0, PGSIZE);
            cnt = 0;
        }
        pgtab = (uint)nowpg + 1024 * cnt;
        ++cnt;
        *pde = (uint)pgtab | L1_BASE_ENTRY;
    }
    return &pgtab[PTX(va)];
}
//设置页表映射
static int mappages(pde_t *pgdir, void *va, uint pa, uint size, int mode)
{
    char *a, *last;
    pde_t *pte;

    a = (char *)PGROUNDDOWN((uint)va);
    last = (char *)PGROUNDDOWN(((uint)va) + size - 1);
    for (;;)
    {
        if ((pte = walkpgdir(pgdir, a, 1)) == 0)
            return -1;
        *pte = pa | mode;
        if (a == last)
            break;
        a += PGSIZE;
        pa += PGSIZE;
    }
    return 0;
}
static struct kmap
{
    void *vs;
    uint ps;
    uint pe;
    int mode;
} kmap[] = {
    {(void *)KERNBASE, 0x2000000, 0x2000000 + EXTMEM, L2_BASE_ENTRY},
    {(void *)LINK_ADD, LINK_ADD, rodata_end, L2_BASE_ENTRY},
    {(void *)data_start, data_start, PHYSTOP, L2_BASE_ENTRY}};
void kvmalloc()
{
    kpgdir = setupkvm();
    switchkvm();
    printf("kvmalloc over\n\r");
}
void switchkvm()
{
    change_page_addr((uint)kpgdir);
}
//生成kmap描述的内存布局
pde_t *setupkvm(void)
{
    pde_t *pgdir;
    struct kmap *k;

    for (int i = 0; i < 4; i++)
    {
        if ((pgdir = (pde_t *)kalloc()) == 0)
        {
            printf("内存不足\n\r");
            return 0;
        }
    }
    memset(pgdir, 0, PGSIZE * 4);

    for (k = kmap; k < &kmap[NELEM(kmap)]; k++)
    {
        if (mappages(pgdir, k->vs, k->ps, k->pe - k->ps, k->mode) < 0)
        {
            return 0;
        }
    }
    return pgdir;
}