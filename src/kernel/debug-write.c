#include "uart.h"

static char hex_letters[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static char buf[] = {'0','0','0','0','0','0','0','0'};

void debug_write_char(char c) 
{
    uart_send(c);
}

void debug_write_hex(int i)
{    
    debug_write_char('0');
    debug_write_char('x');

    int j=7;
    do
    {
        buf[j--] = hex_letters[i & 0xf];
        i = (i >> 4);
    } while(j >= 0);
    
    for(j = 0; j < 8; j++)
    {
        debug_write_char(buf[j]);
    }

    debug_write_char(' ');
}

void debug_write_string(char* c, int len) 
{
    int i;
    for (i = 0; i < len; i++) {
        debug_write_char(c[i]);
    }
}
