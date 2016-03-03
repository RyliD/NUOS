struct security_operations {
    int (*file_open) (struct file *file, const struct credentials *cred);
    int (*file_close) (struct file *file, const struct credentials *cred);
}

int security_init();
int register_security(struct security_operations *ops);

int security_file_open(struct file *file, const struct credentials *cred);
int security_file_close(struct file *file, const struct credentials *cred);