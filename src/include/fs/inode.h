#include <include/fs.h> // for super_block and such
struct inode *inode_get(struct super_block *, unsigned long inode_num);
int write_inode(struct inode *, unsigned long);
