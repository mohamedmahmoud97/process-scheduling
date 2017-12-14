#include <stdio.h>
#include <stdlib.h>

typedef struct proc{
    int id;
    int CPU_time;
    int IO_time;
    int arrival_time;
    bool IO_done;
    char*state;
    int ready_time;
    int start_time;
    int turnaround_time;
}proc;

struct proc **process;
int no_proc=0;
int *blockedArray;
int *readyArray;
int frontR = 0;
int rearR = -1;
int itemCountR = 0;
int frontB = 0;
int rearB = -1;
int itemCountB = 0;

void readInputFile(FILE*inFile, char*fileName);
int getMin(int*array, int count);
int fpeek(FILE *stream);
void FCFS(FILE*outFile);
void RR(FILE*outFile, int quantum_time);
bool isEmptyR();
bool isFullR();
int sizeR();
void insertR(int id);
int removeDataR();
bool isEmptyB();
bool isFullB();
int sizeB();
void insertB(int id);
int removeDataB();