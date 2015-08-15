#include "cw.h"
#define CLOCKRATE 48000000
/*#define CWDELAY 1000000000*((1/CWFREQ)*(1/SINUS_LENGTH))*/
#define DITTIME 100 //Time in milliseconds for a dit
#define DAHTIME (3 * (DITTIME))
#define LED1_On() PORTA |= (1<<7)
#define LED1_Off() PORTA &= ~(1<<7)

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
	0xA0,
	0xB0,
	0xB8,
	0xBC,
	0xBE,
	0xBF,
	0xAF,
	0xA7,
	0xA3,
	0xA1,
	};


void cwTone(char DitOrDah){
	LED1_On();		
	if (DitOrDah == 0) {
		/* Then we have a dah, 0 and all. `==*/ 
		_delay_ms(DAHTIME);
	} else {
		_delay_ms(DITTIME);
	}
	LED1_Off();	
}
char cwSend(char* data, int len){
	//sends stuff...
	char charLen;
	char currChar;
	char* cwDataPtr;
	char currBit;
	
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
			cwTone((currChar & ( 0x80 >> (3+currBit))));
			/* A little bit crazy, passes to the sender, the current bit. Ands the current morse byte with a shifted 1  to get the current character*/ 
			_delay_ms(DITTIME);
			charLen--;
			currBit ++;
		}
		cwDataPtr++;
		_delay_ms(DAHTIME);



	}
	_delay_ms(DAHTIME);
	
}
 
