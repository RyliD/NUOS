#ifndef RPI_GPIO_H
#define RPI_GPIO_H

#include "rpi-base.h"

#define RPI_GPIO_BASE       0x3F200000        // RPI_PERIPHERAL_BASE + 0x200000

#define LED_GPFSEL          GPFSEL4
#define LED_GPFBIT          21
#define LED_GPSET           GPSET1
#define LED_GPCLR           GPCLR1
#define LED_GPIO_BIT        15
#define LED_ON()            do { RPI_GetGpio()->LED_GPCLR = ( 1 << LED_GPIO_BIT ); } while( 0 )
#define LED_OFF()           do { RPI_GetGpio()->LED_GPSET = ( 1 << LED_GPIO_BIT ); } while( 0 )

#define GPFSEL0             RPI_GPIO_BASE + 0x0000    // GPIO Function Select 0     32
#define GPFSEL1             RPI_GPIO_BASE + 0x0004    // GPIO Function Select 1     32
#define GPFSEL2             RPI_GPIO_BASE + 0x0008    // GPIO Function Select 2     32
#define GPFSEL3             RPI_GPIO_BASE + 0x000C    // GPIO Function Select 3     32
#define GPFSEL4             RPI_GPIO_BASE + 0x0010    // GPIO Function Select 4     32
#define GPFSEL5             RPI_GPIO_BASE + 0x0014    // GPIO Function Select 5     32

#define GPSET0              RPI_GPIO_BASE + 0x001C    // GPIO Pin Output Set 0      32
#define GPSET1              RPI_GPIO_BASE + 0x0020    // GPIO Pin Output Set 1      32

#define GPCLR0              RPI_GPIO_BASE + 0x0028    // GPIO Pin Output Clear 0    32
#define GPCLR1              RPI_GPIO_BASE + 0x002C    // GPIO Pin Output Clear 1    32

#define GPLEV0              RPI_GPIO_BASE + 0x0034    // GPIO Pin Level 0           32
#define GPLEV1              RPI_GPIO_BASE + 0x0038    // GPIO Pin Level 1           32

#define GPEDS0              RPI_GPIO_BASE + 0x0040    // GPIO Pin Event Detect Status 0     32
#define GPEDS1              RPI_GPIO_BASE + 0x0044    // GPIO Pin Event Detect Status 1     32

#define GPREN0              RPI_GPIO_BASE + 0x004C    // GPIO Pin Rising Edge Detect Enable 0       32
#define GPREN1              RPI_GPIO_BASE + 0x0050    // GPIO Pin Rising Edge Detect Enable 1       32

#define GPFEN0              RPI_GPIO_BASE + 0x0058    // GPIO Pin Falling Edge Detect Enable 0      32
#define GPFEN1              RPI_GPIO_BASE + 0x005C    // GPIO Pin Falling Edge Detect Enable 1      32

#define GPHEN0              RPI_GPIO_BASE + 0x0064    // GPIO Pin High Detect Enable 0      32
#define GPHEN1              RPI_GPIO_BASE + 0x0068    // GPIO Pin High Detect Enable 1      32

#define GPLEN0              RPI_GPIO_BASE + 0x0070    // GPIO Pin Low Detect Enable 0       32
#define GPLEN1              RPI_GPIO_BASE + 0x0074    // GPIO Pin Low Detect Enable 1       32

#define GPAREN0             RPI_GPIO_BASE + 0x007C    // GPIO Pin Async Rising Edge Detect Enable 0     32
#define GPAREN1             RPI_GPIO_BASE + 0x0080    // GPIO Pin Async Rising Edge Detect Enable 1     32

#define GPAFEN0             RPI_GPIO_BASE + 0x0088    // GPIO Pin Async Falling Edge Detect Enable 0    32
#define GPAFEN1             RPI_GPIO_BASE + 0x008C    // GPIO Pin Async Falling Edge Detect Enable 1    32

#define GPPUD               RPI_GPIO_BASE + 0x0094    // GPIO Pin Pull-up/down Enable               32
#define GPPUDCLK0           RPI_GPIO_BASE + 0x0098    // GPIO Pin Pull-up/down Enable Clock 0       32
#define GPPUDCLK1           RPI_GPIO_BASE + 0x009C    // GPIO Pin Pull-up/down Enable Clock 1       32

#define RPI_GPIO_FSEL0_00_INPUT     ( 0 )
#define RPI_GPIO_FSEL0_00_OUTPUT    ( 1 )

#define RPI_GPIO_FSEL0_01_INPUT     ( 0 << 3 )
#define RPI_GPIO_FSEL0_01_OUTPUT    ( 1 << 3 )

#define RPI_GPIO_FSEL0_02_INPUT     ( 0 << 6 )
#define RPI_GPIO_FSEL0_02_OUTPUT    ( 1 << 6 )

#define RPI_GPIO_FSEL0_03_INPUT     ( 0 << 9 )
#define RPI_GPIO_FSEL0_03_OUTPUT    ( 1 << 9 )

#define RPI_GPIO_FSEL0_04_INPUT     ( 0 << 12 )
#define RPI_GPIO_FSEL0_04_OUTPUT    ( 1 << 12 )

#define RPI_GPIO_FSEL0_05_INPUT     ( 0 << 15 )
#define RPI_GPIO_FSEL0_05_OUTPUT    ( 1 << 15 )

#define RPI_GPIO_FSEL0_06_INPUT     ( 0 << 18 )
#define RPI_GPIO_FSEL0_06_OUTPUT    ( 1 << 18 )

#define RPI_GPIO_FSEL0_07_INPUT     ( 0 << 21 )
#define RPI_GPIO_FSEL0_07_OUTPUT    ( 1 << 21 )

#define RPI_GPIO_FSEL0_08_INPUT     ( 0 << 24 )
#define RPI_GPIO_FSEL0_08_OUTPUT    ( 1 << 24 )

#define RPI_GPIO_FSEL0_09_INPUT     ( 0 << 27 )
#define RPI_GPIO_FSEL0_09_OUTPUT    ( 1 << 27 )

#endif
