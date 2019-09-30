// Khai Nguyen
// Filename: event.h
// Usage to declare events (enum)

// header guards
#ifndef MYENUM_H
#define MYENUM_H

enum EVENT {
	PROCESS_ARRIVAL,        // 0
	PROCESS_ARRIVE_CPU,            // 1    
	PROCESS_FINISH_CPU,             // 2
	PROCESS_EXIT,           // 3
	DISK1_ARRIVAL,          // 4
	DISK2_ARRIVAL,          // 5
	DISK1_FINISH,           // 6
	DISK2_FINISH,           // 7
	SIMULATION_FINISH       // 8
};

#endif