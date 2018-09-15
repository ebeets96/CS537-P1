#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "537ps.h"

int main(int argc, char* argv[]) {

	// Set argument defaults
	int pid = -1;
	bool statebool = false;
	bool userTime = true;
	bool sysTime = false;
	bool vMem = false;
	bool comLine = true;

	// Handle passed arguments
	int opt;
	// while ((opt = getopt(argc, argv, "p:sUSvc")) != -1) {
	// 	printf("%c : ", opt);
	// 	printf("%s\n", optarg);
	// }

	// Call ps function with all true values
	// Replace when argument passing is accomplished

	printAll(true, true, true, true, true);
	// printOne(atoi(argv[1]), true, true, true, true, true); //Dummy pid for testing

	return 0;
}

void printAll(bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {
	// Read folders in /proc directory
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir("/proc")) == NULL) {
		//Error handling
		printf("errors");
	} else {
		while ((entry = readdir(dir)) != NULL) {
			int folderValue = atoi(entry->d_name);
			if(folderValue != 0 || entry->d_name[0] == '0') {
				//Folder is numeric
				printOne(entry->d_name, state, userTime, sysTime, vMem, comLine);
			}
		}
		closedir(dir);
	}
}

/**
 * pid is process ID to display
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
**/

void printOne(char* pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {
	// Attempt to read /proc/<pid>
	FILE *fp;
	char filename[50] = "/proc/";
	strcat(filename, pid);
	strcat(filename, "/stat");

	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Couldn't open %s\n", filename);
		return;
	} else {
		//Print PID
		int stat_pid;
		fscanf(fp, "%d ", &stat_pid);
		printf("%d: ", stat_pid);

		//Throw out comm variable
		fscanf(fp, "%*s ");

		//Print State
		char stat_state;
		fscanf(fp, "%c ", &stat_state);
		printf("%c ", stat_state);

		//Throw out more variables
		fscanf(fp, "%*d %*d %*d %*d %*d %*u %*u %*u %*u %*u ");

		//Print utime
		unsigned long int utime;
		fscanf(fp, "%lu ", &utime);
		printf("utime=%lu ", utime);

		//Print stime
		unsigned long int stime;
		fscanf(fp, "%lu ", &stime);
		printf("stime=%lu", stime);

		// Print new line
		printf("\n");
	}

}

// void splitString(char* dest[], char *str, const char *delim) {
// 	char *token;
// 	token = strtok(str, delim);
//    	int index = 0;
// 	while(token != NULL) {
// 		dest[index] = token;
// 		token = strtok(NULL, delim);
// 		index++;
// 	}
// }
