#include "functions.h"
#include "irq.h"
#include "rpi-base.h"
#include "rpi-gpio.h"

/*  BCM2835 ARM Peripherals
    Chapter 14
    Timer (ARM side)
*/
#define RPI_ARMTIMER_BASE                   0x3F00B000      // RPI_PERIPHERAL_BASE + 0xB000

#define RPI_ARMTIMER_Load                   RPI_ARMTIMER_BASE + 0x400
#define RPI_ARMTIMER_Value                  RPI_ARMTIMER_BASE + 0x404
#define RPI_ARMTIMER_Control                RPI_ARMTIMER_BASE + 0x408
#define RPI_ARMTIMER_IRQClear               RPI_ARMTIMER_BASE + 0x40C
#define RPI_ARMTIMER_RAWIRQ                 RPI_ARMTIMER_BASE + 0x410
#define RPI_ARMTIMER_MaskedIRQ              RPI_ARMTIMER_BASE + 0x414
#define RPI_ARMTIMER_Reload                 RPI_ARMTIMER_BASE + 0x418
#define RPI_ARMTIMER_PreDivider             RPI_ARMTIMER_BASE + 0x41C
#define RPI_ARMTIMER_FreeRunningCounter     RPI_ARMTIMER_BASE + 0x420

#define RPI_ARMTIMER_CTRL_23BIT             ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1        ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16       ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256      ( 2 << 2 )

#define RPI_ARMTIMER_CTRL_INT_ENABLE        ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE       ( 0 << 5 )

#define RPI_ARMTIMER_CTRL_ENABLE            ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE           ( 0 << 7 )

void armtimer_irq_handler(void)
{
    static int lit = 0;
    _put32(RPI_ARMTIMER_IRQClear, 1);
    //_put32(0x3F00B40C, 1);

    if( lit ) {
        //_put32(GPCLR1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F20002C, (1 << 15)); 
        lit = 0;
    } else {
        //_put32(GPSET1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F200020, (1 << 15));
        lit = 1;
    }
}

void init_arm_timer(void)
{
    register_interrupt_handler(64, (interrupt_handler_t)armtimer_irq_handler);

    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    _put32(RPI_ARMTIMER_Load, 0x400);

    /* Setup the ARM Timer */
    _put32(RPI_ARMTIMER_Control,
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256);
}