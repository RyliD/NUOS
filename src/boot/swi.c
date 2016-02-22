#include "swi.h"
#include "functions.h"

void c_swi_handler(unsigned number, unsigned *regs)
{
    //write_hex(number);

    switch(number){
        case SYSCALL_NONE:
            sys_none();
            break;
        case SYSCALL_EXIT:
            //sys_exit((int)regs[0]);
            break;
        case SYSCALL_EXECVE:
            sys_execve((char*)regs[0], (char**)regs[1], (char**)regs[2]);
            break;
        case SYSCALL_FORK:
            sys_fork();
            break;
        case SYSCALL_GETPID:
            sys_getpid();
            break;
        case SYSCALL_KILL:
            sys_kill((int)regs[0], (int)regs[1]);
            break;
        case SYSCALL_TIMES:
            //sys_times((struct tms)regs[0]);
            break;
        case SYSCALL_OPEN:
            sys_open((char*)regs[0], (int)regs[1], (int)regs[2]);
            break;
        case SYSCALL_CLOSE:
            sys_close((int)regs[0]);
            break;
        case SYSCALL_ISATTY:
            sys_isatty((int)regs[0]);
            break;
        case SYSCALL_STAT:
            //sys_stat((char*)regs[0], (struct stat)regs[1]);
            break;
        case SYSCALL_FSTAT:
            //sys_fstat((int)regs[0], (struct stat)regs[1]);
            break;
        case SYSCALL_LSEEK:
            sys_lseek((int)regs[0], (int)regs[1], (int)regs[2]);
            break;
        case SYSCALL_READ:
            sys_read((int)regs[0], (char*)regs[1], (int)regs[2]);
            break;
        case SYSCALL_WRITE:            
            sys_write((int)regs[0], (char*)regs[1], (int)regs[2]);
            break;
        case SYSCALL_LINK:
            sys_link();
            break;
        case SYSCALL_UNLINK:
            sys_unlink((char*)regs[0]);
            break;
        case SYSCALL_SBRK:
            sys_sbrk((int)regs[0]);
            break;
        default:
            break;
    }
}

void user_none(void)
{
    asm volatile("swi %0" :: "I" (SYSCALL_NONE));    
}
void user_exit(int status)
{
    asm volatile("swi %0" :: "I" (SYSCALL_EXIT));
}
int user_execve(char *name, char **argv, char **env)
{
    asm volatile("swi %0" :: "I" (SYSCALL_EXECVE));
}
int user_fork(void)
{
    asm volatile("swi %0" :: "I" (SYSCALL_FORK));
}
int user_getpid(void)
{
    asm volatile("swi %0" :: "I" (SYSCALL_GETPID));
}
int user_kill(int pid, int sig)
{
    asm volatile("swi %0" :: "I" (SYSCALL_KILL));
}
clock_t user_times(struct tms *buf)
{
    asm volatile("swi %0" :: "I" (SYSCALL_TIMES));
}
int user_open(const char *name, int flags, int mode)
{
    asm volatile("swi %0" :: "I" (SYSCALL_OPEN));
}
int user_close(int file)
{
    asm volatile("swi %0" :: "I" (SYSCALL_CLOSE));
}
int user_isatty(int file)
{
    asm volatile("swi %0" :: "I" (SYSCALL_ISATTY));
}
int user_stat(const char *file, struct stat *st)
{
    asm volatile("swi %0" :: "I" (SYSCALL_STAT));
}
int user_fstat(int file, struct stat *st)
{
    asm volatile("swi %0" :: "I" (SYSCALL_FSTAT));
}
int user_lseek(int file, int ptr, int dir)
{
    asm volatile("swi %0" :: "I" (SYSCALL_LSEEK));
}
int user_read(int file, char *ptr, int len)
{
    asm volatile("swi %0" :: "I" (SYSCALL_READ));
}
int user_write(int file, char *ptr, int len)
{
    asm volatile("swi %0" :: "I" (SYSCALL_WRITE));
}
int user_link(void)
{
    asm volatile("swi %0" :: "I" (SYSCALL_LINK));
}
int user_unlink(char *name)
{
    asm volatile("swi %0" :: "I" (SYSCALL_UNLINK));
}
caddr_t user_sbrk(int incr)
{
    asm volatile("swi %0" :: "I" (SYSCALL_SBRK));
}
