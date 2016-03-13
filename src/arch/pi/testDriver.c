 #include "functions.h"
 #include "init.h"
 #include "irq.h"
 #include "rpi-gpio.h"
 #include "types.h"


/*
* Corey stuff
*/

#define RPI_UART_BASE   0x3F201000      // RPI_PERIPHERAL_BASE + 0x201000

struct rpi_uart {
	unsigned int UART_DR;               // 0x3F201000   // Data register
	unsigned int UART_RSRECR;           // 0x3F201004   // 
	unsigned int NONE1;                 // 0x3F201008
	unsigned int NONE2;                 // 0x3F20100C
	unsigned int NONE3;                 // 0x3F201010
	unsigned int NONE4;                 // 0x3F201014
	unsigned int UART_FR;               // 0x3F201018   // Flag register
	unsigned int NONE5;                 // 0x3F20101C
	unsigned int UART_ILPR;             // 0x3F201020   // not in use   
	unsigned int UART_IBRD;             // 0x3F201024   // Integer Baud rate divisor
	unsigned int UART_FBRD;             // 0x3F201028   // Fractional Baud rate divisor
	unsigned int UART_LCRH;             // 0x3F20102C   // Line Control Register
	unsigned int UART_CR;               // 0x3F201030   // Control Register
	unsigned int UART_IFLS;             // 0x3F201034   // Interrupt FIFO Level Select Register
	unsigned int UART_IMSC;             // 0x3F201038   // Interrupt Mask set clear register
	unsigned int UART_RIS;              // 0x3F20103C   // Raw interrupt status register
	unsigned int UART_MIS;              // 0x3F201040   // Masked interrupt status register
	unsigned int UART_ICR;              // 0x3F201044   // Interrupt clear register
	unsigned int UART_DMACR;            // 0x3F201048   // DMA control register
};

static volatile struct rpi_uart * const uart =
(volatile struct rpi_uart*)RPI_UART_BASE;

void testDriver_irq_handler(void)
{
	debug_write_string("1", 1);

		static int lit = 0;
		disable_interrupt_handler(57);
		//uart->UART_ICR = 1;

    if( lit ) {
        //_put32(GPCLR1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F20002C, (1 << 15));
        lit = 0;
        //debug_write_string("off ", 4);
    } else {
        //_put32(GPSET1, RPI_GPIO_FSEL0_05_OUTPUT);
        _put32(0x3F200020, (1 << 15));
        lit = 1;
        //debug_write_string("on ", 3);
    }
		register_interrupt_handler(57, (interrupt_handler_t)testDriver_irq_handler);
}

void init_testDriver(void)
{
	debug_write_string("+", 1);

    register_interrupt_handler(57, (interrupt_handler_t)testDriver_irq_handler);
	unsigned int ra;

		/* Disable the UART by zeroing the "control register".  */
		uart->UART_CR = 0;

		// Set GPIO pins 14 and 15 to alt function 0
		ra = _get32(GPFSEL1);
	ra &= ~(7 << 12);  // Mask Pin 14
	ra |= (4 << 12);   // Func0
	ra &= ~(7 << 15);  // Mask Pin 15
	ra |= (4 << 15);   // Func0
	_put32(GPFSEL1,ra);

		// Disable Pull-up/down for pins 14 and 15
		int i;
		_put32(GPPUD, 0);
		for (i = 0; i < 150; i++) { }
	_put32(GPPUDCLK0, (1 << 14) | (1 << 15));
		for (i = 0; i < 150; i++) { }
	_put32(GPPUDCLK0, 0);

		/* Poll the "flags register" to wait for the UART to stop transmitting or
		 * receiving. */
		while (uart->UART_FR &(1<<3)) { }

		/* Flush the transmit FIFO by marking FIFOs as disabled in the "line control
		 * register". */
		uart->UART_LCRH &= ~(1<<4);

		/* Clear pending interrupts by writing to the "interrupt clear" register. */
		uart->UART_ICR = (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<1);

		/* Set the UART's baud rate.  This is done by writing to separate "integer
		 * baud rate divisor" and "fractional baud rate divisor" registers.  */
		uart->UART_IBRD = 0x1;
		uart->UART_FBRD = 0x28;

		/* Write the appropriate values to the UART's "line control register" to set
		 * it to an 8 bit word length, with parity bit and FIFOs disabled.  */
		uart->UART_LCRH = (3<<5);

		/* Allow the UART to generate interrupts only when receiving or
		 * transmitting.  */
		//uart->UART_IMSC = (1<<5) | (1<<4);
		//uart->UART_IMSC = (1<<4);
		uart->UART_IMSC = (1 << 4);

		/* Enable the UART, with both the receive and transmit functionality, by
		 * writing to its control register.  */
		uart->UART_CR = (1<<9) | (1<<8) | (1<<0);

}
