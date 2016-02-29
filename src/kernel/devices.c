#include "init.h"

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
}