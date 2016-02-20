#include "irq.h"

void init_irq(void)
{
    init_irq_hw();
}

void handle_interrupt(unsigned int line)
{    
    interrupt_handler_t handler = interrupt_vector[line];
    if (handler)
    {
        (*handler)();
    }
    // error
}

void disable_interrupt_handler(int line)
{
    interrupt_vector[line] = 0;
    irq_disable_hw(line);
}

void register_interrupt_handler(int line, interrupt_handler_t handler)
{
    interrupt_vector[line] = handler;
    irq_enable_hw(line);
}

void c_irq_handler(void)
{
    c_irq_handler_hw();
}
