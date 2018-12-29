#include <stdio.h>
#include <stdlib.h>

#define SIZE 15


void mergeSort(int*, int*);
void merge(int*, int*, int*, int*);
void printArr(int*, int);


/*--------------------MAIN-----------------------*/
int main(void){
	int array[SIZE] = {92, 14, 7, 8, 0, 29, 4,17, 45, 76, 28, 64, 1, 13, 50};
	printf("original array:\n");
	printArr(array, SIZE);
	mergeSort(array, array+SIZE-1);
	printf("sorted array:\n");
	printArr(array, SIZE);
	return 0;
}


void mergeSort(int* first, int* last){
	if(first==last){
		//array of size 1, do nothing
	}else{
		int* mid = first+(last-first)/2;
		mergeSort(first, mid);
		mergeSort(mid+1, last);
		merge(first, mid, mid+1, last);
	}
}

void merge(int* a1, int* a2, int* b1, int* b2){
	//create copies of left and right array
	int size_a = a2-a1+1;
	int size_b = b2-b1+1;
	int* left = malloc(size_a*sizeof(int));
	int* right = malloc(size_b*sizeof(int));
	for(int* p=a1; p<=a2; ++p){
		left[p-a1] = *p;
	}
	for(int* p=b1; p<=b2; ++p){
		right[p-b1] = *p;
	}

	//fill array ranged from a1~b2 using copy arrays
	int ai = 0;
	int bi = 0;
	for(int* current=a1; current<=b2; ++current){
		if(ai<size_a && bi<size_b){
			if(left[ai]<right[bi]){
				*current = left[ai];
				++ai;
			}else{
				*current = right[bi];
				++bi;
			}
		}else if(ai<size_a){
			while(current<=b2 && ai<size_a){
				*current = left[ai];
				++current;
				++ai;
			}
		}else if(bi<size_b){
			while(current<=b2 && bi<size_b){
				*current = right[bi];
				++current;
				++bi;
			}
		}else{
			//exhausted both arrays
			break;
		}
	}

	//free copy arrays
	free(left);
	free(right);
}

void printArr(int* arr, int size){
	for(int i=0; i<size; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
