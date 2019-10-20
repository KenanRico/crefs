#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int FindTurbSubarray(int const *, int size, int const **, int const **);

int main(void){
	int size = 9;
	int* array = malloc(sizeof(int)*size);
	memcpy(array, (int []){9, 4, 2, 10, 7, 8, 8, 1, 9}, sizeof(int)*size);

	//find and print max turbulent subarray
	int const * start = array;
	int const * end = array;
	int count = FindTurbSubarray(array, size, &start, &end);
	printf("Length of max turbulent subarray is %d\nIt goes: ", count);
	for(int const * p=start; p<=end; ++p){
		printf("%d ", *p);
	}
	printf("\n");

	free(array);
	return 0;
}
typedef char bool;
int FindTurbSubarray(int const * array, int size, int const ** s, int const ** e){
	int count = 2;
	int c = 2;
	bool compare = -1;
	int const * new_s = array;
	for(int i=1; i<size; ++i){
		if(array[i]>array[i-1] && (compare==0||compare==-1)){
			++c;
			compare = 1;
		}else if(array[i]<array[i-1] && (compare==1||compare==-1)){
			++c;
			compare = 0;
		}else{
			c = 2;
			compare=-1;
			new_s = array+i-1;
		}
		if(c>count){
			count = c;
			*s = new_s;
			*e = array+i;
		}
	}
	return count;
}
