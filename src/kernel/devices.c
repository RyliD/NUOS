typedef struct device
{
	int id;
	int (*open)();
	int (*read)();
	int (*write)();
	int (*close)();
};