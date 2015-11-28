/*
 * Walsh Hadamard Transform
 * Serial Implementation
 * @author
 * 	Harsh Shah
 * 	David Lambropolos
 * 	Demetrios Lambropoulos
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int main(int argc, char** argv){
	
	int m; //used for dimension calculation for vector and matrix
	
	printf("Please Enter the m in 2^m \n");
	scanf("%d", &m);

	int dimension = (int)pow(2, (double)m);

	//Display Input to user
	printf("Input M is: %d ", m);
	printf("Row and Column size is %d", dimension);

	//Allocate Vector
	int *vector = (int*)malloc(dimension * sizeof(int));
		
	//Allocate Matrix
	int ** matrix;
	matrix = (int**)malloc(sizeof(int**)* dimension);
	int z = 0;
	for(; z < dimension; z++){
		matrix[z] = (int*)malloc(sizeof(int)*dimension);
	}

	//Allocate Result Vector
	int* result = (int*)malloc(sizeof(int) * dimension);

	//Fill vector with random integers
	z = 0;
	for(; z < dimension; z++){
		vector[z] = rand()%2;
	}


	//Generate the Hadamard Matrix
	int i,j;
	for(i = 0; i < dimension; i++){
		for(j = 0; j < dimension; j++){ //iterate through matrix
			unsigned int PosOrNeg = (i*j) && (UINT_MAX); //AND the Product of the location indices with a string one '1''s 
			int ones = __builtin_popcount(PosOrNeg); //Count the number of ones in PosOrNeg to decide if index should be 1 or -1
			if((ones % 2) == 0){
				matrix[i][j] = 1;
			}else{
				matrix[i][j] = -1;
			}
		}
	}



	//Print the Matrix to Test for Correctness
	for(i = 0; i < dimension; i++){
		for(j = 0; j < dimension; j++){
			printf("%d", matrix[i][j]);
		}
		printf("\n");
	}

	//Free the memory
	free(vector);
	z = 0;
	for(;z < dimension; z++){
		free(matrix[z]);
	}
	free(matrix);
	free(result);

	return 0;

}
