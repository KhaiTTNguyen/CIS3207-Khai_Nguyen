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


typedef struct Dir_Entry{
    char name[FILENAME_LENGTH]; /*15 bytes*/
    char ext[EXTENSION_LENGTH]; /*extension of file, 3 bytes*/
    
    int modified_time; /* Hours*10000 + minute*100 + second*/
    int modified_date; /*Year*100 + Month*10 + Day */
    uint16_t start_cluster; /*start in FAT*/
    uint32_t size; /*in bytes*/
    unsigned int offset; // current offset
    
    
} Dir_Entry;

#endif