#ifndef IRQ_H
#define IRQ_H

typedef void (*interrupt_handler)(void);

void register_interrupt_handler(int line, interrupt_handler handler);

#endif