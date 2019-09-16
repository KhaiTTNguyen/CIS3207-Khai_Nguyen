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

struct process{
    long id;
    string status;
};

struct event{
    EVENT eventType ;
    int etime;
    process event_p;
};

struct compareTime { 
    bool operator()(event const& e1, event const& e2) 
    {
        // "true" if "e1" arrives before "e2"
        return e1.etime > e2.etime; 
    } 
}; 


extern queue <process> CPU;
extern queue <process> disk_1;
extern queue <process> disk_2;
extern priority_queue <event, vector<event>, compareTime> eventQueue;
extern bool CPU_busy;
extern bool disk_1_busy;
extern bool disk_2_busy;
extern long processID;



// functions
void handle_process_arrival(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_arrive_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_finish_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_arrive_disk_1(event currentEvent, priority_queue <event, vector<event>, compareTime>eventQueue);
void handle_process_arrive_disk_2(event newEventTime, priority_queue <event, vector<event>, compareTime>eventQueue);
void handle_disk_1_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_disk_2_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);

double randomDoub();
int randomTime(int tMin, int tMax);
void showpq(priority_queue <event, vector<event>, compareTime> eventQueue);
void showq(queue <process> gq);
#endif
