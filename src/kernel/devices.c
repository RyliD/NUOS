#include "init.h"
#include "uart_device.c"
#include "mmc_device.c"

typedef struct device
{
	int id;
	int (*open)();
	int (*read)();
	int (*write)();
	int (*close)();
};

void init_devices() {
	//create the device table and register devices

	//currently we want to support 2 devices, uart and sd card
	struct device devices[2];

	//uart entry
	devices[0] = uart;

	//flash card (mmc) entry
	device[1] = mmc;
}

struct device uart = {
		.open = null,
		.read = uart_read(),
		.write = uart_write(),
		.close = null
};

struct device mmc = {
		.open = mmc_open(),
		.read = mmc_read(),
		.write = mmc_write(),
		.close = mmc_close()
};