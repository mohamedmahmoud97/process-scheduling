#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scheduling.h"

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

	printf("%d\n", no_proc);
	printf("Processes:\n");
	for(int i=0;i<no_proc;i++)
	{
	   printf("%d %d %d %d\n", process[i]->id, process[i]->CPU_time, process[i]->IO_time, process[i]->arrival_time);
	}

	return 0;
}

void readInputFile(FILE*inFile, char*fileName){

	bool fileFound = false;
	int temp, i = 0;

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
	
	
	//Read matrix A of unknown sizefrom file 1
	/*while(!feof(inFile))
	{
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
        i++;
	}*/

}