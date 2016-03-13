#include <include/fs/ops.h>

void write_super(struct super_block *) {
    // TODO: expand definition
}

bool check_inode_bitmap(struct super_block *) {
    // consistency of existence between the table and the bit map
    return false;
}

void free_blocks(struct inode *inode, unsigned long block,
                                      unsigned long count) {
    // TODO: traverse the inode tree to that data block, for count.
}
