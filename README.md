# Adding a System Call to xv6 RISC-V

This guide explains how to add a new system call to the xv6 RISC-V operating system. xv6 is a simple Unix-like teaching operating system developed at MIT. 

## Prerequisites

- Basic understanding of C programming
- Familiarity with operating system concepts
- A working [xv6](https://github.com/mit-pdos/xv6-riscv) development environment on RISC-V

## Steps to Add a System Call

### 1. Define the System Call

First, decide on the name and functionality of the new system call. For this example, we add a simple system call named `sys_helloworld` that prints "Hello, world!" to the console.

### 2. Modify the System Call Number

Edit the `kernel/syscall.h` file to add a new system call number. Append the new system call number to the list of existing system calls.

```c
...

#define SYS_helloworld  22 // Assign an unused number

...
```

### 3. Declare the System Call Function
Declare the new system call function in the `kernel/syscall.c` file.

```c
extern uint64 sys_helloworld(void);
```

### 4. Implement the System Call Function
Implement the system call in a new function in `kernel/sysproc.c`.

```c
uint64
sys_helloworld(void)
{
    printf("Hello, world!\n");
    return 0; // Return value to user program
}
```

### 5. Add System Call to syscalls Array
Add the system call to the syscalls array in `kernel/syscall.c`.

```c
static uint64 (*syscalls[])(void) = {
[SYS_fork]        sys_fork,
[SYS_exit]        sys_exit,
[SYS_wait]        sys_wait,
[SYS_pipe]        sys_pipe,
[SYS_read]        sys_read,
[SYS_kill]        sys_kill,
[SYS_exec]        sys_exec,
[SYS_fstat]       sys_fstat,
[SYS_chdir]       sys_chdir,
[SYS_dup]         sys_dup,
[SYS_getpid]      sys_getpid,
[SYS_sbrk]        sys_sbrk,
[SYS_sleep]       sys_sleep,
[SYS_uptime]      sys_uptime,
[SYS_open]        sys_open,
[SYS_write]       sys_write,
[SYS_mknod]       sys_mknod,
[SYS_unlink]      sys_unlink,
[SYS_link]        sys_link,
[SYS_mkdir]       sys_mkdir,
[SYS_close]       sys_close,
[SYS_helloworld]  sys_helloworld, // Add this line
};
```

### 6. Update the User Space Interface
Add a user space interface for the system call in `user/user.h`.

```c
int helloworld(void);
```
Implement the user space interface in `user/usys.pl`.

```perl
entry("helloworld")
```
### 7. Test the System Call
Create a user program to test the new system call. For example, add a new file `user/helloworld.c`.

```c
#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    helloworld();
    exit(0);
}
```
Add the new test program to the `Makefile` to compile it.

```
# In Makefile

...
U_PROGS=\
    $U_cat\
    $U_echo\
    $U_forktest\
    $U_grep\
    $U_helloworld\ # Add this line
...
```
### 8. Compile and Run xv6
Compile the xv6 kernel and run it.

```sh
make clean
make
make qemu
```
In the xv6 shell, run the `helloworld` program to see the output of the new system call.

```sh
$ helloworld
Hello, world!
```
## License

[MIT](https://choosealicense.com/licenses/mit/)
