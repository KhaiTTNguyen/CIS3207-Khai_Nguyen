# Khai_Nguyen_Discrete_Event_Simulator
Project 1 - Giorgio's Discrete Event Simulator

## Introduction
This program demonstrates a simulation of how processes come into the CPU and be processed on disks, with the probability that determines the time they exit the system.

The logs and statistics of the simulation is then recorded for futher understanding of the system's behaviour throughout a provided time frame

## Requirements
- Knowledge of processes 
- Familiarity with C/C++

## Configuration
Configuration constants are included in "config.h"

## Design
Events: represented by structure with eventType, event time, and process attached to that event

Process: created with unique ID

Workflow: is maintained in the specified time frame by the following fuctions that:

- handle_process_arrival
- handle_process_exit
- handle_process_arrive_cpu
- handle_process_finish_cpu
- handle_process_arrive_disk_1
- handle_process_arrive_disk_2
- handle_disk_1_finish
- handle_disk_2_finish
- handle_SIMULATION_FINISH

Test cases are carried out and recorded in the run.txt file.
Logs and stats of the program are recorded in log.txt and stat.txt

# Contributors
Khai Nguyen: khainguyen@temple.edu
