#include <stdbool.h>

int main(int argc, char* argv[]);
void printAll(bool state, bool userTime, bool sysTime, bool vMem, bool comLine);
void printOne(char* pid, bool state, bool userTime, bool sysTime, bool vMem, bool comLine);
void splitString(char* dest[], char *str, const char *delim);
