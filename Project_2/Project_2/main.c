// Khai Nguyen
// Filename: main.c

#include "header.h"

#define LINE_LENGTH 100


int main(int argc, char** argv) {
	
	//#### redirect stdin to a file to take in "a file of commands"
	
	// shell loop
	int status = 1;	// determines whether continue to exec or not
	while (status) {
		printf("prompt> ");

		/*-------------------- read cmd ------------------------*/
		char* cmd_string = (char*)malloc(sizeof(char) * LINE_LENGTH);

		if (cmd_string == NULL) {
			printf("Mem_allocation failed. \n");
			return -1;
		}
		// stop @ "\n" or "EOF"
		fgets(cmd_string, LINE_LENGTH, stdin);

		printf("cmd is %s\n", cmd_string);


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
			args_list[index] = lower(token);
			index++;

			token = strtok(NULL, DELIMITERS);
		}
		args_list[index] = NULL;		// NULL terminate - pass in exec()


		// while (*args_list != NULL) {
		// 	printf("Token list is %s\n", *args_list);
		// 	args_list++;
		// }


		// if no cmds entered
		if (args_list[0] == NULL) {
			continue;
		}
		printf("Shell exec\n");
		status = shell_execute(args_list);
	}
	
	return 0;
}
