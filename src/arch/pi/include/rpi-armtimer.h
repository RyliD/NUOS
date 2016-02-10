
/*  BCM2835 ARM Peripherals
    Chapter 14
    Timer (ARM side)
*/
#ifndef RPI_ARMTIMER_H
#define RPI_ARMTIMER_H

#include "rpi-base.h"

#define RPI_ARMTIMER_BASE                  RPI_PERIPHERAL_BASE + 0xB000

#define RPI_ARMTIMER_Load                  RPI_ARMTIMER_BASE + 0x400
#define RPI_ARMTIMER_Value                 RPI_ARMTIMER_BASE + 0x404
#define RPI_ARMTIMER_Control               RPI_ARMTIMER_BASE + 0x408
#define RPI_ARMTIMER_IRQClear              RPI_ARMTIMER_BASE + 0x40C
#define RPI_ARMTIMER_RAWIRQ                RPI_ARMTIMER_BASE + 0x410
#define RPI_ARMTIMER_MaskedIRQ             RPI_ARMTIMER_BASE + 0x414
#define RPI_ARMTIMER_Reload                RPI_ARMTIMER_BASE + 0x418
#define RPI_ARMTIMER_PreDivider            RPI_ARMTIMER_BASE + 0x41C
#define RPI_ARMTIMER_FreeRunningCounter    RPI_ARMTIMER_BASE + 0x420

#define RPI_ARMTIMER_CTRL_23BIT         ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

#define RPI_ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

#define RPI_ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE       ( 0 << 7 )

#endif
