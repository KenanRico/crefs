#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void initArrays(int**, bool**, int);
void getGreySequence(int*, bool*, int);
int bitChange(int, int);
void destroyArrays(int*, bool*);
void printArray(int*, int);
int powi(int, int);


int main(void){
	//define number of digits
	int N = 6;

	//define auxilary and resulting arrays
	int* result = NULL;
	bool* aux = NULL;
	initArrays(&result, &aux, N);

	//compute grey sequence
	getGreySequence(result, aux, N);
	printArray(result, powi(2,N));

	//free arrays
	destroyArrays(result, aux);

	return 0;
}


void initArrays(int** result_p, bool** aux_p, int N){
	int num = powi(2, N);
	*result_p = malloc(sizeof(int)*num);
	for(int i=0; i<num; ++i){
		(*result_p)[i] = 0;
	}
	*aux_p = malloc(sizeof(bool)*num);
	for(int i=0; i<num; ++i){
		(*aux_p)[i] = false;
	}
}

void getGreySequence(int* result, bool* aux, int N){
	int current = 0;
	result[0] = current;
	aux[current] = true;
	
	int count = powi(2, N);

	for(int i=1; i<count; ++i){
		for(int j=0; j<N; ++j){
			int bit_change = bitChange(current, j);
			if(!aux[bit_change]){
				result[i] = bit_change;
				aux[bit_change] = true;
				current = bit_change;
				break;
			}else;
		}
	}
}

int bitChange(int value, int bit){
	return value^powi(2, bit);
}

void destroyArrays(int* result, bool* aux){
	free(result);
	free(aux);
}

void printArray(int* arr, int size){
	for(int i=0; i<size; ++i){
		printf("%d\n", arr[i]);
	}
	printf("\n");
}

int powi(int base, int exp){
	int result = base;
	if(exp==0){
		result = 1;
	}else{
		for(int i=1; i<exp; ++i){
			result *= base;
		}
	}
	return result;
}
