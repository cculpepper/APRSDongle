#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
	int inPtr;
	int outPtr;
	char* data;
	int capacity;
	int stored;
}QRecStruct ;

int enqueue (QRecStruct* q, char c);
char dequeue (QRecStruct*);
QRecStruct* initQueue(int);
int deInitQueue(QRecStruct*);
char peek (QRecStruct* );
int numEnqueued(QRecStruct*);


#endif
