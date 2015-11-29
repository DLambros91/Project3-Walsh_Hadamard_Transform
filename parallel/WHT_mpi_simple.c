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
		//Initialize Argument Vector
		//Send Matrix to workers
		//Send Vector to workers
		//Send dim to workers

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