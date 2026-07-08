# picoDB
  
Extremely simple SQL-inspired database program, just a little project for learning.  
  
**THIS PROGRAM IS A WORK IN PROGRESS.**  
It does not save anything after closing it and it only supports integers, I'm working for adding strings, floats and save the data in a file (something like SQLite probably?).

## Commands
  
- `SET name value` → creates (or replaces) a variable with a value
- `ADD name value` → sums a value to a variable (if it doesn't exists it makes it)
- `PRINT name` → prints value of a variable
- `EXIT` → exit the program

## Compiling
  
```bash
gcc main.c -o picodb
./picodb
```

## Session example
  
```
picoDB> SET x 10
picoDB> ADD x 5
picoDB> PRINT x
x = 15
picoDB> EXIT
```
