
#include "../include/notmain.h"
#include "../include/init.h"

void notmain(void)
{
    // here we can init the bss if we want to 
    
    // other init stuff
    init_memory();
    init_processor();
    init_uart();
    
    // kernel
}