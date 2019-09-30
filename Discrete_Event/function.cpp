// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"


// PROCESS_ARRIVAL
// if event = PROCESS_ARRIVAL --> put on CPU, create another event with PROCESS_ARRIVAL
void handle_process_arrival(event oldE, priority_queue <event, vector<event>, compareTime> eventQ) {
	/*cout << "The eventQueue in handle_arrive is : ";
	showpq(eventQ);*/
	if (!CPU.empty() || CPU_busy == true) {
		CPU.push(oldE.event_p);
		oldE.event_p.status = "on CPU queue";
	}

	if (CPU.empty() && CPU_busy == false) {
		event newEvent = { PROCESS_ARRIVE_CPU, oldE.etime, oldE.event_p };
		eventQ.push(newEvent);
		CPU_busy = true;
		newEvent.event_p.status = "arrive at cpu";
	}

	// New processes ONLY generated here
	double eventTime = oldE.etime + randomTime(ARRIVE_MIN, ARRIVE_MAX);
	processID++;
	process arrivalProcess = { processID, "arrive in system" };
	event arrivalEvent = { PROCESS_ARRIVAL, eventTime, arrivalProcess };
	eventQ.push(arrivalEvent);
	eventQueue = eventQ;

	// stat record
	
}


// PROCESS_ARRIVE_CPU
// pick event ARRIVE_CPU --> add time --> create FINISH_CPU
void handle_process_arrive_cpu(event oldE, priority_queue <event, vector<event>, compareTime> eventQ) {
	double eventTime = oldE.etime + randomTime(CPU_MIN, CPU_MAX);

	// record stats
	record_time(0, eventTime - oldE.etime);
	record_size_CPU();
	record_throughput(0);

	event finish_CPU_Event = { PROCESS_FINISH_CPU, eventTime, oldE.event_p };
	finish_CPU_Event.event_p.status = "finish cpu";
	eventQ.push(finish_CPU_Event);
	// cout << "The eventQueue in CPU_arrive is : ";
	// showpq(eventQ);
	eventQueue = eventQ;
}
/*
handle_process_finish_cpu:
input: event, priority_queue
output: void
*/
void handle_process_finish_cpu(event oldE, priority_queue <event, vector<event>, compareTime> eventQ) {
	// process exit
	CPU_busy = false;
	double quit_prob = randomDoub();
	cout << "Quit prob is: " << quit_prob << endl;

	if (quit_prob < QUIT_PROB) {
		event newExitEvent = { PROCESS_EXIT, oldE.etime, oldE.event_p };
		newExitEvent.event_p.status = "exit";
		eventQ.push(newExitEvent);
		eventQueue = eventQ;
		// process goes to DISK1 or DISK2
	}
	else if (disk_1.empty() && disk_1_busy == false) {
		event newDisk1Event = { DISK1_ARRIVAL, oldE.etime, oldE.event_p };
		newDisk1Event.event_p.status = "arrive at disk1";
		eventQ.push(newDisk1Event);
		disk_1_busy = true;
		eventQueue = eventQ;
	}
	else if (disk_2.empty() && disk_2_busy == false) {
		event newDisk2Event = { DISK2_ARRIVAL, oldE.etime, oldE.event_p };
		newDisk2Event.event_p.status = "arrive at disk2";
		eventQ.push(newDisk2Event);
		disk_2_busy = true;
		eventQueue = eventQ;
	}
	else {
		if (disk_1.size() < disk_2.size()) {
			oldE.event_p.status = "on disk1 queue";
			disk_1.push(oldE.event_p);
		}
		else {
			oldE.event_p.status = "on disk2 queue";
			disk_2.push(oldE.event_p);
		}
	}

	// put new process onto CPU
	if (!CPU.empty()) {
		process newCPUProcess = CPU.front();
		CPU.pop();
		event cpuArrivalEvent = { PROCESS_ARRIVE_CPU, oldE.etime, newCPUProcess };
		cpuArrivalEvent.event_p.status = "arrive at cpu";
		eventQ.push(cpuArrivalEvent);
		CPU_busy = true;
		eventQueue = eventQ;
	}
}


// PROCESS_ARRIVE_DISK_1
// grab disk_arrival event --> add time -> create disk_finish 
void handle_process_arrive_disk_1(event oldEvent, priority_queue <event, vector<event>, compareTime>eventQ) {
	double newEventTime = oldEvent.etime + randomTime(DISK1_MIN, DISK1_MAX);
	
	record_time(1, newEventTime - oldEvent.etime);
	record_size_disk_1();
	record_throughput(1);

	event newDiskEvent = { DISK1_FINISH, newEventTime, oldEvent.event_p };
	newDiskEvent.event_p.status = "finish at disk1";
	eventQ.push(newDiskEvent);
	eventQueue = eventQ;
}

// PROCESS_ARRIVE_DISK_2
// grab disk_arrival event --> add time -> create disk_finish 
void handle_process_arrive_disk_2(event oldEvent, priority_queue <event, vector<event>, compareTime>eventQ) {
	double newEventTime = oldEvent.etime + randomTime(DISK2_MIN, DISK2_MAX);
	
	// record stats
	record_time(2, newEventTime - oldEvent.etime);
	record_size_disk_2();
	record_throughput(2);

	event newDiskEvent = { DISK2_FINISH, newEventTime, oldEvent.event_p };
	newDiskEvent.event_p.status = "finish at disk2";
	eventQ.push(newDiskEvent);
	eventQueue = eventQ;
}

// PROCESS_FINISH_DISK --- MAKE SEPARATE FOR 2 DISKS
void handle_disk_1_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQ) {
	disk_1_busy = false;
	if (CPU_busy == true || CPU.empty() == false) {
		CPU.push(oldEvent.event_p);
		oldEvent.event_p.status = "on CPU queue";
	}
	if (CPU_busy == false && CPU.empty()) {
		event cpuArriveEvent = { PROCESS_ARRIVE_CPU, oldEvent.etime, oldEvent.event_p };
		CPU_busy = true;
		cpuArriveEvent.event_p.status = "arrive at cpu";
		eventQ.push(cpuArriveEvent);
		eventQueue = eventQ;
	}

	// pull another process to disk
	if (disk_1.empty() == false) {
		event diskArrive = { DISK1_ARRIVAL, oldEvent.etime, disk_1.front() };
		diskArrive.event_p.status = "arrive at disk1";
		eventQ.push(diskArrive);
		disk_1.pop();
		disk_1_busy = true;
		eventQueue = eventQ;
	}
}

void handle_disk_2_finish(event oldEvent, priority_queue <event, vector<event>, compareTime> eventQ) {
	disk_2_busy = false;
	if (CPU_busy == true || CPU.empty() == false) {
		CPU.push(oldEvent.event_p);
		oldEvent.event_p.status = "on CPU queue";
	}
	if (CPU_busy == false && CPU.empty()) {
		event cpuArriveEvent = { PROCESS_ARRIVE_CPU, oldEvent.etime, oldEvent.event_p };
		cpuArriveEvent.event_p.status = "arrive at cpu";
		CPU_busy = true;
		eventQ.push(cpuArriveEvent);
		eventQueue = eventQ;
	}

	// pull another process to disk
	if (disk_2.empty() == false) {
		event diskArrive = { DISK2_ARRIVAL, oldEvent.etime, disk_2.front() };
		diskArrive.event_p.status = "arrive at disk2";
		eventQ.push(diskArrive);
		disk_2.pop();
		disk_2_busy = true;
		eventQueue = eventQ;
	}
}




/*--------Supplement functions----------*/
double randomDoub() {
	return ((double)rand() / (double)RAND_MAX);
}

double randomTime(int tMin, int tMax) {
	return (double)(rand() % (tMax - tMin + 1)) + tMin;
}

void showpq(priority_queue <event, vector<event>, compareTime> eventQ) {
	priority_queue <event, vector<event>, compareTime> g = eventQ;
	while (!g.empty())
	{
		cout << '\t' << g.top().eventType << " with time " << g.top().etime;
		g.pop();
	}
	cout << '\n';
}


void showq(queue <process> gq) {
	queue <process> g = gq;
	while (!g.empty())
	{
		cout << '\t' << g.front().id << ":" << g.front().status;
		g.pop();
	}
	cout << '\n';
}



void record_size_CPU() {
	if (CPU.size() > component_max_size[0]) {
		component_max_size[0] = CPU.size();
	}
	CPU_size.push(CPU.size());
}

void record_size_disk_1() {
	if (disk_1.size() > component_max_size[1]) {
		component_max_size[1] = disk_1.size();
	}
	disk_1_size.push(disk_1.size());
}

void record_size_disk_2() {
	if (disk_2.size() > component_max_size[2]) {
		component_max_size[2] = disk_2.size();
	}
	disk_2_size.push(disk_2.size());
}


void record_time(int component_num, double time_difference) {
	if (component_num == 0) {
		use_time[component_num] += time_difference;
	}

	if (component_num == 1) {
		use_time[component_num] += time_difference;
	}

	if (component_num == 2) {
		use_time[component_num] += time_difference;
	}
}

void record_time_disk_1(double time_difference) {
	use_time[1] += time_difference;
}

void record_time_disk_2(double time_difference) {
	use_time[2] += time_difference;
}


void record_throughput(int component_num) {
	if (component_num == 0) {
		thoughput[component_num]++;
	}

	if (component_num == 1) {
		thoughput[component_num]++;
	}

	if (component_num == 2) {
		thoughput[component_num]++;
	}
}


void print_stats(fstream& file) {
			
	// calculate average size
	double all_CPU_size = 0.0;
	double cpu_size = CPU_size.size();
	while (!CPU_size.empty()) {
		all_CPU_size += CPU_size.front();
		CPU_size.pop();
	}

	double average_size_cpu = all_CPU_size/cpu_size;

	double all_disk1_size = 0.0;
	double d1_size = disk_1_size.size();
	while (!disk_1_size.empty()) {
		all_disk1_size += disk_1_size.front();
		disk_1_size.pop();
	}

	double average_size_disk1 = all_disk1_size / d1_size;

	double all_disk_2_size = 0.0;
	double d2_size = disk_2_size.size();
	while (!disk_2_size.empty()) {
		all_disk_2_size += disk_2_size.front();
		disk_2_size.pop();
	}

	double average_size_disk_2 = all_disk_2_size / d2_size;

	// calculate throughput
	double t_0 = (double) thoughput[0] / use_time[0];
	double t_1 = (double) thoughput[1] / use_time[1];
	double t_2 = (double) thoughput[2] / use_time[2];

	// calculate ultiplization
	double cpu_ulti = use_time[0] / FIN_TIME;
	double disk1_ulti = use_time[1] / FIN_TIME;
	double disk2_ulti = use_time[2] / FIN_TIME;

		string line;

		// Backup streambuffers of  cout 
		streambuf* stream_buffer_cout = cout.rdbuf();
		streambuf* stream_buffer_cin = cin.rdbuf();

		// Get the streambuffer of the file 
		streambuf* stream_buffer_file = file.rdbuf();

		// Redirect cout to file 
		cout.rdbuf(stream_buffer_file);
		cout << "-----------------Queue----------------" << endl;
		cout << "Average size of CPU Queue: " << average_size_cpu << endl;
		cout << "Max size of CPU Queue: " << component_max_size[0] << endl;
		cout << "Average size of Disk1 Queue: " << average_size_disk1 << endl;
		cout << "Max size of Disk2 Queue: " << component_max_size[1] << endl;
		cout << "Average size of Disk2 Queue: " << average_size_disk_2 << endl;
		cout << "Max size of Disk2 Queue: " << component_max_size[2] << endl;

		cout << "-----------------Ultilization----------------" << endl;
		cout << "Ulitilization of CPU: " << cpu_ulti << endl;
		cout << "Ulitilization of Disk 1: " << disk1_ulti << endl;
		cout << "Ulitilization of Disk 2: " << disk2_ulti << endl;
		
		cout << "-----------------Throughput----------------" << endl;
		cout << "Throughput of CPU: " << t_0 << " jobs per time unit" << endl;
		cout << "Throughput of Disk 1: " << t_1 << " jobs per time unit" << endl;
		cout << "Throughput of Disk 2: " << t_2 << " jobs per time unit" << endl;

}



void print_log(event currentE, fstream& file) {
	string line;

	// Backup streambuffers of  cout 
	streambuf* stream_buffer_cout = cout.rdbuf();
	streambuf* stream_buffer_cin = cin.rdbuf();

	// Get the streambuffer of the file 
	streambuf* stream_buffer_file = file.rdbuf();

	// Redirect cout to file 
	cout.rdbuf(stream_buffer_file);

	cout << "At time " << currentE.etime << " process " << currentE.event_p.id << " " << currentE.event_p.status << "\n" << endl;

	// Redirect cout back to screen 
	cout.rdbuf(stream_buffer_cout);
	cout << "At time " << currentE.etime << " process " << currentE.event_p.id << " " << currentE.event_p.status << "\n" << endl;
}
