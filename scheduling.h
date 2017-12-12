#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int id;
    int CPU_time;
    int IO_time;
    int arrival_time;
    int turnaroud_time;
}process;

void readInputFile(FILE*inFile);
