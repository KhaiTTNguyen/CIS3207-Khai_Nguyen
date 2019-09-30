// Khai Nguyen
// Filename: main.cpp

#include "header.h"

queue <process> CPU;
queue <process> disk_1;
queue <process> disk_2;
priority_queue <event, vector<event>, compareTime> eventQueue;
bool CPU_busy;
bool disk_1_busy;
bool disk_2_busy;
long processID;

int component_max_size[4];
double use_time[3];
long thoughput[3];
queue <int> CPU_size;		// 0
queue <int> disk_1_size;	// 1
queue <int> disk_2_size;	// 2

/*-----MAIN FILE STARTS HEREH-----*/

int main() {
	srand(time(NULL));

	CPU;
	disk_1;
	disk_2;
	eventQueue;
	CPU_busy = false;
	disk_1_busy = false;
	disk_2_busy = false;
	processID = 0;
	
	component_max_size;
	use_time;
	thoughput;


	/*cout << "CPU_busy is : " << CPU_busy << endl;
	cout << "disk_1_busy is : " << disk_1_busy << endl;
	cout << "disk_2_busy is : " << disk_2_busy << endl;*/

	process initial_p = { 0, "start" };
	process final_p = { 99999, "end" };

	event initial_e = { PROCESS_ARRIVAL, INIT_TIME, initial_p };
	event finish_e = { SIMULATION_FINISH, FIN_TIME, final_p };
	eventQueue.push(initial_e);
	eventQueue.push(finish_e);

	cout << "The eventQueue is : ";
	showpq(eventQueue);
	/*------------------------*/

	bool running = true;
	
	fstream file_str;
	fstream file_str_stat;

	file_str.open("log.txt", ios::out);
	file_str_stat.open("stat.txt", ios::out);

	while (!eventQueue.empty() && running == true) {
		event currentEvent = eventQueue.top();
		cout << "Current event is: " << currentEvent.eventType << endl;
		eventQueue.pop();

		// add a function - write event into log file (At time [t] [process ID] [event description])
		print_log(currentEvent, file_str);

		switch (currentEvent.eventType) {  // switch case to determine how to handle event
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
	}
	print_stats(file_str_stat);
	
	file_str.close();
	file_str_stat.close();
	return 0;

}