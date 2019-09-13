// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"


double randomDoub(){
    double q = ((double)rand() / RAND_MAX);
    return Q_MIN + q * (Q_MAX - Q_MIN);
}

int randomTime(int tMin, int tMax){
    return rand() % (tMax + 1) + tMin;
}

int getfavoritenumber(void)
{
    return 3;
}

void cpu_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    // process exit
    CPU_busy = false;
    double quit_prob = randomDoub();
    cout << "Quit prob is: "<< quit_prob << endl;
    if (quit_prob < QUIT_PROB){
        // time = currentTime OR oldEvent.etime
        event newEvent {PROCESS_EXIT, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
    // process goes to DISK1 or DISK2
    } else if (disk_1.empty() && disk_1_busy == false) {       
        event newEvent {DISK1_ARRIVAL, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
        disk_1_busy = true;
    } else if (disk_2.empty() && disk_2_busy == false) {        
        event newEvent {DISK2_ARRIVAL, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
        disk_2_busy = true;
    } else {
        if (disk_1.size() < disk_2.size()){
            disk_1.push(oldEvent.event_p);
        } else {
            disk_2.push(oldEvent.event_p);
        }
    }

    if (!CPU.empty()){
        process newCPUProcess = CPU.pop();
        currentTime = currentTime + randomTime(CPU_MIN, CPU_MAX);
        event cpuArrivalEvent = {CPU_ARRIVAL, currentTime, newCPUProcess};
        // enQueue?
        //adding 
        CPU_busy = true;
    }
}


// PROCESS_ARRIVAL
void handle_process_arrival(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    if (!CPU.empty() || CPU_busy == true){      // CPU_busy == false
        CPU.push(oldEvent.event_p);
    } 

    if (CPU.empty() && CPU_busy == false){
        event newEvent {PROCESS_ARRIVAL, currentTime, oldEvent.event_p};
        // put on eventQueue?
    } 

    currentTime = currentTime + randomTime(ARRIVE_MIN, ARRIVE_MAX);
    process arrivalProcess {processCount, "arrive in system", currentTime}
    processCount++;
    event arrivalEvent {PROCESS_ARRIVAL, currentTime, arrivalProcess};
    

    // print to log file
}


// // PROCESS_ARRIVE_CPU
// void cpu_enter(){
//     currentTime = currentTime + randomTime(CPU_MIN, CPU_MAX);
//     // process arrivalProcess {processCount, "arrive in system", currentTime}
//     // processCount++;
//     event finishCPUEvent {CPU_ARRIVAL, currentTime, // arrivalProcess};
    
//     event time = current system time + random interval between CPU_MIN and CPU_MAX
// eventQueue.pop(event, EventQueue);
// }


/*--------Supplement functions----------*/
void showpq(priority_queue <event, vector<event>, compareTime> eventQueue) 
{ 
    priority_queue <event, vector<event>, compareTime> g = eventQueue; 
    while (!g.empty()) 
    { 
        cout << '\t' << g.top().etime; 
        g.pop(); 
    } 
    cout << '\n'; 
} 


void showq(queue <process> gq) 
{ 
    queue <process> g = gq; 
    while (!g.empty()) 
    { 
        cout << '\t' << g.front().ptime; 
        g.pop(); 
    } 
    cout << '\n'; 
} 


// PROCESS_FINISH_DISK --- MAKE SEPARATE FOR 2 DISKS
void handle_disk_1_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    disk_1_busy = false;
    if (CPU_busy == true || !CPU.empty()){
        CPU.push(oldEvent.event_p);
    }

    if (CPU_busy == false && CPU.empty()){
        event cpuArriveEvent = {CPU_ARRIVAL, currentTime, oldEvent.event_p};
        CPU_busy = true;
    }
    
    if (!disk_1.empty()){

    }

If CPU is not occupied AND queue is empty
    create new event PROCESS_ARRIVE_CPU
        event time = current system time
        set CPU to occupied
If Disk Queue is non-empty
    pull process off of queue and create new event PROCESS_ARRIVE_DISK_?
    set disk to occupied
}


// SEED rand only ONCE


// process myQueuePop(priority_queue <event, vector<event>, compareTime> eventQueue){
//     return eventQueue.pop();
//     // findmax(queue.size); // to calculate STAT file (queue avg size // max & avg time CPU in use // throughput = number_of_job_handles/)
    
// }


/*

// PROCESS_FINISH_CPU
void {
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


// PROCESS_ARRIVE_DISK
Create new event PROCESS_FINISH_DISK
    event time = current system time + random interval between
    DISK_MIN and DISK_MAX (could be different for disk 1 and disk 2!)
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
