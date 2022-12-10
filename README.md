# How to Run
Using the following command compiles the program and creates an execution file:
```bash
$ make
```

The following command executes the program:
```bash
$ ./proj3 FILE ALGO
# The program requires two additional arguments to function properly: the file name (including
# the file extension) and the initials of select scheduling algorithms. The available algorithms 
# are:
# - RR (Round Robin)
# - SRT (Shortest Remaining Time)
# - FB (Feedback)
# - ALL (selects all algorithms above)
# *Replace the parameters with an argument
```
Additioanlly, the text file should be formatted such that each line as a job name, an arrival time, and a duration in order, tab-delimited. The job names should be ordered alphabetically, with the first letter at the top. The arrival times should be in order, with the first job beginning at time 0.

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



