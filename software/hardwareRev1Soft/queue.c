#include <stdlib.h>
#include "queue.h"


int enqueue (QRecStruct* q, char c){
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
char peek(QRecStruct* q){
	if (q->stored == 0){
		return -1;
	} else {
		return q->data[q->outPtr];
	}
}

char dequeue ( QRecStruct* q){
	char c;
	if (q->stored == 0){
		return -1;
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
QRecStruct* initQueue(int len){
	QRecStruct *q;
	q = (QRecStruct*) malloc(sizeof(QRecStruct));
	q->data = malloc(len * sizeof(char));
	q->capacity = len;
	q->outPtr = 0;
	q->inPtr = 0;
	q->stored = 0;
	return q;
}


int numEnqueued(QRecStruct* q){
	return q->stored;
}

int deInitQueue(QRecStruct* q ){
	free( q->data);
	free(q);
	return 0;
}


