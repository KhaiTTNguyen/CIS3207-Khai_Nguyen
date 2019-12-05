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
#include <errno.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FILENAME_LENGTH 19 // 15(name) + 1(.) + 3(ext)
#define EXTENSION_LENGTH 3

#define NUM_DATA_BLOCKS DISK_BLOCKS/2
#define MAX_NUM_FILES 256

typedef struct Dir_Entry{
    char name[FILENAME_LENGTH]; /*15 bytes*/
    uint16_t start_block; /*start block # in FAT*/
    uint16_t size; /*in bytes*/
    uint16_t file_type; //file = 1, directory = 0
    uint16_t valid;
    unsigned int first_block;
    unsigned int size;
    uid_t user;
    gid_t group;
    mode_t mode;
    struct timespec access_time;
    struct timespec modify_time;
    struct timespec create_time;
} Dir_Entry;

// description of disk layout
// total 14 BYTES
typedef struct superblock {
    // a magic number of identity of your disk
    int magic;

    // description of disk layout
    int blocksize;
    int de_start;
    int de_length;
    int fat_start;
    int fat_length;
    int db_start;
    int valid_files;

    // meta data for root dir
    uid_t user;
    gid_t group;
    mode_t mode;
    struct timespec access_time;
    struct timespec modify_time;
    struct timespec create_time;
} superblock;

typedef struct fatent_s {
  unsigned int used:1;
  unsigned int eof:1;
  unsigned int next:30;
} fatent;



extern superblock * disk_superblock;
extern Dir_Entry * root_entry;
extern uint16_t FAT[DISK_BLOCKS];
extern int total_fd;
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

int fs_open(char *name);

int write_fat(uint16_t * FAT);
int read_fat();
int create_FAT_entry();

void read_dirent(int index, Dir_Entry* de, superblock* disk_v);
void update_dirent(int index, Dir_Entry* de, superblock* disk_v);

int fs_create(char *name);

#endif