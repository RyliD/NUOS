#ifndef DEVICE_H
#define DEVICE_H

typedef struct
{
    int (*open)();
    int (*read)();
    int (*write)();
    int (*close)();
} device;

#endif