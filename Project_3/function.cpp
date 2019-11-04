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
unordered_set<string> load_dictionary(char * fileArg){

    unordered_set<string> word_dict;
    unordered_set<string>::iterator it = word_dict.begin(); 

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

void put(int value, circular_buffer* connection_queue) {
    connection_queue->buffer[connection_queue->fill_ptr] = value;
    connection_queue->fill_ptr = (connection_queue->fill_ptr + 1) % QUEUE_CAPACITY;
    connection_queue->count++;
}

int get(circular_buffer* connection_queue){
    int tmp = connection_queue->buffer[connection_queue->use_ptr];
    connection_queue->use_ptr = (connection_queue->use_ptr + 1) % QUEUE_CAPACITY;
    connection_queue->count--;
    return tmp;
}

void addSocketToQueue(int socket, circular_buffer* connection_queue_Ptr){
    pthread_mutex_lock(&mutex_conn); // aquire lock
    
    while (connection_queue_Ptr->count == QUEUE_CAPACITY){
        // block thread if buffer is full
        pthread_cond_wait(&empty_conn, &mutex_conn); 
    }
    // add socket to queue
    put(socket, connection_queue_Ptr);
    printf("Socket added is %d\n", socket);

    pthread_cond_signal(&fill_conn);
    pthread_mutex_unlock(&mutex_conn); // release lock
}

int removeSocketFromQueue(circular_buffer* connection_queue_Ptr){
    pthread_mutex_lock(&mutex_conn);
    while (connection_queue_Ptr->count == 0){
        pthread_cond_wait(&fill_conn, &mutex_conn);
    }
    int tmp_socket = get(connection_queue_Ptr);
    pthread_cond_signal(&empty_conn);
    pthread_mutex_unlock(&mutex_conn);
    printf("Socket removed is %d\n", tmp_socket);
    return tmp_socket; 
}


// void add_word_to_logQueue(string word, circular_buffer* log_queue_Ptr){
//     pthread_mutex_lock(&mutex_log); // aquire lock
    
//     while (log_queue_Ptr->count == QUEUE_CAPACITY){
//         // block thread if buffer is full
//         pthread_cond_wait(&empty_log, &mutex_log); 
//     }
//     // add socket to queue
//     put(word, log_queue_Ptr);

//     pthread_cond_signal(&fill_log);
//     pthread_mutex_unlock(&mutex_log); // release lock
// }

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
}

int is_word_in_dictionary(string word){
    if ( word_dictionary.find(word) != word_dictionary.end() ){
		return 1; // true
    } else {
        return 1; // false
    }
}

// // NASTY BUG IN HERE
/*
Also, keep in mind that in the worker thread example, there is
a potential buffer overflow that can occur! Can you spot it?
(hint: the call to strcat.) Make sure you avoid this when you
write your finished code.
*/
void * workerThread(void * arg){
    // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    while (1){  // keep thread alive
        int fd = removeSocketFromQueue(connection_queue_Ptr); // if no socket --> sleep thread
        char* buffer = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
        // printf("%d sockets exist\n", connection_queue_Ptr->count);
        printf("Char * before read is: %s\n", buffer);
        while (read(fd, buffer, MAX_WORD_SIZE) > 0){
            std::string word(buffer); // create "string" from "char*" 
            printf("Char * is: %s\n", buffer);

            int wasFound = is_word_in_dictionary(word);
            printf("Was found = %d\n", wasFound);
            char * writeBack = NULL;
            if (wasFound){
                writeBack = concat(buffer, "OK\n");
            } else {
                writeBack = concat(buffer, "MISSPELLED\n");
            }

            // error check
            if (write(fd, writeBack, strlen(writeBack) + 1) < 0) {	
			    printf("write system_call error\n");
            }
            free(buffer);
            free(writeBack);
            buffer = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
            // add_to_log_queue(word);     // if log queue is full -- have to handle
            // //......
        }
        close(fd);
        printf("Worker thread finished 1 word!\n");
    }
    // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    printf("Worker thread died!\n");
}

char* concat(const char *s1, const char *s2){
    char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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