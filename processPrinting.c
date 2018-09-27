#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include "processPrinting.h"


const int bufSize = 100;

/*
 * Print all user processes
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
**/

// Prints all processes that belong to the user
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
				printOne(entry->d_name, state, userTime, sysTime, vMem, comLine, true);
			}
		}
		closedir(dir);
	}
}

/**
 * prints one process
 * pid is process ID to display
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
 * returns true if printed successfully
 * else returns false
**/

bool printOne(char* pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine, bool checkUser) {
	// Load files required for ps command
	char procRoot[bufSize];
	strcpy(procRoot, "/proc/");
	strcat(procRoot, pid);

	char statusFilename[bufSize];
	strcpy(statusFilename, procRoot);
	strcat(statusFilename, "/status");

	char statFilename[bufSize];
	strcpy(statFilename, procRoot);
	strcat(statFilename, "/stat");

	char statmFilename[bufSize];
	strcpy(statmFilename, procRoot);
	strcat(statmFilename, "/statm");

	char cmdFilename[bufSize];
	strcpy(cmdFilename, procRoot);
	strcat(cmdFilename, "/cmdline");

	// Create variables for process data
	char stat_state;
	int stat_pid;
	unsigned long int utime;
	unsigned long int stime;
	int vMemVal;
	char command[bufSize];

	// Check status file
	FILE *statusFile = fopen(statusFilename, "r");
	if(statusFile == NULL) {
		return false;
	} else if (checkUser) {
		// Get user id
		int uid = getuid();
		char statusLine[bufSize];
		// Get to the correct line in the status file
		for (int i = 0; i < 8; i++) {
			if (fgets(statusLine, bufSize, statusFile) == NULL) {
				return false;
			}
		}
		int process_uid;
		// Get process uid
		fscanf(statusFile, "%*s %d", &process_uid);
		// Check that uid matches process uid
		if (uid != process_uid) {
			return false;
		}
	}
	fclose(statusFile);

	// Check stat file
	FILE *statFile = fopen(statFilename, "r");
	if(statFile == NULL) {
		return false;
	} else {
		// Load data from stat file
		fscanf(statFile, "%d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu ", &stat_pid, &stat_state, &utime, &stime);
	}
	fclose(statFile);

	// Check statm file
	FILE *statmFile = fopen(statmFilename, "r");
	if(statmFile == NULL) {
		return false;
	} else {
		// Load data from stat file
		fscanf(statmFile, "%d", &vMemVal);
	}
	fclose(statmFile);

	// Check cmdLine file
	FILE *cmdFile = fopen(cmdFilename, "r");
	if(cmdFile == NULL) {
		return false;
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

	if(vMem) {
		printf(" %d", vMemVal);
	}

	if(comLine) {
		printf(" [%s]", command);
	}

	printf("\n");

	return true;
}
