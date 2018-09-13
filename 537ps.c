#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
	printf("Called");
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir("/proc")) == NULL) {
		//Error handling
		printf("errors");
	} else {
		while ((entry = readdir(dir)) != NULL) {
			printf("  %s\n", entry->d_name);
		}
		closedir(dir);
	}
	// Call printOne on each process
}

/**
 * pid is process ID to display
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
**/

void printOne(int pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {

}
