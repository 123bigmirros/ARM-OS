#include "./types.h"
enum procstate
{
    UNUSEED,  //表示变量未被使用，不是进程状态
    EMBRYO,   //表示新建的进程
    SLEEPING, //表示进程在等待唤醒
    RUNNABLE, //表示进程可运行
    RUNNING,  //进程正在运行
    ZOMBIE    //进程已经死亡
};
struct context
{
    uint cpsr;
    uint sp;
    uint lr;
    uint pc;
};
struct proc
{
    uint sz;              //进程所占内存大小字节
    pde_t *pgdir;         //进程页表
    char *kstack;         //内核栈，用来运行内核进程
    enum procstate state; //进程状态
    uint pid;             //进程id
    struct proc *parent;  //父进程
    struct context *context;
};