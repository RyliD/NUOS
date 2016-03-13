// operations to be done on the file system.
#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) // thanks stackoverflow

/* PERMISSIONS */
enum {
    PERMISSION_READ   = 1;
    PERMISSION_WRITE  = 2;
    PERMISSION_EXEC   = 4; // maintain 777 from traditional Linux

    /* These probably need to be somewhere else, or be checked when
    their predecessors are referenced. */
    PERMISSION_OPEN   = 8;
    PERMISSION_CLOSE  = 16;
}

/* ALL of the filesystem operations all going in here. Most of the Linux
source is so large because of the VFS abstraction. We are NOt adhering to that.
As such, there should be much less code. */
void write_super(struct super_block *); // TODO: expand definition
void check_inode_bitmap(struct super_block *); // error out if fails
