// Khai Nguyen
// Filename: main.cpp

#include "config.h"
#include "header.h"
using namespace std;

int main()
{
    cout<< getfavoritenumber() << endl;
    cout<< "Finish time is " << FIN_TIME << endl;
    cout<< "Quit prob is " << QUIT_PROB << endl;

    int a = 8;
    a++;
    
    enum event { red, green, blue };
    event r = blue;

    switch(r)
    {
        case red  : std::cout << r << endl;   break;
        case green: std::cout << r << endl; break;
        case blue : std::cout << r << endl;  break;
    }

//     Time t1(10, 50, 59);
//      t1.print();   // 10:50:59
//      Time t2;
//      t2.print(); // 06:39:09
//      t2.setTime(6, 39, 9);
//      t2.print();  // 06:39:09

//      if(t1.equals(t2))
//           cout << "Two objects are equal\n";
//      else
//           cout << "Two objects are not equal\n";


    return 0;
}




/*
Data Structure:
3 Queues � one for the CPU and one for each disk drive
 
Process = struct{
    ID, 
    status, 
    time
}


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
