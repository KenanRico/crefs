#include "util.h"
#include <stdio.h>

void PrintArray(int* array, int size){
	for(int i=0; i<size; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
}
