#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern struct ptable ptable;
extern int inctable[35];
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpinfo(void) 
{
    struct pstat *pstat;

    argptr(0, (void*)&pstat, sizeof(*pstat));

    if (pstat == 0) {
        return -1;
    }

    acquire(&ptable.lock);
    struct proc *p;
    int i;
    for (p = ptable.proc; p != &(ptable.proc[NPROC]); p++) 
    {
        i = p - ptable.proc;

        /* if (p->state == UNUSED) { */
        /*     pstat->inuse[i] = 0; */
        /* } else { */
        /*     pstat->inuse[i] = 1; */
        /* } */
        pstat->inuse[i] = p->inuse;
        pstat->pid[i] = p->pid;
        pstat->ticks[i] = p->ticks;
        pstat->tickets[i] = p->tickets;
    }
    release(&ptable.lock);
    return 0;
}

int
sys_getpid(void)
{
  return proc->pid;
}

uintp
sys_sbrk(void)
{
  uintp addr;
  uintp n;

  if(arguintp(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int sys_getcount(void){
  int syscall;
  argint(0, &syscall) < 0;

  return inctable[syscall - 1];
}

int
sys_killrandom(void)
{
  int usedpr[NPROC]={0};
  acquire(&ptable.lock);
  struct proc *p;
  int incr = 0;
  for (p = ptable.proc; p != &(ptable.proc[NPROC]); p++) 
    {
        if(p->state != UNUSED) {
          usedpr[incr]=p->pid;
          incr++;
        }
    }
  release(&ptable.lock);
  int rd_pid = rand() % incr;  
  cprintf("Killing PID %d\n", usedpr[rd_pid]);
  return kill(usedpr[rd_pid]);cprintf("Killing PID %d\n", usedpr[rd_pid]);
 
}

int sys_getfavnum(void)
{
return 67;
}

void sys_halt(void){
outw(0x604, 0x2000);
}


int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
