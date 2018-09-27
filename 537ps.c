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

int main(int argc, char* argv[]) {

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

	if (optind < argc) {
                printf("Incorrect argument\n");
                validEntry = false;
        }

	if (validEntry == false) {
		return 1;
	}

	if (strcmp(pid, "") == 0) {
		printAll(s, U, S, v, c);
	} else {
		if (!printOne(pid, s, U, S, v, c, false)) {
			printf("No such process: %s\n", pid);
		}
	}

	return 0;
}
