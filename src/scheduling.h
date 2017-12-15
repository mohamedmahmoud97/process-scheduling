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
int frontR;
int rearR;
int itemCountR = 0;
int frontB;
int rearB;
int itemCountB = 0;

void readInputFile(FILE*inFile, char*fileName);
int getMin(int*array, int count);
int fpeek(FILE *stream);
void FCFS(FILE*outFile);
void RR(FILE*outFile, int quantum_time);

void createR();
void insertR(int data);
void checkR(int data);
void deleteR(int data);

void createB();
void insertB(int data);
void checkB(int data);
void deleteB(int data);
