#include "../Variety/mmu.h"
#include "../Variety/memlayout.h"
#include "../Variety/types.h"
#include "../uart/my_printf.h"
#include "../uart/uart.h"
#include "../Variety/arm.h"
void init_page();
void creat_entry(pde_t *ttb, uint va, uint pa, uint mode);
extern char Kernel_end[];

int main()
{
        Uart_Init();
        kinit1(Kernel_end, P2V(64 * 1024 * 1024));
        kvmalloc();

        return 0;
}
void init_page()
{
        pde_t *ttb = (pde_t *)0x80000000;
        pde_t s;
        for (s = 0x0; s < 0xfff00000; s += 0x100000)
        {
                creat_entry(ttb, s, s, SESSION_BASE_ENTRY);
        }
        creat_entry(ttb, 0x80000000, 0x2000000, SESSION_BASE_ENTRY);
        return;
}
void creat_entry(pde_t *ttb, uint va, uint pa, uint mode)
{
        int index = (va / 0x100000);
        ttb[index] = (pa & 0xfff00000) | mode;
}