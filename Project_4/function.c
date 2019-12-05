/*
Below are the operational functions for the file system
*/


#include "header.h" // cotaining disk.h

/*
This function creates a fresh (and empty) file system on the virtual disk with name disk_name. 
As part of this function, you should first invoke make_disk(disk_name) to create a new disk. 

Then, open this disk and write/initialize the necessary meta-information for your file system so that it can be later used (mounted). 
STATIC calls

The function returns 0 on success, and -1 when the disk disk_name could not be created, opened, or properly initialized.
*/

/* call this ONCE ONLY */

int make_fs(char *disk_name){
  // create disk
  // make_disk();
  printf("About to open disk\n");

  if (open_disk("Test_Disk") < 0){
    printf("disk can't be opened\n");
    return -1;
  }

  printf("Disk opened\n");


  
  // initialize superblock
  // write content of SUPERBLOCK to 1st block on disk
  superblock my_superblock;  
  my_superblock.blocksize = BLOCK_SIZE; // int blocksize;   
  my_superblock.bps = 512; // 512 bytes/sector
  my_superblock.spb = 8;    // 8 sector/cluster
  my_superblock.fat_start = 1;          // int fat_start;
  my_superblock.fat_length = (DISK_BLOCKS * sizeof(uint16_t)) / BLOCK_SIZE; // in unit of blocks    
  my_superblock.DE_start = 1 + my_superblock.fat_length;  //int DE_start, in block number;
  my_superblock.DE_length = (DISK_BLOCKS/2 - 1 - my_superblock.fat_length) / sizeof(Dir_Entry) ; // number of Dir_Entries allowed
  my_superblock.DataRegion_start = NUM_DATA_BLOCKS; // in block number;  
  my_superblock.valid_files = 1;

  printf("Starting to write supper block\n");
  // write the contents of the SUPER BLOCK to the first block on the disk.
  char temp_mem[BLOCK_SIZE];
  memset(temp_mem, 0, BLOCK_SIZE);
  memcpy(temp_mem, &my_superblock, sizeof(superblock));

  if (block_write(0, temp_mem) < 0) {   // write to 1st block
    perror("Error while writing to disk"); 
  }

  memset(temp_mem, 0, BLOCK_SIZE);
  /*-------------------------initialize the FAT-------------------------*/
  
  // Write out fat_length  blank FAT blocks starting at fat_start
  // for (uint16_t k = my_superblock.fat_start; k < my_superblock.fat_start + my_superblock.fat_length; k++) {
  //     if (block_write(k, temp_mem) < 0) { 
  //         perror("Error while writing to disk");
  //     }
  // }
  printf("Start writing FAT\n");
  uint16_t temp_FAT[DISK_BLOCKS];
  
  for (uint16_t i = 0; i < 1 + my_superblock.fat_length + 1; ++i){ // units of blocks
    temp_FAT[i] = -1;
  }

  for (uint16_t i = 1 + my_superblock.fat_length + 1; i < DISK_BLOCKS; ++i){
    temp_FAT[i] = 0x00;
  }
  printf("Done filing FAT\n");
  
  write_fat(&temp_FAT[0]);
  printf("Done writing FAT\n");

  /*-------------------------initialize ROOT Dir Entry-------------------------*/
  memset(temp_mem, 0, BLOCK_SIZE);
  printf("Start writing Dir\n");
  
  Dir_Entry root; //= (Dir_Entry *) calloc(1, sizeof(Dir_Entry));
  root.file_type = 0; // directory
  strcpy(root.name, "ROOT");
  printf("name copied\n");
  root.start_block = my_superblock.fat_start + my_superblock.fat_length;
  root.occupied = 1;
  printf("prepare to copy\n");
  

  // copy ROOT to buffer
  memcpy(temp_mem, &root, sizeof(Dir_Entry));
  
  printf("temp_mem is %s\n", &temp_mem);

  printf("root start block is %d\n", root.start_block);
  if (block_write(root.start_block, temp_mem) < 0) {   // write to start block of Dir_Entry
      perror("Error while writing to disk"); 
  }
  
  close_disk();
  printf("Disk close\n");
  
  return 0;
}

/*
Load structures into RAM

This function mounts a file system that is stored on a virtual disk with name disk_name. 
With the mount operation, a file system becomes "ready for use." 
You need to open the disk and then load the meta-information that is necessary to handle the file system operations that are discussed below. 

The function returns 0 on success, and -1 when the disk disk_name could not be opened or when the disk does not contain a valid file system 
(that you previously created with make_fs).

*/

/* call everytime */
/* load necessary structures onto disk */
// read in the FAT array from the disk into an array in memory

int mount_fs(char *disk_name){
    // load the necessary data stuctures from
    // the virtual disk into your program’s memory.
    
    // NEED THIS
    if (open_disk(disk_name) < 0){
      printf("Disk could not be opened\n");
      return -1;
    }

    /* ---------------------read superblock---------------------*/
    char superblock_data[BLOCK_SIZE];
    if (block_read(0, superblock_data) < 0) { 
        fprintf(stderr, "block_read failed for block 0\n"); 
        return -1;
    }
    
    disk_superblock = (superblock*) calloc(1, sizeof(superblock));
    memcpy(disk_superblock, &superblock_data, sizeof(superblock)); // copy to global variables 

    printf("BLOCKSIZE: %i\n", disk_superblock->blocksize); 
    printf("DE_START: %i\n", disk_superblock->DE_start); 
    printf("DE_LENGTH: %i\n", disk_superblock->DE_length); 
    printf("FAT_START: %i\n", disk_superblock->fat_start); 
    printf("FAT_LENGTH: %i\n", disk_superblock->fat_length); 
    printf("DB_START: %i\n", disk_superblock->DataRegion_start); 
    printf("valid_files: %i\n", disk_superblock->valid_files); 


    /*-------------------read FAT-------------------------*/
    // Get FAT Entries // create a temporary FAT table and pass it around with a pointer during run time
    // copy to the operating FAT in memmory
    if (read_fat() < 0){
      printf("Cannot read FAT data in\n");
      return -1;
    }

    printf("FAT on memmory is:\n");
    for (int i = 9; i < 30; i++){
      printf("Read FAT is %d\n",FAT[i]);
    }
    
    /*-------------------read Dir_Entry-------------------------*/
    // for (int j = disk_superblock->DE_start; j < disk_superblock->DE_start + disk_superblock->DE_length; j++) {
    
    // struct dirent * root_entry_ptr = root_entry; // keep the beginning of Dir_Entries
    int num_dirents_per_block = BLOCK_SIZE / sizeof(Dir_Entry);
    printf("numdirents/block is %d\n", num_dirents_per_block);
    root_entry = (Dir_Entry*) calloc(num_dirents_per_block, sizeof(Dir_Entry));  // so that equals BLOCK_SIZE

    if (block_read(disk_superblock->DE_start, (char*) root_entry) < 0) { 
        perror("Error while reading from disk"); 
        return -1;
    }

    printf("root entry read is %s\n", root_entry->name);
    printf("root entry occupied: %i\n", root_entry->occupied);
    printf("root entry start block: %i\n", root_entry->start_block);

    return 0;
}


/*
This function unmounts your file system from a virtual disk with name disk_name. 
As part of this operation, you need to write back all meta-information so that the disk persistently 
reflects all changes that were made to the file system (such as new files that are created, data that is written, ...). 

You should also close the disk. 

The function returns 0 on success, and -1 when the disk disk_name could not be closed or when data could not be written to the disk (this should not happen). If there are any open file descriptors (that point to files in the file system that is about to be unmounted), umount_fs will close them.
*/
int umount_fs(char *disk_name){
    printf("unmounting\n");
    /*-----------------Write super block----------------*/

    char superblock_data[BLOCK_SIZE];
    memcpy(&superblock_data, disk_superblock, sizeof(superblock)); // copy to global variables 
    if (block_read(0, superblock_data) < 0) { 
        fprintf(stderr, "block_write failed for block 0\n"); 
        return -1;
    }
    
    /*-----------------Write FAT----------------*/
    if (write_fat(&FAT[0]) < 0){
      printf("Cannot write FAT data in\n");
      return -1;
    }

    /*-----------------Write Dir Entries----------------*/
    // seems like we need dir_length

    close_disk();

    return 0;
}

/*
Create a directory with the name name. 
returns zero on success, 
-1 if an error occurred. 
Failure:
1. when the directory with name already exists), 
2. when the file name is too long (it exceeds 15 characters for the directory name), 
3. when there are already 256 files present in the directory.
*/
int fs_mkdir(char *name){ // same as creating a file
  // check if the directory with name already exists)
  
  // check if name length is valid
  
  // check if number of files <= 256
    // /*--------------------------------------------------------------------*/
    // int full = 1;
    // Dir_Entry * temp = calloc(1, sizeof(Dir_Entry));   // fix this
    // for (int i = 0; i < disk_superblock->de_length; i++){
    //   // locate position of dir_entry
      
    //   // check valid 
    //   if (temp->valid == 0) {
    //     full = 0;
    //     break;
    //   }
    // }
    /*--------------------------------------------------------------------*/
    // check if there are available dir_entry


    // update name
    // set time & date
    // set start_block
    // set size
    // set offset
    // set temp->valid = 1

    // disk_vcb->valid_files++;
    
  return 0;
}

/*
 (in this case, name is a path to the file that is to be opened, including the actual filename part of the path) 
The file specified by name is opened for reading and writing, 

Note that the same file (file with the same name) can be opened multiple times. --> provide multiple, independent file descriptors.

must support a maximum of 64 file descriptors that can be open simultaneously. f

Failure: 
1. when the file with name cannot be found (i.e., it has not been created previously or is already deleted). 
2. when there are already 64 file descriptors active. 
When a file is opened, the file offset (seek pointer) is set to 0 (the beginning of the file).

return the file descriptor corresponding to this file, -1 on failure.  
*/

int fs_open(char *name){
    
    // check if there has been 64 file descriptors active
    if(total_fd == 64){
      fprintf(stderr, "Maximum file descriptors reached"); 
      return -1;
    }

    int rem_files = disk_superblock->valid_files;
    // grab the file dir_entry 
    // Loop through dirents, looking for the valid dirent with a matching name
    int fd;
    for (int i = 0; i < disk_superblock->DE_length && rem_files > 0; i++) {
      Dir_Entry * tmp = (Dir_Entry *) alloca(sizeof(Dir_Entry));
      read_dirent(i, tmp, disk_superblock);
      if ((tmp->occupied == 1) && (strcmp(name, tmp->name) == 0)) {
        fd = open(name, O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR); // needs error check
        total_fd++;

        root_entry += i; // increment root_entry to points to "i"
        printf("currently at dirent %i\n", i);
        printf("currently at block %i\n", tmp->start_block);
        printf("Got fd = %d\n",fd);
        return fd;
      } else if (tmp->occupied) {
        rem_files--;
      }
    }

    fprintf(stderr, "Could not find specified file: %s", name); 
    return -1;
    // get FAT entry from first block / current_index
}


/*
This function attempts to write nbyte bytes of data to the file referenced by the descriptor fildes from the buffer pointed to by buf. 

******The function assumes that the buffer buf holds at least nbyte bytes****** 

When the function attempts to write past the end of the file, the file is automatically extended to hold the additional bytes. 

It is possible that the disk runs out of space while performing a write operation. In this case, the function attempts to write as many bytes as possible (i.e., to fill up the entire space that is left). 

The maximum file size is 32 Mbytes (which is, 8192 blocks, each 4K). 

Upon successful completion, the number of bytes that were actually written is returned. This number could be smaller than nbyte when the disk runs out of space (when writing to a full disk, the function returns zero). 

In case of failure, the function returns -1. 

It is a failure when the file descriptor fildes is not valid. The write function implicitly increments the file pointer by the number of bytes that were actually written.
*/


int fs_write(int fildes, void *buf, size_t nbyte){
    
    // file opened
    // int og_size = nbyte;

    //*************When a file is opened, the file offset (seek pointer) is set to 0 (the beginning of the file)*************

    // get FAT entry from first block / current_index
    //int current_index = f_dirent->start_block;

    /*
    if (nbyte > fs_get_filesize(fildes)){
      int total_blocks_required = nbyte/BLOCK_SIZE;
      return -1;
      // update dirent & FAT
    }

    */
    printf("Fildes is %d\n", fildes);
    printf("Buff in fs_write is %s\n", buf);
    printf("nbytes in fs_write is %d\n", nbyte);
  
    if (write(fildes, buf, nbyte) < 0) {	
		  printf("write system_call error\n");
    }

    char * readBack = (char*) alloca(20);
    read(fildes, readBack, nbyte);

    printf("Buff written in fs_write is %s\n", readBack);
    // while (nbyte > 0) {
    //     //char current_buffer[BLOCK_SIZE];
    //     //block_read(disk_superblock->DataRegion_start + current_FAT_index, current_buffer);

        
    //     buf = buf + BLOCK_SIZE;

    //     nbyte -= BLOCK_SIZE;

    //     if (EOF) {
    //         break;
    //     } else {
    //         current_index = FAT[current_index];
    //     }
    // }

    // Update size metadata
    // Dir entry->size

    return nbyte;

}

/*
The file descriptor "fildes" is closed. 
A closed file descriptor can no longer be used to access the corresponding file. 

return 0 on success. 
In case the file descriptor fildes does not exist or is not open, the function returns -1.
*/

int fs_close(int fildes){
  
  // check if file exists
    // if not return -1;

  // read to tempbuff toWrite
  // assume content of fidles < BLOCKSIZE
  char toWrite[BLOCK_SIZE];
  printf("Fildes is %d\n", fildes);
  if(read(fildes, toWrite, BLOCK_SIZE) < 0){
    printf("Cant write to toWrite buf\n");
    return -1;
  }

  printf("toWrite contains: %s\n", toWrite);

  printf("Done checking toWrite\n");

  // offset
  int offset = root_entry->start_block;
  block_write(offset, toWrite);
  // fs_lseek(handle,offset);

  // // only write to taht specific block
  // if (write(handle, toWrite, BLOCK_SIZE) < 0) {
  //   perror("block_write: failed to write");
  //   return -1;
  // }

  total_fd--;
  root_entry = origin_root; // push root_entry back to origin_root
  close(fildes);
  return 0;
}


/*
This function returns the current size of the file pointed to by the file descriptor fildes. 
In case fildes is invalid, the function returns -1.

*/

int fs_get_filesize(int fildes){
    // check if file exists
    
    // grab the file dir_entry 
    Dir_Entry * temp = (Dir_Entry *) calloc(1, sizeof(Dir_Entry));
    return temp->size;
}




/*
Creates a new file with name name in your file system (name is the path to the file including the name of the file itself). 
The file is initially empty. 
The maximum length for a file name is 15 characters (this is also the maximum length of a directory name). 
Also, there can be at most 256 files in the directory. 

Return 0 if success
-1 on failure. 
Failure: 
1. when the file with name already exists (using the full path specified in name), 
2. when the file name is too long (it exceeds 15 characters for the directory name and 15 characters for the name of the file), 
3. when there are already 256 files present in the specified directory. 
Note that to access a file that is created, it has to be subsequently opened.
*/

int fs_create(char *name){
    // check if exceed 256 files
    if (disk_superblock->valid_files == MAX_NUM_FILES){
      fprintf(stderr, "Reached maximum num of files\n");
      return -1;
    }

    // check if meets maximum length filename
    if (strlen(name) > FILENAME_MAX){
      fprintf(stderr, "File name exceed max limit\n");
      return -1;
    }

    // create a new dir_entry
    if (strrchr(name, '/') > name) {  // find last '/'
      fprintf(stderr, "Unable to create on a multilevel dir\n");
      return -1;
    }
    printf("Find unused dirent\n");
    // -------------------find an unused dirent-------------------------
    int full = 1; // check if need more blocks
    Dir_Entry * temp = (Dir_Entry *) alloca(sizeof(Dir_Entry));   // fix this
    printf("dirent allocated\n");
    int i;
    for (i = 0; i < disk_superblock->DE_length; i++){
      read_dirent(i, temp, disk_superblock); // read dirent at "i" to "temp" Dir_Entry
      // check valid 
      printf("dirent read\n");
      if (temp->occupied == 0) {
        full = 0;
        break;
      }
    }
    
    // Throw error if all dirents full
    if (full == 1) {
      fprintf(stderr, "There are no more available dirents\n");
      return -1;
    }

    printf("Start writing new dirent\n");
    //------------------------------------------------------------
    // fill an unoccupied Dir_Entry
    printf("Dirent name is %s\n", temp->name);
    temp->occupied = 1;
    temp->size = 0;
    
    temp->file_type = 1;  // this is a file
    memcpy(temp->name, name, strlen(name) + 1);
    temp->start_block = create_FAT_entry(); /*start block # in FAT*/
    printf("FAT info written\n");

    update_dirent(i, temp, disk_superblock);

    printf("new dirent info written\n");

    disk_superblock->valid_files++;
    printf("Done writing dirent\n");

    return 0;
}


/*
This function deletes the file with the path and name name from the directory of your file system 
and frees all data blocks and meta-information that correspond to that file. 

The file that is being deleted must not be open. 
That is, there cannot be any open file descriptor that refers to the file name. 
When the file is open at the time that fs_delete is called, the call fails and the file is not deleted. 

return 0 on success, 
-1 on failure. 

Failure
1. when the file with name does not exist. 
2. when the file is currently open (i.e., there exists at least one open file descriptor that is associated with this file).
*/

// ** DONT really nead to zero out the data --  they are all bytes --> overwrite them late on when creating new files

int fs_delete(char *name){
    // split string to get file name

    // find dir_entry location - check if file exist
    // create a new dir_entry
    int full = 1; // check if need more blocks
    Dir_Entry * temp = (Dir_Entry *) calloc(1, sizeof(Dir_Entry));   // fix this
    
    // mark FAT entry as unused
    unsigned int current_index = temp->start_block;
    while (FAT[current_index] != -1) { // if not EOF
      int tmp_index = current_index;
      current_index = FAT[current_index];
      FAT[tmp_index] = 0;
    }

    if (FAT[current_index] == -1){  // fix the final block
         FAT[current_index] = 0;
    }
    // Decrease the number of valid files on the disk
    
    //disk_superblock->valid_files--;

    return 0;
}


/*
This function attempts to read nbyte bytes of data from the file referenced by the descriptor fildes into the buffer pointed to by buf. 
The function assumes that the buffer buf is large enough to hold at least nbyte bytes. 

When the function attempts to read past the end of the file, it reads all bytes until the end of the file. 

Return: the number of bytes that were actually read 
This number could be smaller than nbyte when attempting to read past the end of the file (when trying to read while the file pointer is at the end of the file, the function returns zero). 

Failure: the function returns -1. It is a failure when the file descriptor fildes is not valid. 
The read function implicitly increments the file pointer by the number of bytes that were actually read.
*/
int fs_read(int fildes, void *buf, size_t nbyte){
    printf("fs_read called\n");

    // check if file exists
    
    // grab the file dir_entry 
    

    // get FAT entry from first block / current_index
    
    // int current_index = ...; 
    while (nbyte > 0) {
        char current_buffer[BLOCK_SIZE];
        // block_read(start_of_data_region + current_FAT_index, current_buffer);

        memcpy(buf, current_buffer, BLOCK_SIZE);

        nbyte -= BLOCK_SIZE;

        if (EOF) {
            break;
        } else {
            // current_index = FAT[current_index];
        }
    }
    return 0;
}

/*
This function sets the file pointer (the offset used for read and write operations) associated with the file descriptor fildes to the argument offset. 

It is an error to set the file pointer beyond the end of the file. 

To append to a file, one can set the file pointer to the end of a file, 
for example, by calling fs_lseek(fd, fs_get_filesize(fd));. 

Upon successful completion, a value of 0 is returned. fs_lseek returns -1 on failure. 

It is a failure when the file descriptor fildes is invalid, 
when the requested offset is larger than the file size, 
or when offset is less than zero.

*/
// The off_t data type is a signed integer
int fs_lseek(int fildes, off_t offset){
  // check if file descriptor is valid


  // check if offset > file size
  if (offset > fs_get_filesize(fildes)){
    printf("requested offset is larger than the file size, \n");
    return -1;
  }

/*--------------------------------*/

  if ((offset < 0) || (offset >= DISK_BLOCKS)) {
    fprintf(stderr, "offset index out of bounds\n");
    return -1;
  }

  // move seeker to that "block" number
  if (lseek(fildes, offset * BLOCK_SIZE, SEEK_SET) < 0) {  // fix offset of "handle"/disk file
    perror("fs_lseek: failed to lseek");
    return -1;
  }

/*-----------------------------------*/

    return 0;
}

/*
This function causes the file referenced by fildes to be truncated to 
length bytes in size. 
If the file was previously larger than this new size, the extra data are lost and the corresponding data blocks on disk (if any) must be freed. 
It is not possible to extend a file using fs_truncate. 
When the file pointer is larger than the new length, then it is also set to length (the end of the file). 
Upon successful completion, a value of 0 is returned. 

fs_lseek returns -1 on failure. 
It is a failure when the file descriptor fildes is invalid or the requested length is larger than the file size.
*/
int fs_truncate(int fildes, off_t length){

    // check if file exists
    
    // grab the file dir_entry 
    Dir_Entry * temp = (Dir_Entry *) calloc(1, sizeof(Dir_Entry));   // fix this
    
    // If length > file_size, throw an error
    if (length > temp->size) {
      fprintf(stderr, "Cannot truncate\n");
      return -1;
    }

    /* clear all FAT entrie for file after "length" */
    // get FAT entry from first block / current_index
    int current_index = 0;  //............. index at "length"

    int new_end_index = current_index;

    while (FAT[current_index] != EOF) {
      int temp_index = current_index; 
      current_index = FAT[current_index];
      
      FAT[temp_index] = 0;
    }

    FAT[new_end_index] = -1;

    char current_buffer[BLOCK_SIZE];
    // zero out the blocks after "length"
    //block_read(start_of_data_region + new_end_index, current_buffer);

    // NEED THIS
    // memset(...);


    // block_write(start_of_data_region + new_end_index, current_buffer);    

    // Update size metadata
    
    return 0;
}

