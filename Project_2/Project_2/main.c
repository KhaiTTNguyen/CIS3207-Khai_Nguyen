// Khai Nguyen
// Filename: main.c

#include "header.h"

#define LINE_LENGTH 100

char **environ;
char *shell="/home/khaing/Documents/CIS_3207/CIS3207-Khai_Nguyen/Project_2/Project_2/myshell";

int main(int argc, char** argv) {
	environ;
	shell;
	// putenv("myshell_root=/cygdrive/c/Users/USER/Desktop/Hw/C files/myshell");

	//#### redirect stdin to a file to take in "a file of commands"
	
	/*
	if (strcmp(argv[1],"*.txt") == 0){
		// open file and stream input into shell
	} 
	*/

	// shell loop
	size_t len=strlen(shell);
	char * prompt = getenv("PWD")+(len)*sizeof(char);
	int status = 1;	// determines whether continue to exec or not
	while (status) {
		printf("%s> ", prompt);

		/*-------------------- read cmd ------------------------*/
		char* cmd_string = (char*)malloc(sizeof(char) * LINE_LENGTH);

		if (cmd_string == NULL) {
			printf("Mem_allocation failed. \n");
			return -1;
		}
		// stop @ "\n" or "EOF"
		if (fgets(cmd_string, LINE_LENGTH, stdin) == NULL){
			printf("Read line error\n");
			return -1;
		}


		/*-------------------- parse cmd ------------------------*/
		char** args_list = (char**)malloc(sizeof(char*) * LINE_LENGTH);
		int index = 0;
		char* token;

		if (args_list == NULL) {
			fprintf(stderr, "Mem_allocation failed. \n");
			return -1;
		}

		/* get the first token */
		token = strtok(cmd_string, DELIMITERS);

		/* walk through other tokens */
		while (token != NULL) {
			args_list[index] = token;
			index++;

			token = strtok(NULL, DELIMITERS);
		}
		args_list[index] = NULL;		// NULL terminate - pass in exec()

		// if no cmds entered
		if (args_list[0] == NULL) {
			continue;
		}
		printf("Shell exec\n");
		printf("Arg list in main: %s\n", args_list[0]);
		status = shell_execute(args_list);
		printf("Shell exec completed\n");
	}
	
	return 0;
}
