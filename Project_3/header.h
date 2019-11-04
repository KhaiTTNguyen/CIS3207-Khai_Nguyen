// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <fstream> // file opss
#include <set> // for set operations 
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <unordered_set>

using namespace std;

// define constants
// use enum {NUM_BUILT_INS = 8,...}
#define DELIMITERS " \t\r\n\a"
#define NUM_BUILT_INS 8 	// 8 built-in functions
#define LINE_LENGTH 100
#define N_THREADS 5
#define QUEUE_CAPACITY 5
#define MAX_WORD_SIZE 100 // logest word is pneumonoultramicroscopicsilicovolcanoconiosis - 45 lettters
// pthread_mutex_init(&)

// declare 
// mutexes
extern pthread_mutex_t mutex_conn;
extern pthread_mutex_t mutex_log;

// condition variables
extern pthread_cond_t fill_conn;
extern pthread_cond_t empty_conn;
extern pthread_cond_t fill_log;
extern pthread_cond_t empty_log;


extern unordered_set<string> word_dictionary;

struct circular_buffer {
	int buffer[QUEUE_CAPACITY];
    int fill_ptr;
    int use_ptr;
    int count;
};

struct log_circular_buffer {
	string buffer[QUEUE_CAPACITY];
    int fill_ptr;
    int use_ptr;
    int count;
};

extern circular_buffer* connection_queue_Ptr;
extern log_circular_buffer* log_queue_Ptr;

// Fucntion declarations
unordered_set<string> load_dictionary(char * fileArg);
void spawn_worker_threads();
void addSocketToQueue(int socket, circular_buffer* connection_queue_Ptr);
int removeSocketFromQueue(circular_buffer* connection_queue_Ptr);
void add_word_to_logQueue(string word, log_circular_buffer* log_queue_Ptr);
char* remove_word_from_logQueue(log_circular_buffer* log_queue_Ptr);

void put(int value, circular_buffer* connection_queue);
int get(circular_buffer* connection_queue);
void put_log(string value, log_circular_buffer* log_queue_Ptr);
string get_log(log_circular_buffer* log_queue_Ptr);

int is_word_in_dictionary(string word);

void * workerThread(void * arg);
char * concat(const char *s1, const char *s2);

#endif