#include <stdlib.h>
#include <string.h>

void assignString(char** var, char* string) {
    *var = (char*) malloc(strlen(string) * sizeof(char));
    strcpy(*var, string);
}