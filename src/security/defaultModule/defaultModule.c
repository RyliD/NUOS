#include "security/security.h"
#include "defaultModule/defaultModule.h"


int init_default_module()
{
    return register_security(&default_ops);
}

//Below are all hooks that will be used when this security module is loaded
int file_open(struct file *file, const struct credentials *cred)
{
    //TODO: Check creds
    return 0;
}

int file_close(struct file *file, const struct credentials *cred)
{
    //TODO: Check creds
    return 0;
}

static struct security_operations default_ops {
    .file_open = file_open,
    .file_close = file_close,
};