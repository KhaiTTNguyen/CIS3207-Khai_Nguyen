

#include "header.h" // cotaining disk.h

int write_fat(uint16_t * FAT){
    char * fat_ptr = (char*) FAT; //--> same region of mem, slicing by cahr vs unint16_t
    printf("Assigned\n");
    int block_index = 1; /// where FAT starts
    int total_size = DISK_BLOCKS * sizeof(uint16_t);
    while (total_size > 0){
        block_write(block_index, fat_ptr);
        total_size -= BLOCK_SIZE;
        fat_ptr += BLOCK_SIZE;
        block_index++;
        printf("Size remaining %d\n", total_size);
    }
    printf("End write\n");
    return 0;
}


// read BLOCK --> fat_ptr (buff)


int read_fat(){
    char * fat_ptr = (char*) FAT; //--> same region of mem, slicing by char vs unint16_t
    int block_index = 1 ; /// where FAT starts
    int total = DISK_BLOCKS * sizeof(uint16_t); // in bytes
    while (total > 0){
        block_read(block_index, fat_ptr);
        total -= BLOCK_SIZE;
        fat_ptr += BLOCK_SIZE;
        block_index++;
    }
    return 0;
}

