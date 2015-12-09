/*
 *  Walsh Hadamard Trasnform Fast
 *  OpenMP Implementation
 *  @authors
 *  	Harsh Shah
 *  	Davidek Lambropoulos
 *  	Demetrios Lambropoulos
 */


#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"

int bitwise_dotproduct(int input){
	int numOneBits = 0;
	int currNum = input;
	while(currNum != 0){
		if((currNum & 1) == 1){
			numOneBits++;
		}
		currNum = currNum >> 1;
	}
	return numOneBits;
}

int hadamard_entry(int k , int n){
	int a = k & n;
	int count = bitwise_dotproduct(a);
	if((count % 2) == 0){
		return 1;
	}
	return -1;
}


int main(int argc, char* argv[]){
	//input
	unsigned long m;
	m = atoi(argv[1]);

	//Determine dimension of matrix and vector
	unsigned long dim = (int)(pow(2, m));

	int*  vector;


	int iter = 0;

	vector = (int*)malloc(sizeof(int)*dim);

	//Initialize the Vector
	for(iter = 0; iter < dim; iter++){
		vector[iter] = iter;
		printf("%d ", vector[iter]);
	}

	printf("\n");
	//Initialize result vector
	int *result;
	result = (int*)malloc(sizeof(int)*dim);
	for(iter = 0; iter < dim; iter++){
		result[iter] = 0;
	}

	//Used for timing
	double starttime, endtime;
	starttime = get_time();
	int count = 0;
	/********* start openmp *******/
	int nthreads, tid;
	nthreads = omp_get_num_threads();
	int i;
	for(i = dim/2; i > 1; i = i/2){
		printf("i : %d\n", i);
		int j;
		for(j = 0; j < i; j = j + i){
			int z;
			for(z = j; z < j + i; z++){
				result[z] = vector[z] + vector[z + i];
				result[z+i] = vector[z] - vector[z + i];
			}
			printf("\n");
		}
		for(iter = 0; iter < dim; iter++){
			vector[iter] = result[iter];
			printf("%d ", vector[iter]);
		}
		printf("\n");
	}

	/********* end openmp *********/
	endtime = get_time();
	printf("Elapsed time %g\n ", (endtime - starttime));
	for(iter = 0; iter < dim; iter++){
		printf(" %d ", vector[iter]);
	}

	free(vector);
	free(result);

	return EXIT_SUCCESS;
}
