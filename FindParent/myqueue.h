

#ifndef MY_QUEUE
#define MY_QUEUE

typedef struct myQueueNode{
	void* data;
	struct myQueueNode* prev;
	struct myQueueNode* next;
} Q_node;

typedef struct myQueue{
	Q_node* head;
	Q_node* tail;
} Queue;

//----------------API calls-------------
void queueInit(Queue*);
void queuePush(Queue*, void*);
void* queuePop(Queue*);
void queueDestroy(Queue*);
int queueSize(Queue const *);

//-----------------test calls--------------
void queuePrint(Queue const *);

#endif
