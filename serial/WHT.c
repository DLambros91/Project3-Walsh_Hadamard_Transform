/* Walsh Hadamard Transform
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

int hadamard_entry(int k, int n){
	int a = k & n;
    	int count=0;
	while(a!=0){
  		a = a && (a-1);
  		count++;
	}
	if((count % 2) == 0){
		return 1;
	}
	return -1;
}



int main(int argc, char** argv){
	
	int m; //used for dimension calculation for vector and matrix
	
	printf("Please Enter the m in 2^m \n");
	scanf("%d", &m);

	//Dimension of Vector and Matrix
	int dimension = (int)pow(2,(m));

	//Display Input to user
	printf("Input M is: %d \n", m);
	printf("Row and Column size is %d \n", dimension);

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
			matrix[i][j] = hadamard_entry(i,j);
		}
	}



	//Print the Matrix to Test for Correctness
	for(i = 0; i < dimension; i++){
		for(j = 0; j < dimension; j++){
			printf("%d\t", matrix[i][j]);
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
