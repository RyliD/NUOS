#include "swi.h"
#include "functions.h"

void c_swi_handler(unsigned number, unsigned *regs)
{
    //write_hex(number);

    switch(number){
        case SYSCALL_NONE:
            _none();
            break;
        case SYSCALL_EXIT:
            //_exit((int)regs[0]);
            break;
        case SYSCALL_EXECVE:
            _execve((char*)regs[0], (char**)regs[1], (char**)regs[2]);
            break;
        case SYSCALL_FORK:
            _fork();
            break;
        case SYSCALL_GETPID:
            _getpid();
            break;
        case SYSCALL_KILL:
            _kill((int)regs[0], (int)regs[1]);
            break;
        case SYSCALL_TIMES:
            //_times((struct tms)regs[0]);
            break;
        case SYSCALL_OPEN:
            _open((char*)regs[0], (int)regs[1], (int)regs[2]);
            break;
        case SYSCALL_CLOSE:
            _close((int)regs[0]);
            break;
        case SYSCALL_ISATTY:
            _isatty((int)regs[0]);
            break;
        case SYSCALL_STAT:
            //_stat((char*)regs[0], (struct stat)regs[1]);
            break;
        case SYSCALL_FSTAT:
            //_fstat((int)regs[0], (struct stat)regs[1]);
            break;
        case SYSCALL_LSEEK:
            _lseek((int)regs[0], (int)regs[1], (int)regs[2]);
            break;
        case SYSCALL_READ:
            _read((int)regs[0], (char*)regs[1], (int)regs[2]);
            break;
        case SYSCALL_WRITE:            
            _write((int)regs[0], (char*)regs[1], (int)regs[2]);
            break;
        case SYSCALL_LINK:
            _link();
            break;
        case SYSCALL_UNLINK:
            _unlink((char*)regs[0]);
            break;
        case SYSCALL_SBRK:
            _sbrk((int)regs[0]);
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
