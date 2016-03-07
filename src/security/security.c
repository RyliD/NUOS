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
<<<<<<< HEAD
    if (security_ops == null)
=======
    if (security_ops != null)
>>>>>>> 961eacf5e11e14eb314301e4d0b28492e7bc05c6
    {
        security_ops = ops;
        return 0;
    }
    return ERROR;
}

<<<<<<< HEAD
int unregister_security(struct security_operations *ops)
{
    security_ops = null;
}

int security_file_open(struct file *file, const struct credentials *cred) 
{
    int ret;
    if (security_ops != null) 
    {
        ret = security_ops->file_open(file, cred);
        if (ret)
            return ret;
        //Notify?
        
        //TODO: Unnecessary when notify is implemented
        return ret;
    }
    return ERROR;
=======
int security_file_open(struct file *file, const struct credentials *cred) 
{
    int ret;
    ret = security_ops->file_open(file, cred);
    if (ret)
        return ret;
    //Notify?
    
    //TODO: Unnecessary when notify is implemented
    return ret;
>>>>>>> 961eacf5e11e14eb314301e4d0b28492e7bc05c6
}

int security_file_close(struct file *file, const struct credentials *cred) 
{
    int ret;
<<<<<<< HEAD
    if (security_ops != null) 
    {
        ret = security_ops->file_close(file, cred);
        if (ret)
            return ret;
        //Notify?
        
        //TODO: Unnecessary when notify is implemented
        return ret;
    }
    return ERROR;
=======
    ret = security_ops->file_close(file, cred);
    if (ret)
        return ret;
    //Notify?
    
    //TODO: Unnecessary when notify is implemented
    return ret;
>>>>>>> 961eacf5e11e14eb314301e4d0b28492e7bc05c6
}