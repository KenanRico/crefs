#include <stdio.h>
#include <stdlib.h>

int main(void){
	int childID = fork();
	int* ptr = (int*) malloc(sizeof(int)*2);
	ptr[0] = childID; 
	if(childID!=0){
		ptr[1] = childID*2;
	}else{
		ptr[1] = 1;
	}
	printf("num1=%d, num2=%d \n", ptr[0], ptr[1]);
	free(ptr);
	return 0;
}
