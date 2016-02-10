
#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-armtimer.h"
#include "rpi-irq.h"

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{

    /* Enable the timer interrupt IRQ */
    PUT32(Enable_Basic_IRQs, RPI_BASIC_ARM_TIMER_IRQ);

    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    PUT32(RPI_ARMTIMER_Load, 0x400);

    /* Setup the ARM Timer */
    PUT32(RPI_ARMTIMER_Control,
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256);

    /* Enable interrupts! */
    _enable_interrupts();

    /* Never exit as there is no OS to exit to! */
    while(1)
    {

    }
}
