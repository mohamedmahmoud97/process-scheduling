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
				deleteB(process[i]->id);
				insertR(process[i]->id);
				process[i]->state = READY;
			}
		}

		//make the first process be the first running one and save id in now
		if (simulation_time == 0){
			int k=0;
			while(readyArray[k]==-99){
				k++;
			}
			now = readyArray[k];
			deleteR(now);
			process[now]->state = RUNNING;
			process[now]->start_time = simulation_time;
		}

		//if no process running and there is a process in queueR
		if (flagRun==0 && itemCountR!=0){
			int k=0;
			while(readyArray[k]==-99){
				k++;
			}
			now = readyArray[k];
			deleteR(now);
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
			if(itemCountR==0){
				flagRun = 0;
			}
			else{
				now = readyArray[0];
				deleteR(now);
				process[now]->state = RUNNING;
				process[now]->start_time = simulation_time + 1;
			}
		}
		else if (process[now]->IO_done == true && timeTaken==process[now]->CPU_time){
			//make the current state finished and calculate the turnaround time
			process[now]->turnaround_time = simulation_time-process[now]->arrival_time+1;
			process[now]->state = FINISHED;

			if(itemCountR==0){
				flagRun = 0;
			}
			else{
				now = readyArray[0];
				deleteR(now);
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

/* Function to create an empty priority queue */
void createR(){
    frontR = rearR = -1;
}

/* Function to insert value into priority queue */
void insertR(int data){
    if (rearR >= no_proc - 2){
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((frontR == -1) && (rearR == -1)){
        frontR++;
        rearR++;
        readyArray[rearR] = data;
        return;
    }
    else
        checkR(data);
    rearR++;
		itemCountR++;
}

/* Function to check priority and place element */
void checkR(int data){
    int i,j;

    for (i = 0; i <= rearR; i++){
        if (data < readyArray[i]){
            for (j = rearR + 1; j > i; j--){
                readyArray[j] = readyArray[j - 1];
            }
            readyArray[i] = data;
            return;
        }
    }
    readyArray[i] = data;
}

/* Function to delete an element from queue */
void deleteR(int data){
		int i;

    if ((frontR==-1) && (rearR==-1)){
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearR; i++){
        if (data == readyArray[i]){
            for (; i < rearR; i++){
                readyArray[i] = readyArray[i + 1];
            }

        readyArray[i] = -99;

        rearR--;

        if (rearR == -1)
            frontR = -1;

				itemCountR--;
				return;
			}
    }
    printf("\n%d not found in queue to delete", data);
}

/* Function to create an empty priority queue */
void createB(){
    frontB = rearB = -1;
}

/* Function to insert value into priority queue */
void insertB(int data){
    if (rearB >= no_proc - 2){
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((frontB == -1) && (rearB == -1)){
        frontB++;
        rearB++;
        readyArray[rearB] = data;
        return;
    }
    else
        checkB(data);
    rearB++;
		itemCountB++;
}

/* Function to check priority and place element */
void checkB(int data){
    int i,j;

    for (i = 0; i <= rearB; i++){
        if (data < readyArray[i]){
            for (j = rearB + 1; j > i; j--){
                readyArray[j] = readyArray[j - 1];
            }
            readyArray[i] = data;
            return;
        }
    }
    readyArray[i] = data;
}

/* Function to delete an element from queue */
void deleteB(int data){
		int i;

    if ((frontB==-1) && (rearB==-1)){
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearB; i++){
        if (data == readyArray[i]){
            for (; i < rearB; i++){
                readyArray[i] = readyArray[i + 1];
            }

        readyArray[i] = -99;

        rearB--;

        if (rearB == -1)
            frontB = -1;

				itemCountB--;
				return;
			}
    }
    printf("\n%d not found in queue to delete", data);
}
