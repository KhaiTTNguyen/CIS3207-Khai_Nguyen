// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H


// Include libraries
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char** environ;
extern char* shell;
// define constants
#define DELIMITERS " \t\r\n\a"
#define NUM_BUILT_INS 8 	// 8 built-in functions

// Fucntion declarations
int shell_execute(char** args_list);
int shell_cd(char** args_list);
int shell_pause(char** args_list);
int shell_echo(char** args_list);
int shell_help(char** args_list);
int shell_environ(char** args_list);
int shell_clr(char** args_list);
int is_dir(char *path_name);
int shell_ls(char** args_list);
int shell_exit(char** args_list);
char* lower(char* s);

#endif