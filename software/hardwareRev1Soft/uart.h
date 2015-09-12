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


extern volatile uartDataStruct uart0Data;
extern volatile uartDataStruct uart1Data;
extern volatile uartDataStruct uart2Data;

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

#define uart0GetString(c,d) uartGetString(uart0Data,c,d)
#define uart0PutString(c) uartPutString(uart0Data,c)
#define uart1GetString(c,d) uartGetString(uart1Data,c,d)
#define uart1PutString(c) uartPutString(uart1Data,c)
#define uart2GetString(c,d) uartGetString(uart2Data,c,d)
#define uart2PutString(c) uartPutString(uart2Data,c)
#define initUART0() uartInit((UART_Type*) UART0,9600)
#define uart0Init() uartInit((UART_Type*) UART0,9600)
#define initUART1() uartInit(UART1,9600)
#define initUART2() uartInit(UART2,9600)
#endif

