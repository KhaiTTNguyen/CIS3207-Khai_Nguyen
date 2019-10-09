// khai nguyen
// filename: function.c
// usage: to build functions
//
//
//#include "header.h"
//
///*
//name
//description
//input: event, priority_queue
//output: void
//
//for each function: 
//1. handle error
//2. i/o
//3. regular function
//4. for normal execution - check return of system call
//*/
//
///*
//description: take in args_list & execute
//input: char** arg_list
//output: (int) status
//*/
//int shell_execute(char** args_list) {
//	
//	/*
//	categorize tokens
//	A command to be executed
//	Arguments to the command
//	BASH commands
//	<>
//	>>
//	|
//	& 
//	Input file
//	Output file
//	*/
//	
//
//	 check if file exists
//	 identify built-ins
//	char* builtin_cmds[] = { "cd", "clr", "ls", "environ", "echo", "help", "pause", "exit" };
//	int (*builtin_func[]) (char**) = { &shell_cd, &shell_clr, &shell_ls, &shell_environ, &shell_echo, &shell_help, &shell_pause, &shell_exit };
//
//	 detect which builtin to use
//	 find files in environment $path
//	for (int i = 0; i < NUM_BUILT_INS; i++) {
//		if (strcmp(args_list[0], builtin_cmds[i]) == 0) {
//			return (*builtin_func[i])(args_list);
//		}
//	}
//
//	 if doesnot match the builtins, start normal execution
//	return shell_non_built_ins(args_list);
//}
//
//int shell_non_built_ins(char** args_list) {
//	
//	 You can figure out if the file exists in a particular directory by trying to open the file.
//	 If the open fails, then the file does not exist.
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
//		 Find the full path name for the file
//		 Launch the executable file with the specified parameters using
//		 the execvp command and the argv array
//		 replace args_list[0] = <fullpathnameofcommand>;
//
//		 I/O redirection
//		 pipe()
//		 background exec
//
//		 creat output file
//		int outFile = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
//		 replace stdout with output file    
//		dup2(outFile, 1); // 1 --> file descriptor for stdout    
//		close(outFile); // close duplicate file descriptor, since we don't need it anymore    
//		 execvp with the given command line arguments!    
//		if (execvp(args_list[0], args_list) < 0) {
//			perror("Could not execute command");
//			exit(1);
//		}    // program execution should never reach here, since exec overwrites the code and data    puts("You'll never see me!");  }
//
//	}
//	else { // parent
//		 handle & --> back to shell immediately
//		waitpid(pid, NULL, 0);
//		puts("done waiting!");
//	}
//}
//
///*
//i/o redirection(&file){
//every process
//with 3 default file descriptors
// Here’s how you can handle output redirection for these commands:
1 Save the file descriptor for stdout using dup()
2 Open the output file(with the proper modes for either > or>>)
3 redirect stdout to freshly opened file
4 call the built - in function(whose output will now go to the file)
5 when the function returns, restore stdout using the saved file
descriptor.


// save stdout by creating a duplicate
int saved_stdout = dup(1);
// open file
int file_desc = open("fileName", flags);
// redirect stdout to file
dup2(file_desc, 1);
// close duplicate file desc
close(file_desc);
// make built-in call
echo(args);
// restore stdout after returning from function call
dup2(saved_stdout, 1);
// close duplicate file
close(saved_stdout);


//}
//*/
//
///*
// catch error "| ls"
//pipe()
//	2 channels
//	read
//	write
//	process 1 (close read)
//	check pipeandexec.c on canvas
//	09/24 ppt slides
//	while (1) { char *cmd = getcmd(); int retval = fork(); if (retval == 0) { // this is the child process // setup the child’s process environment here // e.g., where is standard i/o, how to handle signals? exec(cmd); // exec does not return if it succeeds printf(“error: could not execute %s\n”, cmd); exit(1); } else { // this is the parent process; wait for child to finish int pid = retval; wait(pid); } }
//}
//
//*/
//
//
///*
//
//*/
//int shell_cd(char** args_list) {
//	if (args_list[1] == NULL) {
//		printf("No directory specified\n");
//	} else {
//		if (chdir(args_list[1]) != 0) {		// change directory of prompt also
//			printf("chdir system_call error\n");
//		}
//	return 1;
//}
//
//shell_clr() {
//	// printf("\033[H\033[2J");
//}
//
///*
//OUTPUT redirection
dir can take 0 or 1 arguments.
if 0, the directory to be printed will be the current working
directory
use system call get_current_dir_name() (don’t forget to free
	afterwards though!it allocates memory!)
	if 1, use the passed in argument as the directory name.
		Don’t forget to error check!lots can go wrong here		// check can open dir or not


		char dirName[2] = "/"; // name of directory
DIR* dir = opendir(dirName); // error-check this
struct dirent* s; // directory entry
while ((s = readdir(dir)) != NULL) { // get contents
	printf("%s\t", s->name); // print name of dirent
}


//*/
//shell_ls() {
//	//…
//	// check if valid or not
//	// take flags
//	/*
//	opendir() (opens a directory and returns a DIR pointer)
//readdir() (reads the contents of a directory and returns a dirent
//pointer)
//you have to continually call this method to get the entire
//contents of a directory; once they are all exhausted, it will
//return NULL.
//	*/
//}
//
///*
//OUTPUT redirection
Environ should emulate what the env command in bash does :
Prints out the environment variables.
To get an environment variable in C, use the system call
‘getenv().
Example : to get “USER” environment variables, use
	getenv(“USER”)
	You do not need to implement ALL the environment variables
	that env does; Only print out the ones you think are the most
	beneficial for the user to know.

//*/
//shell_environ(){
//	//…
//}
//
//
///*
//OUTPUT redirection
//*/
//shell_echo(char ** args) {
//	/* 
//	save file descriptor for stdout using dup()
//	open output file (with proper modes for> or >>
//	redirect stdout to freshly opened file
//	call builtin 
//	when funct returns, restore stdout using 
//	

Echo is very simple, Just print out the arguments given back
out to the screen.
//	*/
//
//	int saved_stdout = dup(1);
//	int file_desc = open("file_name", flags);
//	dup2(file_desc, 1);
//	close(file_desc);
//
//	echo(&args);
//
//
//}
//
///*
//OUTPUT redirection
//*/
//shell_help() {
//	//…
//}
//
//shell_pause() {
Remember, all pause needs to do is pause the shell until the
user presses enter.
you can use getchar() or C++‘s std::cin.get() in a loop until
the value returned is equal to the’\n’, pretty simple.
//	return NULL;
//}
//
//
///*
//handle quit() & exit()
//*/
//int shell_exit(char ** args) {
	clean up resources

//	return 0;
//}
//
//
///*--------------------supplements-------------------------*/
//
///*put a string to all lower case*/
//char* lower(char* s) {
//	int i;
//	for (i = 0; *(s + i) != '\0'; ++i) {
//		*(s + i) = tolower(*(s + i));
//	}
//	return s;
//}