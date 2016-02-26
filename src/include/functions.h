#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Functions from the .s files
extern void _disable_interrupts();
extern void _enable_interrupts();

extern unsigned int _get_stack_pointer();
extern void _set_stack_pointer(unsigned int);
extern unsigned int _get_frame_pointer();
extern void _set_frame_pointer(unsigned int);

extern unsigned int _get32(unsigned int);
extern void _put32(unsigned int, unsigned int);


//Saves all registers to stack and returns a pointer
//Values must be copied and then stack cleaned up
extern unsigned int* _get_all_registers();
extern void _clean_up_for_get_all_registers();

#endif