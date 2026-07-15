#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 64
#define MAX_LINE 128
#define MAX_VAL 64
const char *DB_FILE;

typedef struct {
  char name[32];
  char type;
  char value[MAX_VAL];
} Var;
Var vars[MAX_VARS];
int varCount = 0;
// Search a variable by it's name
int findVar(char *name) {
  for (int i = 0; i < varCount; i++) {
    if (strcmp(vars[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}
// Create a new variable if it doesn't exists
int getOrCreateVar(char *name) {
  int idx = findVar(name);
  if (idx != -1)
    return idx;
  if (varCount >= MAX_VARS)
    return -1;
  strcpy(vars[varCount].name, name);
  vars[varCount].type = 'I';
  vars[varCount].value[0] = '\0';
  varCount++;
  return varCount - 1;
}
char detectType(char *raw) {
  if (raw[0] == '"')
    return 'S';
  if (strchr(raw, '.') != NULL)
    return 'F';
  return 'I';
}
void cleanString(char *raw, char *out) {
  int len = strlen(raw);
  if (len >= 2 && raw[0] == '"' && raw[len - 1] == '"') {
    strncpy(out, raw + 1, len - 2);
    out[len - 2] = '\0';
  } else {
    strcpy(out, raw);
  }
}
// Save database
void saveDB() {
  FILE *f = fopen(DB_FILE, "w");
  if (!f)
    return;
  for (int i = 0; i < varCount; i++) {
    fprintf(f, "%s|%c|%s\n", vars[i].name, vars[i].type, vars[i].value);
  }
  fclose(f);
}
// Load database
void loadDB() {
  FILE *f = fopen(DB_FILE, "r");
  if (!f)
    return;
  char line[MAX_LINE];
  while (fgets(line, MAX_LINE, f) != NULL) {
    if (varCount >= MAX_VARS)
      break;
    char name[32], value[MAX_VAL];
    char type;
    char *p = strtok(line, "|");
    if (!p)
      continue;
    strcpy(name, p);
    p = strtok(NULL, "|");
    if (!p)
      continue;
    type = p[0];
    p = strtok(NULL, "\n");
    if (!p)
      continue;
    strcpy(value, p);
    strcpy(vars[varCount].name, name);
    vars[varCount].type = type;
    strcpy(vars[varCount].value, value);
    varCount++;
  }
  fclose(f);
}
int main(int argc, char *argv[]) {
  char line[MAX_LINE];
  char cmd[16], name[32], rawValue[MAX_VAL];
  if (argc < 2) {
    printf("Usage: %s <filename.picodb>\n", argv[0]);
    return 1;
  }
  DB_FILE = argv[1];
  // Initial input (load)
  loadDB();
  printf("picoDB\nSET, ADD, PRINT or EXIT\n");
  while (1) {
    printf("picoDB> ");
    // Input
    if (fgets(line, MAX_LINE, stdin) == NULL)
      break;
    if (strncmp(line, "EXIT", 4) == 0)
      break;
    rawValue[0] = '\0';
    if (sscanf(line, "%15s %31s %63[^\n]", cmd, name, rawValue) >= 2) {
      // Process
      if (strcmp(cmd, "SET") == 0) {
        int idx = getOrCreateVar(name);
        if (idx == -1) {
          printf("ERROR: Too many variables\n");
          continue;
        }
        char type = detectType(rawValue);
        char clean[MAX_VAL];
        cleanString(rawValue, clean);
        vars[idx].type = type;
        strcpy(vars[idx].value, clean);
      } else if (strcmp(cmd, "ADD") == 0) {
        int idx = getOrCreateVar(name);
        if (idx == -1) {
          printf("ERROR: Too many variables\n");
          continue;
        }
        char type = detectType(rawValue);
        if (vars[idx].type == 'S' || type == 'S') {
          char clean[MAX_VAL];
          cleanString(rawValue, clean);
          strcat(vars[idx].value, clean);
          vars[idx].type = 'S';
        } else if (vars[idx].type == 'F' || type == 'F') {
          double result = atof(vars[idx].value) + atof(rawValue);
          snprintf(vars[idx].value, MAX_VAL, "%g", result);
          vars[idx].type = 'F';
        } else {
          int result = atoi(vars[idx].value) + atoi(rawValue);
          snprintf(vars[idx].value, MAX_VAL, "%d", result);
        }
      } else if (strcmp(cmd, "PRINT") == 0) {
        int idx = findVar(name);
        // Output
        if (idx != -1) {
          printf("%s = %s\n", vars[idx].name, vars[idx].value);
        } else {
          printf("ERROR: Variable not found\n");
        }
      } else {
        printf("ERROR: Unknown command\n");
      }
    }
  }
  saveDB();
  printf("Goodbye.\n");
  return 0;
}
