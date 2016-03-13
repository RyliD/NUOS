/**
This is a trim version of <Linux 4.4/src/fs/ext2/inode.c>, to match
the functionality needed by NUOS. We know that Linux is super generic
and NUOS will not be.
*/
#include <include/fs.h>
#include <include/fs/inode.h>

// take the block, find your inode
struct inode *inode_get(struct super_block *sb, unsigned long inode_num) {
    return (struct inode);
}

// Signature needs critique
int write_inode(struct inode *node, unsigned long data) {
  return -1; // error. TODO: long values to data blocks.
}
