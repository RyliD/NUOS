#ifndef DEVICE_H
#define DEVICE_H

typedef struct device
{
    int id;
    int (*open)();
    int (*read)();
    int (*write)();
    int (*close)();
};

#endif