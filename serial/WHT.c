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


int main(int argc, char** argv){
	
	int m; //used for dimension calculation for vector and matrix
	
	if(argc == 2){
		m = atoi(argv[1]);
	}

	//Allocate Vector
	int *vector = (int*)malloc((1 << m) * sizeof(int));
		
	//Allocate Matrix
	int ** matrix;
	matrix = (int**)malloc(sizeof(int**)* (1 << m));
	int z = 0;
	for(; z < (1 << m); z++){
		matrix[z] = (int*)malloc(sizeof(int)*(1 << m));
	}

	printf("Input M is: %d ", m);
	printf("Row and column size is %d", (1 << m));


	//Free the memory
	free(vector);
	z = 0;
	for(;z < (1 << m); z++){
		free(matrix[z]);
	}
	free(matrix);
	
	return 0;

}
