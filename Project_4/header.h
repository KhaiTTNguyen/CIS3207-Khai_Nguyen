// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H


#include "disk.h"

#include <stdint.h>     // unit32_t = unsigned int // 4 bytes
#include <sys/types.h>

#define FILENAME_LENGTH 15 
#define EXTENSION_LENGTH 3

#define NUM_DATA_BLOCKS DISK_BLOCKS/2

// vcb structure
typedef struct superblock {
//   // a magic number of identity of your disk
//   int magic;

    // description of disk layout
    int blocksize;
    int de_start;
    int de_length;       // track end of dir_entries    
    int fat_start;
    int fat_length;      // track end of FAT
    int db_start;
    int valid_files;       // count num valid files
    // meta data for root dir
    //   uid_t user;
    //   gid_t group;
    //   mode_t mode;
    struct timespec access_time;
} superblock;


typedef struct Dir_Entry{
    char name[FILENAME_LENGTH]; /*15 bytes*/
    char ext[EXTENSION_LENGTH]; /*extension of file, 3 bytes*/
    
    int modified_time; /* Hours*10000 + minute*100 + second*/
    int modified_date; /*Year*100 + Month*10 + Day */
    unsigned int start_block; /*start in FAT*/
    uint32_t size; /*in bytes*/
    unsigned int offset; // current offset - due to written/read last time
    
    unsigned int valid; 
    // parent dir

} Dir_Entry;

/*
A zero, indicating that the block is free.
A value > 0, meaning that the block corresponding to the
value is the next block in a file.
A -1, indicating that the indexed block is the last block in a
sequence.
*/
int FAT[NUM_DATA_BLOCKS];



#endif