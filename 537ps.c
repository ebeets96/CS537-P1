#include <stdio.h>
#include <stdbool.h>
#include "537ps.h"

int main(int argc, char* argv[]) {
	// // For debugging
	// if(argc < 2)
	// 	return -1;

	// Handle passed arguments


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
