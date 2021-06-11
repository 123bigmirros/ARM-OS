//session
#define PGSIZE 4096      //每4MB内存形成一个虚拟一级页表条目
#define SECTION_SHIFT 20 //页表段类型条目标志总位数
#define SESSION_FLAG (1 << 1)
#define TEX_C_B_FLAG 0
#define APX_AP_FLAG (0x3 << 10)
#define SESSION_BASE_ENTRY (SESSION_FLAG | TEX_C_B_FLAG | APX_AP_FLAG)

//L1 L2
#define L1_FLAG (1 << 0)
#define L2_FLAG (1 << 1)
#define L2_TEX_C_B_FLAG 0
#define L2_APX_AP_FLAG (0x3 << 4)
#define L1_BASE_ENTRY (L1_FLAG)
#define L2_BASE_ENTRY (L2_FLAG | L2_TEX_C_B_FLAG | L2_APX_AP_FLAG)
#define PDXSHIFT 20
#define PTXSHIFT 12
#define PDX(x) (((uint)(x) >> PDXSHIFT) & (0xFFF))
#define PTX(x) (((uint)(x) >> PTXSHIFT) & (0xFF))

#define PTE_ADDR(x) ((uint)(x) & (~0x3FF))
#define PGROUNDUP(x) (((uint)(x) + PGSIZE - 1) & (~(PGSIZE - 1)))
#define PGROUNDDOWN(x) (((uint)(x)) & (~(PGSIZE - 1)))