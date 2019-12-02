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




typedef struct Dir_Entry{
    char name[FILENAME_LENGTH]; /*15 bytes*/
    char ext[EXTENSION_LENGTH]; /*extension of file, 3 bytes*/

    uint16_t start_block; /*start block # in FAT*/
    uint16_t size; /*in bytes*/
    uint16_t offset; // current offset - due to written/read last time
    
    uint16_t file_type; //is it file or directory
    // parent dir
} Dir_Entry;



/*
A zero, indicating that the block is free.
A value > 0, meaning that the block corresponding to the
value is the next block in a file.
A -1, indicating that the indexed block is the last block in a
sequence.
*/
uint16_t FAT[NUM_DATA_BLOCKS];

// description of disk layout
// total 
typedef struct superblock {
    uint16_t blocksize;  // 2 bytes = uint16_t
    uint16_t bps; /* 2 bytes ,bytes per sector, 512 bytes */
    uint8_t spb; /*1 byte, sector per cluster, 8 sector/cluster */
    uint16_t fat_start;
    uint16_t fat_length;      // track end of FAT
    uint16_t DE_start;
    int DataRegion_start;
} superblock;




#endif