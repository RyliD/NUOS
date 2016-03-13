#include "swi.h"

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    int i;    
    while (1) {    
        for (i = 0x2000000; i > 0; i--)
        {
            //user_write(1, "0", 1);
			debug_write_string("a", 1);
        }
		sys_write(1, "0", 1);
		//sys_read(1, "0", 1);
    }
    
    /* Never exit as there is no OS to exit to! */
    while(1) { }
}
