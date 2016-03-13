
#include <errno.h>
#undef errno
extern int errno;

#include <sys/stat.h>
#include <sys/times.h>
#include "swi.h"
#include "uart.h"

extern caddr_t _get_stack_pointer(void);

void sys_none() { }

void sys_exit( int status )
{
    (int)status;
    while(1){}
}

int sys_execve( char *name, char **argv, char **env )
{
    errno = ENOMEM;
    return -1;
}

int sys_fork( void )
{
    errno = EAGAIN;
    return -1;
}

int sys_getpid( void ) { return 1; }

int sys_kill( int pid, int sig )
{
    errno = EINVAL;
    return -1;
}

clock_t sys_times( struct tms *buf ) { return -1; }

int sys_wait( int *status )
{
    errno = ECHILD;
    return -1;
}

// FS / Device 
int sys_close( int file ) { return -1; }
int sys_fstat( int file, struct stat *st )
{
    st->st_mode = S_IFCHR;
    return 0;
}
int sys_isatty(int file) { return 1; }
int sys_lseek(int file, int ptr, int dir) { return 0; }
int sys_open( const char *name, int flags, int mode ) { return -1; }
int sys_read( int file, char *ptr, int len ) {
	uart_receive();
	return 0; 
}
int sys_stat( const char *file, struct stat *st )
{
    st->st_mode = S_IFCHR;
    return 0;
}
int sys_link() { }
int sys_unlink( char *name )
{
    errno = ENOENT;
    return -1;
}
int sys_write( int file, char *ptr, int len )
{
    int i;

    for( i = 0; i < len; i++ )
    {
        uart_send(ptr[i]);
    }

    return len;
}

// Memory
caddr_t sys_sbrk( int incr )
{
    extern char _end;
    static char* heap_end;
    char* prev_heap_end;

    if( heap_end == 0 )
        heap_end = &_end;

     prev_heap_end = heap_end;

     if( ( heap_end + incr ) > _get_stack_pointer() )
     {
        // TRAP HERE!
        while( 1 ) {  }
     }

     heap_end += incr;
     return (caddr_t)prev_heap_end;
}
caddr_t _sbrk( int incr ) { sys_sbrk(incr); }
