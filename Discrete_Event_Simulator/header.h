// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <queue>          // std::queue
#include <string>         // std::string
using namespace std;

/* Declare data structures
// Private structs for that file: in .c file
// Public structs: .h file.
// Queues: CPU and 2 disks
*/
struct process
{
    short id;
    string status;
    double time;
};

queue <process> CPU;
queue <process> disk_1;
queue <process> disk_2;



int getfavoritenumber(void);

#endif
