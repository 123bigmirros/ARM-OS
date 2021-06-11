#include "../Variety/types.h"
#include "../Variety/defs.h"
#include "../Variety/proc.h"
#include "../Variety/param.h"
struct
{
    struct proc proc[NPROC];
} ptable;
int nextpid = 1;
static struct proc *allocproc()
{
    struct proc *p;
    char *sp;

    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
        if (p->state == UNUSEED)
        {
            goto found;
        }
    }
    return 0;
found:
    //初始化proc
    p->state = EMBRYO;
    p->pid = nextpid++;

    if ((p->kstack = kalloc()) == 0)
    {
        p->state = UNUSEED;
        return 0;
    }

    sp = p->kstack + KSTACKSIZE;

    sp -= sizeof(struct context);
    p->context = sp;
    memset(p->context, 0, sizeof(*p->context));
    p->context->lr = 0;
    return p;
}

void userinit()
{
    struct proc *p;
    p = allocproc();
}