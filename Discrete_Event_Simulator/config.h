// Khai Nguyen
// Filename: config.h
// Usage to declare constants

#ifndef CONFIG_H
#define CONFIG_H

// Tell compiler to include a header file only once
#pragma once

// Define constants
#define SEED  1122 // a number that we will feed into our random numbergenerator.
#define INIT_TIME 0
#define FIN_TIME 10000

#define ARRIVE_MIN 20
#define ARRIVE_MAX 80
// new processes willenter the system in a random interval between these twoconstants.

#define QUIT_PROB 0.2

// time a process spends on the CPU
#define CPU_MIN 5
#define CPU_MAX 50

#define DISK1_MIN 50
#define DISK1_MAX 200

#define DISK2_MIN 50
#define DISK2_MAX 200

#endif
