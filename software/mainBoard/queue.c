#include <stdlib.h>
#include "queue.h"


int enqueue (volatile QRecStruct* q, char c){
	if (q->stored < q->capacity){
		q->data[q->inPtr] = c;
		if (q->inPtr == (q->capacity - 1)){
			q->inPtr = 0;
		} else {
			q->inPtr++;
		}
		q->stored++;
		return 0;
	} else {
		return -1;
	}
}
char peek(volatile QRecStruct* q){
	if (q->stored == 0){
		return 1;
	} else {
		return q->data[q->outPtr];
	}
}

char dequeue ( volatile QRecStruct* q){
	char c;
	if (q->stored == 0){
		return 2;
	} else {
		c = q->data[q->outPtr];
		if (q->outPtr == (q->capacity-1)){
			q->outPtr = 0;
		} else {
			q->outPtr++;
		} 
		q->stored--;
		return c;
	}
}
int initQueue(volatile QRecStruct *q){
	int i;
	q->capacity = QUEUE_BUF_SIZE;
	q->outPtr = 0;
	q->inPtr = 0;
	q->stored = 0;
	for (i = 0;i<QUEUE_BUF_SIZE-1;i++){
		q->data[i] = 0;
	}
	return QUEUE_BUF_SIZE;
}
#ifndef ALLOCATE_QUEUE_AT_COMPILE
volatile QRecStruct* initQueueDyn(int len){
	volatile QRecStruct *q;
	q = (volatile QRecStruct*) malloc(sizeof(volatile QRecStruct));
	q->data = malloc(len * sizeof(char));
	q->capacity = QUEUE_BUF_SIZE;
	q->outPtr = 0;
	q->inPtr = 0;
	q->stored = 0;
	return q;
}
#endif
int numEnqueued(volatile QRecStruct* q){
	return q->stored;
}

int deInitQueue(volatile QRecStruct* q ){
	free( q->data);
	free(q);
	return 0;
}
