# Khai_Nguyen_Network_Spell_Check
Project 3: Network_Spell_Check

## Introduction
This is a basic spell checker that can check a word input whether it belongs to a dictionary via a network.

## Design
The spell checker program is broken into 
- main.cpp
- function.cpp
- header.h
- Makefile

## Guide
### For collaborators
Check out file "Program_Description.odt"

### For users (mainly)

#### Requirements
- Understanding of system_calls read(), write(). Familiarity with linux "man" page
- Knowledge of file descriptors, and socket programming
- Knowledge of setting up a network with client & server

#### Usage guide 
- Boot up the "server". User can specify the dictionay file they want to work with

```bash
$ ./myserver 
$ ./myserver 9000
$ ./myserver alt-dictionary.txt
$ ./myserver 9000 alt-dictionary.txt
bind done
Waiting for incoming connections...
```

Then, user has to open another terminal to act as a client and test on their own server machine. Try the loop-back IP address:
 
```bash
$ nc 127.0.0.1 8888
```

Then, from the client terminal, the user can test their dictionary with "words" input
```bash
As
A OK
AOL
AOL OK
frog
frog OK
dog
dog OK
```
# Contributors
Khai Nguyen: khainguyen@temple.edu
