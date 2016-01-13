#include "common.h"
#define MAXQUEUE 80
#ifndef UART0_H
#define UART0_H


void uartInit();
void uartPutStringBlock(char* str);
void uartPutCharBlock(char ch);
#endif

