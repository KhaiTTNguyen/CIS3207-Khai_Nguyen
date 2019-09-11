// Khai Nguyen
// Filename: event.h
// Usage to declare events (enum)

// header guards
#ifndef MYENUM_H
#define MYENUM_H

enum EVENT { 
    PROCESS_ARRIVAL,
    PROCESS_ARRIVE_CPU,
    PROCESS_FINISH_CPU,
    PROCESS_EXIT_SYSTEM,
    PROCESS_ARRIVE_DISK1,
    PROCESS_ARRIVE_DISK2,
    PROCESS_FINISH_DISK1,
    PROCESS_FINISH_DISK2,
    SIMULATION_FINISH
};

#endif