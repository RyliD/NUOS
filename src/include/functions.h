#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Functions from the .s files
extern void _disable_interrupts();
extern void _enable_interrupts();

extern unsigned int _get_stack_pointer();

extern unsigned int _get32(unsigned int);
extern void _put32(unsigned int, unsigned int);

#endif