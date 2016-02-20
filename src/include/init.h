#ifndef INIT_H
#define INIT_H

void clear_BSS();

void init_irq();
void init_memory();
void init_processor();

void init_gpio();
void init_arm_timer();

void init_uart();

#endif