#include "irq.h"
#include "debug-write.h"
#include "functions.h"
#include "processor.h"

void init_irq(void)
{
    init_irq_hw();
	debug_write_hex(_get_stack_pointer());
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

void c_irq_handler()
{
	// int i;
	// debug_write_char('a');
	// debug_write_hex(regs);
	// for(i = 0; i < 14; i++) {
		// debug_write_hex(regs + (i));
		// debug_write_string(" : ", 3);
		// debug_write_hex(regs[i]);
		// debug_write_string(" : ", 3);
		// debug_write_hex(&(regs[i]));
		// debug_write_string("\n", 1);
	// }
	
    // debug_write_hex(_get_stack_pointer());
    c_irq_handler_hw();

}
