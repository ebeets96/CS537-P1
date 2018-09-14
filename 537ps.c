#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "537ps.h"

int main(int argc, char* argv[]) {
	// // For debugging
	// if(argc < 2)
	// 	return -1;
	
	int pid = -1;
	bool s = false;
	bool U = true;
	bool S = false;
	bool v = false;
	bool c = true;

	// Handle passed arguments
	char opt;
	while ((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch (opt) {
			case 'p':
				if (atoi(optarg) != 0) {
					pid = atoi(optarg);
				} else {
					// Argument is not an integer
				}
				break;
			case 's':
				s = true;
				break;
			case 'U':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
					U = false;
				}
				break;
			case 'S':
				S = true;
				break;
			case 'v':
				v = true;
				break;
			case 'c':
				if (optarg != NULL && strcmp(optarg, "-") == 0) {
					c = false;
				}
				break;
		}
	}	

	// For testing 
	printf("pid: %d\n", pid);
	printf("s flag: %s\n", s ? "true" : "false");
	printf("U flag: %s\n", U ? "true" : "false");
	printf("S flag: %s\n", S ? "true" : "false");
	printf("v flag: %s\n", v ? "true" : "false");
	printf("c flag: %s\n", c ? "true" : "false");
	//

	// Call ps function with all true values
	// Replace when argument passing is accomplished

	//printAll(true, true, true, true, true);
	// printOne(atoi(argv[1]), true, true, true, true, true); //Dummy pid for testing

	return 0;
}

void printAll(bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {
	// Read folders in /proc directory

	// Call printOne on each process
}

/**
 * pid is process ID to display and equals -1 to show all processes
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
**/

void printOne(int pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {

}
