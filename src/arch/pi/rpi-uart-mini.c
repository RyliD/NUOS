#include "functions.h"
#include "init.h"
#include "irq.h"
#include "rpi-gpio.h"
#include "types.h"

#define RPI_AUX_PERIPHERALS_BASE   0x3F215000      // RPI_PERIPHERAL_BASE + 0x215000

struct rpi_aux_peripherals {
    unsigned int AUX_IRQ;               // 0x3F215000   // Auxiliary Interrupt Status
    unsigned int AUX_ENABLES;           // 0x3F215004   // Auxiliary enables
    unsigned int NONE1;                 // 0x3F215008
    unsigned int NONE2;                 // 0x3F21500C
    unsigned int NONE3;                 // 0x3F215010
    unsigned int NONE4;                 // 0x3F215014
    unsigned int NONE5;                 // 0x3F215018
    unsigned int NONE6;                 // 0x3F21501C
    unsigned int NONE7;                 // 0x3F215020
    unsigned int NONE8;                 // 0x3F215024
    unsigned int NONE9;                 // 0x3F215028
    unsigned int NONE10;                // 0x3F21502C
    unsigned int NONE11;                // 0x3F215030
    unsigned int NONE12;                // 0x3F215034
    unsigned int NONE13;                // 0x3F215038
    unsigned int NONE14;                // 0x3F21503C
    unsigned int AUX_MU_IO_REG;         // 0x3F215040   // Mini Uart I/O Data
    unsigned int AUX_MU_IER_REG;        // 0x3F215044   // Mini Uart Interrupt Enable
    unsigned int AUX_MU_IIR_REG;        // 0x3F215048   // Mini Uart Interrupt Identify
    unsigned int AUX_MU_LCR_REG;        // 0x3F21504C   // Mini Uart Line Control
    unsigned int AUX_MU_MCR_REG;        // 0x3F215050   // Mini Uart Modem Control
    unsigned int AUX_MU_LSR_REG;        // 0x3F215054   // Mini Uart Line Status
    unsigned int AUX_MU_MSR_REG;        // 0x3F215058   // Mini Uart Modem Status
    unsigned int AUX_MU_SCRATCH;        // 0x3F21505C   // Mini Uart Scratch
    unsigned int AUX_MU_CNTL_REG;       // 0x3F215060   // Mini Uart Extra Control
    unsigned int AUX_MU_STAT_REG;       // 0x3F215064   // Mini Uart Extra Status
    unsigned int AUX_MU_BAUD_REG;       // 0x3F215068   // Mini Uart Baudrate
};

static volatile struct rpi_aux_peripherals * const aux_peripherals = 
    (volatile struct rpi_aux_peripherals*)RPI_AUX_PERIPHERALS_BASE;

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
	//_put32(AUX_ENABLES, 1);
    aux_peripherals->AUX_ENABLES = (1 << 0);
    // Clear FIFO interrupts
	//_put32(AUX_MU_IER_REG, 0);
    aux_peripherals->AUX_MU_IER_REG = 0;
    // Disable Extra control functions
	//_put32(AUX_MU_CNTL_REG, 0);
    aux_peripherals->AUX_MU_CNTL_REG = 0;
    // Set Uart to 8-bit mode
	//_put32(AUX_MU_LCR_REG, 1);
    aux_peripherals->AUX_MU_LCR_REG = 1;
    // nothing??
	//_put32(AUX_MU_MCR_REG, 0);
    aux_peripherals->AUX_MU_MCR_REG = 0;
    // interrupt fires on holding valid byte
	//_put32(AUX_MU_IER_REG,0x5);
    aux_peripherals->AUX_MU_IER_REG = 0x5;
    // set baud rate
	//_put32(AUX_MU_IIR_REG,0xC6);    
	//_put32(AUX_MU_BAUD_REG,270);
    aux_peripherals->AUX_MU_IIR_REG = 0xC6;
    aux_peripherals->AUX_MU_BAUD_REG = 270;
    
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
	//_put32(AUX_MU_CNTL_REG, 3);
    aux_peripherals->AUX_MU_CNTL_REG = (1 << 1) | (1 << 0);
    
    // Enable AUX interrupts
	//_put32(Enable_IRQs_1, 1<<29);    
	//_put32(0x3F00B210, 1<<29);    
    register_interrupt_handler(29, (interrupt_handler_t)uartmini_irq_handler);
}


int uart_can_receive()
{
    // if bit 1 not set, then no transmit interrupts are pending
    //unsigned int a = _get32(AUX_MU_IIR_REG); 
    unsigned int a = aux_peripherals->AUX_MU_IIR_REG;
    return (a & 1) != 1;
}

int uart_can_send()
{
    // bit 7 set means can buffer next char
    //return (_get32(AUX_MU_LSR_REG) & 1<<7);  
    unsigned int a = aux_peripherals->AUX_MU_LSR_REG;
    return (a & (1 << 7));
}

int uart_receive()
{
    //return _get32(AUX_MU_IO_REG);
    return aux_peripherals->AUX_MU_IO_REG;
}

void uart_send(char c)
{
    while(1) {
        if (uart_can_send()) break;
    }
    //_put32(AUX_MU_IO_REG, c);
    aux_peripherals->AUX_MU_IO_REG = c;
}

void write_string(char* c, int len) 
{
    int i;
    for (i = 0; i < len; i++) {
        uart_send(c[i]);
    }
}
