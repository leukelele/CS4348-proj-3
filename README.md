# How to Run
Using the following command compiles the program and creates an execution file:
```bash
$ make
```

The following command executes the program:
```bash
$ ./proj3 FILE ALGO
# The program requires two additional arguments to function properly: the file name (including
# the file extension) and the initials of select scheduling algorithms. The available algorithms are:
# - RR (Round Robin)
# - SRT (Shortest Remaining Time)
# - FB (Feedback)
# - ALL (selects all algorithms above)
# *Replace the parameters with an argument
```

To clean up the files, use the following command:
```bash
$ make clean
```

## Examples
```bash
$ ./proj3 jobs.txt RR
```
```bash
$ ./proj3 jobs.txt SRT
```
```bash
$ ./proj3 jobs.txt FB
```
```bash
$ ./proj3 jobs.txt ALL
```



