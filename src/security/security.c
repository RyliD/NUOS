#include "security.h"
#include "defaultModule/defaultModule.h"

static struct security_operations *security_ops = null;
static const int ERROR = 1;

int security_init()
{
    init_default_module();
}

int register_security(struct security_operations *ops) 
{
    if (security_ops != null)
    {
        security_ops = ops;
        return 0;
    }
    return ERROR;
}

int security_file_open(struct file *file, const struct credentials *cred) 
{
    int ret;
    ret = security_ops->file_open(file, cred);
    if (ret)
        return ret;
    //Notify?
    
    //TODO: Unnecessary when notify is implemented
    return ret;
}

int security_file_close(struct file *file, const struct credentials *cred) 
{
    int ret;
    ret = security_ops->file_close(file, cred);
    if (ret)
        return ret;
    //Notify?
    
    //TODO: Unnecessary when notify is implemented
    return ret;
}