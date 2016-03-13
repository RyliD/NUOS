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
bool check_inode_bitmap(struct super_block *); // error out if fails

/** from Linux/fs/ext2/balloc.c:
Takes an inode the starting block and the number of blocks to remove.
*/
void free_blocks(struct inode *, unsigned long, unsigned long);

// Check any given flags against the option, return whether the desired
// permission bits were found. A.k.a. "allowed"
static bool check_permissions(unsigned short current_flags,
                              unsigned short desired) {
    /* 0 values of basic types map to false, others map to true. */
    return current_flags & desired; // If bool is inoptimal, this will change.
}
