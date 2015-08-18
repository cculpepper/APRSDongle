<<<<<<< HEAD
#include "MKL26Z4.h"
#include "queue.h"
#define MAXQUEUE 80
#ifndef UART0_H
#define UART0_H
typedef struct {
	volatile QRecStruct* rxQ;
	volatile QRecStruct* txQ;
}uart0DataStruct;

void uart0Init(void);
int uart0GetString(char* str, int len);
int uart0TxInQueue(void);
void uart0Wait(void);
void uart0PutString(char* str);
void uart0PutChar(char ch);
char uart0GetChar(void);
char uart0GetCharBlock(void);
void uart0putNum(int num);
void UART0_IRQHandler(void);
#endif

=======
#include "MKL26Z4.h"
#include "queue.h"
#define MAXQUEUE 80
#ifndef UART0_H
#define UART0_H
typedef struct {
	volatile QRecStruct* rxQ;
	volatile QRecStruct* txQ;
}uart0DataStruct;

void uart0Init(void);
int uart0GetString(char* str, int len);
int uart0TxInQueue(void);
void uart0Wait(void);
void uart0PutString(char* str);
void uart0PutChar(char ch);
char uart0GetChar(void);
char uart0GetCharBlock(void);
void uart0putNum(int num);
void UART0_IRQHandler(void);
#endif

>>>>>>> 84f8769cc613e3b8a61078ac300a2ff84b4d58b7
