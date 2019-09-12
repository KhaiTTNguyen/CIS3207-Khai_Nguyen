// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

int getfavoritenumber(void)
{
    return 3;
}

// SEED rand only ONCE


// process myQueuePop(priority_queue <event, vector<event>, compareTime> eventQueue){
//     return eventQueue.pop();
//     // findmax(queue.size); // to calculate STAT file (queue avg size // max & avg time CPU in use // throughput = number_of_job_handles/)
    
// }

/* 
// PROCESS_ARRIVAL
{
If CPU is occupied or Queue is non-empty
put process on CPU queue

If CPU is not occupied AND queue is empty
    create new event PROCESS_ARRIVE_CPU
        event time = current system time
        set CPU to occupied

Create new event for PROCESS_ARRIVAL (so the processes
keep on pourin’ in!
    event time = current system time + random interval between
    ARIVE_MIN and ARRIVE_MAX
    create new process with a unique ID

    print to log file
}

// PROCESS_ARRIVE_CPU
{
Create new event PROCESS_FINISH_CPU 
    event time = current system time + random interval between CPU_MIN and CPU_MAX
}

// PROCESS_FINISH_CPU
{
Set CPU To not occupied
Determine if process will exit system or not based on QUIT_PROB
    if quit, create new event PROCESS_EXIT_SYSTEM with time = current system time
    if not quit: check if disk1 or disk2 is currently not occupied
        If either one is free, create new event
        PROCESS_ARRIVE_DISK1 or PROCESS_ARRIVE_DISK_2
        and set the disk to OCCUPIED

        Otherwise, place process on one of the two disk queues (go to the one that is smaller)

If CPU Queue is non-empty
    pull process off of queue and create new event PROCESS_ARRIVE_CPU
    set CPU to occupied
}

// **pending**
cpu_exit(oldEvent, eventQueue){
    // process exit
    // create new PROCESS_EXIT event
    if (random double between 0 and 1 < QUIT_PROB){
        create newEvent of type PROCESS_EXIT
        assign process from oldEvent to newEvent
        assign newEvent time to oldEvent time
        EventQueue.push(newEvent)

    // process not exit
    } else {

    }
}

// PROCESS_ARRIVE_DISK
Create new event PROCESS_FINISH_DISK
    event time = current system time + random interval between
    DISK_MIN and DISK_MAX (could be different for disk 1 and disk 2!)
}

// PROCESS_FINISH_DISK
Set Disk to not occupied
If CPU occupied or Queue is non-empty
    put process on CPU queue
If CPU is not occupied AND queue is empty
    create new event PROCESS_ARRIVE_CPU
        event time = current system time
        set CPU to occupied
If Disk Queue is non-empty
    pull process off of queue and create new event PROCESS_ARRIVE_DISK_?
    set disk to occupied
}

// SIMULATION_FINISH
Cleanup!
Finish writing to log file
Write final statistics to STAT file
close all file handles
free up any alloc’d memory left
print a nice message saying goodbye, maybe :)

// random generator
int indexTur = rand() % (R_MAX + 1) + R_MIN;    // generate random index between R_MIN and R_MAX

*/
// void cpu_enter (){
//     /*
//     events 
//     time
//     a description
//     a set of rules
//     */
// }
// 

// bool Time :: equals(const Time &otherTime)
// {
//      if(hour == otherTime.hour
//           && minute == otherTime.minute
//           && second == otherTime.second)
//           return true;
//      else
//           return false;
// }
