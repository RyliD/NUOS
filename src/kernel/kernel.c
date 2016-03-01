#include "swi.h"

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
	
    int i;    
	int lit = 0;
	//put data
	_put32(0x00012345, 0x00020000);
	//_put32(0x00212345, 0x40000000);
	
	
    //mmu_section(0x00200000,0x00000000,0x0000);
    while (1) {    
		i = _get32(0x00012345);
        for (; i > 0; i--)
        {
            //user_write(1, "0", 1);
            //sys_write(1, "0", 1);

			
        }
		if( lit ) {
			//_put32(GPCLR1, RPI_GPIO_FSEL0_05_OUTPUT);
			_put32(0x3F20002C, (1 << 15)); 
			lit = 0;
			
			//mmu_section(0x00200000,0x00000000,0x0000);
			//debug_write_string("off ", 4);
		} else {
			//_put32(GPSET1, RPI_GPIO_FSEL0_05_OUTPUT);
			_put32(0x3F200020, (1 << 15));
			lit = 1;
			//debug_write_string("on ", 3);
			//mmu_section(0x00100000,0x00000000,0x0000);
		}
    }
    
    /* Never exit as there is no OS to exit to! */
    while(1) { }
}
