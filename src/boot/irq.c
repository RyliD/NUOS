
#include "irq.h"
#include "rpi-armtimer.h"

void c_irq_handler(void)
{
    static int lit = 0;
    
    PUT32(RPI_ARMTIMER_IRQClear, 1);
    
    /* Flip the LED */
    if( lit )
    {
        PUT32(0x3F20002C, (1 << 15));   
        lit = 0;
    }
    else
    {
        PUT32(0x3F200020, (1 << 15));
        lit = 1;
    }
}