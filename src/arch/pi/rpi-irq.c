
#include <stdint.h>
#include <stdbool.h>

#include "init.h"
#include "rpi-armtimer.h"
#include "rpi-base.h"
#include "rpi-gpio.h"
#include "rpi-irq.h"


void init_irq(void)
{
    
}


void __attribute__((interrupt("ABORT"))) reset_vector(void) { }
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void) {
    while( 1 ) { }
}
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void) {
    while( 1 ) { }
}
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void) { }
void __attribute__((interrupt("ABORT"))) data_abort_vector(void) { }
void __attribute__((interrupt("IRQ"))) interrupt_vector(void) {
    static int lit = 0;
    PUT32(RPI_ARMTIMER_IRQClear, 1);

    if( lit ) {
        PUT32(GPCLR1, RPI_GPIO_FSEL0_05_OUTPUT);
        // PUT32(0x3F20002C, (1 << 15)); 
        lit = 0;
    } else {
        PUT32(GPSET1, RPI_GPIO_FSEL0_05_OUTPUT);
        // PUT32(0x3F200020, (1 << 15));
        lit = 1;
    }
}
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void) {
    interrupt_vector();
}
