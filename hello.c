#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int
main(void) {
   printf("return val of system call is %d\n", hello());
   printf("new system  call\n");
    exit();
 }
