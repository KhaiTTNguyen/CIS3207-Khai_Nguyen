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
    double ptime;
    // Initialize variables
    process(short id, string status, double ptime) 
    : id(id), status(status), ptime(ptime)
    { 
    } 
};

struct event
{
    EVENT eventType;
    double etime;
    process event_p;

    event(EVENT eventType,double etime,process event_p) 
    : eventType(eventType), etime(etime), event_p(event_p)
    { 
    } 
};

struct compareTime { 
    bool operator()(event const& e1, event const& e2) 
    {
        // "true" if "p1" is longer than "p2"
        return e1.etime < e2.etime; 
    } 
}; 

int getfavoritenumber(void);

#endif
