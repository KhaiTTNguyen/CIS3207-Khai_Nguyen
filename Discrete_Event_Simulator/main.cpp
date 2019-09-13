// Khai Nguyen
// Filename: main.cpp

#include "header.h"

queue <process> CPU;
queue <process> disk_1;
queue <process> disk_2;
bool CPU_busy = false;
bool disk_1_busy = false;
bool disk_2_busy = false;

int main()
{
    srand(time(NULL));

    double q = ((double)rand() / RAND_MAX);
    double real_q = Q_MIN + q * (Q_MAX - Q_MIN);
    
    cout << "Q is: " << q << endl;

    priority_queue <event, vector<event>, compareTime> eventQueue;

    process A1 { 1, "running", 0.2 };
    process A2 { 2, "starting", 0.9 };
    process A3 { 3, "terminating", 0.4 };
    // process A4;

    event B1 {PROCESS_ARRIVAL, 0.5, A1};
    event B2 {DISK1_FINISH, 0.2, A1};
    event B3 {DISK2_FINISH, 0.57, A1};
    // event B4;

    CPU.push(A1);
    CPU.push(A2);
    CPU.push(A3);
    CPU.push(A2);
    CPU.push(A2);
    //CPU.push(A4);
    //CPU.push(A4);
    
    cout << "The CPU queue is : "; 
    showq(CPU); 
    
    eventQueue.push(B1);
    eventQueue.push(B2);
    eventQueue.push(B1);
    eventQueue.push(B3);
    eventQueue.push(B1);
    //eventQueue.push(B4);
    //eventQueue.push(B4);

    cout << "The eventQueue is : "; 
    showpq(eventQueue); 

    cout<< "A1.status is: " << A1.status << endl;
    cout<< getfavoritenumber() << endl;
    cout<< "Finish time is " << FIN_TIME << endl;
    cout<< "Quit prob is " << QUIT_PROB << endl;

    enum event_tag { red, green, blue };
    event_tag r = blue;

    switch(r)
    {
        case red  : std::cout << "Color is " << r << endl;   break;
        case green: std::cout << "Color is " << r << endl; break;
        case blue : std::cout << "Color is " << r << endl;  break;
    }

/*------------------------*/
double currentTime;
cpu_finish(B1, eventQueue);
// while (!eventQueue.empty()){ // (&& running -- til hit SIMULATION_FINISH event)
//     currentTime = eventQueue.top().etime; // update currentTimeof simulation
//     cout << "currentTime is " << currentTime << endl;

//     event currentEvent = eventQueue.top();
//     eventQueue.pop();
// //     // add a function - write event into log file (At time [t] [process ID] [event description])
//    switch(currentEvent.eventType){  // switch case to determine how to handle event
//         case PROCESS_ARRIVAL: handle_process_arrival(event, eventQueue);
//             break;
//         case CPU_ARRIVAL: eventQueue.pop(event, EventQueue);
//             break;
//         case CPU_FINISH: cpu_finish(currentEvent, eventQueue);
//             break;
//         case DISK1_ARRIVAL: eventQueue.pop();
//             break;
//         case DISK2_ARRIVAL:eventQueue.pop();
//             break;
//         case DISK1_FINISH: handle_disk_finish();
//             break;
//         case DISK2_FINISH: handle_disk_finish();
//             break;
//         case SIMULATION_FINISH: running = !running;
//             break;
//     }
//     // update CPU and Disk queues, creates new events where appropriate
//     update_CPU();
//     update_disks();

//     // GET a user input & print stats//user debug before moving on, instead of running everything all@once
// }

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
