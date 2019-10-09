// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H


// Include libraries

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <fcntl.h>
#include <sys/types.h>


// define constants
#define DELIMITERS " \t\r\n\a"
#define NUM_BUILT_INS 8 	// 8 built-in functions

// Fucntion declarations

int shell_exit(char** args);
char* lower(char* s);

#endif