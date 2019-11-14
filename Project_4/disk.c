#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "disk.h"

/******************************************************************************/
static int active = 0;  /* is the virtual disk open (active) */
static int handle;      /* file descriptor to handle virtual disk       */

/******************************************************************************/

/*
Create an empty, virtual disk file
Return 0 on success, and -1 when the disk disk_name could not be created, opened, or properly initialized.
*/
int make_disk(char *name)
{ 
  int f, cnt;
  char buf[BLOCK_SIZE];

  if (!name) {
    fprintf(stderr, "make_disk: invalid file name\n");
    return -1;
  }

  if ((f = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
    perror("make_disk: cannot open file");
    return -1;
  }

  memset(buf, 0, BLOCK_SIZE);
  for (cnt = 0; cnt < DISK_BLOCKS; ++cnt)
    write(f, buf, BLOCK_SIZE);

  close(f);

  return 0;
}

/*
You need to open the disk and then load the meta-information that is necessary to handle the file system operations 

“mount disk” (open the drive file 
and read the information from boot block

returns 0 on success, and -1 when the disk disk_name could not be opened or when the disk does not contain a valid file system 
*/
int open_disk(char *name)
{
  int f;

  if (!name) {
    fprintf(stderr, "open_disk: invalid file name\n");
    return -1;
  }  
  
  if (active) {
    fprintf(stderr, "open_disk: disk is already open\n");
    return -1;
  }
  
  if ((f = open(name, O_RDWR, 0644)) < 0) {
    perror("open_disk: cannot open file");
    return -1;
  }

  handle = f;
  active = 1;

  return 0;
}

/*
close a previously opened disk (file) 
write back all meta-information so that the disk persistently reflects all changes that were made to the file system


returns 0 on success, and -1 when the disk disk_name could not be closed 
or when data could not be written to the disk (this should not happen). 
If there are any open file descriptors (that point to files in the file system that is about to be unmounted), umount_fs will close them.
*/

int close_disk()
{
  if (!active) {
    fprintf(stderr, "close_disk: no open disk\n");
    return -1;
  }
  
  close(handle);

  active = handle = 0;

  return 0;
}

/*
each write not only has to write data to disk but has to first decide
which block to allocate to the file and thus update other structures of the
disk accordingly 
*/

int block_write(int block, char *buf)
{
  if (!active) {
    fprintf(stderr, "block_write: disk not active\n");
    return -1;
  }

  if ((block < 0) || (block >= DISK_BLOCKS)) {
    fprintf(stderr, "block_write: block index out of bounds\n");
    return -1;
  }

  if (lseek(handle, block * BLOCK_SIZE, SEEK_SET) < 0) {  //
    perror("block_write: failed to lseek");
    return -1;
  }

  if (write(handle, buf, BLOCK_SIZE) < 0) {
    perror("block_write: failed to write");
    return -1;
  }

  return 0;
}

/*

*/
int block_read(int block, char *buf)
{
  if (!active) {
    fprintf(stderr, "block_read: disk not active\n");
    return -1;
  }

  if ((block < 0) || (block >= DISK_BLOCKS)) {
    fprintf(stderr, "block_read: block index out of bounds\n");
    return -1;
  }

  if (lseek(handle, block * BLOCK_SIZE, SEEK_SET) < 0) {
    perror("block_read: failed to lseek");
    return -1;
  }

  if (read(handle, buf, BLOCK_SIZE) < 0) {    // read 1 BLOCK --> grab BLOCK_SIZE
    perror("block_read: failed to read");
    return -1;
  }

  return 0;
}
