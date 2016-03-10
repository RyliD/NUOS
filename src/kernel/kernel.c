#include "swi.h"
#include "debug-write.h"
#include "functions.h"

void * get_pc () { return __builtin_return_address(0); }

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    int i;    
    while (1) {    
        for (i = 0x20000000; i > 0; i--)
        {
			// debug_write_hex(_get_stack_pointer());
            //user_write(1, "0", 1);
            //sys_write(1, "O", 1);
			// debug_write_hex((int)get_pc());
			// debug_write_hex((int)get_pc());
			// debug_write_hex((int)get_pc());
			debug_write_char('~');
			debug_write_char('!');
			debug_write_char('@');
			debug_write_char('#');
			debug_write_char('$');
			debug_write_char('%');
			debug_write_char('^');
			debug_write_char('&');
			debug_write_char('*');
			debug_write_char('(');
			debug_write_char(')');
        }
    }
    
    /* Never exit as there is no OS to exit to! */
    while(1) { }
}
