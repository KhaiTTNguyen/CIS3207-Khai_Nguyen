// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <queue>          // std::queue
#include <string>         // std::string
#include <time.h>         // for random

#include "config.h"  
#include "event.h"
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
    // Initialize variables
    process(short id, string status, double time) 
    : id(id), status(status), time(time)
    { 
    } 
};

struct compareTime { 
    bool operator()(process const& p1, process const& p2) 
    {
        // "true" if "p1" is longer than "p2"
        return p1.time < p2.time; 
    } 
}; 

int getfavoritenumber(void);

#endif
