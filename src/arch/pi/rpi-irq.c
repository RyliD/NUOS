#include "irq.h"
#include "rpi-base.h"

#define RPI_INTERRUPT_CONTROLLER_BASE   0x3F00B200      // RPI_PERIPHERAL_BASE + 0xB200

struct rpi_interrupt_controller {
    unsigned int IRQ_basic_pending;     // 0x3F00B200
    unsigned int IRQ_pending_1;         // 0x3F00B204
    unsigned int IRQ_pending_2;         // 0x3F00B208
    unsigned int FIQ_control;           // 0x3F00B20C
    unsigned int Enable_IRQs_1;         // 0x3F00B210
    unsigned int Enable_IRQs_2;         // 0x3F00B214
    unsigned int Enable_Basic_IRQs;     // 0x3F00B218
    unsigned int Disable_IRQs_1;        // 0x3F00B21C
    unsigned int Disable_IRQs_2;        // 0x3F00B220
    unsigned int Disable_Basic_IRQs;    // 0x3F00B22C
};

#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)
#define RPI_BASIC_PENDING_1             (1 << 8)
#define RPI_BASIC_PENDING_2             (1 << 9)
#define RPI_BASIC_GPU_IRQ_7             (1 << 10)
#define RPI_BASIC_GPU_IRQ_9             (1 << 11)
#define RPI_BASIC_GPU_IRQ_10            (1 << 12)
#define RPI_BASIC_GPU_IRQ_18            (1 << 13)
#define RPI_BASIC_GPU_IRQ_19            (1 << 14)
#define RPI_BASIC_GPU_IRQ_53            (1 << 15)
#define RPI_BASIC_GPU_IRQ_54            (1 << 16)
#define RPI_BASIC_GPU_IRQ_55            (1 << 17)
#define RPI_BASIC_GPU_IRQ_56            (1 << 18)
#define RPI_BASIC_GPU_IRQ_57            (1 << 19)
#define RPI_BASIC_GPU_IRQ_62            (1 << 20)

#define RPI_IRQ_1_AUX_IRQ               (1 << 29)

#define RPI_IRQ_2_I2C_SPI_SLV_IRQ       (1 << 11)
#define RPI_IRQ_2_PWA0_IRQ              (1 << 13)
#define RPI_IRQ_2_PWA1_IRQ              (1 << 14)
#define RPI_IRQ_2_SMI_IRQ               (1 << 16)
#define RPI_IRQ_2_GPIO0_IRQ             (1 << 17)
#define RPI_IRQ_2_GPIO1_IRQ             (1 << 18)
#define RPI_IRQ_2_GPIO2_IRQ             (1 << 19)
#define RPI_IRQ_2_GPIO3_IRQ             (1 << 20)
#define RPI_IRQ_2_I2C_IRQ               (1 << 21)
#define RPI_IRQ_2_SPI_IRQ               (1 << 22)
#define RPI_IRQ_2_PCM_IRQ               (1 << 23)
#define RPI_IRQ_2_UART_IRQ              (1 << 25)

static volatile struct rpi_interrupt_controller * const interrupt_controller = 
    (volatile struct rpi_interrupt_controller*)RPI_INTERRUPT_CONTROLLER_BASE;

interrupt_handler_t interrupt_vector[32 + 32 + 8]; // this is defined in the device specific irq file because it depends on the number of irq lines

void init_irq_hw(void)
{
}

void irq_disable_hw(int line)
{
    if (line < 32)
    {
        interrupt_controller->Disable_IRQs_1 = (1 << line);
    }
    else if (line < 64)
    {
        interrupt_controller->Disable_IRQs_2 = (1 << (line - 32));
    }
    else 
    {
        interrupt_controller->Disable_Basic_IRQs = (1 << (line - 64));        
    }
}

void irq_enable_hw(int line)
{
    if (line < 32)
    {
        interrupt_controller->Enable_IRQs_1 = (1 << line);
    }
    else if (line < 64)
    {
        interrupt_controller->Enable_IRQs_2 = (1 << (line - 32));
    }
    else 
    {
        interrupt_controller->Enable_Basic_IRQs = (1 << (line - 64));        
    }
}

void c_irq_handler_hw(void)
{
    unsigned int irq1 = interrupt_controller->IRQ_pending_1;
    unsigned int irq2 = interrupt_controller->IRQ_pending_2;
    unsigned int irqb = interrupt_controller->IRQ_basic_pending;
    
    unsigned int i, j;
    for (i = 0; i < 32; i++) {
        j = (1 << i);
        if ((j & irq1) != 0) 
            handle_interrupt(i);
        if ((j & irq2) != 0)
            handle_interrupt(i + 32);
        if ((j & irqb) != 0)
            handle_interrupt(i + 64);        
    }
}