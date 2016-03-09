#include "debug-write.h"

int uart_write() {
    debug_write_string("hi", 2);
    return 0;
}

int uart_read() {
    return 0;
}