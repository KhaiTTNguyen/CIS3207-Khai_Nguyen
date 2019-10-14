 //khai nguyen
 //filename: function.c
 //usage: to build functions


#include "header.h"

/*
name
description
input: event, priority_queue
output: void

for each function: 
1. handle error
2. i/o
3. regular function
4. for normal execution - check return of system call
*/

/*
File descriptor
0	Standard input	stdin
1	Standard output	stdout
2	Standard error	stderr
*/

int shell_execute(char** args_list) {	
	size_t find_index = 0; // index to catch ">>" ">" "<" "|" "&"
	size_t out_redir_indx = 0;
    size_t in_redir_indx = 0;
	// process IDs 
	pid_t pid_read = -1;
	pid_t pid_write = -1;

	for (find_index = 0; *(args_list + find_index)!=NULL; find_index++){
		if(strcmp(">",*(args_list+find_index))==0){
			out_redir_indx = find_index;
			int fd_trunc = 0;
			if((fd_trunc = open(*(args_list+find_index+1), O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))==-1){
				printf("File %s could not be open",*(args_list+find_index+1));
			} else {
				if((pid_write = fork()) < 0){
					printf("Error fork in \">\"! \n");
				} else if (pid_write == 0){		// child
                    dup2(fd_trunc,STDOUT_FILENO);
                } else {	// parent
					close(fd_trunc);
					if(pid_read == 0) { // close remaning reading child process
						exit(EXIT_SUCCESS);
					} else {
						return wait(NULL);
					}
				}
			}
		}
		
		if(strcmp(">>",*(args_list + find_index))==0){
			out_redir_indx = find_index;
			int fd_append;
            if((fd_append = open(*(args_list+find_index+1),O_WRONLY | O_APPEND | O_CREAT ,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))==-1){
                printf("File %s could not be open",*(args_list+find_index+1));
            } else {
                if((pid_write = fork()) < 0){
                    puts("Error fork in \">>\"! \n");
                } else if(pid_write == 0){
                    dup2(fd_append,STDOUT_FILENO);
                } else {
                    close(fd_append);
                    if(pid_read == 0)
                        exit(EXIT_SUCCESS);
                    else
                        return wait(NULL);
                } 
            }
		}	

		if(strcmp("<",*(args_list+find_index))==0){
            in_redir_indx = find_index;
            int fd_read;
			printf("Reach here");
            if((fd_read=open(*(args_list+find_index+1), O_RDONLY)==-1)){
                printf("File %s could not be open",*(args_list+find_index+1));
            } else {   
                if((pid_read = fork()) < 0){
                    puts("Error fork in \"<\"! \n");
                } else if(pid_read == 0){
                    dup2(fd_read,STDIN_FILENO);
                } else {
                    close(fd_read);
                    if(pid_write == 0) {
                        exit(EXIT_SUCCESS);
                    } else {
                        return wait(NULL);
					}
				}   
            }   
        }

		if(strcmp("|",*(args_list + find_index))==0){
			pid_t pidT;
            if((pidT = fork()) < 0){
                printf("Error fork in \"|\"! \n");
            } else if(pidT == 0){
                exec_pipe(args_list,find_index); //function for pipe redirection
                exit(EXIT_SUCCESS);
            } else{
                return wait(NULL); // returns the process ID of the terminated child
            }
		}	
	}

	// make compatible with non-special character case
	if((out_redir_indx != 0 && in_redir_indx == 0) 
	|| (out_redir_indx != 0 && out_redir_indx < in_redir_indx)) {
		*(args_list + out_redir_indx) = NULL;
	} else if((in_redir_indx != 0 && out_redir_indx == 0) 
	|| (in_redir_indx != 0 && in_redir_indx < out_redir_indx)) {
		*(args_list + in_redir_indx) = NULL;
	}

	/*-------------------------------------------shell_built_ins-------------------------------------------*/
	char* builtin_cmds[] = { "cd", "clr", "dir", "environ", "echo", "help", "pause", "exit" };
	void (*builtin_func[]) (char**) = { &shell_cd, &shell_clr, &shell_ls, &shell_environ, &shell_echo, &shell_help, &shell_pause, &shell_exit };
	// detect which builtin to use
	for (int i = 0; i < NUM_BUILT_INS; i++) {
		if (strcmp(args_list[0], builtin_cmds[i]) == 0) {
			(*builtin_func[i])(args_list);
			if(pid_write == 0 || pid_read == 0) { 	// end child of read/write
                exit(EXIT_SUCCESS);
			} else {
                return 1;
			}
		}
	}

	/*-------------------------------------------shell_non_built_ins-------------------------------------------*/
	pid_t pid;
    if((pid = fork()) < 0){
        printf("Error fork in \"exec non-builtins\" \n");
    } else if (pid == 0){	// child
        if(strcmp("&",*(args_list + find_index - 1))==0) {
            *(args_list + find_index -1) = NULL;
		}	
        if(execvp(args_list[0],args_list) < 0){
            printf("Not a valid command: %s\n",*args_list);
            exit(EXIT_FAILURE);
        }
    } else {	// parent
        if(pid_write == 0 || pid_read == 0){
            exit(EXIT_SUCCESS);
        } else {
            if(strcmp("&",*(args_list+find_index-1)) != 0){
                return wait(NULL);
			}
        }
    }
}


int exec_pipe(char **args_list, int p_indx){
	// an array containing the input and output file descriptors
  	// pipe_file_descs[0] -> read from this
  	// pipe_file_descs[1] -> write to this 
  	int pipe_file_descs[2];	
	pid_t pid_P = 0;
	
	// create pipe
	if (pipe(pipe_file_descs) == -1){
		perror("Failed to create pipe!");
		return EXIT_FAILURE;
	}

    if((pid_P = fork()) < 0){
        puts("Error fork");
    } else if (pid_P == 0){ 		// child
        close(pipe_file_descs[0]);
        dup2(pipe_file_descs[1],1);
		// erase "|" symbol
        *(args_list + p_indx) = NULL;
        shell_execute(args_list);		
       	exit(EXIT_SUCCESS);
    } else { 	// parent
        close(pipe_file_descs[1]);
        dup2(pipe_file_descs[0],0);
        args_list = args_list + p_indx + 1;
        shell_execute(args_list);
        
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    return 1;
}

/*----------------------------------------------shell_cd---------------------------------------------*/
void shell_cd(char** args_list) {

	if(*(args_list+2)!=NULL){
        printf("Invalid arguments in \"cd\".\n");
	} else if (args_list[1] == NULL) {
		printf("No directory specified\n");
	} else if(is_dir(*(args_list+1))!=1){
        printf("Invalid directory: %s\n",*(args_list+1));
    } else {
		if (chdir(*(args_list+1)) != 0) {	
			printf("chdir system_call error\n");
		}
		// set new current directory - this change directory of prompt also
		setenv("PWD",get_current_dir_name(),1);
	}
}

/*----------------------------------------------shell_ls---------------------------------------------*/
/* returns 1 if path_name represents a directory, 0 if it isn't */
int is_dir(char *path_name) {
    if (path_name == NULL){
		return 1;
	}

	struct stat buff;
    if (stat(path_name, &buff) < 0){
        fprintf(stderr, "stat: %s\n", strerror(errno));
        return 0;
    }
    return S_ISDIR(buff.st_mode);
}

void shell_ls(char** args_list) {

	char * cur_dir; 
	// more than 1 arguments -- for I/O redirection, already erase the symbol
	if (args_list[2] != NULL){
		printf("Invalid arguments in \"dir\".\n");
	} else {
		DIR* dir_p;
        struct dirent *entry;
		if (is_dir(args_list[1]) != 1){
				printf("Invalid directory: %s\n", args_list[1]);
				free(args_list);
		} else {
			// 0 argument
			if (args_list[1] == NULL || args_list[1] == " ")  {
				cur_dir = (char*)get_current_dir_name();
				dir_p = opendir(cur_dir);
				free(cur_dir); 
			// 1 argument
			} else {
				dir_p = opendir(args_list[1]);
			}
			// start reading dir
			while((entry = readdir(dir_p))!=NULL){
				if(strcmp(entry->d_name,".")==0) continue;
				if(strcmp(entry->d_name,"..")==0) continue;
				printf("%s\t",entry->d_name);
			}
			puts("");
			closedir(dir_p);
		}
	}
	free(args_list);
}



/*----------------------------------------------shell_clr---------------------------------------------*/
void shell_clr(char** args_list){
	if(*(args_list+1)!=NULL){
        printf("Invalid arguments for \"clr\".");
    } else {
		printf("\033[H\033[J");
	}
}

/*----------------------------------------------shell_environ---------------------------------------------*/
void shell_environ(char** args_list){
	if ( *(args_list+1)!= NULL) {
		printf("Invalid! No arguments for \"environ\"\n");
	} else {	
		printf("PWD : %s\n", getenv("PWD"));
		printf("PATH : %s\n", getenv("PATH"));
   		printf("HOME : %s\n", getenv("HOME"));
   		printf("ROOT : %s\n", getenv("ROOT"));
		
	}
}


/*
Name: shell_echo 
Description: prints out the arguments given back out to the screen.
output redirection
*/
void shell_echo(char** args_list) {
	for(size_t i = 1;*(args_list + i) != NULL; i++){
        printf("%s ",*(args_list + i));
    }
    puts("");
}

/*
output redirection
*/
void shell_help(char** args_list) {
	//.....
	
}

void shell_pause(char** args_list) {
//remember, all pause needs to do is pause the shell until the
//user presses enter.
//you can use getchar() or c++�s std::cin.get() in a loop until
//the value returned is equal to the�\n�, pretty simple.
	while (1){
		char c = getchar();
		if (c == '\n'){
			break;
		}
	}
}


/*
handle quit() & exit()
*/
void shell_exit(char** args_list) {
	for (int i = 0; i < LINE_LENGTH; i++){
		free(args_list[i]);
	}
	free(args_list);

	exit(EXIT_SUCCESS);
}

/*--------------------supplements-------------------------*/

/*put a string to all lower case*/
// char* lower(char* s) {
// 	int i;
// 	for (i = 0; *(s + i) != '\0'; ++i) {
// 		*(s + i) = tolower(*(s + i));
// 	}
// 	return s;
// }