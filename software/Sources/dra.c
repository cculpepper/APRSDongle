#include "uart.h"
#include "stdio.h"
#include "string.h"

#define FREQSTRLEN 9 /* This takes into account the null termination. */ 
char draTxFreq[FREQSTRLEN]; /* 144.3900\0*/ 
char draRxFreq[FREQSTRLEN];
char draSquelch[2]; /* [0-8]\0*/ 
char draInited;
char checkDRA(void){
	int count;
	char ret[40];
	count = 3;
	while (count-->0){
		putString("AT+DMOCONNECT");
		putChar(0x0D);
		putChar(0x0A);
		getString(ret);
		if (strcmp(ret, "+DMOCONNECT: 0") == 0){
			draInited = 1;
			return 0;
		}
	} 
	draInited = 0;
	return 1;
}

char updateTxFreq(char* freq){
	 /* This doesnt take into account if the freq is good.....*/ 
	int lcv;
	for (lcv=0;lcv<FREQSTRLEN;lcv++){
		draTxFreq[lcv] = freq[lcv];
	}
	return programDra();
}

char updateRxFreq(char* freq){
	 /* This doesnt take into account if the freq is good.....*/ 
	int lcv;
	for (lcv=0;lcv<FREQSTRLEN;lcv++){
		draRxFreq[lcv] = freq[lcv];
	}
	return programDra();
}

char programDra(void){
	 /* AT+DMOSETGROUP=BW，TX_F，RX_F，Tx_subaudio，SQ，Rx_subaudio*/ 
	/* Sets up for 12.5 Khz BW*/ 
	if (draInited){
	PutString("AT+DMOSETGROUP=0，");
	PutString(draTxFreq);
	PutString(", ");
	PutString(draRxFreq);
	PutString(", 0000, ");
	PutString(draSquelch);
	PutString(", 0000");
	putChar(0x0D);
	putChar(0x0A);
	return 0;
	} else {
		return 1;
	}
}

char draTx(){
	/* Need to set PTA4 to low. High is Rx*/ 
	GPIOA_PSOR |= (1<<4);
}
char draRx(){
	GPIOA_PCOR |= (1<<4);
}
char initDra(void){
	
