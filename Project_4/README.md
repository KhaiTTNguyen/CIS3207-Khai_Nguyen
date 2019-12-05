# Khai_Nguyen_File_System
Project 4: File System

## Introduction
This is a basic file system that is implemented using the File Allocation Table (FAT)

## Design
The file system program is broken into
- main.c
- function.c
- helper_func.c
- disk.c
- disk.h
- header.h
- Makefile

## Guide
#### Requirements
- Understanding of system_calls read(), write(). Familiarity with linux "man" page
- Knowledge of file descriptors, FAT, disk architecture

#### Usage guide 
- Make the disk, function provided

```bash
int make_disk(char *name);
```

Then, we need to set up the file system using: 
```bash
int make_fs(char *disk_name);
```

## Testing procedure
Incremental tests were carried out as followed:

```bash
int make_disk(char *name);
```

```bash
int make_fs(char *disk_name);
```

```bash
int mount_fs(char *disk_name);
```

```bash
int umount_fs(char *disk_name);
```

```bash
int fs_create(char *name);
```

```bash
int fs_open(char *name);
int fs_write(int fildes, void *buf, size_t nbyte);
int fs_close(int fildes);

int fs_get_filesize(int fildes);
```

```bash
int fs_lseek(int fildes, off_t offset);
```

```bash
int fs_read(int fildes, void *buf, size_t nbyte);
```

```bash
int fs_delete(char *name);
```

```bash
int fs_truncate(int fildes, off_t length);
```
##Project stage (Incompleted)
Having issue writing and reading into file descriptors

# Contributors
Khai Nguyen: khainguyen@temple.edu

