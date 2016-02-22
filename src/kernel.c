
#include "functions.h"
#include "uart.h"
#include "swi.h"

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    int i;    
    while (1) {    
        for (i = 0x20000000; i > 0; i--)
        {
            user_write(1, "0", 1);
        }
    }
    
    /* Never exit as there is no OS to exit to! */
    while(1) { }
}


void write_char(char c) 
{
    uart_send(c);
}

static char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static char buf[] = {'0','0','0','0','0','0','0','0'};
void write_hex(int i)
{    
    write_char('0');
    write_char('x');

    int j=7;
    do
    {
        buf[j--] = hex[i & 0xf];
        i = (i >> 4);
    } while(j>=0);
    for(j=0;j<8;j++){
        write_char(buf[j]);
    }

    write_char(' ');
}

void write_string(char* c, int len) 
{
    int i;
    for (i = 0; i < len; i++) {
        write_char(c[i]);
    }
}

char read_char()
{
    return uart_receive();
}
