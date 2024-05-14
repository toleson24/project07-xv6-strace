#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  struct proc *mp = myproc();
  argint(0, &n);
  if (mp->trace)
    printf("[%d] exit(%d)\n", mp->pid, n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  struct proc *mp = myproc();
  if (mp->trace)
    printf("[%d] getpid()\n", mp->pid);
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  struct proc *mp = myproc();
  if (mp->trace)
    printf("[%d] fork()\n", mp->pid);
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  struct proc *mp = myproc();
  if(mp->trace)
    printf("[%d] wait(%d)\n", mp->pid, p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_strace(void)
{
  int n;
  argint(0, &n);
  myproc()->trace = n;
  return 0;
}
