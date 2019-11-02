// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

    /*
    // Ask for dictionary
    // if none is provided - use DEFAULT_DICTIONARY 
    
    // Ask for port number
    // if none is provided - use DEFAULT_PORT
    */
set<string> load_dictionary(char * fileArg){

    set<string> word_dict;
    set<string>::iterator it = word_dict.begin(); 

    // Ask for dictionary file
    // if none is provided - use DEFAULT_DICTIONARY     
    ifstream input;
    string filename = fileArg;

    // cout << "Specify a dictionary file : ";
    // getline(std::cin, filename);

    if (filename == ""){
        filename = "dictionary.txt";
        input.open(filename.c_str());
    } else {
        input.open(filename.c_str());
        while(input.fail()){
            input.clear();
            cout<<"Incorrect filename, please enter again: ";
            cin>>filename;
            input.open(filename.c_str());
        }
    }

    for(string line; getline(input,line );){
        // add line to Set
        word_dict.insert(line); 
    }

    return word_dict;
}

void addSocketToBuffer(int socket){
    pthread_mutex_lock(&mutex); // aquire lock
    // add socket to queue here
    // code in slide - cacreful
    pthread_mutex_unlock(&mutex); // release lock
}

void spawn_worker_threads(){
    // array which holds worker threads
    pthread_t threads[N_THREADS];
    // create worker threads
    for (size_t i = 0; i < N_THREADS; ++i){
        if(pthread_create(&threads[i],NULL,workerThread,NULL) != 0){
            printf("Error: Failed to create thread\n");
            exit(1);
        }
    }

    // DELETE THIS WHEN workerThread() is ready
    for(int j=0; j < N_THREADS; j++){
        pthread_join(threads[j], NULL); 
    }
}

// bool is_word_in_dictionary(string word){
//     // return
// }

// // NASTY BUG IN HERE
/*
Also, keep in mind that in the worker thread example, there is
a potential buffer overflow that can occur! Can you spot it?
(hint: the call to strcat.) Make sure you avoid this when you
write your finished code.
*/
void * workerThread(void * arg){
//     // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
//     while (1)
//     {
//         int fd = removeSocketFromQueue(); // if no socket --> sleep thread
//         while (/*read word/buffer success*/){
//             bool wasFound = is_word_in_dictionary(word);
//             if (wasFound){
//                 strcat(word, "OK\n");
//             } else {
//                 strcat(word, "MISSPELLED\n");
//             }
//             write(fd, word, strlen(word) + 1);
//             add_to_log_queue(word);     // if log queue is full -- have to handle
//             //......
//         }
        
//     }
//     // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    printf("Worker thread created!\n");
}


// void *logThread(void *arg){
//     // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    
//     while(1){
//         // remove string from buffer
//         if( (fPtr = fopen("LOG.txt", "w")) == NULL) {
//             printf("Error opening file!\n");
//         }
//     }
// }