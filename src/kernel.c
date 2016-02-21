
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    /* Never exit as there is no OS to exit to! */
    while(1) { }
}


#include "uart.h"

void write_char(char c) 
{
    uart_send(c);
}

void write_hex(int i) 
{
    int j,a;
    
    write_char('0');
    write_char('x');
    
    for (j=7;j>=0;j--) {
        a = (i & ('f' << j) >> j);
        a += (a > 0xa) ? 0x30 : 0x37;
        write_char(a);
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
