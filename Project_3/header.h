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
#include <pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>

using namespace std;

// define constants
// use enum {NUM_BUILT_INS = 8,...}
#define DELIMITERS " \t\r\n\a"
#define NUM_BUILT_INS 8 	// 8 built-in functions
#define LINE_LENGTH 100
#define N_THREADS 5

// pthread_mutex_init(&)

// declare 
// mutexes
extern pthread_mutex_t mutex;
// condition variables
extern pthread_cond_t fill;
extern pthread_cond_t empty;

extern set<string> word_dictionary;

// struct exec_context {
// 	int out_redir_trunc_indx;
// 	int out_redir_append_indx;
//     int in_redir_indx;
//     int pipe_indx;
//     int backgroundRun_indx;
// };

// Fucntion declarations
set<string> load_dictionary(char * fileArg);
void spawn_worker_threads();
void addSocketToBuffer(int socket);
void * workerThread(void * arg);

#endif