#include "MKL26Z4.h"
#include "queue.h"
#include "uart2.h"
#define MAXQUEUE 80
#define MAXGETRETRIES 100000
volatile uart2DataStruct uart2Data;

int uart2TxInQueue(){
	return uart2Data.txQ->stored;
}
void initUART2(void){
	// Initialize clock to module
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	// We go from the bus clock. UART1 and UART2 are the same. 9600 baud
	UART2->BDH = 0;
	UART2->BDL = 0x9C;
	UART2->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK;
	initQueue(uart2Data.rxQ);
	initQueue(uart2Data.txQ);
	
	// Also need to get the pins correct. PTD3 is TX, RX is PTD2
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[2] = PORT_PCR_MUX(3);
	PORTD->PCR[3] = PORT_PCR_MUX(3);
	
	NVIC_EnableIRQ(UART2_IRQn);
	__enable_irq();
	
}
int uart2GetString(char* str, int len){

	char temp;
	int i;
	len--;
	i = 0;
	while (numEnqueued(uart2Data.rxQ) >0){
		__disable_irq();
		temp = dequeue(uart2Data.rxQ);
		__enable_irq();
		if (temp == '\r' | temp == '\n'){
			// Then weve reached the end of a line.
			temp = peek(uart2Data.rxQ);
			if (temp == '\r' | temp == '\n'){
				dequeue(uart2Data.rxQ);
				str[i] = 0;
				return i;
			} else {
				// Then we dont need to dequeue.
				str[i] = 0;
				return i;
			}
		} else {
			// Then were going good.
			str[i++] = temp;
		}
		if (i == len){
			// end of buf.
			str[i] = 0;
			return i;
		}
	}
	// Then out of queue.
	str[i] = 0;
	return i;
}
void uart2PutString(char* str){
	int i;
	char curr;
	i = 0;
	curr = str[i];
	while (curr){
		uart2PutChar(curr);
		curr = str[++i];
	}
	//UCA0IE |=  UCTXIE;
}
void uart2PutChar(char ch){
	

/*	if (uart2Data.txQ->stored == uart2Data.txQ->capacity) {
		UART2->C2 |= UART_C2_TIE_MASK | UART_C2_TE_MASK ;
		__enable_irq();
	}
*/

	while (uart2Data.txQ->stored == uart2Data.txQ->capacity);
	__disable_irq();
	enqueue(uart2Data.txQ, ch);
	__enable_irq();
UART2->C2 |= UART_C2_TIE_MASK;//  | UART_C2_TE_MASK;
}

char uart2GetChar(void){
	char ret;
	int retryCount;
	retryCount = 0;
	while (retryCount < MAXGETRETRIES){
		if (numEnqueued(uart2Data.rxQ)){
			__disable_irq();
			ret = dequeue(uart2Data.rxQ);
			__enable_irq();
			return ret;
		}
	}
	return 0x35;
}
char uart2GetCharBlock(void){
	char ret;
	char status;
	UART2->C2 &= ~(UART_C2_RIE_MASK);
	status = UART2->S1;
	while ((status & UART_S1_RDRF_MASK) == 0){
		status = UART2->S1;
	}
	ret = UART2->D;
	UART2->C2 |= (UART_C2_RIE_MASK);
	return ret;
}
void uart2Wait(){
	while(uart2Data.txQ->stored);
	while((UART2->S1 & UART_S1_TDRE_MASK)==0);
}
void uart2putNum(int num){
	char ch;
	ch = (num / 10000) + '0';
	uart2PutChar(ch);
	num %= 10000;
	ch = (num / 1000) + '0';
	uart2PutChar(ch);
	num %= 1000;
	ch = (num / 100) + '0';
	uart2PutChar(ch);
	num %= 100;
	ch = (num / 10) + '0';
	uart2PutChar(ch);
	num %= 10;
	ch = num + '0';
	uart2PutChar(ch);

}
void UART2_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART2->S1;
	if (status & UART_S1_TDRE_MASK){
			UART2->D = dequeue(uart2Data.txQ);
			//UART2->C2 |= UART_C2_TE_MASK;
		if (uart2Data.txQ->stored <= 0){
			// Then we can disable the transmit interrupt	
			UART2->C2 &= ~(UART_C2_TIE_MASK);
		} 
	}
	if (status & UART_S1_RDRF_MASK){
		enqueue(uart2Data.rxQ, UART2->D);
	}
	__enable_irq();
}
