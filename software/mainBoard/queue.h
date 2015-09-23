#ifndef QUEUE_H
#define QUEUE_H
#define ALLOCATE_QUEUE_AT_COMPILE
#define QUEUE_BUF_SIZE 80
typedef struct {
	int inPtr;
	int outPtr;
#ifdef ALLOCATE_QUEUE_AT_COMPILE
	char data[QUEUE_BUF_SIZE];
#else
	char* data;
#endif
	int capacity;
	int stored;
} QRecStruct ;

int enqueue (volatile QRecStruct* q, char c);
char dequeue (volatile QRecStruct*);
int initQueue(volatile QRecStruct*);
//volatile QRecStruct* initQueue(int);
volatile QRecStruct* initQueueDyn(int);
int deInitQueue(volatile QRecStruct*);
char peek (volatile QRecStruct* );
int numEnqueued(volatile QRecStruct*);


#endif
