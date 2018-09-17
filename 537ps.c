#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "537ps.h"

int main(int argc, char* argv[]) {
	// Handle passed arguments
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
	// Load files required for ps command
	char procRoot[20] = "/proc/";
	strcat(procRoot, pid);

	char statusFilename[30];
	strcpy(statusFilename, procRoot);
	strcat(statusFilename, "/status");

	char statFilename[30];
	strcpy(statFilename, procRoot);
	strcat(statFilename, "/stat");

	char statmFilename[30];
	strcpy(statmFilename, procRoot);
	strcat(statmFilename, "/statm");

	char cmdFilename[30];
	strcpy(cmdFilename, procRoot);
	strcat(cmdFilename, "/cmdline");

	// Create variables for process data
	char stat_state;
	int stat_pid;
	unsigned long int utime;
	unsigned long int stime;
	int vMemVal;
	char command[100];

	// Check status file
	FILE *statusFile = fopen(statusFilename, "r");
	if(statusFile == NULL) {
		return;
	} else {
		//Read the user id
	}
	fclose(statusFile);

	// ---------------------- TODO --------------------------
	// Check if user ID matches the process and return if not
	// ---------------------- TODO --------------------------

	// Check stat file
	FILE *statFile = fopen(statFilename, "r");
	if(statFile == NULL) {
		return;
	} else {
		// Load data from stat file
		fscanf(statFile, "%d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu ", &stat_pid, &stat_state, &utime, &stime);
	}
	fclose(statFile);

	// Check statm file
	FILE *statmFile = fopen(statmFilename, "r");
	if(statmFile == NULL) {
		return;
	} else {
		// Load data from stat file
		fscanf(statmFile, "%d", &vMemVal);
	}
	fclose(statmFile);

	// Check cmdLine file
	FILE *cmdFile = fopen(cmdFilename, "r");
	if(cmdFile == NULL) {
		return;
	} else {
		// Load data from stat file
		fgets(command, sizeof(command), cmdFile);
	}
	fclose(cmdFile);

	// Print data
	printf("%d:", stat_pid);

	if(state) {
		printf(" %c", stat_state);
	}

	if(userTime) {
		printf(" utime=%lu", utime);
	}

	if(sysTime) {
		printf(" stime=%lu", stime);
	}

	if(sysTime) {
		printf(" stime=%lu", stime);
	}

	if(vMem) {
		printf(" %d", vMemVal);
	}

	if(comLine) {
		printf(" %s", command);
	}

	printf("\n");

}
