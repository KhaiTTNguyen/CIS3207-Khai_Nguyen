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
#include <sys/wait.h>
#include <errno.h>

// define constants
#define DELIMITERS " \t\r\n\a"
#define NUM_BUILT_INS 8 	// 8 built-in functions
#define LINE_LENGTH 100

// struct exec_context {
// 	int out_redir_trunc_indx;
// 	int out_redir_append_indx;
//     int in_redir_indx;
//     int pipe_indx;
//     int backgroundRun_indx;
// };

// Fucntion declarations
int shell_execute(char** args_list);
void shell_cd(char** args_list);
void shell_pause(char** args_list);
void shell_echo(char** args_list);
void shell_help(char** args_lis);
void shell_environ(char** args_list);
void shell_clr(char** args_list);
int is_dir(char *path_name);
void shell_ls(char** args_list);
void shell_exit(char** args_list);
int exec_pipe(char **args, int p_indx);
// char* lower(char* s);

#endif