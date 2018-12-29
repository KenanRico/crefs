#include "myqueue.h"

#include <stdlib.h>
#include <stdio.h>


void queueInit(Queue* q){
	//init head and tail
	q->head = malloc(sizeof(Q_node));
	q->tail = q->head;
	q->head->data = NULL;
	q->head->prev = NULL;
	q->head->next = NULL;
}

void queuePush(Queue* q, void* d){
	//allocate heap memory for new node
	q->tail->next = malloc(sizeof(Q_node));
	//define new node
	q->tail->next->prev = q->tail;
	q->tail->next->data = d;
	q->tail->next->next = NULL;
	q->tail = q->tail->next;
}

void* queuePop(Queue* q){
	void* data = NULL;

	if(queueSize(q)>0){
		//make a copy of tail's data
		data = q->tail->data;
		//make a pointer to tail
		Q_node* tail_copy = q->tail;
		//move tail forward
		q->tail = q->tail->prev;
		q->tail->next = NULL;
		//free tail
		free(tail_copy);
	}else{
		printf("Unable to pop an empty queue\n");
	}

	return data;
}

void queueDestroy(Queue* q){
	//repeatedly pop queue until reaching head node
	while(q->tail!=q->head){
		queuePop(q);
	}
	//free head node
	free(q->head);
}

int queueSize(Queue const * q){
	int size = 0;
	Q_node* curr = q->head;
	while(curr!=q->tail){
		++size;
		curr = curr->next;
	}
	return size;
}


void queuePrint(Queue const * q){
	Q_node* curr = q->head->next;
	while(curr!=NULL){
		printf("%d ", *(int*)(curr->data));
		curr = curr->next;
	}
	printf("\n");
}
