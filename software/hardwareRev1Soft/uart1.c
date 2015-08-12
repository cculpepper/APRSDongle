#include "MKL26Z4.h"
#include "queue.h"
#include "uart2.h"
#include "uart1.h"
#include "gps.h"


void initUART1(void){
	// Initialize clock to module
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
	// We go from the bus clock. UART1 and UART1 are the same. 9600 baud
	UART1->BDH = 0;
	UART1->BDL = 0x9C;
	UART1->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK;\
	
	// Also need to get the pins correct. PTC4 is TX, RX is PTC3
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] = PORT_PCR_MUX(3);
	PORTC->PCR[4] = PORT_PCR_MUX(3);
	
	NVIC_EnableIRQ(UART1_IRQn);
	__enable_irq();
	
}

void UART1_IRQHandler(void){
	
	char status;
	__disable_irq();
	status = UART1->S1;
	if (status & UART_S1_TDRE_MASK){
			UART1->D = ' ';
	}
	if (status & UART_S1_RDRF_MASK){
		status =  (UART1->D);
		ParseGPS(status);
		uart2PutChar(status);
	}
	__enable_irq();
}
