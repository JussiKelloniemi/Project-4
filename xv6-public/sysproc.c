#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern int readcount;
extern int mkdircount;
extern int closecount;
extern int opencount;
extern int writecount;

int 
sys_getmkdircount(void) // Counts how many times mkdir has been called
{
  return mkdircount;
}

int 
sys_getclosecount(void) // Counts how many times close has been called
{
  return closecount;
}

int 
sys_getopencount(void) // Counts how many times open has been called
{
  return opencount;
}

int 
sys_getwritecount(void) // Counts how many times write has been called
{
  return writecount;
}

int 
sys_getreadcount(void) // Counts how many times read has been called
{
  return readcount;
}

/* Copied this from ulib.c so that it can be called here */
int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

int
sys_resetcount(void) // Resets each counter when they are called
{
  char *call;
  if(argstr(0, &call) < 0) {
    return -1;
  }
  if((strcmp(call, "read")) == 0) {
    readcount = 0;
  }
  if((strcmp(call, "write")) == 0) {
    writecount = 0;
  }
  if((strcmp(call, "open")) == 0) {
    opencount = 0;
  }
  if((strcmp(call, "close")) == 0) {
    closecount = 0;
  }
  if((strcmp(call, "mkdir")) == 0) {
    mkdircount = 0;
  }

  return 0;
}

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

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
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
    if(myproc()->killed){
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
