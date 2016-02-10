
#include "init.h"
#include "rpi-gpio.h"

void init_gpio(void)
{
    /* Write 1 to the LED init nibble in the Function Select GPIO
    peripheral register to enable LED pin as an output */
    int ra = GET32(GPFSEL4); //0x3f200008);
    ra |= 21;
    PUT32(GPFSEL4, ra); //0x3f200008, ra);

}
