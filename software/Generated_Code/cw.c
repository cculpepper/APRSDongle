#include "WAIT1.h"
#include "DA1.h"
#include "cw.h"
#include "TI1.h"
#include "LED1.h"
#define CLOCKRATE 48000000
#define CWFREQ 600
#define CWDELAY 1000000000*((1/CWFREQ)*(1/SINUS_LENGTH))
#define DITTIME 100 //Time in milliseconds for a dit
#define DAHTIME (3 * (DITTIME))
#define DITCYCLES ((DITTIME)*CWFREQ) 
#define DAHCYCLES ((DAHTIME)*CWFREQ) 
/*#define DITCYCLES (DITTIME * CWFREQ)*/
/*#define DAHCYCLES (DAHTIME * CWFREQ)*/


const short CWSinusOutputData[SINUS_LENGTH] = {
2248u, 2447u, 2642u, 2831u, 3013u, 3185u, 3347u, 3496u, 3631u, 3750u, 3854u, 3940u, 4007u, 4056u, 4086u, 4096u, 4086u, 4056u, 4007u, 3940u, 3854u, 3750u, 3631u, 3496u, 3347u, 3185u, 3013u, 2831u, 2642u, 2447u, 2248u, 2048u, 1847u, 1648u, 1453u, 1264u, 1082u, 910u, 748u, 599u, 464u, 345u, 241u, 155u, 88u, 39u, 9u, 0u, 9u, 39u, 88u, 155u, 241u, 345u, 464u, 599u, 748u, 910u, 1082u, 1264u, 1453u, 1648u, 1847u, 2048u,

};

const char CwLetterData[26] = {
	 /* 3 bit length, 5 bits of data. Can do everything but symbols.....*/ 
	/* Bits are right aligned, 1 is dit, 0 is dah a is 10 */ 
	0x50, 
	0x8E,
	0x8A,
	0x6C,
	0x30,
	0x9A,
	0x64,
	0x9E,
	0x58,
	0x90,
	0x68,
	0x96,
	0x40,
	0x48,
	0x60,
	0x92,
	0x9A,
	0x74,
	0x7C,
	0x20,
	0x78,
	0x9C,
	0x70,
	0x8C,
	0x88,
	0x86
};  
const char CwNumberData[10] = {
	0xB0,
	0xB8,
	0xBC,
	0xBE,
	0xBF,
	0xAF,
	0xA7,
	0xA3,
	0xA1,
	0xA0};


void cwTone(char DitOrDah, LDD_TDeviceData* cwDacPtr){
	unsigned long CyclesLeft;
	int sinIndex;
	LDD_TError Error;
	if (DitOrDah == 0) {
		/* Then we have a dah, 0 and all. `==*/ 
		CyclesLeft = DAHCYCLES;
	} else {
		CyclesLeft = DITCYCLES;
	}
	LED1_On();	
	while (CyclesLeft > 0){

		Error = DA1_SetValue(cwDacPtr, CWSinusOutputData[sinIndex]);
		WAIT1_Waitus(33);
		/*WAIT1_Waitns(CWDELAY);*/
		sinIndex++;
		if (sinIndex > SINUS_LENGTH){
			sinIndex = 0;
			CyclesLeft--;
		}
	}
	LED1_Off();	
}
char cwSend(char* data, int len, LDD_TDeviceData* cwDacPtr){
	//sends stuff...
	int sinIndex;
	char charLen;
	char currChar;
	char* cwDataPtr;
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
		while ( charLen > 0 ){
			cwTone(currChar & ( 0x80 >> (5-charLen)), cwDacPtr);
			/* A little bit crazy, passes to the sender, the current bit. Ands the current morse byte with a shifted 1  to get the current character*/ 
			WAIT1_Waitms(DITTIME);
			charLen--;
		}
		cwDataPtr++;
		WAIT1_Waitms(DAHTIME);



	}
	for (charLen = 0; charLen < 10; charLen++){
		LED1_On();
		WAIT1_Waitms(100);
		LED1_Off();
		WAIT1_Waitms(100);
	}
}
 
