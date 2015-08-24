#include "MKL26Z4.h"
#include "queue.h"
#define MAXQUEUE 80
#ifndef UART0_H
#define UART0_H
typedef struct {
	volatile QRecStruct rxQ;
	volatile QRecStruct txQ;
	volatile UART_Type *UART;
}uartDataStruct;

void uartInit(UART_Type *UART_to_init, int baud);
int uartGetString(uartDataStruct uartData, char* str, int len);
int uartTxInQueue(uartDataStruct uartData);
void uartWait(uartDataStruct uartData);
void uartPutString(uartDataStruct uartData, char* str);
void uartPutChar(uartDataStruct uartData, char ch);
char uartGetChar(uartDataStruct uartData);
char uartGetCharBlock(uartDataStruct uartData);
void uartputNum(uartDataStruct uartData, int num);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
#endif

