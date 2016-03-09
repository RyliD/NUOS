#include <include/fs.h>

struct inode{
    int id_num; // the "inode number"
    struct block_group *group;
}

struct inode_map {
    int inodes_in_use;
    // TODO: other properties to store here
}

// defines the ext2-like super_block to be used in our implemantation
struct super_block {
    // definition things here.
    long inode_count; // total # inodes in the system (used and unused)
    long block_count; // total # of blocks in the system (used and unused)

    /* accounting for the offset for the super_block (on disk), this is the
    first data block.
    */
    int first_data_block;
    int block_size; // size of the blocks that are fonud in block groups
    const int magic = 0x3F53; // because Linux says so.
    long lastcheck_timestamp; // last Unix time that 'fschk' was ran
    // TODO:
    // string volume name
    // uuid
}

struct path {

    char *name;

    // Every path should know where it came from.
    struct directory_entry *parent_dir;

    // a transformation function that should be optimized for ARM
    // this will be define in one location and assigned to each creation
    // also, cheaper than including everything all the time.
    char *(*fully_qualified_name) (*struct path);
}

struct directory_entry {
    // Every path should know where it came from.
    struct directory_entry *parent_dir;

}

struct block_group {
    // reference to the system's super_block
    struct super_block *sb;
    int inode_table_index; // To be assigned on init.
    // TODO: make inode table (?struct, pointer/array, other?)
    long *first_block; // the block address for the first Data Block
}
