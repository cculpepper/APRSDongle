#include "uart0.h"
#include "dac.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#ifndef DRA_H
#define DRA_H
#define draPutString(x) uart0PutString(x);
#define draGetString(x, y) uart0GetString(x, y );

#define FREQSTRLEN 9 /* This takes into account the null termination. */ 

typedef struct{
	char draTxFreq[FREQSTRLEN]; /* 144.3900\0*/ 
	char draRxFreq[FREQSTRLEN];
	char draSquelch[2]; /* [0-8]\0*/ 
	char draPL[5];
	
	char draInited;
} draDataStruct;
extern draDataStruct draData;
int initDRA(void);

char checkDRA(void);
char updateTxFreq(char* freq);
char updateRxFreq(char* freq);
char programDra(void);
void draTx(void);
void draRx(void);
#endif
