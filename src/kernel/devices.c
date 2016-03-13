#include "init.h"
#include "device.h"
#include "debug-write.h"
#include "types.h"

/**
 * Function Implementations
 */

//UART Functions
int uart_write() {
	debug_write_string("xyzabc", 12);
	return 0;
}

int uart_read() {
	return 0;
}

//MMC Functions
int mmc_write() {
	return 0;
}

int mmc_read() {
	return 0;
}

int mmc_open() {
	return 0;
}

int mmc_close() {
	return 0;
}

int uart_init() {

}


void init_devices() {
	//create the device table and register devices

	//currently we want to support 2 devices, uart and sd card
	device devices[2];

	//UART entry
	devices[0] = (device) {
			null,
			&uart_read,
			&uart_write,
			null
	};

	uart_init();
	//init the uart device

	//flash card (mmc) entry
	devices[1] = (device) {
			&mmc_open,
			&mmc_read,
			&mmc_write,
			&mmc_close
	};

	devices[0].write();
}

