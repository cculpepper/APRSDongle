<<<<<<< HEAD
#include "MKL26Z4.h"
#include "queue.h"
#ifndef UART1_H
#define UART1_H
#define MAXQUEUE 80
typedef struct {
	volatile QRecStruct* rxQ;
	volatile QRecStruct* txQ;
} uart1DataStruct;

void initUART1(void);
int uart1GetString(char* str, int len);
int uart1TxInQueue(void);
void uart1Wait(void);
void uart1PutString(char* str);
void uart1PutChar(char ch);
char uart1GetChar(void);
char uart1GetCharBlock(void);
void uart1putNum(int num);
void UART1_IRQHandler(void);
#endif

=======
#include "MKL26Z4.h"
#include "queue.h"
#ifndef UART1_H
#define UART1_H
#define MAXQUEUE 80
typedef struct {
	volatile QRecStruct* rxQ;
	volatile QRecStruct* txQ;
} uart1DataStruct;

void initUART1(void);
int uart1GetString(char* str, int len);
int uart1TxInQueue(void);
void uart1Wait(void);
void uart1PutString(char* str);
void uart1PutChar(char ch);
char uart1GetChar(void);
char uart1GetCharBlock(void);
void uart1putNum(int num);
void UART1_IRQHandler(void);
#endif

>>>>>>> 84f8769cc613e3b8a61078ac300a2ff84b4d58b7
