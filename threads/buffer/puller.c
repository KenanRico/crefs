#include "sharedresource.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int* puller_buffer = NULL;

void puller_loop();

void* Puller(void* arg){
	printf("in puller:\n");
	puller_buffer = (int*)malloc(sizeof(int)*size);
	for(unsigned int i=0; i<size; i++){
		puller_buffer[i] = -1;
	}

	puller_loop(); 

	for(unsigned int i=0; i<size; i++){
		printf("value: %d\n", puller_buffer[i]);
	}
	
	free(puller_buffer);
	pthread_exit(NULL);
}

void puller_loop(){
	for(unsigned int i=0; i<size; i++){
		puller_buffer[i] = buffer[i];
	}
}
