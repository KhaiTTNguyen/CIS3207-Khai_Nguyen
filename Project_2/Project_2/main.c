// Khai Nguyen
// Filename: main.c

#include "header.h"


// char *shell = "/home/khaing/Documents/CIS_3207/CIS3207-Khai_Nguyen/Project_2/Project_2/myshell";

int main(int argc, char** argv) {
	putenv("PWD=/home/khaing/Documents/CIS_3207/CIS3207-Khai_Nguyen/Project_2/Project_2/");

	//#### redirect stdin to a file to take in "a file of commands"
	
	/*
	if (strcmp(argv[1],"*.txt") == 0){
		// open file and stream input into shell
	} 
	*/

	// shell loop
	
	int status = 1;	// determines whether continue to exec or not
	while (status) {
		char * prompt = getenv("PWD");
		printf("%s> ", prompt);

		/*-------------------- read cmd ------------------------*/
		// calloc() initialzes pointers to 0 or NULL, better than malloc()
		char* cmd_string = (char*)calloc(LINE_LENGTH, sizeof(char));

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
		char** args_list = (char**)calloc(LINE_LENGTH, sizeof(char*));
		if (args_list == NULL) {
			fprintf(stderr, "Mem_allocation failed. \n");
			return -1;
		}

		int index = 0;
		char* token;

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

		if(strcmp("./myshell",*args_list) == 0){
            // status = myshell(args_list);
        }
        else
            status = shell_execute(args_list);
	}
	
	return EXIT_SUCCESS;
}
