#include "functions.h"
#include "irq.h"
#include "rpi-base.h"
#include "rpi-gpio.h"

/*  BCM2835 ARM Peripherals
    Chapter 14
    Timer (ARM side)
*/
#define RPI_ARMTIMER_BASE                   0x3F00B400      // RPI_PERIPHERAL_BASE + 0xB400

struct rpi_armtimer {
    unsigned int Load;                  // 0x3F00B400
    unsigned int Value;                 // 0x3F00B404
    unsigned int Control;               // 0x3F00B408
    unsigned int IRQClear;              // 0x3F00B40C
    unsigned int RAWIRQ;                // 0x3F00B410
    unsigned int MaskedIRQ;             // 0x3F00B414
    unsigned int Reload;                // 0x3F00B418
    unsigned int PreDivider;            // 0x3F00B41C
    unsigned int FreeRunningCounter;    // 0x3F00B420
};

#define RPI_ARMTIMER_CTRL_23BIT             ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1        ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16       ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256      ( 2 << 2 )

#define RPI_ARMTIMER_CTRL_INT_ENABLE        ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE       ( 0 << 5 )

#define RPI_ARMTIMER_CTRL_ENABLE            ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE           ( 0 << 7 )

static volatile struct rpi_armtimer * const armtimer = 
    (volatile struct rpi_armtimer*)RPI_ARMTIMER_BASE;

void armtimer_irq_handler(void)
{
    static int lit = 0;
    armtimer->IRQClear = 1;

    if( lit ) {
        //_put32(GPCLR1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F20002C, (1 << 15)); 
        lit = 0;
        //write_char('0');
        write_string("off ", 4);
    } else {
        //_put32(GPSET1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F200020, (1 << 15));
        lit = 1;
        //write_char('1');
        write_string("on ", 3);
    }
}

void init_arm_timer(void)
{
    register_interrupt_handler(64, (interrupt_handler_t)armtimer_irq_handler);

    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    armtimer->Load = 0x400;

    /* Setup the ARM Timer */
    armtimer->Control = 
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;
}
