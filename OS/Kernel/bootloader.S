#include "../Variety/mode.h"
#include "../Variety/mmu.h"
.text
.global _start@该入口设置为中断向量，arm-contex-a7可以在任何位置设置中断向量，但是要保证32byte对齐
_start:
        b start
        .word 0
        b _software_interrupt
        .word 0
        .word 0
        b _data_abort
        .word 0
        .word 0
start:
        @uboot在已经默认了svc模式，所有不用开启
        @bl _cmode    

        @装载中断向量表
        bl _set_vertors 
        
        @设置堆栈，运行c函数的需要
        @需要清楚堆栈的运行方式
        ldr  sp,=0x80400000 

        @初始化页表，页表为直接映射，并保证页表首地址为16kb对齐
        @该页表将在以后被覆盖       
        bl init_page 
        
        @打开系统的虚拟内存(mmu),
        bl _set_mmu 
        bl main
halt:
        b halt
_cmode:
        
_set_mmu:@设置将虚拟内存开始的4MB映射到相同的物理地址上
  

        
        @0x80000000为页表地址,mmu查找c2来获取页表的地址
        ldr r0,=#0x80000000
        mcr p15, 0, r0, c2, c0, 0
        
        @domain无用，但是必须设置
        ldr r0,=DOMAIN_DEFAULT  
        mcr p15, 0, r0, c3, c0, 0 @设置c3来控制domain

        mrc p15,0,r0,c1,c0,0
        orr r0,r0,#0x1     @使能MMU
        mcr p15, 0, r0, c1, c0, 0
        
        mov pc,lr

_set_vertors:
        ldr r0,=_start
        mcr p15,0,r0,c12,c0,0
        mov pc,lr

