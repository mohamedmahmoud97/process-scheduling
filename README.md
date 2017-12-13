# Process Scheduling Program

It's a program that simulates two operating system scheduling
algorithms:

- First Come First Served (FCFS)
- Round Robin (RR)

The program reads an input file that lists the information of the processes that need to be scheduled to run on the processor.


You can use the included Makefile to compile your code and run the test cases.

- You will need to type the command 'make' to build the code.
```
[uname@hostname ~]$ make
```

- You will need to type the command 'make run' to run the test cases.
```
[uname@hostname ~]$ make run
```

- You may use ./scheduling x y z to test the program for algorithm x%, quantum time y% if used RR algorithm, and filename z%.
```
[uname@hostname ~]$ ./scheduling 0 sample
```
OR
```
[uname@hostname ~]$ ./scheduling 1 5 sample
```