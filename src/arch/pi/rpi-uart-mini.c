#include "functions.h"
#include "init.h"
#include "irq.h"
#include "rpi-gpio.h"
#include "types.h"

#define AUX_IRQ                 RPI_GPIO_BASE + 0x15000    // Auxiliary Interrupt Status       3
#define AUX_ENABLES             RPI_GPIO_BASE + 0x15004    // Auxiliary enables                3

#define AUX_MU_IO_REG           RPI_GPIO_BASE + 0x15040    // Mini Uart I/O Data               8
#define AUX_MU_IER_REG          RPI_GPIO_BASE + 0x15044    // Mini Uart Interrupt Enable       8
#define AUX_MU_IIR_REG          RPI_GPIO_BASE + 0x15048    // Mini Uart Interrupt Identify     8
#define AUX_MU_LCR_REG          RPI_GPIO_BASE + 0x1504C    // Mini Uart Line Control           8
#define AUX_MU_MCR_REG          RPI_GPIO_BASE + 0x15050    // Mini Uart Modem Control          8
#define AUX_MU_LSR_REG          RPI_GPIO_BASE + 0x15054    // Mini Uart Line Status            8
#define AUX_MU_MSR_REG          RPI_GPIO_BASE + 0x15058    // Mini Uart Modem Status           8
#define AUX_MU_SCRATCH          RPI_GPIO_BASE + 0x1505C    // Mini Uart Scratch                8
#define AUX_MU_CNTL_REG         RPI_GPIO_BASE + 0x15060    // Mini Uart Extra Control          8
#define AUX_MU_STAT_REG         RPI_GPIO_BASE + 0x15064    // Mini Uart Extra Status           32
#define AUX_MU_BAUD_REG         RPI_GPIO_BASE + 0x15068    // Mini Uart Baudrate               16

void uartmini_irq_handler() 
{    
}

void init_uart()
{
    unsigned int ra;
    
    // Disable AUX interrupts
    disable_interrupt_handler(29);
    //_put32(Disable_IRQs_1, 1<<29);
    //_put32(0x3F00B21C, 1<<29);
        
    // Enable Mini Uart    
	_put32(AUX_ENABLES, 1);    
    // Clear FIFO interrupts
	_put32(AUX_MU_IER_REG, 0);    
    // Disable Extra control functions
	_put32(AUX_MU_CNTL_REG, 0);    
    // Set Uart to 8-bit mode
	_put32(AUX_MU_LCR_REG, 1);    
    // nothing??
	_put32(AUX_MU_MCR_REG, 0);    
    // interrupt fires on holding valid byte
	_put32(AUX_MU_IER_REG,0x5);    
    // set baud rate
	_put32(AUX_MU_IIR_REG,0xC6);    
	_put32(AUX_MU_BAUD_REG,270);
    
    // Set GPIO pin 14 to TX and 15 to RX modes
    ra = _get32(GPFSEL1);
	ra &= ~(7<<12);    // Pin 14
	ra |= 2<<12;       // Func5
	ra &= ~(7<<15);    // Pin 15
	ra |= 2<<15;	   // Func5
	_put32(GPFSEL1,ra);
    
    // Disable Pull-up/down for pins 14 and 15
    _put32(GPPUD, 0);
    int i;
    for (i = 0; i < 150; i++) { }
	_put32(GPPUDCLK0,(1<<14)|(1<<15));
    for (i = 0; i < 150; i++) { }
    _put32(GPPUD, 0);
    for (i = 0; i < 150; i++) { }
	_put32(GPPUDCLK0,0);
       
    // Enable tx and rx
	_put32(AUX_MU_CNTL_REG, 3);
    
    // Enable AUX interrupts
	//_put32(Enable_IRQs_1, 1<<29);    
	//_put32(0x3F00B210, 1<<29);    
    register_interrupt_handler(29, (interrupt_handler_t)uartmini_irq_handler);
}


int uart_can_receive()
{
    unsigned int a = _get32(AUX_MU_IIR_REG); // if bit 1 not set, then no transmit interrupts are pending
    return (a & 1) != 1;
}

int uart_can_send()
{
    return (_get32(AUX_MU_LSR_REG) & 1<<7); // bit 7 set means can buffer next char 
}

int uart_receive()
{
    return _get32(AUX_MU_IO_REG);
}

void uart_send(char c)
{
    while(1) {
        if (uart_can_send()) break;
    }
    _put32(AUX_MU_IO_REG, c);
}

void write_string(char* c, int len) 
{
    int i;
    for (i = 0; i < len; i++) {
        uart_send(c[i]);
    }
}
