#include "MKL26Z4.h"
#include "queue.h"
#include "uart0.h"
#define MAXQUEUE 80
#define MAXGETRETRIES 100000
volatile uart0DataStruct uart0Data;

int uart0TxInQueue(){
	return uart0Data.txQ->stored;
}
void uart0Init(void){
	// Initialize clock to module
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	// We go from the bus clock. UART1 and UART0 are the same. 9600 baud
	UART0->BDH = 0;
	UART0->BDL = 0x9C;
	UART0->C2 = UART0_C2_RIE_MASK | UART0_C2_RE_MASK | UART0_C2_TE_MASK;
	uart0Data.rxQ = initQueue(MAXQUEUE);
	uart0Data.txQ = initQueue(MAXQUEUE);
	
	// Also need to get the pins correct. PTD3 is TX, RX is PTD2
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[2] = PORT_PCR_MUX(3);
	PORTD->PCR[3] = PORT_PCR_MUX(3);
	
	NVIC_EnableIRQ(UART0_IRQn);
	__enable_irq();
	
}
int uart0GetString(char* str, int len){

	char temp;
	int i;
	len--;
	i = 0;
	while (numEnqueued(uart0Data.rxQ) >0){
		__disable_irq();
		temp = dequeue(uart0Data.rxQ);
		__enable_irq();
		if (temp == '\r' | temp == '\n'){
			// Then weve reached the end of a line.
			temp = peek(uart0Data.rxQ);
			if (temp == '\r' | temp == '\n'){
				dequeue(uart0Data.rxQ);
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
void uart0PutString(char* str){
	int i;
	char curr;
	i = 0;
	curr = str[i];
	while (curr){
		uart0PutChar(curr);
		curr = str[++i];
	}
	//UCA0IE |=  UCTXIE;
}
void uart0PutChar(char ch){
	

/*	if (uart0Data.txQ->stored == uart0Data.txQ->capacity) {
		UART0->C2 |= UART0_C2_TIE_MASK | UART0_C2_TE_MASK ;
		__enable_irq();
	}
*/

	while (uart0Data.txQ->stored == uart0Data.txQ->capacity);
	__disable_irq();
	enqueue(uart0Data.txQ, ch);
	__enable_irq();
UART0->C2 |= UART0_C2_TIE_MASK;//  | UART0_C2_TE_MASK;
}

char uart0GetChar(void){
	char ret;
	int retryCount;
	retryCount = 0;
	while (retryCount < MAXGETRETRIES){
		if (numEnqueued(uart0Data.rxQ)){
			__disable_irq();
			ret = dequeue(uart0Data.rxQ);
			__enable_irq();
			return ret;
		}
	}
	return 0x35;
}
char uart0GetCharBlock(void){
	char ret;
	char status;
	UART0->C2 &= ~(UART0_C2_RIE_MASK);
	status = UART0->S1;
	while ((status & UART0_S1_RDRF_MASK) == 0){
		status = UART0->S1;
	}
	ret = UART0->D;
	UART0->C2 |= (UART0_C2_RIE_MASK);
	return ret;
}
void uart0Wait(){
	while(uart0Data.txQ->stored);
	while((UART0->S1 & UART0_S1_TDRE_MASK)==0);
}
void uart0putNum(int num){
	char ch;
	ch = (num / 10000) + '0';
	uart0PutChar(ch);
	num %= 10000;
	ch = (num / 1000) + '0';
	uart0PutChar(ch);
	num %= 1000;
	ch = (num / 100) + '0';
	uart0PutChar(ch);
	num %= 100;
	ch = (num / 10) + '0';
	uart0PutChar(ch);
	num %= 10;
	ch = num + '0';
	uart0PutChar(ch);

}
void UART0_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART0->S1;
	if (status & UART0_S1_TDRE_MASK){
			UART0->D = dequeue(uart0Data.txQ);
			//UART0->C2 |= UART0_C2_TE_MASK;
		if (uart0Data.txQ->stored <= 0){
			// Then we can disable the transmit interrupt	
			UART0->C2 &= ~(UART0_C2_TIE_MASK);
		} 
	}
	if (status & UART0_S1_RDRF_MASK){
		enqueue(uart0Data.rxQ, UART0->D);
	}
	__enable_irq();
}
