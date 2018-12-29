#include "sharedresource.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int* pusher_buffer = NULL;


void pusher_initBuffer();
void pusher_loop();

void* Pusher(void* arg){
	printf("in pusher:\n");
	pusher_initBuffer();

	pusher_loop();

	free(pusher_buffer);
	pthread_exit(NULL);
}

void pusher_initBuffer(){
	pusher_buffer = (int*)malloc(sizeof(int)*size);
	for(unsigned int i=0; i<size; i++){
		pusher_buffer[i] = i;
	}
}

void pusher_loop(){
	for(unsigned int i=0; i<size; i++){
		buffer[i] = pusher_buffer[i];
	}
}
