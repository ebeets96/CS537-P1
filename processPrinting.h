/*
 * Eric Beets (beets) & Jack David (jackd)
*/

#include <stdbool.h>

void printAll(bool state, bool userTime, bool sysTime, bool vMem, bool comLine);
bool printOne(char* pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine, bool checkUser);
