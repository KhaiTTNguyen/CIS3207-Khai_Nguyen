// Khai Nguyen
// Filename: main.c
// Usage: build main program

#include "header.h"

int main (int argc, char *argv[]){
    // if (make_disk("Test_Disk") < 0){
    //     printf("Error creating disk\n");
    //     return -1;
    // }

    if (open_disk("Test_Disk") < 0){
    printf("disk created\n");
    return 0;
}