#include <include/fs.h>

struct inode {
    int id_num; // the "inode number"
    struct block_group *group;
    struct super_block *owner_sb;

    struct timespec last_access_time;
    struct timespec last_modified_time;
    struct timespec created_time;
}

struct inode_map {
    int inodes_in_use;
    // TODO: other properties to store here
}

// encapsulation of the time
struct timespec {
    uint millis;
    ulong nanons;
}

// defines the ext2-like super_block to be used in our implemantation
// NOTE: all sizes are in bytes
struct super_block {
    // definition things here.
    ulong inode_count; // total # inodes in the system (used and unused)
    ulong block_count; // total # of blocks in the system (used and unused)
    ulong free_block_count;
    ulong free_inode_count;
    /* accounts for the offset for the super_block (on disk), this is the
    first data block. */

    // If uint
    uint first_data_block; // int because it's simply a small value
    uint block_size; // size of the blocks that are found in block groups
    uint blocks_per_group;
    uint inodes_per_group;
    const int magic = 0x3F53; // because Linux says so. EXT2 marker
    ulong lastcheck_timestamp; // last Unix time that 'fschk' was ran
    int first_inode_id; /* the inode number of this block's first inode.
    our implementation should only have one super_block, but just in case. */
    int inode_size; /* subject to change, the total size of an inode */
    int block_group_id;

    ulong inode_bitmap;

    // TODO:
    char *volume_name;
    // uuid
}

struct path {
    int permission_flags; // call ops/check_permissions with this field
    char *name;
}

struct directory_entry {
      // Every path should know where it came from.
      struct directory_entry *parent_dir;

      /* a transformation function that should be optimized for ARM
      this will be define in one location and assigned to each creation
      also, cheaper than including everything all the time. */
      char *(*fully_qualified_name) (*struct path);
}

struct block_group {
    // reference to the system's super_block
    struct super_block *sb;
    int inode_table_index; // To be assigned on init.
    // TODO: make inode table (?struct, pointer/array, other?)
    long *first_block; // the address for the first data block of this group.
}
