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
        return -1;
    }

    printf("Filesys made\n");



    if (mount_fs("Test_Disk") < 0){
        printf("Filesys cant be mounted\n");
        return -1;
    }

    printf("Filesys mounted\n");

    if (fs_create("file1.txt") < 0){
        printf("Fiel cant be created\n");
        return -1;
    }
    printf("file1_created\n");

    if (umount_fs("Test_Disk") < 0){
        printf("FILEsys cant be umounted\n");
        return -1;
    }
    printf("FS umounted\n");

    return 0;
}