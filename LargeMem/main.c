#include <stdio.h>
#include <stdlib.h>


int main(){
	//alloc 500MB
	char* ptr = malloc(500*1024*1024);
	*ptr = 1;
	*(ptr+500*1024*1024-1) = 1;
	int i = 1;
	while(i!=0){
		scanf("%d",&i);
	}
	free(ptr);
}
