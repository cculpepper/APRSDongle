#include "delay.h"
#include "cw.h"
#include "gpio.h"

#ifdef AUDIOCW

#include "PIT.h"
#include "dac.h"
#include "sin.h"
#endif

#define CLOCKRATE 28000000
#define CWFREQ 700
/*#define CWDELAY 1000000000*((1/CWFREQ)*(1/SINUS_LENGTH))*/
#define DITTIME 100 //Time in milliseconds for a dit
#define DAHTIME (3 * (DITTIME))
/*#define DITCYCLES (DITTIME * CWFREQ)*/
/*#define DAHCYxCLES (DAHTIME * CWFREQ)*/
#define TONECYCLES ((CLOCKRATE / CWFREQ) / CWSINLENGTH)
//#define AUDIOCW


const char CwLetterData[26] = {
	 /* 3 bit length, 5 bits of data. Can do everything but symbols.....*/ 
	/* Bits are right aligned, 1 is dit, 0 is dah a is 10 */ 	0x50, 	0x8E,	0x8A,	0x6C,	0x30,	0x9A,	0x64,	0x9E,	0x58,	0x90,	0x68,	0x96,	0x40,	0x48,	0x60,	0x92,	0x9A,	0x74,	0x7C,	0x20,	0x78,	0x9C,	0x70,	0x8C,	0x88,	0x86
};  
const char CwNumberData[10] = {	0xA0,	0xB0,	0xB8,	0xBC,	0xBE,	0xBF,	0xAF,	0xA7,	0xA3,	0xA1,
	};

int sinIndex;

#ifdef AUDIOCW
void cwPitIsr(void){
	dacSet(cwSinData[sinIndex++]);
	if(sinIndex > CWSINLENGTH ){
		sinIndex = 0;
	}
}
#endif
void cwTone(char DitOrDah){
	unsigned long CyclesLeft;
	sinIndex = 0;
#ifdef AUDIOCW
	startPIT0((void*) cwPitIsr, TONECYCLES);
#endif
	if (DitOrDah == 0) {
		/* Then we have a dah, 0 and all. `==*/ 
		delay(DAHTIME);
	} else {
		delay(DITTIME);
	}
#ifdef AUDIOCW
	stopPIT0();
#endif
	sinIndex = 0;
}
char cwSend(char* data, int len){
	//sends stuff...
	char charLen;
	char currChar;
	char* cwDataPtr;
	char currBit;
	led1Off();
#ifdef AUDIOCW
	dacInit();
#endif
	cwDataPtr = data;
	while((data+len) > cwDataPtr){
		currChar = *cwDataPtr;
		if (currChar >= 'A' && currChar <= 'Z'){
			currChar = CwLetterData[currChar - 'A']; /* This sets the current char to the morse binary representation of the letter if it is a letter. */ 
		} else if (currChar >= '0' && currChar <= '9'){
			currChar = CwNumberData[currChar - '0'];
		} else {
			currChar = 0;  /* Because I dont know what to do...*/ 
		}

		charLen = (currChar >> 5); /* This is the length of the morse code char, in the top 3 bits*/ 
		currBit = 0;
		while ( charLen > 0 ){
			led1On();
			cwTone((currChar & ( 0x80 >> (3+currBit))));
			led1Off();
			/* A little bit crazy, passes to the sender, the current bit. Ands the current morse byte with a shifted 1  to get the current character*/ 
			delay(DITTIME);
			charLen--;
			currBit ++;
		}
		cwDataPtr++;
		delay(DAHTIME);



	}
}
 
