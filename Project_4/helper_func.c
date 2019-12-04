

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


/* takes an index for a directory entry 
and finds that directory entry on disk. 
 */
void read_dirent(int index, Dir_Entry* de, superblock* disk_v) {
  // Get the block number where we will find the directory entry,
  // there are num_dirents_per_block
  int num_dirents_per_block = BLOCK_SIZE / sizeof(Dir_Entry);
  int block_index = disk_v->DE_start + (index / num_dirents_per_block);

  // Get the block data
  char block_buffer[BLOCK_SIZE];
  block_read(block_index, block_buffer);

  memcpy(de, block_buffer + (index % num_dirents_per_block) * sizeof(Dir_Entry), sizeof(Dir_Entry));
}