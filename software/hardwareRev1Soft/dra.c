<<<<<<< HEAD
#include "uart0.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <MKL26Z4.h>
#include "dra.h"

#define FREQSTRLEN 9 /* This takes into account the null termination. */ 


draDataStruct draData;
int initDRA(void){
	// Gets the DRA ready to go. 
	strcpy(draData.draTxFreq, "144.3900");
	strcpy(draData.draRxFreq, "144.3900");
	uart0Init();
	SIM->SCGC5  |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK ;
	// Need to init the pinz
	// PTB19 is hight low select. 
	PTB->PDDR |= (1 << 19) | (1 << 3);
	PTA->PDDR |= (1<<12);
	PTE->PDDR &= (1<<20);
	PTE->PSOR |= (1<<20); // Need to turn off the transmitter. 
	
	// PTB3 is the power down thingamajig. 
	// PTA12 is the squelch detect. 
	// PTe20 is the PTT. THIS IS THE NEW PIN Other was PTA4
	return 0;
}

char checkDRA(void){
	int count;
	char ret[40];
	count = 3;
	while (count-->0){
		draPutString("AT+DMOCONNECT\r\n");
		draGetString(ret, 40);
		if (strcmp(ret, "+DMOCONNECT: 0") == 0){
			draData.draInited = 1;
			return 0;
		}
	} 
	draData.draInited = 0;
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
	if (draData.draInited){
	draPutString("AT+DMOSETGROUP=0，");
	draPutString(draData.draTxFreq);
	draPutString(", ");
	draPutString(draData.draRxFreq);
	draPutString(", 0000, ");
	draPutString(draData.draSquelch);
	draPutString(", 0000");
	draPutString("\r\n");
	return 0;
	} else {
		return 1;
	}
}

void draTx(){
	/* Need to set PTA4 to low. High is Rx*/ 
	PTE->PSOR &= ~(1<<20);
}
void draRx(){
	PTE->PCOR |= (1<<20);
	
}
=======
#include "uart0.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <MKL26Z4.h>
#include "dra.h"

#define FREQSTRLEN 9 /* This takes into account the null termination. */ 


draDataStruct draData;
int initDRA(void){
	// Gets the DRA ready to go. 
	strcpy(draData.draTxFreq, "144.3900");
	strcpy(draData.draRxFreq, "144.3900");
	uart0Init();
	SIM->SCGC5  |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK ;
	// Need to init the pinz
	// PTB19 is hight low select. 
	PTB->PDDR |= (1 << 19) | (1 << 3);
	PTA->PDDR |= (1<<12);
	PTE->PDDR &= (1<<20);
	PTE->PSOR |= (1<<20); // Need to turn off the transmitter. 
	
	// PTB3 is the power down thingamajig. 
	// PTA12 is the squelch detect. 
	// PTe20 is the PTT. THIS IS THE NEW PIN Other was PTA4
	return 0;
}

char checkDRA(void){
	int count;
	char ret[40];
	count = 3;
	while (count-->0){
		draPutString("AT+DMOCONNECT\r\n");
		draGetString(ret, 40);
		if (strcmp(ret, "+DMOCONNECT: 0") == 0){
			draData.draInited = 1;
			return 0;
		}
	} 
	draData.draInited = 0;
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
	if (draData.draInited){
	draPutString("AT+DMOSETGROUP=0，");
	draPutString(draData.draTxFreq);
	draPutString(", ");
	draPutString(draData.draRxFreq);
	draPutString(", 0000, ");
	draPutString(draData.draSquelch);
	draPutString(", 0000");
	draPutString("\r\n");
	return 0;
	} else {
		return 1;
	}
}

void draTx(){
	/* Need to set PTA4 to low. High is Rx*/ 
	PTE->PSOR &= ~(1<<20);
}
void draRx(){
	PTE->PCOR |= (1<<20);
	
}
>>>>>>> 84f8769cc613e3b8a61078ac300a2ff84b4d58b7
