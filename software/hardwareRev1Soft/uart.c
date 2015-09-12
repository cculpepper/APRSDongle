#include "MKL26Z4.h"
#include "queue.h"
#include "uart.h"
#include "gps.h"
#define MAXQUEUE 80
#define MAXGETRETRIES 100000

volatile uartDataStruct uart0Data;
volatile uartDataStruct uart1Data;
volatile uartDataStruct uart2Data;

int uartTxInQueue(uartDataStruct uartData){
	return uartData.txQ.stored;
}
void uartInit(UART_Type *UART_to_init, int baud){
	 /*Initialize clock to module*/
     /* PTA2,1 is the DRA UART, ALT2 UART0 
      * PTC3,4 is GPS. ALT3 UART1
      * PTD2,3 is the external. ALT3, UART2*/ 
	if (UART_to_init == (UART_Type*) UART0){
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		 /*Also need to get the pins correct. PTD3 is TX, RX is PTD2*/
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		PORTA->PCR[1] = PORT_PCR_MUX(2);
		PORTA->PCR[2] = PORT_PCR_MUX(2);
		uart0Data.UART = (UART_Type*) UART0;
		NVIC_EnableIRQ(UART0_IRQn);
		UART_to_init->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK;
	} else if (UART_to_init == (UART_Type*) UART1){
		SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
		 /*Also need to get the pins correct. PTD3 is TX, RX is PTD2*/
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC->PCR[3] = PORT_PCR_MUX(3);
		PORTC->PCR[4] = PORT_PCR_MUX(3);
		uart1Data.UART = UART1;
		NVIC_EnableIRQ(UART1_IRQn);
		UART_to_init->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK ;
	} else if (UART_to_init == (UART_Type*) UART2){
		SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
		 /*Also need to get the pins correct. PTD3 is TX, RX is PTD2*/
		/* This is the external UART*/ 
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
		PORTD->PCR[2] = PORT_PCR_MUX(3);
		PORTD->PCR[3] = PORT_PCR_MUX(3);
		uart2Data.UART = UART2;
		NVIC_EnableIRQ(UART2_IRQn);
		UART_to_init->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK;
	} else {
		return;
	}


	 /*We go from the bus clock. UART1 and UART0 are the same. 9600 baud*/
	UART_to_init->BDH = 0;
	UART_to_init->BDL = 0x9C;
	
	__enable_irq();
	
}
int uartGetString(uartDataStruct uartData, char* str, int len){

	char temp;
	int i;
	len--;
	i = 0;
	while (&uartData.rxQ.stored >0){
		__disable_irq();
		temp = dequeue(&uartData.rxQ);
		__enable_irq();
		if (temp == '\r' | temp == '\n'){
			 /*Then weve reached the end of a line.*/
			temp = peek(&uartData.rxQ);
			if (temp== '\r' | temp == '\n'){
				dequeue(&uartData.rxQ);
				str[i] = 0;
				return i;
			} else {
				 /*Then we dont need to dequeue.*/
				str[i] = 0;
				return i;
			}
		} else {
			 /*Then were going good.*/
			str[i++] = temp;
		}
		if (i == len){
			 /*end of buf.*/
			str[i] = 0;
			return i;
		}
	}
	 /*Then out of queue.*/
	str[i] = 0;
	return i;
}
void uartPutString(uartDataStruct uartData, char* str){
	int i;
	char curr;
	i = 0;
	curr = str[i];
	while (curr){
		uartPutChar(uartData, curr);
		curr = str[++i];
	}
	/*UCA0IE |=  UCTXIE;*/
}
void uartPutChar(uartDataStruct uartData, char ch){
	uartData.UART->C2 |= UART_C2_TE_MASK;
	while (uartData.txQ.stored == uartData.txQ.capacity);
	__disable_irq();
	enqueue(&(uartData.txQ), ch);
	__enable_irq();
	uartData.UART->C2 |= UART_C2_TIE_MASK;
}

void uartPutCharBlock(uartDataStruct uartData, char ch){
	uartData.UART->C2 &= ~UART_C2_TIE_MASK;
	while (uartData.UART->S1 & UART_S1_TDRE_MASK == 0);
	uartData.UART->D = ch;
}
char uartGetChar(uartDataStruct uartData){
	char ret;
	int retryCount;
	retryCount = 0;
	while (retryCount++ < MAXGETRETRIES){
		if (numEnqueued(&uartData.rxQ)){
			__disable_irq();
			ret = dequeue(&uartData.rxQ);
			__enable_irq();
			return ret;
		}
	}
	return 0x35;
}
char uartGetCharBlock(uartDataStruct uartData){
	char ret;
	char status;
	uartData.UART->C2 &= ~(UART_C2_RIE_MASK);
	status = uartData.UART->S1;
	while ((status & UART_S1_RDRF_MASK) == 0){
		status = uartData.UART->S1;
	}
	ret = uartData.UART->D;
	/*UART->C2 |= (UART_C2_RIE_MASK);*/
	 /* This means that we need to initialize the uart again. 
	  * */ 
	return ret;
}
void uartWait(uartDataStruct uartData){
	while(uartData.txQ.stored);
	while((uartData.UART->S1 & UART_S1_TDRE_MASK)==0);
}
void UART0_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART0->S1;
	if (status & UART0_S1_TDRE_MASK){
		UART0->D = dequeue(&uart0Data.txQ);
			//UART_IN_USE->C2 |= UART0_C2_TE_MASK;
		if (uart0Data.txQ.stored <= 0){
			// Then we can disable the transmit interrupt	
			UART0->C2 &= ~(UART0_C2_TIE_MASK);
		} 
	}
	if (status & UART0_S1_RDRF_MASK){
		enqueue(&uart0Data.rxQ, UART0->D);
	}
	__enable_irq();
}
void UART1_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART1->S1;
	if (status & UART_S1_TDRE_MASK){
			UART1->D = dequeue(&uart1Data.txQ);
			//UART_IN_USE->C2 |= UART1_C2_TE_MASK;
		if (uart1Data.txQ.stored <= 1){
			// Then we can disable the transmit interrupt	
			UART1->C2 &= ~(UART_C2_TIE_MASK);
		} 
	}
	if (status & UART_S1_RDRF_MASK){
		/*enqueue(uart1Data.rxQ, UART1->D);*/
		ParseGPS(UART1->D);
	}
	__enable_irq();
}
void UART2_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART2->S1;
	if (status & UART_S1_TDRE_MASK){
			UART2->D = dequeue(&uart2Data.txQ);
			//UART_IN_USE->C2 |= UART2_C2_TE_MASK;
		if (uart2Data.txQ.stored <= 2){
			// Then we can disable the transmit interrupt	
			UART2->C2 &= ~(UART_C2_TIE_MASK);
		} 
	}
	if (status & UART_S1_RDRF_MASK){
		enqueue(&uart2Data.rxQ, UART2->D);
	}
	__enable_irq();
}
