// Khai Nguyen
// Filename: main.c
// Usage: build main program

#include "header.h"

// global variables 
superblock * disk_superblock;
uint16_t FAT[DISK_BLOCKS]; // covers all diskblocks
Dir_Entry * root_entry; // pointer to an array of dirents
Dir_Entry * origin_root;
int total_fd;

int main (int argc, char *argv[]){
    // if (make_disk("Test_Disk") < 0){
    //     printf("Error creating disk\n");
    //     return -1;
    // }
    int total_fd = 0;

    if (make_fs("Test_Disk") < 0){
        printf("Filesys cant be made\n");
        return -1;
    }

    printf("Filesys made\n");



    if (mount_fs("Test_Disk") < 0){
        printf("Filesys cant be mounted\n");
        return -1;
    }
    origin_root = root_entry; // keep origin root
    printf("Filesys mounted\n");

    if (fs_create("file1.txt") < 0){
        printf("Fiel cant be created\n");
        return -1;
    }
    printf("file1_created\n");

    int fd1 = fs_open("file1.txt");
    // dup2(,fd1); // creating another dup
    
    printf("file1_opened with fd1 = %d\n", fd1);
    // try writing to fd1
    // ******The function assumes that the buffer buf holds at least nbyte bytes****** 
    char buf [15] = "Sample string"; 
    // printf("Buff len is %d\n", strlen(buf));
    fs_write(fd1, buf, strlen(buf) + 1);

    if (fs_close(fd1) < 0){
        printf("Fiel cant be closed\n");
        return -1;
    }
    printf("file1_closed\n");



    if (umount_fs("Test_Disk") < 0){
        printf("FILEsys cant be umounted\n");
        return -1;
    }
    printf("FS umounted\n");

    return 0;
}