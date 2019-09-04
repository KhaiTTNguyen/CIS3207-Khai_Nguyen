// Khai Nguyen
// Filename: main.cpp

#include "config.h"
#include "header.h"

int main()
{
    // Declare queues in main 
    queue <process> CPU;
    queue <process> disk_1;
    queue <process> disk_2;

    process A1 { 1, "running", 0.2 };
    CPU.push(A1);
    cout<< "A1.status is: " << A1.status << endl;
    cout<< getfavoritenumber() << endl;
    cout<< "Finish time is " << FIN_TIME << endl;
    cout<< "Quit prob is " << QUIT_PROB << endl;

    enum event_tag { red, green, blue };
    event_tag r = blue;

    switch(r)
    {
        case red  : std::cout << r << endl;   break;
        case green: std::cout << r << endl; break;
        case blue : std::cout << r << endl;  break;
    }

/*
while (!eventQueue.empty() && running){ // main simulation loop (runs until hit SIMULATION_FINISH event)
    currentTime= eventQueue.top().time; // update currentTimeof simulation
    switch(eventQueue.top().eventType){  // switch case to determine how to handle event
        case PROCESS_ARRIVAL: handle_process_arrival();
        case CPU_ENTER: eventQueue.pop();
        case PROCESS_FINISH: handle_process_finish);
        case PROCESS_EXIT: eventQueue.pop();
        case DISK1_ARRIVAL: eventQueue.pop();
        case DISK2_ARRIVAL:eventQueue.pop();
        case DISK1_FINISH: handle_disk_finish();
        case DISK2_FINISH: handle_disk_finish();
        case SIMULATION_FINISH: running = !running;
    }
    // update CPU and Disk queues, creates new events where appropriate
    update_CPU();
    update_disks();
}

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
