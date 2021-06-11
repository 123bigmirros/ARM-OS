.text
.global _software_interrupt
_software_interrupt:
    push {r0-r12,r14}
    mov r0,lr;
    bl  trap
    pop {r0-r12,r14}
    movs pc,lr
.global _data_abort
_data_abort:
    push {r0-r12,r14}
    bl test2
    bl trap
    pop {r0-r12,r14}
    subs pc,lr,#8


