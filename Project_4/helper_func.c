

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


/*
 * searches FAT to find the next available slot,
 * return the corresponding index into the FAT array.
 */
int create_FAT_entry() {

    int i;
    int found = 0;
    for (i = 0; i < DISK_BLOCKS; i++) {
        if (FAT[i] == 0) {
        found = 1; 
        break;
        }
    }

    if (!found){
        return -1;
    } 

    printf("crating fat entry\n");

    FAT[i] = -1;

    // Zero out the data
    char* zero_buff = (char*) alloca(BLOCK_SIZE);
    printf("writing to block %i in DaReg\n", disk_superblock->DataRegion_start + i);
    block_write(disk_superblock->DataRegion_start + i, zero_buff);

    return i;
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

/* This function takes an index into the directory entries and a dirent struct
 * and updates the dirent at that index to the one given.
 */
void update_dirent(int index, Dir_Entry* de, superblock* disk_v) {
    int num_dirents_per_block = BLOCK_SIZE / sizeof(Dir_Entry);
    int block_index = disk_v->DE_start + (index / num_dirents_per_block);

    // Get the block in which the dirent resides
    char block_buffer[BLOCK_SIZE];
    block_read(block_index, block_buffer);

    // Overwrite the correct dirent
    memcpy(block_buffer + (index % num_dirents_per_block) * sizeof(Dir_Entry), de, sizeof(Dir_Entry));

    // Write the block back to disk
    block_write(block_index, block_buffer);
} 


int find_dirent_by_name(Dir_Entry* de, char* path, superblock* disk_vcb) {
  
  int rem_files = disk_vcb->valid_files;

  // Loop through dirents, looking for the valid dirent with a matching name
  for (int i = 0; i < disk_vcb->DE_length && rem_files > 0; i++) {
    Dir_Entry* tmp = (Dir_Entry*)alloca(sizeof(Dir_Entry));
    read_dirent(i, tmp, disk_vcb);
    if ((tmp->occupied == 1) && (strcmp(path, tmp->name) == 0)) {
       *de = *tmp;
       return i;
    } else if (tmp->occupied) {
      rem_files--;
    }
  }

  fprintf(stderr, "Could not find specified file: %s", path); 
  return -ENOENT;
}


