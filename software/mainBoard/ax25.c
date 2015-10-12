
#include "dac.h"
#include "ax25.h"
#include "PIT.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif 

/*volatile char 	ax25CurrBit; //the index of the current bit.*/
/*volatile char*	ax25DataPtr; //points to the current byte*/
/*volatile int 		ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark*/
/*volatile int 		cycleDelay;		//Numbers of cycles left to delay*/
void ax25StartSinTimer(void);
void ax25StartToneTimer(void);
void ax25StopTimer(void);
//const short ax25SinData[AX25SINDATALENGTH] = {	2248u,	2447u,	2642u,	2831u,	3013u,	3185u,	3347u,	3496u,	3631u,	3750u,	3854u,	3940u,	4007u,	4056u,	4086u,	4094u,	4086u,	4056u,	4007u,	3940u,	3854u,	3750u,	3631u,	3496u,	3347u,	3185u,	3013u,	2831u,	2642u,	2447u,	2248u,	2048u,	1847u,	1648u,	1453u,	1264u,	1082u,	910u,	748u,	599u,	464u,	345u,	241u,	155u,	88u,	39u,	9u,	0u,	9u,	39u,	88u,	155u,	241u,	345u,	464u,	599u,	748u,	910u,	1082u,	1264u,	1453u,	1648u,	1847u,	2048u};

const short ax25SinData[AX25SINDATALENGTH] = {	0x620, 0x680, 0x740, 0x800, 0x856, 0x912, 0x964, 0x1012, 0x1056, 0x1100,        0x1136, 0x1164, 0x1192, 0x1212, 0x1228, 0x1236, 0x1240, 0x1236, 0x1228, 0x1212, 0x1192, 0x1164, 0x1136, 0x1100, 0x1056, 0x1012, 0x964, 0x912, 0x856, 0x800,     0x740, 0x680, 0x620, 0x556, 0x496, 0x440, 0x380, 0x324, 0x272, 0x224, 0x180,    0x140, 0x104, 0x72, 0x44, 0x24, 0x8, 0x0, 0x0, 0x0, 0x8, 0x24, 0x44, 0x72,      0x104, 0x140, 0x180, 0x224, 0x272, 0x324, 0x380, 0x440, 0x496, 0x556 };
volatile int ax25BytesLeft;
volatile char* ax25DataPtr;
volatile int ax25SinIndex;
volatile signed char ax25CurrBit;
volatile char ax25Padding;
volatile signed char ax25CurrByte;
volatile char ax25Sending;
volatile char ax25Preamble;
volatile uint32_t ax25CurrDelay;  /* Ticks of a 24 MHz clock we are currently delaying.  */ 
volatile char ax25OnesCount;

char ax25GetSending(void){
	return ax25Sending;	
}
//volatile extern uint16_t ax25CRC; /* Not sure about this*/ 
volatile uint16_t ax25CRC;
int ax25IntSend(char* dataPtr, int len){

	uint32_t locCRC;
	ax25BytesLeft = len;
	ax25DataPtr = dataPtr;
	/*ax25CrcPoly = 0; //0b0001000000100001;*/
	ax25SinIndex = 0;
	ax25CurrBit = 7;
	ax25Padding = 0;
	ax25CRC = 1;  /* TODO more here. No idea how this works...*/ 
	ax25CurrByte = 0x7E;  /* The flag */ 
	ax25Sending = 1;
	ax25OnesCount = 0;
	ax25Preamble = 1;
	ax25CurrDelay = AX25SPACEDELAY;
	
	dacInit();
	/* Now we need to set up the 1.2 KHz timer up for regular sending...*/ 
	ax25StartSinTimer();
	ax25StartToneTimer();
	
	while (ax25Sending);
	locCRC = ax25CRC;
	ax25CurrByte = (locCRC & 0xFF00) >> 8;
	//PIT_LDVAL0 = 12000000; //This may fix the issues
	//PIT_LDVAL1 = 12000000; //This may fix the issues
	ax25StopTimers();
	//cwSend("DONE", 5, ax25DacPtr  );
}

void ax25StartSinTimer(void){
	/* No idea what to do here*/ 
	/* Note this uses the 24 MHz bus clock */ 
	startPIT0(ax25ChangeDac, ax25CurrDelay);
}
void ax25StartToneTimer(void){
	/* starts the timer to change the tone, 1200 times a second.  */ 

	startPIT1(ax25ChangeBit, AX25BAUDTIME);
}
void ax25StopTimers(void){
	stopPIT0();
	stopPIT1();
	SIM->SCGC6 &= ~ SIM_SCGC6_PIT_MASK;
}

void ax25SwitchFreq(void){
	if (ax25CurrDelay == AX25MARKDELAY){
		ax25CurrDelay = AX25SPACEDELAY;
	} else {
		ax25CurrDelay = AX25MARKDELAY;
	}
}

void ax25ChangeBit(void){

	if (ax25Sending){
		if ((0x80 >> ax25CurrBit) & ax25CurrByte){
			/*[> If a one, keep frequencies<] */
			if (ax25Padding){
				ax25OnesCount++;
				if (ax25OnesCount > 5){
					ax25SwitchFreq();
					ax25OnesCount = 0;
				}
			} 
		} else {
			ax25OnesCount = 0;
			ax25SwitchFreq();
		}
		if (ax25CurrBit <= 0){  /*We check after because its easier. If we need to increment the current byte*/
			/*then weve already sent it.  */
			/*[> Then we need to move onto the next thing<] */
			ax25BytesLeft--;
			ax25CurrByte = *ax25DataPtr;
			ax25DataPtr++;
			if (!ax25Preamble){ // if were sending the preamble, keep sending
			if (ax25BytesLeft <= 0){
				ax25Sending = 0;
				/*return;  [> Nothing left ta do<] */
			}
		} else {
			ax25Preamble = 0;
			ax25Padding = 0;
		}
			ax25CurrBit = 7;
		} else {
			ax25CurrBit--;
		}
	}
}

extern void ax25ChangeDac(void){
	/*Write your code here ... */
	/*ax25TimerIntHand();*/
	/*This is for the sin wave */
	if (ax25Sending){
		dacSet(ax25SinData[ax25SinIndex++]);
		if (ax25SinIndex >= AX25SINDATALENGTH){
			ax25SinIndex = 0;
		}
		PIT->CHANNEL[0].LDVAL = ax25CurrDelay;
	}
}
void ax25UpdateCrc(char bit){
	ax25CRC ^= bit;
	if (ax25CRC & 1){
		ax25CRC = (ax25CRC >> 1) ^ 0x8408;
	} else {
		ax25CRC = ax25CRC >> 1;
	}
}