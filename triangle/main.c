#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1000


int counter = 0;

typedef struct _Triangle{
	int** array;
	unsigned int dimension;
} Triangle;

void initArrays(Triangle*);
void destroyArrays(Triangle*);
int minPath(Triangle const *, int, int, int**);
int min(int, int);


int main(void){

	//declare and init triangle
	Triangle triangle = {NULL, 8};
	initArrays(&triangle);

	//print triangle data
	for(unsigned int i=0; i<triangle.dimension; i++){
		for(unsigned int j=0; j<=i; j++){
			printf("%d ", triangle.array[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//init 2d array as memoization, run minPath algorithm, and free memoization	
	int** mem = malloc(sizeof(int*) * triangle.dimension);
	for(unsigned int i=0; i<triangle.dimension; i++){
		mem[i] = malloc(sizeof(int) * triangle.dimension);
		for(unsigned int j=0; j<triangle.dimension; j++){
			mem[i][j] = -1;
		}
	}
	int min_path_sum = minPath(&triangle, triangle.dimension, 0, mem);
	for(unsigned int i=0; i<triangle.dimension; i++){
		free(mem[i]);
	}
	free(mem);

	//print min_path
	printf("%d\n", min_path_sum);

	//print counter
	printf("performance counter: %d\n", counter);

	//free triangle data
	destroyArrays(&triangle);
	return 0;
}



void initArrays(Triangle* triangle){
	FILE* input_file = fopen("data.txt", "r");

	///if file exists, read data from file; if not, use default data
		//allocate to arrays
		triangle->array = malloc(sizeof(int*)*triangle->dimension);
		for(unsigned int i=0; i<triangle->dimension; i++){
			triangle->array[i] = malloc(sizeof(int)*(i+1));
		}
		//assign values
		triangle->array[0][0] = 5;
		triangle->array[1][0] = 1;
		triangle->array[1][1] = 12;
		triangle->array[2][0] = 0;
		triangle->array[2][1] = 7;
		triangle->array[2][2] = 8;
		triangle->array[3][0] = 21;
		triangle->array[3][1] = 17;
		triangle->array[3][2] = 9;
		triangle->array[3][3] = 4;
		triangle->array[4][0] = 6;
		triangle->array[4][1] = 4;
		triangle->array[4][2] = 9;
		triangle->array[4][3] = 7;
		triangle->array[4][4] = 1;
		triangle->array[5][0] = 15;
		triangle->array[5][1] = 14;
		triangle->array[5][2] = 19;
		triangle->array[5][3] = 11;
		triangle->array[5][4] = 8;
		triangle->array[5][5] = 10;
		triangle->array[6][0] = 0;
		triangle->array[6][1] = 1;
		triangle->array[6][2] = 5;
		triangle->array[6][3] = 2;
		triangle->array[6][4] = 8;
		triangle->array[6][5] = 7;
		triangle->array[6][6] = 0;
		triangle->array[7][0] = 4;
		triangle->array[7][1] = 1;
		triangle->array[7][2] = 11;
		triangle->array[7][3] = 7;
		triangle->array[7][4] = 2;
		triangle->array[7][5] = 8;
		triangle->array[7][6] = 2;
		triangle->array[7][7] = 9;

	fclose(input_file);
}

void destroyArrays(Triangle* triangle){
	for(unsigned int i=0; i<triangle->dimension; i++){
		free(triangle->array[i]);
	}
	free(triangle->array);
}

int minPath(Triangle const * triangle, int array_index_inverse, int path_index, int** mem){
	++counter;

	int** array = triangle->array;
	int N = triangle->dimension;
	int n = array_index_inverse;
	int i = path_index;

	int current_path_sum = 0;

	///implementation using memoization: O(n^2)
	if(array_index_inverse<=1){
		current_path_sum = array[N-n][i];
	}else{
		if(mem[N-n][i]!=-1){
			current_path_sum = mem[N-n][i];
		}else{
			current_path_sum = (mem[N-n][i] = array[N-n][i] + min(minPath(triangle, n-1, i, mem), minPath(triangle, n-1, i+1, mem)));
		}
	}
	///implementation without using memoization: O(2^n)
	/*if(array_index_inverse<=1){
		current_path_sum = array[N-n][i];
	}else{
		current_path_sum = array[N-n][i] + min(minPath(triangle, n-1, i, mem), minPath(triangle, n-1, i+1, mem));
	}*/
	
	return current_path_sum;
}

int min(int a, int b){
	return (a<b) ? a:b;
}
