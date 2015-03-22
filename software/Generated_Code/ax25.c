
#include "WAIT1.h"
#include "DA1.h"
#include "ax25.h"
#include "TI1.h"
#include "LED1.h"
#define CLOCKRATE 48000000
#define AX25FUDGECYCLES 10  /*Just a number of cycles to fudge the delay closer*/ 
#define AX25MARKFREQ 1200
/*#define AX25MARKDELAYNS (( 1/ AX25MARKFREQ )*( 1/SINUS_LENGTH )*1000000000)*/
#define AX25MARKDELAYNS 1302
#define AX25MARKDELAY ( CLOCKRATE * (1 / AX25MARKFREQ) * ( 1 / SINUS_LENGTH ) - AX25FUDGECYCLES)
#define AX25SPACEFREQ 2200
#define AX25SPACEDELAYNS 7102
/*#define AX25SPACEDELAYNS (( 1/ AX25SPACEFREQ )*( 1/SINUS_LENGTH )*1000000000)*/
#define AX25SPACEDELAY ( CLOCKRATE * (1 / AX25SPACEFREQ) * ( 1 / SINUS_LENGTH ) - AX25FUDGECYCLES)
#define AX25MARKSINSEGMENTS 64000 /* Number of sin segments before changing tones*/ 
#define AX25SPACESINSEGMENTS 117000
/*#define AX25MARKSINSEGMENTS 64 [> Number of sin segments before changing tones<] */
/*#define AX25SPACESINSEGMENTS 117*/
/*#define AX25MARKDELAY 625*/
/*#define AX25MARKDELAY 3255*/
/*#define AX25SPACEDELAY 340*/
/*#define AX25SPACEDELAY 1775*/

volatile char 	ax25CurrBit; //the index of the current bit.
volatile char*	ax25DataPtr; //points to the current byte
volatile int 		ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark
volatile int 		cycleDelay;		//Numbers of cycles left to delay
const short SinusOutputDatafull[SINUS_LENGTH] = {
2248u, 2447u, 2642u, 2831u, 3013u, 3185u, 3347u, 3496u, 3631u, 3750u, 3854u, 3940u, 4007u, 4056u, 4086u, 4096u, 4086u, 4056u, 4007u, 3940u, 3854u, 3750u, 3631u, 3496u, 3347u, 3185u, 3013u, 2831u, 2642u, 2447u, 2248u, 2048u, 1847u, 1648u, 1453u, 1264u, 1082u, 910u, 748u, 599u, 464u, 345u, 241u, 155u, 88u, 39u, 9u, 0u, 9u, 39u, 88u, 155u, 241u, 345u, 464u, 599u, 748u, 910u, 1082u, 1264u, 1453u, 1648u, 1847u, 2048u,

};
const short SinusOutputData[SINUS_LENGTH] = {
749u,
815u,
880u,
943u,
1004u,
1061u,
1115u,
1165u,
1210u,
1250u,
1284u,
1313u,
1335u,
1352u,
1362u,
1365u,
1362u,
1352u,
1335u,
1313u,
1284u,
1250u,
1210u,
1165u,
1115u,
1061u,
1004u,
943u,
880u,
815u,
749u,
682u,
615u,
549u,
484u,
421u,
360u,
303u,
249u,
199u,
154u,
115u,
80u,
51u,
29u,
13u,
3u,
0u,
3u,
13u,
29u,
51u,
80u,
115u,
154u,
199u,
249u,
303u,
360u,
421u,
484u,
549u,
615u,
682u,
};

char ax25SendNoInt(char* data, int len, LDD_TDeviceData* ax25DacPtr){
	//sends stuff...
	int sinIndex;
	LDD_TError Error;
	unsigned short sinIndexChange; // The number of sin indices left until a change. Janky as shit. 
	int delayFudgeCycles; // Number of cycles to remove from the current delay. 
	/*LED1_On();*/
	delayFudgeCycles = 0;
	sinIndexChange = SINUS_LENGTH;
	ax25CurrBit = 7;
	ax25DataPtr = data;
	ax25ToneDelay = AX25SPACEDELAYNS; //Dont know if this is right.;
	sinIndex = 0;
	Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
	if (Error != 0){
		/* Then we probz cant go further, not going to worry for now. */ 
		1+1;
	}
	while ((data+len) > ax25DataPtr){
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
		if (sinIndexChange <=0){
			if((0x80 >> ax25CurrBit) & *ax25DataPtr){ 
				//We need to change the freq
				if (ax25ToneDelay == AX25MARKDELAYNS){
					ax25ToneDelay = AX25SPACEDELAYNS;
					sinIndexChange = AX25SPACESINSEGMENTS;
					LED1_Off();
					cwSend("S",1,ax25DacPtr);
				} else {
					ax25ToneDelay = AX25MARKDELAYNS;
					sinIndexChange = AX25MARKSINSEGMENTS;
					LED1_On();
					cwSend("M",1,ax25DacPtr);
				}
				delayFudgeCycles +=8; // The above takes about 8 cycles..................
			} else {

				cwSend("H",1,ax25DacPtr);
			}
			ax25CurrBit --;
			if (ax25CurrBit == 0){
				//we need to inc the data ptr and set the currbit to 7
				ax25CurrBit = 7;
				ax25DataPtr++;
				/*cwSend(ax25DataPtr, 1, ax25DacPtr);*/
				delayFudgeCycles += 4;//The above takes about 4 cycles....
			}	
		}
	}
	/*LED1_Off();*/
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
