# Khai_Nguyen_Linux_Shell
Project 2: Linux Shell

## Introduction
This is a model of a Linux shell that has basic builtin commands and the functionality to execute external commands

## Design
The shell program is broken down into:
- main.c
- function.c
- header.h
- Makefile

## Guide
### For collaborators
Check out file "Program_Description.odt"

### For users (mainly)

#### Requirements
- Understanding of system_calls fork(), exec(), wait(), dup(). Familiarity with linux "man" page
- Knowledge of file descriptors, file access to build I/O redirection, pip

#### Usage guide 
List of built-ins includes:
- "cd" - change directory
```bash
$ cd ..
$ cd [folder]
```

- "clr" - clear screen
```bash
$ clr
```

- "dir" - list files and directories 
```bash
$ dir
$ dir [folder]
$ dir [folder] > out.txt
$ dir [folder] >> out.txt
```

- "environ" - list enviroment variables
```bash
$ environ 
$ environ > out.txt
$ environ >> out.txt
```
- "echo" - prints argument of "echo" back to console
```bash
$ echo [message]
$ echo [message] > out.txt
```

- "help" - display usage guide
```bash
$ help
$ help > out.txt
```

- "pause" - pause the shell till user press enter
```bash
$ pause
```

- "exit" - exit the shell
```bash
$ exit
```

The shell can also accomodate external commands
```bash
$ ./hello
$ ./take_hello
$ ./hello | ./take_hello
```
# Contributors
Khai Nguyen: khainguyen@temple.edu

