#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define FROM_MASTER 1  /* setting a message type */
#define FROM_WORKER 2  /* setting a message type */


//Performs a bitwise dot product
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

//Calculates the value of the Hadamard matrix at any index
int hadamard_entry(int k, int n){
	int a = k & n;
    	int count = bitwise_dotproduct(a);
	if((count % 2) == 0){
		return 1;
	}
	return -1;
}

MPI_Status status;

int main(int argc, char **argv){

	//Dimension Paramter dim
	int dim = (int)pow(2,(double)atoi(argv[1]));

	//MPI Parameters for Initialization and Communication
	int procid, numprocs, numworkers;
	int dest;

	//Allocate Memory for arguements
	int  *vector;

	//Initiliaze the vector
	vector = (int*)malloc(sizeof(int)*dim);
	int iter;
	for(iter = 0; iter < dim; iter++){
		vector[iter] = 1;
	}

	//Initialize Result Vector
	int *result = (int*)malloc(sizeof(int)*dim);

	//Calculated Data Chunks to Send and Recieve
	int start_index, end_index, width, extra;
	int temp = 0;


	//Initialize MPI Framework
	MPI_Init(&argc, &argv);
	//Assign IDs to all the nodes
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	//Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	//Num workers is one minus processes due to master process
	numworkers = numprocs - 1;
	width = (dim/numprocs);

	//Broadcast Arrays to all processors
	MPI_Bcast(&width, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
	MPI_Bcast(&(vector[0]), dim, MPI_INT, MASTER, MPI_COMM_WORLD);
	MPI_Bcast(&dim, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
	MPI_Bcast(&(result[0]), dim, MPI_INT, MASTER, MPI_COMM_WORLD);

	/********** master process **********/
	if(procid == MASTER){
		width = (dim)/numprocs;
		if(width == 0){	//Number of workers > elements of the matrix
			start_index = 0;
			end_index = start_index + dim - 1;
			for(dest = 1; dest <= numworkers; dest++){
				MPI_Send(&start_index, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
				MPI_Send(&end_index, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
				start_index = end_index + 1;
				end_index = start_index + dim - 1;
			}
		}else{		//Number of workers < elements of the matrix
			start_index = 0;
			end_index = (width*dim) - 1;
			for(dest = 1; dest <= numworkers; dest++){
				MPI_Send(&start_index, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
				MPI_Send(&end_index, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
				start_index = end_index + 1;
				end_index = start_index + (width*dim) - 1;
			}
			//Master Will do work
			while(start_index <= ((dim*dim) - 1)){
				int h_i = start_index / dim;
				int h_j = 0;
				int t_end = h_i + width - 1;
				while(h_i <= t_end){
					int value = 0;
					for(h_j = 0; h_j < dim; h_j = h_j + 1){
						value += hadamard_entry(h_i, h_j);
					}
					result[h_i] = value;
					printf("(%d, %d) : %d\n", h_i, h_j, value);
					h_i = h_i + 1;
				}
				start_index = end_index + 1;
				end_index = start_index + (width*dim) - 1;
			}
		}
	}
	/********** worker process **********/
	if(procid > MASTER){
		if(width == 0){
			if(procid > dim){
				//No work for this process
			}else{
				MPI_Recv(&start_index, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);
				MPI_Recv(&end_index, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);
				int h_i = start_index/dim;
				int h_j = 0;
				int value = 0;
				for(h_j = 0; h_j < dim; h_j++){
					value += hadamard_entry(h_i, h_j) + vector[h_j];
				}
				result[h_i] = value;
				printf("(%d,%d) : %d\n", h_i, h_j, value);
			}
		}

		if(width != 0){	
			MPI_Recv(&start_index, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);
			MPI_Recv(&end_index, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);
			int h_i = start_index / dim; //Hadamard Matrix Index i
			int h_j = 0; //Hadamard Matrix index j
			int t_end = h_i + width - 1;
	
			while(h_i <= t_end){

				int value = 0;
				for(h_j = 0; h_j < dim; h_j = h_j + 1){
					value += hadamard_entry(h_i, h_j) + vector[h_j];
				}
				result[h_i] = value;
				printf("(%d,%d) : %d\n", h_i, h_j, value);
				h_i = h_i + 1;
			}
		}

	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();


	free(result);
	free(vector);
	return EXIT_SUCCESS;
}

