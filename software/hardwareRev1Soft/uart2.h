#include "MKL26Z4.h"
#include "queue.h"
#define MAXQUEUE 80
#ifndef UART2_H
#define UART2_H
typedef struct {
	volatile QRecStruct* rxQ;
	volatile QRecStruct* txQ;
} uart2DataStruct;

void initUART2(void);
int uart2GetString(char* str, int len);
int uart2TxInQueue(void);
void uart2Wait(void);
void uart2PutString(char* str);
void uart2PutChar(char ch);
char uart2GetChar(void);
char uart2GetCharBlock(void);
void uart2putNum(int num);
void UART2_IRQHandler(void);
#endif
