#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "disk.h"

/******************************************************************************/
static int active = 0;  /* is the virtual disk open (active) */
static int handle;      /* file handle to virtual disk       */

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
Create a directory with the name name. 
returns zero on success, 
-1 if an error occurred. 
Failure:
1. when the directory with name already exists), 
2. when the file name is too long (it exceeds 15 characters for the directory name), 
3. when there are already 256 files present in the directory.
*/
int fs_mkdir(char *name){
  return 0;
}



/*

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

  if (lseek(handle, block * BLOCK_SIZE, SEEK_SET) < 0) {
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

// FAT 0, 1 or -1 (end of file)


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
  return 0;
}


/*
The file descriptor "fildes" is closed. 
A closed file descriptor can no longer be used to access the corresponding file. 

return 0 on success. 
In case the file descriptor fildes does not exist or is not open, the function returns -1.
*/

int fs_close(int fildes){
  return 0;
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
  
  /*
  int fd = open("foo", O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
  */
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

int fs_delete(char *name){
  return 0;
}


