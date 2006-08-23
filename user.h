int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int cons_putc(int);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int panic(char*);
int cons_puts(char*);
int exec(char *, char **);
int open(char *, int);
int mknod (char*,short,short,short);
int unlink (char*);
int fstat (int fd, struct stat *stat);
int link(char *, char *);
int mkdir(char *);
int chdir(char *);
int dup(int);
int getpid();

int stat(char *, struct stat *stat);
int puts(char*);
char* strcpy(char*, char*);
char *strchr(const char *s, char c);
int strcmp(const char *p, const char *q);
void printf(int fd, char *fmt, ...);
char *gets(char *, int max);
unsigned int strlen(char *);
void * memset(void *dst, int c, unsigned int n);