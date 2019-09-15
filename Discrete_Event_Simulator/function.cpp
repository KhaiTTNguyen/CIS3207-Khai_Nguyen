// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

// PROCESS_ARRIVAL
// if event = PROCESS_ARRIVAL --> put on CPU, create another event with PROCESS_ARRIVAL
void handle_process_arrival(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    if (!CPU.empty() || CPU_busy == true){ 
        CPU.push(oldEvent.event_p);
    } 

    if (CPU.empty() && CPU_busy == false){
        event newEvent = {PROCESS_ARRIVAL, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
        cout << "The eventQueue in handle_arrive is : "; 
        showpq(eventQueue);
        CPU_busy = true;
    } 
    
    // New processes ONLY generated here
    int eventTime = oldEvent.etime + randomTime(ARRIVE_MIN, ARRIVE_MAX);
    processID++;
    process arrivalProcess = {processID, "arrive in system"};
    event arrivalEvent = {PROCESS_ARRIVAL, eventTime, arrivalProcess};
    eventQueue.push(arrivalEvent);
}

// PROCESS_ARRIVE_CPU
// pick event ARRIVE_CPU --> add time --> create FINISH_CPU
void handle_process_arrive_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    int eventTime = oldEvent.etime + randomTime(CPU_MIN, CPU_MAX);
    event finish_CPU_Event = {PROCESS_FINISH_CPU, eventTime, oldEvent.event_p};
    eventQueue.push(finish_CPU_Event);
}

void handle_process_finish_cpu(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    // process exit
    CPU_busy = false;
    double quit_prob = randomDoub();
    cout << "Quit prob is: "<< quit_prob << endl;

    if (quit_prob < QUIT_PROB){
        event newEvent = {PROCESS_EXIT, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
    // process goes to DISK1 or DISK2
    } else if (disk_1.empty() && disk_1_busy == false) {       
        event newEvent = {DISK1_ARRIVAL, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
        disk_1_busy = true;
    } else if (disk_2.empty() && disk_2_busy == false) {        
        event newEvent = {DISK2_ARRIVAL, oldEvent.etime, oldEvent.event_p};
        eventQueue.push(newEvent);
        disk_2_busy = true;
    } else {
        if (disk_1.size() < disk_2.size()){
            disk_1.push(oldEvent.event_p);
        } else {
            disk_2.push(oldEvent.event_p);
        }
    }

    // put new process onto CPU
    if (!CPU.empty()){
        process newCPUProcess = CPU.front();
        CPU.pop();
        event cpuArrivalEvent = {PROCESS_ARRIVE_CPU, oldEvent.etime, newCPUProcess};
        eventQueue.push(cpuArrivalEvent);
        CPU_busy = true;
    }
}


// PROCESS_ARRIVE_DISK_1
// grab disk_arrival event --> add time -> create disk_finish 
void handle_process_arrive_disk_1(event oldEvent, priority_queue <event, vector<event>, compareTime>eventQueue){
    int newEventTime = oldEvent.etime + randomTime(DISK1_MIN, DISK1_MAX);
    event newDiskEvent = {DISK1_FINISH, newEventTime, oldEvent.event_p};
}

// PROCESS_ARRIVE_DISK_2
// grab disk_arrival event --> add time -> create disk_finish 
void handle_process_arrive_disk_2(event oldEvent, priority_queue <event, vector<event>, compareTime>eventQueue){
    int newEventTime = oldEvent.etime + randomTime(DISK2_MIN, DISK2_MAX);
    event newDiskEvent = {DISK2_FINISH, newEventTime, oldEvent.event_p};
}

// PROCESS_FINISH_DISK --- MAKE SEPARATE FOR 2 DISKS
void handle_disk_1_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    disk_1_busy = false;
    if (CPU_busy == true || CPU.empty() == false){
        CPU.push(oldEvent.event_p);
    }
    if (CPU_busy == false && CPU.empty()){
        event cpuArriveEvent = {PROCESS_ARRIVE_CPU, oldEvent.etime, oldEvent.event_p};
        CPU_busy = true;
    }
    
    // pull another process to disk
    if (disk_1.empty() == false){
        event diskArrive = {DISK1_ARRIVAL, oldEvent.etime, disk_1.front()};
        eventQueue.push(diskArrive);
        disk_1.pop();
        disk_1_busy = true;
    }
}

void handle_disk_2_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQueue){
    disk_2_busy = false;
    if (CPU_busy == true || CPU.empty() == false){
        CPU.push(oldEvent.event_p);
    }
    if (CPU_busy == false && CPU.empty()){
        event cpuArriveEvent = {PROCESS_ARRIVE_CPU, oldEvent.etime, oldEvent.event_p};
        CPU_busy = true;
    }
    
    // pull another process to disk
    if (disk_2.empty() == false){
        event diskArrive = {DISK2_ARRIVAL, oldEvent.etime, disk_2.front()};
        eventQueue.push(diskArrive);
        disk_2.pop();
        disk_2_busy = true;
    }
}







/*--------Supplement functions----------*/
double randomDoub(){
    return ((double)rand()/(double)RAND_MAX);
}

int randomTime(int tMin, int tMax){
    return (rand() % (tMax - tMin + 1)) + tMin;
}

void showpq(priority_queue <event, vector<event>, compareTime> eventQueue) { 
    priority_queue <event, vector<event>, compareTime> g = eventQueue; 
    while (!g.empty()) 
    { 
        cout << '\t' << g.top().etime; 
        g.pop(); 
    } 
    cout << '\n'; 
} 


void showq(queue <process> gq) { 
    queue <process> g = gq; 
    while (!g.empty()) 
    { 
        cout << '\t' << g.front().id  << ":" << g.front().status; 
        g.pop(); 
    } 
    cout << '\n'; 
} 

// process myQueuePop(priority_queue <event, vector<event>, compareTime> eventQueue){
//     return eventQueue.pop();
//     // findmax(queue.size); // to calculate STAT file (queue avg size // max & avg time CPU in use // throughput = number_of_job_handles/)
    
// }
