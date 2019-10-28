// Khai Nguyen
// Filename: main.cpp
// Usage: build main program

#include "header.h"

int main()
{

    vector<string> msg {"Hello", "C", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;


    /*
    // Read dict file into a Set
    */
    // declaring set 
    set<string> word_dict = load_dictionary();
    
    // cout << "\nThe elements in set2 are: "; 
    // for (auto it = word_dict.begin(); it != word_dict.end(); it++){ 
    //     cout << *it << " "; 
    // }

    /*
        initialize thread_spool
        Don’t forget to spawn the logger thread too!
        encapsulate this thread-spawning inside its own function
        // code provided in slide
    */


    /*
        // Initialize network connection
        // (code provided)

        // network connect setup (sit in a while loop)
        // while(1){
        //     accept() - to get a new socket/fd (block main thread while it waits)
        //     Error check socket __DEC32_SUBNORMAL_MIN__
        // }    
    */

   /*
    // Waiting for clients to connect
        // -----infinite loop----- 
    // accept() on the socket connection - get new socket desc
    // error check socket desc
    // put socket desc on connection-queue (CIRCULAR BUFFER - in text book)
    

    // need enqeue( -check if queue full- ) & dedqueue( - check if queue empty- ) --- keep in mind this is Producer/Consumer
    // code in slides
   */

    /*
    // Once clients connect, place the socket descriptor
    // of the given connection on a connection queu

    */

   /*
    1) accept and distribute connection requests from clients, 
    2) construct a log file of all spell check activities.
   */
  return 0;
}


// compile with -lpthread flag
// "target": the ingredients to make "target"
//     how to make "target" uisng ingredients

// netcat ($ nc IP) or telnet to connect to server

// test for:
// deadlocks
// livelocks
// race conditions - multiple threads access the queue - use mutex lock to enforce mutual exclusion

// if queue is empty --> worker thread sleep
// if queue is full --> main thread 
// ---> use "conditional variables" & "signals" to block thread when it not needed (NO SEMAPHORES)

// "conditional variable" -- asynchronous

// --------------------------------------

// client connect server

// client send a word to server

// server check word

// server responds

// repeat 2-4 still client disconnect


// Design:
// main thread 
// 1. initialize/- loads dictionary (C++ set), sit and wait for connections
// 2.  create/spawn other threads -- read Pthread library
// 3. Initialize
// 4. Wait for connection - while loop
// 5. One client connects - create a socket -- fd for network connection
// - put on queue


// load _dict() -- pass using pointer


// ------------------------------
// worker threads 
// - pull those socket off the queue --- use queue_remove()]
// - read work from socketusing read()
// - check word in dictionary
//     if word was found --> write() "OK" to the socket
//     else write() "Mispelled"

// - Add word + status as a string to the log-queue

// Contine read() & write till read() returns -1

// close socket
// ------------------------------


// - "worker threads" receive the words & check in dictionary
// - spool of threads - read from a file - check in dictionary -
//  -----------------------------------------------------
// logger thread 
// - writee down things that happened 
// - take the result as a string

// ---------------------------------------
// spawn a thread()? - use p-thread lib to create (no C++ threads)
// The pthread_create() function starts a new thread in the calling process.
// when you create a thread --> must specify it-s entry point --> function where it starts

// pthread_create(&threads[i], NULL, workerThread (where to start), arguments_structure) != 0)

// pack arguments into a structure -- arguments_structure

// pthread_create(&threads[i], NULL, workerThread, NULL) != 0)
// ---------------------------------------

// ---------------------------------------


// --------------------------------------
// Connection queue - fixed size circular buffer -- how to create? check textbook

/*
In order to guarantee that the call to pthread cond wait is indi-
visible with respect to other instances of pthread cond wait and pthread cond signal, Pthreads
requires that a mutex variable mutex be associated with the condition variable cond, and that a call to
pthread mutex wait must always be protected by that mutex:

Pthread_mutex_lock(&mutex);
Pthread_cond_wait(&cond, &mutex);
Pthread_mutex_unlock(&mutex);
*/

// functions: -- Producer/consumer problem
//     return item add_queue(int socket, int * queue_buffer)
//         pthread mutex_lock(&mutex)
//         //............
           // init by pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//         while (circular_buffer is full){
//             // A thread waits for some program condition associated with the condition variable cond to become true    
//             pthread_cond_wait(&empty, &mutex);  --> have to use pthread_cond_init() --> need 2 cond_variable (empty & queue) --> 4 cond_variable in total for 2 queues
//         }

//         // add sockets to queue 

//         //signal 
//         pthread_cond_signal(&fill, &mutex);
        
//         pthread mutex_unlock(&mutex)
        

//     return item remove_queue(int socket, int * queue_buffer)
// -------------------------------------









// Extra credit 
// make your own client to test the server for 2 pts extra
// Bryant O Hardon - take client code professor points out
