// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <fstream> // file opss
#include<set> // for set operations 
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t

using namespace std;

// define constants
// use enum {NUM_BUILT_INS = 8,...}
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
set<string> load_dictionary(void);


#endif