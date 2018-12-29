#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 10000




long start_time = 0;


void* thread_0_func(void*);
void* thread_1_func(void*);
void create_thread(pthread_t*, int, int*);


int main(){
	unsigned int count = 2;
	pthread_t threads[2];

	int* buffer = (int*)malloc(sizeof(int)*BUFFER_SIZE);
	for(unsigned int i=0; i<BUFFER_SIZE; i++){
		buffer[i] = 0;
	}

	start_time = time((long*)0);
	for(unsigned int i=0; i<count; i++){
		create_thread(&threads[i], i, buffer);
	}

	for(unsigned int i=0; i<count; i++){
		pthread_join(threads[i], NULL);
	}
	free(buffer);

	return 0;
}


void* thread_0_func(void* arg){
	int* buffer = (int*)arg;

	//function body

	pthread_exit(NULL);
}
void* thread_1_func(void* arg){
	int* buffer = (int*)arg;

	//function body
	
	pthread_exit(NULL);
}

void create_thread(pthread_t* tID, int t, int* ptr){
	int status = 0;
	switch(t){
		case 0:
			status = pthread_create(tID, NULL, thread_0_func, (void*)ptr);
			break;
		case 1:
			status = pthread_create(tID, NULL, thread_1_func, (void*)ptr);
			break;
		default:
			break;
	}
	if(status!=0){
		printf("Failed to create thread, error code %d \n", status);
	}else;
}
