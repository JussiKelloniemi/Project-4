# Project 4
Jussi Kelloniemi

## Features

### getreadcount()
Getreadcount tracks different counters inside system calls. This can be called from the shell using: ```getcount <call-name> [r]```<br>
It can track how many times read, write, open, close and mkdir system calls have been called since kernel started.<br>
User can also reset each of these counters by using the "r" argument: ```getcount <name> r```<br>
Most changes were made to sysproc.c, syscall.c sysfile.c and getcount.c

## Running the program

To run the program I used these versions of QEMU, GCC and Linux:
* QEMU version used: QEMU emulator version 8.2.2 (Debian 1:8.2.2+ds-0ubuntu1.17)
* GCC: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
* Linux: Ubuntu 24.04.1 LTS
I also had to make changes to Makefile because the current version of gcc has stricter rules and for this reason wouldn't compile certain files without those changes.<br>


## Function
Every system call that is trackable has counter inside their functions for example sys_read counter:
```bash
int
sys_read(void)
{
  
  struct file *f;
  int n;
  char *p;
  
  readcount++; // Counter

  if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  return fileread(f, p, n);
}
```
Every time this system call is called it adds to the tracker so that the user can see how many time each system call is called since kernel started.<br>
Argstr is use to copy-in the call name from user space to kernel space.


## How to use counter and compile
The program can be launched using: ```make qemu```<br>
```bash
qemu-system-i386 -serial mon:stdio -drive file=fs.img,index=1,media=disk,format=raw -drive file=xv6.img,index=0,media=disk,format=raw -smp 2 -m 512 
xv6...
cpu0: starting 0
sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 inodestart 32 bmap start 58
init: starting sh
$ mkdir test1
$ mkdir test2
$ getcount mkdir
mkdir count: 2
$ getcount mkdir r
$ getcount mkdir
mkdir count: 0
$ 
```
This example shows what it looks like when you run the program using ```make qemu```<br>
After this as an example I create two directories and check mkdir count using getcount. After that I reset the counter using ```getcount mkdir r```and then checking the count again which has now reseted.<br>
The program does not print the counter after reseting it automatically because that can add new counts for that counter. This happens for example when i check read count. Checking that counter calls that read function making the count larger.<br>
Here is few more different calls user can check 
```bash 
$ getcount open
open count: 2
$ getcount close
close count: 1
$ getcount write
write count: 93
$ getcount write r
$ getcount write
write count: 2
```