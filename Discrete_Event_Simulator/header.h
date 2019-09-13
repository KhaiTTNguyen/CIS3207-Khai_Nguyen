// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <queue>          // std::queue
#include <string>         // std::string
#include <stdlib.h> 
#include <time.h>         // for random

#include "config.h"  
#include "event.h"

#define Q_MIN 0.0
#define Q_MAX 1.0

using namespace std;

/* Declare data structures
// Private structs for that file: in .c file
// Public structs: .h file.
*/

struct process
{
    int id;
    string status;
    double ptime;
    // Default constructor
    // process(int id = 0, string status = "", double ptime = 0.0) 
    // : id(id), status(status), ptime(ptime) {} 
};

struct event
{
    EVENT eventType ;
    double etime;
    process event_p;

    // event(EVENT eventType = PROCESS_ARRIVAL, double = 0.0, process event_p = {0, "", 0.0}) 
    // : eventType(eventType), etime(etime), event_p(event_p) {} 
};

struct compareTime { 
    bool operator()(event const& e1, event const& e2) 
    {
        // "true" if "e1" is longer than "e2"
        return e1.etime > e2.etime; 
    } 
}; 

extern queue <process> CPU;
extern queue <process> disk_1;
extern queue <process> disk_2;
extern bool CPU_busy;
extern bool disk_1_busy;
extern bool disk_2_busy;


int getfavoritenumber(void);

// functions
void cpu_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
double randomDoub();
void showpq(priority_queue <event, vector<event>, compareTime> eventQueue);
void showq(queue <process> gq);
#endif
