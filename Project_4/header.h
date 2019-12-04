// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H


#include "disk.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>     // unit32_t = unsigned int // 4 bytes
#include <sys/types.h>
#include <string.h> 
#include <unistd.h>

#define FILENAME_LENGTH 19 // 15(name) + 1(.) + 3(ext)
#define EXTENSION_LENGTH 3

#define NUM_DATA_BLOCKS DISK_BLOCKS/2

typedef struct Dir_Entry{
    char name[FILENAME_LENGTH]; /*15 bytes*/
    uint16_t start_block; /*start block # in FAT*/
    uint16_t size; /*in bytes*/
    uint16_t file_type; //file = 1, directory = 0
    uint16_t occupied;
    // parent dir
} Dir_Entry;

// description of disk layout
// total 14 BYTES
typedef struct superblock {
    uint16_t blocksize;  // 2 bytes = uint16_t
    uint16_t bps; /* 2 bytes ,bytes per sector, 512 bytes */
    uint16_t spb; /*2 bytes, sector per cluster, 8 sector/cluster */
    uint16_t fat_start;
    uint16_t fat_length;      // track end of FAT
    uint16_t DE_start;
    uint16_t DE_length;
    uint16_t DataRegion_start;
    uint16_t max_num_files;
} superblock;

extern superblock * disk_superblock;
extern Dir_Entry * root_entry;
extern uint16_t FAT[DISK_BLOCKS];
/*
A value = 0, indicating that the block is free.
A value > 0, meaning that the block corresponding to the
value is the next block in a file.
A value = -1, indicating that the indexed block is the last block in a
sequence.
*/

int make_fs(char *disk_name);
int mount_fs(char *disk_name);
int umount_fs(char *disk_name);

int write_fat(uint16_t * FAT);
int read_fat();
int create_FAT_entry();

void read_dirent(int index, Dir_Entry* de, superblock* disk_v);
void update_dirent(int index, Dir_Entry* de, superblock* disk_v);

int fs_create(char *name);

#endif