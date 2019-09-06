#include "heapsort.h"
#include "util.h"
#include <stdio.h>

int main(void){
	int array[] = {16,9,2,7,10,11,5,4,28};
	int size = sizeof(array)/sizeof(int);
	PrintArray(array, size);
	HeapSort(array, size);
	PrintArray(array, size);
	return 0;
}
