/*
	Walsh Hadamard Transform
	MPI Implementation
	@author
		Harsh Shah
		Demetrios Lambropoulos
		Davidek Lambropoulos
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"



#define MASTER 0       /* id of the first process */ 
#define FROM_MASTER 1  /* setting a message type */ 
#define FROM_WORKER 2  /* setting a message type */

MPI_status status;

int bitwise_dotproduct(int input) {
  int numOneBits = 0;

  int currNum = input;
  while (currNum != 0) {
    if ((currNum & 1) == 1) {
      numOneBits++;
    }
    currNum = currNum >> 1;
  }
  return numOneBits;
} 

int hadamard_entry(int k, int n){
	int a = k & n;
    int count = bitwise_dotproduct(a); 
	if((count % 2) == 0){
		return 1;
	}
	return -1;
}

main(int argc, char **argv){
	
	//Dimension Paramter dim
	int dim = (int)pow(2,(double)atoi(argv[1]));
	
	//Send and Recievce Parameters	
	int numprocs,   /* number of processes in partition */
    procid,         /* a process identifier */ 
    numworkers,     /* number of worker processes */
    source,         /* process id of message source */
    dest,           /* process id of message destination */
    nbytes,         /* number of bytes in message */
    mtype,          /* message type */
    intsize,        /* size of an integer in bytes */
    dbsize,         /* size of a double float in bytes */
    rows,           /* rows of A sent to each worker */ 
    averow, extra, offset, 
    i, j, k, count;

	//Allocate Memory for arguements
	int iter = 0;	
	double **matrix;
	matrix = (double**)malloc(sizeof(double**)*dim);
	for(iter = 0; iter < dim; iter++){
		matrix[iter] = (double*)malloc(sizeof(double)*dim);
	}
	double *vector = (double*)malloc(sizeof(double)*dim);
	double *result = (double*)malloc(sizeof(double)*dim);

	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);	
	numworkers = numprocs - 1;
	
	
	/********** master process **********/
	if(procid == MASTER){
		//Initialize Hadamard Matrix
		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++){
				matrix[i][j] = hadamard_entry(i,j);
			}
		}
		//Initialize Argument Vector
		for(i = 0; i < dim; i++){
			vector[i] = rand()%2;	
		}
		//Send Parameters
		
		//Recieve from workers
	}
	/********** worker process **********/
	if(procid > MASTER){
		//Receive the Date
		//Operate on the data
		//Send the data
	}

	MPI_Finalize();
	
	free(vector);
	free(result);
	iter = 0;
	for(iter = 0; iter < dim; iter++){
		free(matrix[i]);	
	}
	free(matrix);

}