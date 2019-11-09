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

bool isNumber(char * number){
    int i = 0;

    //checking for negative numbers
    if (*number == '-'){
        return false;
    }
    for (; *number != 0; number++){
        if (!isdigit(*number)){
            return false;
        }
    }
    return true;
}

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

void put_log(string value, log_circular_buffer* log_queue_Ptr) {
    log_queue_Ptr->buffer[log_queue_Ptr->fill_ptr] = value;
    log_queue_Ptr->fill_ptr = (log_queue_Ptr->fill_ptr + 1) % QUEUE_CAPACITY;
    log_queue_Ptr->count++;
}


string get_log(log_circular_buffer* log_queue_Ptr){
    string tmp = log_queue_Ptr->buffer[log_queue_Ptr->use_ptr];
    log_queue_Ptr->use_ptr = (log_queue_Ptr->use_ptr + 1) % QUEUE_CAPACITY;
    log_queue_Ptr->count--;
    return tmp;
}
/*----------------------------For worker thread--------------------------------------*/

void addSocketToQueue(int socket, circular_buffer* connection_queue_Ptr){
    pthread_mutex_lock(&mutex_conn); // aquire LOCK
    
    /*
    here we use WHILE instead of IF because, in case there are multiple producers,

    when "this" producer produces till full - it sleeps (wait)
    then consumers jumps in to eat the buff - at the end of each eat --> signal producer
    "this" producer wakes, but only READY TO RUN, not running

    if there is another producer sneaks in acquire the lock,
     it will produce till full
    
    then the when comes the turn of the "awaken" "this" consumer to run, the buffer is already FULL..
    --> use WHILE to recheckc if the buffer is full or not
    */
    while (connection_queue_Ptr->count == QUEUE_CAPACITY){
        // block thread if buffer is full
        pthread_cond_wait(&empty_conn, &mutex_conn); // when wait, release LOCK
    }
    // add socket to queue
    put(socket, connection_queue_Ptr);
    // printf("Socket added is %d\n", socket);

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
    // printf("Socket removed is %d\n", tmp_socket);
    return tmp_socket; 
}

/*----------------------------For log thread--------------------------------------*/
void add_word_to_logQueue(string word, log_circular_buffer* log_queue_Ptr){
    pthread_mutex_lock(&mutex_log); // aquire lock
    
    while (log_queue_Ptr->count == QUEUE_CAPACITY){
        // block thread if buffer is full
        pthread_cond_wait(&empty_log, &mutex_log); 
    }
    // add socket to queue
    put_log(word, log_queue_Ptr);
    
    pthread_cond_signal(&fill_log);
    pthread_mutex_unlock(&mutex_log); // release lock
}

char* remove_word_from_logQueue(log_circular_buffer* log_queue_Ptr){
    pthread_mutex_lock(&mutex_log);
    while (log_queue_Ptr->count == 0){
        pthread_cond_wait(&fill_log, &mutex_log);
    }
    string word = get_log(log_queue_Ptr);
    // convert string to char*
    char* toWrite = (char *)malloc(word.size() + 1);
    memcpy(toWrite, word.c_str(), word.size() + 1);

    pthread_cond_signal(&empty_log);
    pthread_mutex_unlock(&mutex_log);
    return toWrite; 
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

    // encap logger thread in here 
    pthread_t logger_thread;
    if(pthread_create(&logger_thread,NULL,logThread,NULL) != 0){
        printf("Error: Failed to create thread\n");
        exit(1);
    }
}

int is_word_in_dictionary(string word){
    // cout << "\nThe elements in set are: "; 
    // for (auto it = word_dictionary.begin(); it != word_dictionary.end(); it++){ 
    //     cout << *it << " "; 
    // }

    if ( word_dictionary.count(word) > 0 ){
		return 1; // true
    } else {
        return 0; // false
    }
}

int read_line(int fd, void *buffer, int n) {
    int numRead;                    /* # of bytes fetched by last read() */
    int total_read;                     /* Total bytes read so far */
    char *buf;
    char letter;
    
    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }
    
    buf = (char*)buffer;                      
    total_read = 0;
    for (;;) {
        numRead = read(fd, &letter, 1);
        if (letter == '\n'){
            break;
        }

        if (numRead == -1) {
            if (errno == EINTR) {      /* Interrupted --> restart read() */
                continue;
            } else {
                return -1;              /* Some other error */
            }
        } else if (numRead == 0) {      /* EOF */
            if (total_read == 0){           /* No bytes read; return 0 */
                return 0;
            } else {                        /* Some bytes read; add '\0' */
	            break;
            }
        } else {                        /* 'numRead' must be 1 if we get here */
            if (total_read < n - 1) {      /* Discard those after (n - 1) bytes */
                total_read++;
                *buf++ = letter;
            }
        }
    }

    *buf = '\0';
    // printf("Total read is %d\n",total_read);
    return total_read;
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
        char *buffer = (char*) calloc(MAX_WORD_SIZE, sizeof(char));
        // printf("Char before read %s", buffer);
        // printf("newline\n");
        int bytes_read = 0;
        while (bytes_read = read_line(fd, buffer, MAX_WORD_SIZE ) > 0){
            string word = buffer; // create "string" from "char*" 
            // printf("Char after read %s", buffer);
            // printf("newline\n");
            // printf("Bytes read were: %d\n", bytes_read);
            int wasFound = is_word_in_dictionary(word);
            // printf("Was found = %d\n", wasFound);
            char * writeBack = (char*) calloc(MAX_WORD_SIZE, sizeof(char));
            if (wasFound){
                writeBack = concat(buffer, " OK\n");
            } else {
                writeBack = concat(buffer, " MISSPELLED\n");
            }
            
            printf("Write back is %s\n", writeBack);
            // error check
            if (write(fd, writeBack, MAX_WORD_SIZE) < 0) {	
			    printf("write system_call error\n");
            }

            free(writeBack);
            free(buffer);
            char *buffer = (char*) calloc(MAX_WORD_SIZE, sizeof(char));
            // printf("Char after deallocated %s\n", buffer);
            // add to log queue
            add_word_to_logQueue(word, log_queue_Ptr);     // if log queue is full -- have to handle
            
        }
        close(fd);
        printf("One connection closed!\n");
    }
    // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    printf("Worker thread died!\n");
}

char* concat(const char *s1, const char *s2){
    char *result = (char*)calloc(strlen(s1) + strlen(s2) + 1, sizeof(char)); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void * logThread(void *arg){
    // assert(ptr != NULL);  // put in gcc - no debug --> get rid of all assert()
    
    while(1){ // keep log thread alive
        // remove string from buffer
        // printf("%d words exist in logQueue\n", log_queue_Ptr->count);
        char *toWrite = remove_word_from_logQueue(log_queue_Ptr);
        FILE *fPtr;
        if( (fPtr = fopen("LOG.txt", "a")) == NULL) {
            printf("Error opening file!\n");
        }
        printf("Word to log: %s\n", toWrite);
        fprintf(fPtr, "Word to checked was: %s\n", toWrite);
        free(toWrite);
        fclose(fPtr);
    }
    printf("Logger thread died!\n");
}