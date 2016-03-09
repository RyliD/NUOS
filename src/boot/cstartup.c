#include "init.h"
#include "debug-write.h"
extern int __bss_start__;
extern int __bss_end__;

extern void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags );

void clear_BSS()
{    
    int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;

    while( bss < bss_end )
        *bss++ = 0;
}

void cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
{
    clear_BSS();
    
	
    init_uart();
    // other init stuff
    init_irq();
    init_memory();
    init_processor();
    
    // devices
    init_devices();
    init_gpio();
    init_arm_timer();
    
    /* Enable interrupts! */
    _enable_interrupts();
    
    // kernel
    kernel_main( r0, r1, r2 );

    while(1) { }
}
