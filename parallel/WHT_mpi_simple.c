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

		averow = dim / numworkers; extra = dim % numworkers;

		offset = 0; mtype = FROM_MASTER;

		//Send

		for(dest = 1; dest < numworkers; dest++){

			rows = (dest <= extra) ? averow + 1 : averow;

			MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);

			MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);

			count = rows*dim;

			MPI_Send(&matrix[offset][0], count, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);

			count = dim;

			MPI_Send(&vector, count, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);

			offset = offset + rows;

		}

		

		//Recieve from workers



	}

	/********** worker process **********/

	if(procid > MASTER){

		//Receive the Data

		mtype = FROM_MASTER;

		source = MASTER;

		MPI_Recv(&offset,1,MPI_INT,source,mtype,MPI_COMM_WORLD, &status);

    	MPI_Recv(&rows,1,MPI_INT,source,mtype,MPI_COMM_WORLD, &status);

	

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