#include "sharedresource.h"

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

//externs in sharedresource.h
int* buffer = NULL;
pthread_t* threadIDs = NULL;
pthread_attr_t* threadAttrs = NULL;

unsigned int size = 10000;
unsigned int thread_count = 2;



//main thread resources/procedures
void initBuffer();
void initThreadProperties();
void createThreads();
void waitThreads();
void deinitBuffer();
void deinitThreadProperties();

int main(){
	initBuffer(); //init buffer to be of size 1000, each element being 0
	initThreadProperties();	

	createThreads();
	waitThreads();
	
	deinitBuffer();
	deinitThreadProperties();
}

void initBuffer(){
	buffer = (int*)malloc(sizeof(int)*size);
	for(unsigned int i=0; i<size; i++){
		buffer[i] = 0;
	}
}

void initThreadProperties(){
	threadIDs = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
	for(unsigned int i=0; i<thread_count; i++){
		threadIDs[i] = 0;
	}

	threadAttrs = (pthread_attr_t*)malloc(sizeof(pthread_attr_t)*thread_count);
	for(unsigned int i=0; i<thread_count; i++){
		pthread_attr_init(&threadAttrs[i]);
	}
}

void createThreads(){
	pthread_create(&threadIDs[0], &threadAttrs[0], Pusher, NULL);
	pthread_create(&threadIDs[1], &threadAttrs[1], Puller, NULL);
}
void waitThreads(){
	for(unsigned int i=0; i<thread_count; i++){
		pthread_join(threadIDs[i], NULL);
	}
}


void deinitBuffer(){
	free(buffer);
}

void deinitThreadProperties(){
	free(threadIDs);
	free(threadAttrs);
}
