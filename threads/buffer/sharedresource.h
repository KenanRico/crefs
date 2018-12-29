#include <pthread.h>


extern int* buffer;
extern pthread_t* threadIDs;
extern pthread_attr_t* threadAttrs;

extern unsigned int size;
extern unsigned int thread_count;

extern void* Pusher(void*);
extern void* Puller(void*);
