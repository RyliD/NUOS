#ifndef IRQ_H
#define IRQ_H

typedef int (*interrupt_handler_t)(void);
extern interrupt_handler_t interrupt_vector[];

void c_irq_handler();
void disable_interrupt_handler(int line);
void register_interrupt_handler(int line, interrupt_handler_t handler);

// Hardware specific functions
void c_irq_handler_hw();
void irq_disable_hw(int line);
void irq_enable_hw(int line);
void init_irq_hw();

#endif