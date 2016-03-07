int init_default_module();

//Below are all hooks that will be used when this security module is loaded
int file_open(struct file *file, const struct credentials *cred);
int file_close(struct file *file, const struct credentials *cred);