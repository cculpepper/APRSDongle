#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
	int inPtr;
	int outPtr;
	char* data;
	int capacity;
	int stored;
} QRecStruct ;

int enqueue (volatile QRecStruct* q, char c);
char dequeue (volatile QRecStruct*);
volatile QRecStruct* initQueue(int);
int deInitQueue(volatile QRecStruct*);
char peek (volatile QRecStruct* );
int numEnqueued(volatile QRecStruct*);


#endif
