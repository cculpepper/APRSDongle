#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "MKL26Z4.h"
#include "dra.h"
#include "gpio.h"
int stringCpy(char* dst, char* src){
	int i;
	i = 0;
	do {
		dst[i] = src[i];
	} while (src[i++]!= 0);
	return i;
}


draDataStruct draData;
int initDRA(void){
	// Gets the DRA ready to go. 
	stringCpy(draData.draTxFreq, "145.3900");
	stringCpy(draData.draRxFreq, "145.3900");
	uart0Init();
	SIM->SCGC5  |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK ;
	// Need to init the pinz
	// PTB19 is hight low select. 
	PTB->PDDR |= (1 << 19) | (1 << 3);
	PORTB->PCR[3] = PORT_PCR_MUX(1);
	PORTB->PCR[19] = PORT_PCR_MUX(1);
	PORTE->PCR[20] = PORT_PCR_MUX(1);
	PTA->PDDR &= ~(1<<12);
	PTE->PDDR |= (1<<20);
	PTB->PCOR = (1<<19);
	PTE->PSOR = (1<<20); // Need to turn off the transmitter. 
	PTA->PDDR &= ~(1<<12);
	PTA->PDDR |= (1<<4);
	PTB->PCOR = (1<<19);
	PTA->PSOR = (1<<4); // Need to turn off the transmitter. 
	
	// PTB3 is the power down thingamajig. 
	PTB->PCOR = (1<<3); // Turn off the device to make it less confused. 
	delay(100);
	PTB->PSOR = (1<<3); // Turn on the device
	// PTA12 is the squelch detect. 
	// PTe20 is the PTT. THIS IS THE NEW PIN Other was PTA4
	return 0;
}

char checkDRA(void){
	int count;
	char ret[40];
	count = 4;
	led4Off();
	led3Off();
	led2Off();
	led1Off();
	PTC->PCOR = 0xf00;
	led4On();
	led3On();
	led2On();
	led1On();
	PTC->PCOR = 0xf00;
	while (count-->0){
		//led1On();
		delay(10);
		//led2On();
		uartClearRxQueue(uart0Data);
		//led3On();
		
		draPutString("\r\nAT+DMOCONNECT\r\n");
		//led4On();
		delay(100);
		//draGetString(ret, 40);
		led3On();
		//if (strcmp(ret, "+DMOCONNECT: 0") == 0){
			draData.draInited = 1;
		//	return 0;
		//}
	} 
	//draData.draInited = 0;
	return 1;
}

char updateTxFreq(char* freq){
	 /* This doesnt take into account if the freq is good.....*/ 
	int lcv;
	for (lcv=0;lcv<FREQSTRLEN;lcv++){
		draData.draTxFreq[lcv] = freq[lcv];
	}
	return programDra();
}

char updateRxFreq(char* freq){
	 /* This doesnt take into account if the freq is good.....*/ 
	int lcv;
	for (lcv=0;lcv<FREQSTRLEN;lcv++){
		draData.draRxFreq[lcv] = freq[lcv];
	}
	return programDra();
}

char programDra(void){
	 /* AT+DMOSETGROUP=BW，TX_F，RX_F，Tx_subaudio，SQ，Rx_subaudio*/ 
	/* Sets up for 12.5 Khz BW*/ 
	int count;
	if (draData.draInited){
		do{
	//draPutString("AT+DMOSETGROUP=0，");
	draPutString("AT+DMOSETGROUP=0,145.3900,145.3900,0000,7,0000\r\n");
	//draPutString(draData.draTxFreq);
	//draPutString(", ");
	//draPutString(draData.draRxFreq);
	//draPutString(", 0000, ");
	//draPutString(draData.draSquelch);
	//draPutString(", 0000");
	//draPutString("\r\n");
			delay(100);
		} while (count++ < 4);
	return 0;
	} else {
		return 1;
	}
}

void draTx(){
	/* Need to set PTA4 to low. High is Rx*/ 
	PTA->PCOR = (1<<4);
}
void draRx(){
	PTA->PSOR = (1<<4);
	
}
