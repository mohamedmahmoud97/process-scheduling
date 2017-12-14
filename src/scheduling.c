#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "scheduling.h"

#define RUNNING "running"
#define BLOCKED "blocked"
#define READY "ready"
#define FINISHED "finished"
#define NOTARRIVED "notarrived"


int main(int argc, char *argv[])
{
	FILE *inFile;
	FILE *outFile;

	int quantum_time;
	char*fileName;

	int algorithm = atoi(argv[1]);

	if(algorithm==1){
		quantum_time = atoi(argv[2]);
		fileName = argv[3];	
	}
	else{
		fileName = argv[2];	
	}

	readInputFile(inFile, fileName);

	blockedArray = malloc((no_proc-1) * sizeof(int));
	readyArray = malloc((no_proc-1) * sizeof(int));

	if(algorithm==0){
		printf("Algorithm will be used is FCFS\n");
		FCFS(outFile);
	}
	else if(algorithm==1){
		printf("Algorithm will be used is RR\n");
		RR(outFile,quantum_time);
	}

	return 0;
}

void readInputFile(FILE*inFile, char*fileName){

	bool fileFound = false;
	int temp; 

	//open file and set mode to read
	do
	{
    	inFile = fopen(fileName,"r");
    	if(!inFile)
    	{
        	printf("File Not Found!!\n");
           	fileFound=true;
    	}
    	else
        	fileFound=false;

	}while(fileFound);

	process = malloc(10 * sizeof(proc));

	for(int i=0; !feof(inFile); i++){
		no_proc++;
		process[i] = (struct proc*)malloc(sizeof(struct proc));
        for(int j=0; j<4; j++){
        	fscanf(inFile, "%d", &temp);
 			if(j==0){
 				process[i]->id = temp;
 			}
 			if(j==1){
 				process[i]->CPU_time = temp;
 			}
 			if(j==2){
 				process[i]->IO_time = temp;
 			}
 			if(j==3){
 				process[i]->arrival_time = temp;
 			}
        }
    }

}

void FCFS(FILE*outFile){

	bool fileFound = false;
	int simulation_time = 0;

	//open file and set mode to write 
	do
	{
    	outFile = fopen("sampleFCFS.out","w");
    	if(!outFile)
    	{
        	printf("File Not Found!!\n");
           	fileFound=true;
    	}
    	else
        	fileFound=false;

	}while(fileFound);

	//a variable to hold the id of the current process
	int now = -1;

	//a flag to know if there is a process not done
	int flagDone = 0;

	//clear flag if no process is running
	int	flagRun = 1;

	//make a counter for calculating no_cycles CPU is busy
	int busy_time = 0;

	//set all processes IO_done attribute to false
	for (int i = 0; i < no_proc-1; ++i)
	{
		process[i]->IO_done = false;
		process[i]->state = NOTARRIVED;
	}

	//the main loop of the running scheduling
	while(true){

		//set flag to zero each loop to check if all done
		flagDone = 0;

		//loop on all processes that hasn't started yet each time 
		//to check on the arrival time with the current simulation time
		for (int i = 0; i < no_proc-1; ++i)
		{
			if (process[i]->arrival_time == simulation_time)
			{
				insertR(process[i]->id);
				process[i]->state = READY;
			}
		}
		//loop on all processes in blocked state each time 
		//to check on the arrival time with the current simulation time
		for (int i = 0; i < no_proc-1; ++i)
		{
			if (process[i]->ready_time==simulation_time && strcmp(process[i]->state,BLOCKED)==0)
			{
				//here should remove this process from the block queue
				insertR(process[i]->id);
				process[i]->state = READY;
			}
		}

		//make the first process be the first running one and save id in now
		if (simulation_time == 0){
			now = removeDataR();
			process[now]->state = RUNNING;
			process[now]->start_time = simulation_time;
		}

		//if no process running and there is a process in queueR
		if (flagRun==0 && sizeR()!=0){
			now = getMin(readyArray,no_proc-1);
			now = removeDataR();
			process[now]->state = RUNNING;
			process[now]->start_time = simulation_time;
			flagRun = 1;
		}

		//save the now that will be changed in a temp variable
		int tempNow;

		//timetaken in running
		int timeTaken = simulation_time - process[now]->start_time + 1;

		//print in the file
		fprintf(outFile, "%d: ", simulation_time);
		printf("%d: ", simulation_time);
		for (int i = 0; i < no_proc-1; ++i)
		{
			if(strcmp(process[i]->state,FINISHED)!=0 && strcmp(process[i]->state,NOTARRIVED)!=0){
				printf("%d: ", process[i]->id);
				printf("%s   ", process[i]->state);
				fprintf(outFile, "%d: ", process[i]->id);
				fprintf(outFile, "%s  ", process[i]->state);
			}
			if (strcmp(process[i]->state,FINISHED)!=0){
				flagDone = 1;
			}
			if (strcmp(process[i]->state,RUNNING)==0){
				busy_time++;
			}
		}
		fprintf(outFile, "\n");
		printf("\n");

		if(process[now]->IO_done == false && timeTaken==process[now]->CPU_time){
			//block  the current process and add it to blockedArray
			insertB(now);
			process[now]->ready_time = simulation_time + process[now]->IO_time + 1;
			process[now]->state = BLOCKED;
			tempNow = now;

			//set the next process in now
			if(sizeR()==0){
				flagRun = 0;
			}
			else{
				now = removeDataR();
				//now = getMin(readyArray,no_proc-1);
				process[now]->state = RUNNING;
				process[now]->start_time = simulation_time + 1;
			}
		}

		else if (process[now]->IO_done == true && timeTaken==process[now]->CPU_time){
			//make the current state finished and calculate the turnaround time
			process[now]->turnaround_time = simulation_time-process[now]->arrival_time+1;
			process[now]->state = FINISHED;
			
			if(sizeR()==0){
				flagRun = 0;
			}
			else{
				now = removeDataR();
				//now = getMin(readyArray,no_proc-1);
				process[now]->state = RUNNING;
				process[now]->start_time = simulation_time + 1;
			}
		}

		process[tempNow]->IO_done = true;

		if (flagDone == 0)
		{
			break;
		}

		sleep(0.5);
		simulation_time++;
	}

	//print in the file the 
	fprintf(outFile, "\nFinishing time: %d\n", simulation_time-1);
	fprintf(outFile, "CPU Utilization: %.3f\n", (busy_time*1.0)/(simulation_time));	
	for (int i = 0; i < no_proc-1; ++i){
		fprintf(outFile, "Turnaround time of process %d: %d\n", process[i]->id, process[i]->turnaround_time);

	}

	return;
}

void RR(FILE*outFile, int quantum_time){

}

int getMin(int*array, int count){
	int min = 999999;
	for (int i = 0; i < count; ++i)
	{
		min = (array[i]<min)?array[i]:min;
	}
	return min;
}

int fpeek(FILE *stream)
{
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

bool isEmptyR() {
   return itemCountR == 0;
}

bool isFullR() {
   return itemCountR == no_proc-1;
}

int sizeR() {
   return itemCountR;
}  

void insertR(int id) {

   if(!isFullR()) {
	
      if(rearR == no_proc-1-1) {
         rearR = -1;            
      }       

      readyArray[++rearR] = id;
      itemCountR++;
   }
}

int removeDataR() {
   int data = readyArray[frontR++];
	
   if(frontR == no_proc-1) {
      frontR = 0;
   }
	
   itemCountR--;
   return data;  
}

bool isEmptyB() {
   return itemCountB == 0;
}

bool isFullB() {
   return itemCountB == no_proc-1;
}

int sizeB() {
   return itemCountB;
}  

void insertB(int id) {

   if(!isFullB()) {
	
      if(rearB == no_proc-1-1) {
         rearB = -1;            
      }       

      blockedArray[++rearB] = id;
      itemCountB++;
   }
}

int removeDataB() {
   int data = blockedArray[frontB++];
	
   if(frontB == no_proc-1) {
      frontB = 0;
   }
	
   itemCountB--;
   return data;  
}