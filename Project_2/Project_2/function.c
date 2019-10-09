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
description: take in args_list & execute
input: char** arg_list
output: (int) status
*/
int shell_execute(char** args_list) {
	
	/*
	categorize tokens
	a command to be executed
	arguments to the command
	bash commands
	<>
	>>
	|
	& 
	input file
	output file
	*/
	

	// check if file exists
	// identify built-ins
	char* builtin_cmds[] = { "cd", "clr", "dir", "environ", "echo", "help", "pause", "exit" };
	int (*builtin_func[]) (char**) = { &shell_cd, &shell_clr, &shell_ls, &shell_environ, &shell_echo, &shell_help, &shell_pause, &shell_exit };

	 // detect which builtin to use
	for (int i = 0; i < NUM_BUILT_INS; i++) {
		if (strcmp(args_list[0], builtin_cmds[i]) == 0) {
			return (*builtin_func[i])(args_list);
		}
	}

	// if doesnot match the builtins, start normal execution
	return 1;
		//shell_non_built_ins(args_list);
}
//
//int shell_non_built_ins(char** args_list) {
//	
//	 you can figure out if the file exists in a particular directory by trying to open the file.
//	 if the open fails, then the file does not exist.
//
//
//	int pid = fork();
//
//	 catch fork error  
//	if (pid < 0) {
//		puts("fork failed");
//		return 1;
//	}
//
//	 fork sucessful, continue  
//	if (pid == 0) { // child    
//	 use exec to launch external command    
//		puts("executing command");
//		........
//
//		 find the full path name for the file
//		 launch the executable file with the specified parameters using
//		 the execvp command and the argv array
//		 replace args_list[0] = <fullpathnameofcommand>;
//
//		 i/o redirection
//		 pipe()
//		 background exec
//
//		 creat output file
//		int outfile = open("output.txt", o_wronly | o_creat | o_trunc, s_irwxu | s_irwxg | s_irwxo);
//		 replace stdout with output file    
//		dup2(outfile, 1); // 1 --> file descriptor for stdout    
//		close(outfile); // close duplicate file descriptor, since we don't need it anymore    
//		 execvp with the given command line arguments!    
//		if (execvp(args_list[0], args_list) < 0) {
//			perror("could not execute command");
//			exit(1);
//		}    // program execution should never reach here, since exec overwrites the code and data    puts("you'll never see me!");  }
//
//	}
//	else { // parent
//		 handle & --> back to shell immediately
//		waitpid(pid, null, 0);
//		puts("done waiting!");
//	}
//}

/*
i/o redirection(&file){
every process
with 3 default file descriptors
 here�s how you can handle output redirection for these commands:
1 save the file descriptor for stdout using dup()
2 open the output file(with the proper modes for either > or>>)
3 redirect stdout to freshly opened file
4 call the built - in function(whose output will now go to the file)
5 when the function returns, restore stdout using the saved file
descriptor.


 save stdout by creating a duplicate
int saved_stdout = dup(1);
 open file
int file_desc = open("filename", flags);
 redirect stdout to file
dup2(file_desc, 1);
 close duplicate file desc
close(file_desc);
 make built-in call
echo(args);
 restore stdout after returning from function call
dup2(saved_stdout, 1);
 close duplicate file
close(saved_stdout);


}
*/

/*
 catch error "| ls"
pipe()
	2 channels
	read
	write
	process 1 (close read)
	check pipeandexec.c on canvas
	09/24 ppt slides
	while (1) { char *cmd = getcmd(); int retval = fork(); if (retval == 0) { // this is the child process // setup the child�s process environment here // e.g., where is standard i/o, how to handle signals? exec(cmd); // exec does not return if it succeeds printf(�error: could not execute %s\n�, cmd); exit(1); } else { // this is the parent process; wait for child to finish int pid = retval; wait(pid); } }
}

*/


/*

*/
int shell_cd(char** args_list) {
	if (*(args_list+1) == NULL) {
		printf("no directory specified\n");
	}
	else {
		if (chdir(*(args_list+1)) != 0) {		// change directory of prompt also
			printf("chdir system_call error\n");
		}
	}
	// getcwd
	printf("Return 1 in cd\n");
	return 1;
}

int shell_clr(char** args_list){
	printf("\033[h\033[2j");
	return 1;
}

/*
output redirection
prints out the environment variables.

to get an environment variable in c, use the system call
�getenv().
example : to get �user� environment variables, use
	getenv(�user�)
	you do not need to implement all the environment variables
	that env does; only print out the ones you think are the most
	beneficial for the user to know.

*/
int shell_environ(char** args_list){
	if ( *(args_list+1)!= NULL) {
		printf("Invalid! No arguments for \"environ\"\n");
	}
	else {
		size_t i;
        for (i=0; *(environ+i)!=NULL; i++) {
            printf("%s\n", *(environ+i));
        }
	}
	printf("Return 1 in environ\n");
	return 1;
}

/*
output redirection
dir can take 0 or 1 arguments.
if 0, the directory to be printed will be the current working
directory
use system call get_current_dir_name() (don�t forget to free
	afterwards though!it allocates memory!)
	if 1, use the passed in argument as the directory name.
		don�t forget to error check!lots can go wrong here		// check can open dir or not


		char dirname[2] = "/"; // name of directory
dir* dir = opendir(dirname); // error-check this
struct dirent* s; // directory entry
while ((s = readdir(dir)) != null) { // get contents
	printf("%s\t", s->name); // print name of dirent
}


*/
/* returns 1 if path_name represents a directory, 0 if it isn't */
int is_dir(char *path_name) {
    struct stat buff;
    if (stat(path_name, &buff) < 0){
        fprintf(stderr, "stat: %s\n", strerror(errno));
        return 0;
    }
    return S_ISDIR(buff.st_mode);
}

int shell_ls(char** args_list) {
	// more than 1 arguments 
	if (*(args_list+2)!= NULL){
		printf("Invalid arguments.");
	// not a valid directory
	} else if ( is_dir(*(args_list+1)) != 1){
		printf("Invalid directory: %s\n",*(args_list+1));
	// 0  
	} else {
		DIR *dir_p;
        struct dirent *entry;
		
		// 0 argument
		if (*(args_list+1) == NULL) {
			char * cur_dir = (char*)get_current_dir_name();
			printf("Current dir is %s\n", *cur_dir);
			dir_p = opendir(cur_dir);
        // 1 argument
		} else {
			dir_p = opendir(*(args_list+1));
		}

		while((entry = readdir(dir_p))!=NULL){
            if(strcmp(entry->d_name,".")==0) continue;
            if(strcmp(entry->d_name,"..")==0) continue;
            printf("%s\t",entry->d_name);
        }
        puts("");
        closedir(dir_p);
	}
	return 1;
}

/*
output redirection
*/
int shell_echo(char** args_list) {
	/* 
	save file descriptor for stdout using dup()
	open output file (with proper modes for> or >>
	redirect stdout to freshly opened file
	call builtin 
	when funct returns, restore stdout using 
	

echo is very simple, just print out the arguments given back
out to the screen.
	*/
/*
	int saved_stdout = dup(1);
	int file_desc = open("file_name", flags);
	dup2(file_desc, 1);
	close(file_desc);

	echo(&args);*/

	return 1;
}

/*
output redirection
*/
int shell_help(char** args_list) {
	return 1;
}

int shell_pause(char** args_list) {
//remember, all pause needs to do is pause the shell until the
//user presses enter.
//you can use getchar() or c++�s std::cin.get() in a loop until
//the value returned is equal to the�\n�, pretty simple.
	return 1;
}


/*
handle quit() & exit()
*/
int shell_exit(char** args_list) {
	// clean up resources
	return 0;
}


/*--------------------supplements-------------------------*/

/*put a string to all lower case*/
char* lower(char* s) {
	int i;
	for (i = 0; *(s + i) != '\0'; ++i) {
		*(s + i) = tolower(*(s + i));
	}
	return s;
}