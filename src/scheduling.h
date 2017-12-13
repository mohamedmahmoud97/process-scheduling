#include <stdio.h>
#include <stdlib.h>

typedef struct proc{
    int id;
    int CPU_time;
    int IO_time;
    int arrival_time;
    int turnaroud_time;
}proc;

struct proc **process;
int no_proc=0;

void readInputFile(FILE*inFile, char*fileName);
