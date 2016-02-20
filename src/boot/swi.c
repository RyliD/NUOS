#include "swi.h"

void c_swi_handler(unsigned number, unsigned *regs)
{
    register unsigned int addr;
    register unsigned int swi_no;
    
    asm volatile("mov %[addr], lr" : [addr] "=r" (addr) );    
    addr -= 4;    
    swi_no = *((unsigned int *)addr) & 0x00ffffff;
    
    switch(swi_no){
        case 0:
            break;
        default:
            break;
    }
}
