// Khai Nguyen
// Filename: main.c

#include "header.h"


// char *shell = "/home/khaing/Documents/CIS_3207/CIS3207-Khai_Nguyen/Project_2/Project_2/myshell";

int main(int argc, char** argv) {
	putenv("PWD=/home/khaing/Documents/CIS_3207/CIS3207-Khai_Nguyen/Project_2/Project_2/");

	/*------------------------------------process batch file-------------------------------------*/
	if (argv[1] !=  NULL){
		// open file and stream input into shell
		FILE * fp = fopen(argv[1], "r");
		if (fp == NULL){
			printf("Cannot open file %s", argv[1]);
			return EXIT_FAILURE;
		}

		size_t read_status = 1;
		while(!feof(fp) && read_status == 1){
			/*-------------------- read cmd ------------------------*/
			// calloc() initialzes pointers to 0 or NULL, better than malloc()
			char* cmd_string = (char*)calloc(LINE_LENGTH, sizeof(char));

			if (cmd_string == NULL) {
				printf("Mem_allocation failed. \n");
				return -1;
			}
			// start read each line - stop @ "\n" or "EOF"
			if (fgets(cmd_string, LINE_LENGTH, fp) == NULL){
				printf("Done reading batch file\n");
				return -1;
			}
			/*-------------------- parse cmd ------------------------*/
			char** args_list = (char**)calloc(LINE_LENGTH, sizeof(char*));
			if (args_list == NULL) {
				fprintf(stderr, "Mem_allocation failed. \n");
				return -1;
			}

			int index = 0;
			char* token = strtok(cmd_string, DELIMITERS);
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
			// execute
			read_status = shell_execute(args_list);
		}
		fclose(fp);
		return EXIT_SUCCESS;
	} 
	
	/*------------------------------------regular shell loop-------------------------------------*/
	int status = 1;	// determines whether continue to exec or not
	while (status) {
		char * prompt = getenv("PWD");
		printf("%s> ", prompt);

		// read cmd
		// calloc() initialzes pointers to 0 or NULL, better than malloc()
		char* cmd_string = (char*)calloc(LINE_LENGTH, sizeof(char));

		if (cmd_string == NULL) {
			printf("Mem_allocation failed. \n");
			return -1;
		}
		// stop @ "\n" or "EOF"
		if (fgets(cmd_string, LINE_LENGTH, stdin) == NULL){
			printf("Read line error\n");
			printf("cmd str is %s\n", cmd_string);
			return -1;
		}

		/*-------------------- parse cmd ------------------------*/
		char** args_list = (char**)calloc(LINE_LENGTH, sizeof(char*));
		if (args_list == NULL) {
			fprintf(stderr, "Mem_allocation failed. \n");
			return -1;
		}

		int index = 0;
		char* token = strtok(cmd_string, DELIMITERS);
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

		// execute
        status = shell_execute(args_list);
	}
	return EXIT_SUCCESS;
}
