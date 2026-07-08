#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARS 64
#define MAX_LINE 128

typedef struct{
    char name[32];
    int value;
} Var;
Var vars[MAX_VARS];
int varCount = 0;
// Search a variable by it's name
int findVar(char *name){
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}
// Create a new variable if it doesn't exists
int getOrCreateVar(char *name){
    int idx = findVar(name);
    if (idx != -1) return idx;
    strcpy(vars[varCount].name, name);
    vars[varCount].value = 0;
    varCount++;
    return varCount - 1;
}
int main(){
    char line[MAX_LINE];
    char cmd[16], name[32];
    int number;
    printf("picoDB\nSET, ADD, PRINT or EXIT\n");
    while (1) {
        printf("picoDB> ");
        // Input
        if (fgets(line, MAX_LINE, stdin) == NULL) break;
        if (strncmp(line, "EXIT", 4) == 0) break;
        if (sscanf(line, "%s %s %d", cmd, name, &number) >= 2) {
            // Process
            if (strcmp(cmd, "SET") == 0) {
                int idx = getOrCreateVar(name);
                vars[idx].value = number;
            }
            else if (strcmp(cmd, "ADD") == 0) {
                int idx = getOrCreateVar(name);
                vars[idx].value += number;
            }
            else if (strcmp(cmd, "PRINT") == 0) {
                int idx = findVar(name);
                // Output
                if (idx != -1) {
                    printf("%s = %d\n", vars[idx].name, vars[idx].value);
                } else {
                    printf("ERROR: Variable not found\n");
                }
            }
            else {
                printf("ERROR: Unknown command\n");
            }
        }
    }
    printf("Adios.\n");
    return 0;
}
