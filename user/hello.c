#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
 
int
main(void) {
   printf("return val of system call is %d\n", hello());
   printf("mosioc added new system call in xv6 OS\n");
   exit(0);
}

