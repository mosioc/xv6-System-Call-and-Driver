# Adding a System Call and RTC driver to xv6 RISC-V OS 

This guide explains how to run the xv6 RISC-V operating system on Linux, add a new system call and RTC driver to it. xv6 is a simple Unix-like educational operating system developed at MIT. Download full report [here](https://github.com/mosioc/xv6-System-Call-and-Driver/blob/main/xv6-project-report-mehdi-maleki.pdf). 

## Prerequisites

- Basic understanding of C programming
- Familiarity with operating system concepts
- A working [xv6](https://github.com/mit-pdos/xv6-riscv) development environment on RISC-V

Ensure you have the following installed on your Linux distribution:
- `git`
- `qemu`
- `gcc` (with RISC-V support)
- `make`
## Setting Up xv6 RISC-V on Linux
### xv6 Installation Steps

1. **Clone the Repository**

```bash
git clone https://github.com/mit-pdos/xv6-riscv.git
cd xv6-riscv
```
2. **Install RISC-V Toolchain**

Follow the instructions [here](https://github.com/riscv/riscv-gnu-toolchain) to install the RISC-V GNU toolchain. If you don't want to download a lot of files, installing the following is enough: 

Debian or Ubuntu:
```bash
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64 linux-gnu 
   ```
Arch:
```bash
sudo pacman -S riscv64-linux-gnu-binutils riscv64-linux-gnu-gcc riscv64-linux-gnu-gdb qemu-emulators-full
```
3. **Build the xv6 Kernel**

```bash
make
```
4. **Run xv6 using QEMU**

```bash
make
make qemu
```

## Steps to Add a System Call

### 1. Define the System Call

First, decide on the name and functionality of the new system call. For this example, we add a simple system call named `sys_helloworld` that prints "Hello, world!" to the console.

### 2. Modify the System Call Number

Edit the `kernel/syscall.h` file to add a new system call number. Append the new system call number to the list of existing system calls.

```c
//
...

#define SYS_helloworld  22 // Assign an unused number

...
//
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

## Adding a Real-Time Clock (RTC) Driver

The Real-Time Clock (RTC) is a crucial component in many operating systems, providing accurate timekeeping and periodic interrupts for various time-related tasks. In xv6, integrating an RTC driver involves several steps, including interacting with hardware registers, handling interrupts, and providing a user interface for reading the current time.

The RTC driver in xv6 interacts with the hardware clock to retrieve the current time and date. This involves reading from specific hardware registers that maintain time information. Additionally, the RTC can generate interrupts at regular intervals, which can be used for tasks such as system timekeeping or scheduling.

### Steps to Implement the RTC Driver
1. Identify RTC Registers and Hardware Interface
The RTC hardware typically provides registers for seconds, minutes, hours, day, month, and year.
These registers are mapped to specific memory addresses, which the driver will read to get the current time.

3. Define RTC Data Structures
Define a structure to hold the time and date information.
```c
struct rtcdate {
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
};
```
3. Initialize the RTC Driver
Set up the necessary hardware initialization, which might involve configuring the RTC to generate interrupts or setting initial values.

```c
void rtcinit(void) {
    // Initialize RTC hardware settings if needed
}
```
4. Read Time from RTC
Implement a function to read the current time from the RTC registers.

```c
void rtc_read(struct rtcdate *r) {
    // Read from the RTC hardware registers
    r->second = // read from hardware register;
    r->minute = // read from hardware register;
    r->hour =   // read from hardware register;
    r->day =    // read from hardware register;
    r->month =  // read from hardware register;
    r->year =   // read from hardware register;
}
```
5. Handle RTC Interrupts
Set up an interrupt handler for the RTC to handle periodic updates or alarms. This involves configuring the CPU to handle interrupts generated by the RTC.

```c
void rtc_interrupt_handler(void) {
    // Handle the RTC interrupt
}

void init_interrupts(void) {
    // Register the RTC interrupt handler
}
```
6. Expose RTC Functionality to User Programs
Add a system call to allow user programs to read the current time.
```c
extern uint64 sys_rtcdate(void);

uint64 sys_rtcdate(void) {
    struct rtcdate r;
    rtc_read(&r);
    // Copy the rtcdate structure to user space
    // ...
    return 0; // Return appropriate value
}
```
Modify syscall.h to add a new system call number.

```c
#define SYS_rtcdate  23
```

Add the system call to the syscall dispatch table in syscall.c.
```c
static uint64 (*syscalls[])(void) = {
    // ... existing system calls ...
    [SYS_rtcdate]   sys_rtcdate,
};
```
Add a user space interface for the system call.
```c
Copy code
int rtcdate(struct rtcdate *r) {
    return syscall(SYS_rtcdate, r);
}
```
Implement the user space interface in usys.pl.

```c
Copy code
entry("rtcdate")
7. Test the RTC Driver
```
Create a user program to test the RTC functionality.

```c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/date.h"

int main(void) {
    struct rtcdate r;
    rtcdate(&r);
    printf("Date: %d-%d-%d Time: %d:%d:%d\n",
           r.year, r.month, r.day,
           r.hour, r.minute, r.second);
    exit(0);
}
```
Add the new test program to the Makefile to compile it.
```c
Makefile
Copy code
# In Makefile...
U_PROGS=\
    ... \
    $U_rtc_test  # Add this line
```
Compile and run xv6, and execute the test program in the xv6 shell to see the output of the RTC.

```sh
$ rtc_test
Date: 2024-5-27 Time: 15:30:45
```
## License

[MIT](https://choosealicense.com/licenses/mit/)
