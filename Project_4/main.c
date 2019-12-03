// Khai Nguyen
// Filename: main.c
// Usage: build main program

#include "header.h"

// global variables 
superblock * disk_superblock;
uint16_t FAT[DISK_BLOCKS]; // covers all diskblocks
Dir_Entry * root_entry; // pointer to an array of dirents


int main (int argc, char *argv[]){
    // if (make_disk("Test_Disk") < 0){
    //     printf("Error creating disk\n");
    //     return -1;
    // }

    if (make_fs("Test_Disk") < 0){
        printf("Filesys cant be made\n");
    }

    printf("Filesys made\n");



    if (mount_fs("Test_Disk") < 0){
        printf("Filesys cant be mounted\n");
    }

    printf("Filesys mounted\n");
    return 0;
}