# picoDB
  
Extremely simple SQL-inspired database program, just a little project for learning.  
  
## Commands
  
- `SET name value` → creates (or replaces) a variable with a value
- `ADD name value` → sums a value to a variable (if it doesn't exists it makes it)
- `PRINT name` → prints value of a variable
- `EXIT` → exit the program
  
## Supported types
  
- Integers: `SET x 10`
- Floats: `SET y 2.5` (automatically detected with the floating point)
- Strings: `SET s "Hello, World!"` (double quotation marks are required)
  
## Compiling
  
```bash
gcc main.c -o picodb
./picodb
```
  
## Session example
  
```
picoDB> SET x 10
picoDB> ADD x 5
picoDB> SET y 2.5
picoDB> ADD y 1.5
picoDB> SET s "Hello"
picoDB> ADD s " World"
picoDB> PRINT x
x = 15
picoDB> PRINT y
y = 4
picoDB> PRINT s
s = Hello World
picoDB> EXIT
```
