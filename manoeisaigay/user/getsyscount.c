#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
  if (argc <= 1){
	printf(1,"fork-1   exit-2   wait-3   pipe-4\nread-5   kill-6   exec-7   fstat-8\nchdir-9   dup-10   getpid-11   sbrk-12\nsleep-13   uptime-14   open-15   write-16\nmknod-17   unlink-18   link-19   mkdir-20\nclose-21   getfavnum-22   halt-23   getpinfo-24\ngetcount-25   settickets-26   killrandom-27\n");
	 exit();
  }
  printf(1,"This system call has been used %d times\n",getcount(atoi(argv[1])));

  exit();

}


