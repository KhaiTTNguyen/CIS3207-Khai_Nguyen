
#include "header.h"


/*
This function creates a fresh (and empty) file system on the virtual disk with name disk_name. 
As part of this function, you should first invoke make_disk(disk_name) to create a new disk. Then, open this disk and write/initialize the necessary meta-information for your file system so that it can be later used (mounted). The function returns 0 on success, and -1 when the disk disk_name could not be created, opened, or properly initialized.
*/
int make_fs(char *disk_name){
    return 0;
}

/*

This function mounts a file system that is stored on a virtual disk with name disk_name. 
With the mount operation, a file system becomes "ready for use." 
You need to open the disk and then load the meta-information that is necessary to handle the file system operations that are discussed below. 
The function returns 0 on success, and -1 when the disk disk_name could not be opened or when the disk does not contain a valid file system (that you previously created with make_fs).

*/

int mount_fs(char *disk_name){
    return 0;
}


/*

This function unmounts your file system from a virtual disk with name disk_name. As part of this operation, you need to write back all meta-information so that the disk persistently reflects all changes that were made to the file system (such as new files that are created, data that is written, ...). 
You should also close the disk. 
The function returns 0 on success, and -1 when the disk disk_name could not be closed or when data could not be written to the disk (this should not happen). If there are any open file descriptors (that point to files in the file system that is about to be unmounted), umount_fs will close them.

*/
int umount_fs(char *disk_name){
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


/*
This function attempts to read nbyte bytes of data from the file referenced by the descriptor fildes into the buffer pointed to by buf. The function assumes that the buffer buf is large enough to hold at least nbyte bytes. When the function attempts to read past the end of the file, it reads all bytes until the end of the file. Upon successful completion, the number of bytes that were actually read is returned. This number could be smaller than nbyte when attempting to read past the end of the file (when trying to read while the file pointer is at the end of the file, the function returns zero). In case of failure, the function returns -1. It is a failure when the file descriptor fildes is not valid. 
The read function implicitly increments the file pointer by the number of bytes that were actually read.
*/
int fs_read(int fildes, void *buf, size_t nbyte){
    return 0;
}

/*
This function attempts to write nbyte bytes of data to the file referenced by the descriptor fildes from the buffer pointed to by buf. The function assumes that the buffer buf holds at least nbyte bytes. When the function attempts to write past the end of the file, the file is automatically extended to hold the additional bytes. It is possible that the disk runs out of space while performing a write operation. In this case, the function attempts to write as many bytes as possible (i.e., to fill up the entire space that is left). The maximum file size is 32 Mbytes (which is, 8192 blocks, each 4K). Upon successful completion, the number of bytes that were actually written is returned. This number could be smaller than nbyte when the disk runs out of space (when writing to a full disk, the function returns zero). In case of failure, the function returns -1. 
It is a failure when the file descriptor fildes is not valid. The write function implicitly increments the file pointer by the number of bytes that were actually written.
*/
int fs_write(int fildes, void *buf, size_t nbyte);

/*
This function returns the current size of the file pointed to by the file descriptor fildes. In case fildes is invalid, the function returns -1.

*/

int fs_get_filesize(int fildes);

/*
This function sets the file pointer (the offset used for read and write operations) associated with the file descriptor fildes to the argument offset. It is an error to set the file pointer beyond the end of the file. To append to a file, one can set the file pointer to the end of a file, for example, by calling fs_lseek(fd, fs_get_filesize(fd));. Upon successful completion, a value of 0 is returned. fs_lseek returns -1 on failure. It is a failure when the file descriptor fildes is invalid, when the requested offset is larger than the file size, or when offset is less than zero.

*/
int fs_lseek(int fildes, off_t offset);

/*
This function causes the file referenced by fildes to be truncated to length bytes in size. If the file was previously larger than this new size, the extra data are lost and the corresponding data blocks on disk (if any) must be freed. It is not possible to extend a file using fs_truncate. When the file pointer is larger than the new length, then it is also set to length (the end of the file). Upon successful completion, a value of 0 is returned. fs_lseek returns -1 on failure. It is a failure when the file descriptor fildes is invalid or the requested length is larger than the file size.
*/
int fs_truncate(int fildes, off_t length);

