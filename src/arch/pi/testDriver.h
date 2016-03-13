#ifndef testDriver_H
#define testDriver_H

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

void testDriver_irq_handler(void);
void init_testDriver(void);


#endif
