// Khai Nguyen
// Filename: main.cpp

#include "header.h"


    queue <process> CPU;
    queue <process> disk_1;
    queue <process> disk_2;
    priority_queue <event, vector<event>, compareTime> eventQueue;
    bool CPU_busy = false;
    bool disk_1_busy = true;
    bool disk_2_busy = true;
    long processID = 0;

int main(){
    srand(time(NULL));

    cout << "CPU_busy is : "<< CPU_busy << endl; 
    cout << "disk_1_busy is : "<< disk_1_busy << endl;
    cout << "disk_2_busy is : "<< disk_2_busy << endl;

    process initial_p = {0, "start"};
    process final_p = {99999, "end"};

    event initial_e = {PROCESS_ARRIVAL, INIT_TIME, initial_p};
    event finish_e = {SIMULATION_FINISH, FIN_TIME, final_p};
    eventQueue.push(initial_e);
    eventQueue.push(finish_e);
    
    cout << "The eventQueue is : "; 
    showpq(eventQueue);
/*------------------------*/

bool running = true;

while (!eventQueue.empty() && running == true) {
    event currentEvent = eventQueue.top();
    cout << "Current event is: " << currentEvent.eventType << endl;
    eventQueue.pop();
    // add a function - write event into log file (At time [t] [process ID] [event description])

    switch(currentEvent.eventType){  // switch case to determine how to handle event
        case PROCESS_ARRIVAL: 
            handle_process_arrival(currentEvent, eventQueue);
            break;
        case PROCESS_EXIT: // just break (already pop() the event & process above)
            break;
        case PROCESS_ARRIVE_CPU: 
            handle_process_arrive_cpu(currentEvent, eventQueue);
            break;
        case PROCESS_FINISH_CPU: 
            handle_process_finish_cpu(currentEvent, eventQueue);
            break;
        case DISK1_ARRIVAL: 
            handle_process_arrive_disk_1(currentEvent, eventQueue);
            break;
        case DISK2_ARRIVAL: 
            handle_process_arrive_disk_2(currentEvent, eventQueue);
            break;
        case DISK1_FINISH: 
            handle_disk_1_finish(currentEvent, eventQueue);
            break;
        case DISK2_FINISH: 
            handle_disk_2_finish(currentEvent, eventQueue);
            break;
        case SIMULATION_FINISH: running = !running;
            break;
    }

    cout << "The CPU queue is : "; 
    showq(CPU); 
    
    // cout << "The disk1 queue is : "; 
    // showq(disk_1); 

    // cout << "The disk2 queue is : "; 
    // showq(disk_2); 

    cout << "The eventQueue after main is : "; 
    showpq(eventQueue); 
    
    int i = 0;
    cout << "Please enter an integer value: ";
    cin >> i;
    cout << "The value you entered is " << i << endl;

    // update CPU and Disk queues, creates new events where appropriate
    // update_CPU();
    // update_disks();
    
    // printQ(eventQ);

    // GET a user input & print stats//user debug before moving on, instead of running everything all@once
}

/*
Edge case:
both disks queues are full
both disj queues are empty

*/
    return 0;
}




/*



events // event types as an enum -- a set of functions
time
a description
a set of rules
enum event { red, green, blue };
event r = red;
switch(r)
{
    case red  : std::cout << "red\n";   break;
    case green: std::cout << "green\n"; break;
    case blue : std::cout << "blue\n";  break;
}

Functions:
An entry mechanism, by which processes can enter the system
An exit mechanism, by which processes can exit the system

a set of rules for events
if CPU Queue is Empty 
    execute process 422 on CPU
else
    place process 422 on CPU queue


how torepresent your data:


main loop{
    (1) pluck anevent of the event queue, 
    (2) pick the appropriate event handlerfunction and call it (best handled through a switch case)
    (3)continue this process indefinitely untill you hit the end of thesimulation (or if you get a segfault ;) )
}
Note that before entering themain loop, you’ll want to add a special event to the event queue,which represents the simulation finishing, with a time set toFIN_TIME. You’ll probably want to give that event it’s own specialtype, too.
*/
