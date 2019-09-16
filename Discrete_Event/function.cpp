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
		/*cout << "The eventQueue before adding is : ";
		showpq(eventQ);*/
		event newEvent = { PROCESS_ARRIVE_CPU, oldE.etime, oldE.event_p };
		eventQ.push(newEvent);
		/*cout << "The eventQueue after adding is : ";
		showpq(eventQ);
		*/
		CPU_busy = true;
		newEvent.event_p.status = "arrive at cpu";
	}

	// New processes ONLY generated here
	int eventTime = oldE.etime + randomTime(ARRIVE_MIN, ARRIVE_MAX);
	processID++;
	process arrivalProcess = { processID, "arrive in system" };
	event arrivalEvent = { PROCESS_ARRIVAL, eventTime, arrivalProcess };
	eventQ.push(arrivalEvent);
	eventQueue = eventQ;
}

// PROCESS_ARRIVE_CPU
// pick event ARRIVE_CPU --> add time --> create FINISH_CPU
void handle_process_arrive_cpu(event oldE, priority_queue <event, vector<event>, compareTime> eventQ) {
	int eventTime = oldE.etime + randomTime(CPU_MIN, CPU_MAX);
	event finish_CPU_Event = { PROCESS_FINISH_CPU, eventTime, oldE.event_p };
	finish_CPU_Event.event_p.status = "finish cpu";
	eventQ.push(finish_CPU_Event);
	//cout << "The eventQueue in CPU_arrive is : ";
	//showpq(eventQ);
	eventQueue = eventQ;
}

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
	int newEventTime = oldEvent.etime + randomTime(DISK1_MIN, DISK1_MAX);
	event newDiskEvent = { DISK1_FINISH, newEventTime, oldEvent.event_p };
	newDiskEvent.event_p.status = "finish at disk1";
	eventQ.push(newDiskEvent);
	eventQueue = eventQ;
}

// PROCESS_ARRIVE_DISK_2
// grab disk_arrival event --> add time -> create disk_finish 
void handle_process_arrive_disk_2(event oldEvent, priority_queue <event, vector<event>, compareTime>eventQ) {
	int newEventTime = oldEvent.etime + randomTime(DISK2_MIN, DISK2_MAX);
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

void print_log(event currentE) {
	fstream file;
	file.open("log.txt", ios::out);
	string line;

	// Backup streambuffers of  cout 
	streambuf* stream_buffer_cout = cout.rdbuf();
	streambuf* stream_buffer_cin = cin.rdbuf();

	// Get the streambuffer of the file 
	streambuf* stream_buffer_file = file.rdbuf();

	// Redirect cout to file 
	cout.rdbuf(stream_buffer_file);

	cout << "At time " << currentE.etime << " process " << currentE.event_p.id << " " << currentE.event_p.status << endl;

	// Redirect cout back to screen 
	cout.rdbuf(stream_buffer_cout);
	cout << "At time " << currentE.etime << " process " << currentE.event_p.id << " " << currentE.event_p.status << endl;

	file.close();
}

double randomDoub() {
	return ((double)rand() / (double)RAND_MAX);
}

int randomTime(int tMin, int tMax) {
	return (rand() % (tMax - tMin + 1)) + tMin;
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

// process myQueuePop(priority_queue <event, vector<event>, compareTime> eventQueue){
//     return eventQueue.pop();
//     // findmax(queue.size); // to calculate STAT file (queue avg size // max & avg time CPU in use // throughput = number_of_job_handles/)

// }
