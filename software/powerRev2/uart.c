#include "common.h"
#include "uart.h"
#define MAXQUEUE 80
#define MAXGETRETRIES 100000

#define BAUD_RATE 9600
#define UART_INPUT_CLOCK CPU_INT_FAST_CLK_HZ
#define OVERSAMPLERATIO 16
#define UART_BAUD_DIVIDOR UART_INPUT_CLOCK / ((OVERSAMPLERATIO + 1) * BAUD_RATE)
/*baud = clk/((OSR+1)*SBR)*/
/* sbr = clk/((OSR+1)*BAUD*/ 
void uartInit(){
	/*Initialize clock to module*/
	/* PTA2,1 is the DRA UART, ALT2 UART0 
	 * PTC3,4 is GPS. ALT3 UART1
	 * PTD2,3 is the external. ALT3, UART2*/ 
	MCG->MC |= MCG_MC_HIRCEN_MASK;

	SIM->SCGC5 |= SIM_SCGC5_LPUART0_MASK;
	SIM->SOPT2 &= (~SIM_SOPT2_LPUART0SRC_MASK);
	SIM->SOPT2 |= SIM_SOPT2_LPUART0SRC(1);

	// Need to go off of the PLL clock / 2
	/*Also need to get the pins correct. PTD3 is TX, RX is PTD2*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[3] = PORT_PCR_MUX(4);
	PORTB->PCR[4] = PORT_PCR_MUX(4);


	//		NVIC_EnableIRQ(UART0_IRQn);
	LPUART0->BAUD = LPUART_BAUD_OSR(OVERSAMPLERATIO - 1) | (LPUART_BAUD_SBR(UART_BAUD_DIVIDOR));
	LPUART0->CTRL = LPUART_CTRL_RE_MASK | LPUART_CTRL_TE_MASK;

}
void uartPutStringBlock(char* str){
	int i;
	char curr;
	i = 0;
	curr = str[i];
	while (curr){
		uartPutCharBlock(curr);
		curr = str[++i];
	}
	/*UCA0IE |=  UCTXIE;*/
}

void uartPutCharBlock(char ch){
	while ((LPUART0->STAT & LPUART_STAT_TDRE_MASK) == 0);
	LPUART0->DATA = ch;
}
