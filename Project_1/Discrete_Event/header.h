// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H

// Include libraries
#include <iostream>
#include <cstdio>
#include <queue>          // std::queue
#include <string>         // std::string
#include <stdlib.h> 
#include <time.h>         // for random
#include <fstream>

#include "config.h"  
#include "event.h"

#define Q_MIN 0.0
#define Q_MAX 1.0

using namespace std;

/* Declare data structures
// Private structs for that file: in .c file
// Public structs: .h file.
*/

struct process {
	long id;
	string status;
};

struct event {
	EVENT eventType;
	double etime;
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

extern int component_max_size[4];
extern double use_time[3];
extern long thoughput[3];

extern queue <int> CPU_size;		// 0
extern queue <int> disk_1_size;		// 1
extern queue <int> disk_2_size;		// 2



// functions
void handle_process_arrival(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_arrive_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_finish_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_process_arrive_disk_1(event currentEvent, priority_queue <event, vector<event>, compareTime>eventQueue);
void handle_process_arrive_disk_2(event newEventTime, priority_queue <event, vector<event>, compareTime>eventQueue);
void handle_disk_1_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);
void handle_disk_2_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue);

void print_log(event currentE, fstream& file);
double randomDoub();
double randomTime(int tMin, int tMax);
void showpq(priority_queue <event, vector<event>, compareTime> eventQueue);
void showq(queue <process> gq);


void record_throughput(int component_num);
void record_time(int component_num, double time_difference);
void record_size_CPU();
void record_size_disk_1();
void record_size_disk_2();
void print_stats(fstream& file);

#endif
