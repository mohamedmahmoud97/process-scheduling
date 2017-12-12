#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void startRandommat();
void initRandomMat(double** X,int r,int c,int limit);
void nonThreadedMatMult(double**A, double**B, FILE*outFile);
void readMatrixFiles(FILE*inFile1, FILE*inFile2);
int threadedMatMultPerElement(char *argv[], FILE*outFile);
void *elementCalc(void*param);
int threadedMatMultPerRow(char *argv[], FILE*outFile);
void *rowCalc(void*param);
int fpeek(FILE *stream);

int x=0, y_1=0, y2=0, z=0;
int a=0,b=0,c=0;
double **A, **B, **C;

typedef struct process{
    int id;
    int CPU_time;
    int IO_time;
    int arrival_time;
    int turnaroud_time;
}process;

int main(int argc, char *argv[])
{
	FILE *inFile;
	FILE *outFile;

	readInputFile(inFile1);	
	nonThreadedMatMult(A,B,outFile);
	noOfTinE = threadedMatMultPerElement(argv, outFile);
	noOfTinR = threadedMatMultPerRow(argv, outFile);
	printf("# of threads in elements used: %d\n", noOfTinE);
	printf("# of threads in rows used: %d\1", noOfTinR);

	free(A);
	free(B);
	//fclose(inFile1);
    //fclose(inFile2);
    //fclose(outFile);

	return 0;
}