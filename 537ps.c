/*
 * Eric Beets (beets) & Jack David (jackd)
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include "537ps.h"

const int bufSize = 100;

int main(int argc, char* argv[]) {
	// // For debugging
	// if(argc < 2)
	// 	return -1;

	char* pid = "";
	bool s = false;
	bool U = true;
	bool S = false;
	bool v = false;
	bool c = true;
	bool validEntry = true;

	// Handle passed arguments
	char opt;
	while ((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch (opt) {
			case 'p':
				if (optarg != NULL && atoi(optarg) != 0) {
					pid = optarg;
				} else {
					printf("Must provide a PID integer\n");
					validEntry = false;
				}
				break;
			case 's':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
					s = false;;
				} else if (optarg == NULL) {
					s = true;
				} else {
					printf("Usage: -s or -s-\n");
					validEntry = false;
				}
				break;
			case 'U':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
					U = false;
				} else if (optarg == NULL) {
					U = true;
				} else {
					printf("Usage: -U or -U-\n");
					validEntry = false;
				}
				break;
			case 'S':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
                                        S = false;
                                } else if (optarg == NULL) {
                                        S = true;
                                } else {
                                        printf("Usage: -U or -U-\n");
					validEntry = false;
                                }
                                break;
			case 'v':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
                                        v = false;
                                } else if (optarg == NULL) {
                                        v = true;
                                } else {
                                        printf("Usage: -v or -v-\n");
					validEntry = false;
                                }
                                break;
			case 'c':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
                                        c = false;
                                } else if (optarg == NULL) {
                                        c = true;
                                } else {
                                        printf("Usage: -c or -c-\n");
					validEntry = false;
                                }
                                break;
		}
	}

	if (validEntry == false) {
		return 1;
	}

	if (strcmp(pid, "") == 0) {
		printAll(s, U, S, v, c);
	} else {
		printOne(pid, s, U, S, v, c);
	}

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
		return;
	} else {
		// Get user id
		int uid = getuid();
		char statusLine[bufSize];
		// Get to the correct line in the status file
		for (int i = 0; i < 8; i++) {
			if (fgets(statusLine, bufSize, statusFile) == NULL) {
				return;
			}
		}
		int process_uid;
		// Get process uid
		fscanf(statusFile, "%*s %d", &process_uid);
		// Check that uid matches process uid
		if (uid != process_uid) {
			return;
		}
	}
	fclose(statusFile);

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

	if(vMem) {
		printf(" %d", vMemVal);
	}

	if(comLine) {
		printf(" [%s]", command);
	}

	printf("\n");

}
