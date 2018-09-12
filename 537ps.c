#include <stdio.h>
#include <stdbool.h> 
#include "537ps.h"

int main(int argc, char* argv[]) {
	// Handle passed arguments

	// Call ps function with all true values
	// Replace when argument passing is accomplished
	ps(-1, true, true, true, true, true);
	return 0;
}

/**
 * pid is process ID to display and equals -1 to show all processes
 * state represents -s flag
 * userTime represents -U flag
 * sysTime represents -S flag
 * vMem represents -v flag
 * comLine represents -c flag
**/

void ps(int pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine) {

}
