
#include "init.h"
#include "functions.h"
#include "rpi-gpio.h"
#include "rpi-irq.h"
#include "types.h"

#define AUX_IRQ                 RPI_GPIO_BASE + 0x215000    // Auxiliary Interrupt Status       3
#define AUX_ENABLES             RPI_GPIO_BASE + 0x215004    // Auxiliary enables                3

#define AUX_MU_IO_REG           RPI_GPIO_BASE + 0x215040    // Mini Uart I/O Data               8
#define AUX_MU_IER_REG          RPI_GPIO_BASE + 0x215044    // Mini Uart Interrupt Enable       8
#define AUX_MU_IIR_REG          RPI_GPIO_BASE + 0x215048    // Mini Uart Interrupt Identify     8
#define AUX_MU_LCR_REG          RPI_GPIO_BASE + 0x21504C    // Mini Uart Line Control           8
#define AUX_MU_MCR_REG          RPI_GPIO_BASE + 0x215050    // Mini Uart Modem Control          8
#define AUX_MU_LSR_REG          RPI_GPIO_BASE + 0x215054    // Mini Uart Line Status            8
#define AUX_MU_MSR_REG          RPI_GPIO_BASE + 0x215058    // Mini Uart Modem Status           8
#define AUX_MU_SCRATCH          RPI_GPIO_BASE + 0x21505C    // Mini Uart Scratch                8
#define AUX_MU_CNTL_REG         RPI_GPIO_BASE + 0x215060    // Mini Uart Extra Control          8
#define AUX_MU_STAT_REG         RPI_GPIO_BASE + 0x215064    // Mini Uart Extra Status           32
#define AUX_MU_BAUD_REG         RPI_GPIO_BASE + 0x215068    // Mini Uart Baudrate               16

#define AUX_SPI0_CNTL0_REG      RPI_GPIO_BASE + 0x215080    // SPI 1 Control Register 0         32
#define AUX_SPI0_CNTL1_REG      RPI_GPIO_BASE + 0x215084    // SPI 1 Control Register 1         8
#define AUX_SPI0_STAT_REG       RPI_GPIO_BASE + 0x215088    // SPI 1 Status                     32
#define AUX_SPI0_IO_REG         RPI_GPIO_BASE + 0x215090    // SPI 1 Data                       32
#define AUX_SPI0_PEEK_REG       RPI_GPIO_BASE + 0x215094    // SPI 1 Peek                       16

#define AUX_SPI1_CNTL0_REG      RPI_GPIO_BASE + 0x2150C0    // SPI 2 Control Register 0         32
#define AUX_SPI1_CNTL1_REG      RPI_GPIO_BASE + 0x2150C4    // SPI 2 Control Register 1         8
#define AUX_SPI1_STAT_REG       RPI_GPIO_BASE + 0x2150C8    // SPI 2 Status                     32
#define AUX_SPI1_IO_REG         RPI_GPIO_BASE + 0x2150D0    // SPI 2 Data                       32
#define AUX_SPI1_PEEK_REG       RPI_GPIO_BASE + 0x2150D4    // SPI 2 Peek                       16


void init_uart()
{
    unsigned int ra;
    
    // Disable AUX interrupts
    PUT32(Disable_IRQs_1, 1<<29);    
    // Enable Mini Uart    
	PUT32(AUX_ENABLES, 1);    
    // Clear FIFO interrupts
	PUT32(AUX_MU_IER_REG, 0);    
    // Disable Extra control functions
	PUT32(AUX_MU_CNTL_REG, 0);    
    // Set Uart to 8-bit mode
	PUT32(AUX_MU_LCR_REG, 1);    
    // nothing??
	PUT32(AUX_MU_MCR_REG, 0);    
    // interrupt fires on holding valid byte
	PUT32(AUX_MU_IER_REG,0x5);    
    // set baud rate
	PUT32(AUX_MU_IIR_REG,0xC6);    
	PUT32(AUX_MU_BAUD_REG,270);
    
    // Set GPIO pin 14 to TX and 15 to RX modes
    ra = GET32(GPFSEL1);
	ra &= ~(7<<12);    // Pin 14
	ra |= 2<<12;       // Func5
	ra &= ~(7<<15);    // Pin 15
	ra |= 2<<15;	   // Func5
	PUT32(GPFSEL1,ra);
    
    // Disable Pull-up/down for pins 14 and 15
    PUT32(GPPUD, 0);
    int i;
    for (i = 0; i < 150; i++) { }
	PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for (i = 0; i < 150; i++) { }
    PUT32(GPPUD, 0);
    for (i = 0; i < 150; i++) { }
	PUT32(GPPUDCLK0,0);
       
    // Enable tx and rx
	PUT32(AUX_MU_CNTL_REG, 3);
    
    // Enable AUX interrupts
	PUT32(Enable_IRQs_1, 1<<29);    
}


int uart_can_receive() {
    unsigned int a = GET32(AUX_MU_IIR_REG); // if bit 1 not set, then no transmit interrupts are pending
    return (a & 1) != 1;
}

int uart_can_send() {
    return (GET32(AUX_MU_LSR_REG) & 1<<7); // bit 7 set means can buffer next char 
}

int uart_receive() {
    return GET32(AUX_MU_IO_REG);
}

void uart_send(char c) {
    while(1) {
        if (uart_can_send()) break;
    }
    PUT32(AUX_MU_IO_REG, c);
}
