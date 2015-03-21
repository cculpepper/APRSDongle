
#include "WAIT1.h"
#include "DA1.h"
#include "ax25.h"
#include "TI1.h"
#include "LED1.h"
#define CLOCKRATE 48000000
#define AX25FUDGECYCLES 10  /*Just a number of cycles to fudge the delay closer*/ 
#define AX25MARKFREQ 1200
#define AX25MARKDELAY ( CLOCKRATE * (1 / AX25MARKFREQ) * ( 1 / SINUS_LENGTH ) - AX25FUDGECYCLES)
#define AX25SPACEFREQ 2200
#define AX25SPACEDELAY ( CLOCKRATE * (1 / AX25SPACEFREQ) * ( 1 / SINUS_LENGTH ) - AX25FUDGECYCLES)
/*#define AX25MARKDELAY 625*/
/*#define AX25MARKDELAY 3255*/
/*#define AX25SPACEDELAY 340*/
/*#define AX25SPACEDELAY 1775*/

volatile char 	ax25CurrBit; //the index of the current bit.
volatile char*	ax25DataPtr; //points to the current byte
volatile int 		ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark
volatile int 		cycleDelay;		//Numbers of cycles left to delay
const short SinusOutputData[SINUS_LENGTH] = {
2248u, 2447u, 2642u, 2831u, 3013u, 3185u, 3347u, 3496u, 3631u, 3750u, 3854u, 3940u, 4007u, 4056u, 4086u, 4096u, 4086u, 4056u, 4007u, 3940u, 3854u, 3750u, 3631u, 3496u, 3347u, 3185u, 3013u, 2831u, 2642u, 2447u, 2248u, 2048u, 1847u, 1648u, 1453u, 1264u, 1082u, 910u, 748u, 599u, 464u, 345u, 241u, 155u, 88u, 39u, 9u, 0u, 9u, 39u, 88u, 155u, 241u, 345u, 464u, 599u, 748u, 910u, 1082u, 1264u, 1453u, 1648u, 1847u, 2048u,

};


char ax25SendNoInt(char* data, int len, LDD_TDeviceData* ax25DacPtr){
	//sends stuff...
	int sinIndex;
	LDD_TError Error;
	int sinIndexChange; // The number of sin indices left until a change. Janky as shit. 
	int delayFudgeCycles; // Number of cycles to remove from the current delay. 
	LED1_On();
	delayFudgeCycles = 0;
	sinIndexChange = SINUS_LENGTH;
	ax25CurrBit = 7;
	ax25DataPtr = data;
	ax25ToneDelay = AX25MARKDELAY; //Dont know if this is right.;
	sinIndex = 0;
	Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
	if (Error != 0){
		/* Then we probz cant go further, not going to worry for now. */ 
		1+1;
	}
	while (1==1){//((data+len) > ax25DataPtr){
		Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
		/*WAIT1_WaitCycles(ax25ToneDelay-delayFudgeCycles);*/
		/*WAIT1_Waitns(2000);*/
		WAIT1_Waitns(ax25ToneDelay-delayFudgeCycles);
		delayFudgeCycles = 0;
		sinIndex++;
		if (sinIndex >= SINUS_LENGTH){
			sinIndex = 0;
		}
		sinIndexChange--;
		if (1==0){//(sinIndexChange <=0){
			if(!((0x80 >> ax25CurrBit) & *ax25DataPtr)){ 
				//We need to change the freq
				if (ax25ToneDelay == AX25MARKDELAY){
					ax25ToneDelay = AX25SPACEDELAY;
				} else {
					ax25ToneDelay = AX25MARKDELAY;
				}
				delayFudgeCycles +=8; // The above takes about 8 cycles..................
			}
			if (ax25CurrBit == 0){
				//we need to inc the data ptr and set the currbit to 7
				ax25CurrBit = 7;
				ax25DataPtr++;
				delayFudgeCycles += 4;//The above takes about 4 cycles....
			}	
		}
	}
	LED1_Off();
	return 0;

}
char ax25Send(char* data, int len, LDD_TDeviceData* ax25DacPtr){
	//sends stuff...
	int sinIndex;
	LDD_TError Error;
	ax25CurrBit = 7;
	ax25DataPtr = data;
	ax25ToneDelay = AX25MARKDELAY; //Dont know if this is right.;
	sinIndex = 0;
	Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
	ax25TimerInit();
	while ((data+len) > ax25DataPtr){
		Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
		cycleDelay = ax25ToneDelay;
		/*__asm volitile (*/
				/*ax25DelayLoop:*/
				/*add %[cycleDelay], %[cycleDelay], #-4*/
				/*cmp %[cycleDelay], 0*/
				/*[>bgt ax25DelayLoop<]*/
				/*);*/
		WAIT1_Waitns(ax25ToneDelay);
		sinIndex++;
		if (sinIndex >= SINUS_LENGTH){
			sinIndex = 0;
		}
	}
	return 0;
}
char ax25TimerIntHand(){
	char bitMask = 0;
	//bitMask = (0x80 >> ax25CurrBit);
	if(!((0x80 >> ax25CurrBit) & *ax25DataPtr)){ 
		//We need to change the freq
		if (ax25ToneDelay == AX25MARKDELAY){
			ax25ToneDelay = AX25SPACEDELAY;
		} else {
			ax25ToneDelay = AX25MARKDELAY;
		}
	}
	if (ax25CurrBit == 0){
		//we need to inc the data ptr and set the currbit to 7
		ax25CurrBit = 7;
		ax25DataPtr++;
	}	
	return 0;
}
char ax25TimerInit(){
	//need to set up the timer for 0.833333 ms. 
	TI1_Enable(TI1_DeviceData);
	return 1;
}
