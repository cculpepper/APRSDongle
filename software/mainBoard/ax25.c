
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
const short ax25SinData[AX25SINDATALENGTH] = {	2248u,	2447u,	2642u,	2831u,	3013u,	3185u,	3347u,	3496u,	3631u,	3750u,	3854u,	3940u,	4007u,	4056u,	4086u,	4094u,	4086u,	4056u,	4007u,	3940u,	3854u,	3750u,	3631u,	3496u,	3347u,	3185u,	3013u,	2831u,	2642u,	2447u,	2248u,	2048u,	1847u,	1648u,	1453u,	1264u,	1082u,	910u,	748u,	599u,	464u,	345u,	241u,	155u,	88u,	39u,	9u,	0u,	9u,	39u,	88u,	155u,	241u,	345u,	464u,	599u,	748u,	910u,	1082u,	1264u,	1453u,	1648u,	1847u,	2048u};

volatile int ax25BytesLeft;
volatile char* ax25DataPtr;
volatile int ax25SinIndex;
volatile signed char ax25CurrBit;
volatile char ax25Padding;
volatile signed char ax25CurrByte;
volatile char ax25Sending;
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
	ax25CurrDelay = AX25SPACEDELAY;
	
	dacInit();
	/* Now we need to set up the 1.2 KHz timer up for regular sending...*/ 
	ax25StartSinTimer();
	ax25StartToneTimer();
	while (ax25CurrByte == 0x7E);  /*[> Wait for the current byte to chonge.... Hacky. Sorry...<] */
	ax25Padding = 1;
	ax25Sending = 1;
	/*__asm {
loop:
movs r0, #ax25Sending
	//ldrb r0, [r0,0]
	subs r0, r0, 1 // New if r0 is zero, then we are still sending
	beq  loop 
	}*/
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

	startPIT1(ax25ChangeBit, 200000);
}
void ax25StopTimers(void){
	stopPIT0();
	stopPIT1();
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
			if (ax25BytesLeft <= 0){
				ax25Sending = 0;
				/*return;  [> Nothing left ta do<] */
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
/*char ax25Send(char* data, int len, LDD_TDeviceData* ax25DacPtr){*/
/*//sends stuff...*/
/*int sinIndex;*/
/*LDD_TError Error;*/
/*ax25CurrBit = 7;*/
/*ax25DataPtr = data;*/
/*ax25ToneDelay = AX25MARKDELAY; //Dont know if this is right.;*/
/*sinIndex = 0;*/
/*Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
/*ax25TimerInit();*/
/*while ((data+len) > ax25DataPtr){*/
/*Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
/*cycleDelay = ax25ToneDelay;*/
/*[>__asm volitile (<]*/
/*[>ax25DelayLoop:<]*/
/*[>add %[cycleDelay], %[cycleDelay], #-4<]*/
/*[>cmp %[cycleDelay], 0<]*/
/*[>[>bgt ax25DelayLoop<]<]*/
/*[>);<]*/
/*WAIT1_Waitns(ax25ToneDelay);*/
/*sinIndex++;*/
/*if (sinIndex >= AX25SINDATALENGTH){*/
/*sinIndex = 0;*/
/*}*/
/*}*/
/*return 0;*/
/*}*/
/*char ax25TimerIntHand(){*/
/*char bitMask = 0;*/
/*//bitMask = (0x80 >> ax25CurrBit);*/
/*if(!((0x80 >> ax25CurrBit) & *ax25DataPtr)){ */
/*//We need to change the freq*/
/*if (ax25ToneDelay == AX25MARKDELAY){*/
/*ax25ToneDelay = AX25SPACEDELAY;*/
/*} else {*/
/*ax25ToneDelay = AX25MARKDELAY;*/
/*}*/
/*}*/
/*if (ax25CurrBit == 0){*/
/*//we need to inc the data ptr and set the currbit to 7*/
/*ax25CurrBit = 7;*/
/*ax25DataPtr++;*/
/*}	*/
/*return 0;*/
/*}*/
/*char ax25TimerInit(){*/
/*//need to set up the timer for 0.833333 ms. */
/*TI1_Enable(TI1_DeviceData);*/
/*return 1;*/
/*}*/
/*char ax25SendNoInt(char* data, int len, LDD_TDeviceData* ax25DacPtr){*/
/*//sends stuff...*/
/*int sinIndex;*/
/*unsigned short sinIndexChange; // The number of sin indices left until a change. Janky as shit. */
/*int delayFudgeCycles; // Number of cycles to remove from the current delay. */
/*unsigned char oneCount;*/
/*oneCount = 0;  [> This is for bitstuffing<] */
/*[>LED1_On();<]*/
/*delayFudgeCycles = 0;*/
/*sinIndexChange = AX25SPACESINSEGMENTS;*/
/*ax25CurrBit = 7;*/
/*ax25DataPtr = data;*/
/*ax25ToneDelay = AX25SPACEDELAY; //Dont know if this is right.;*/
/*sinIndex = 0;*/
/*DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/

/*while ((data+len) > ax25DataPtr){*/
/*DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);*/
/*WAIT1_WaitCycles(ax25ToneDelay-delayFudgeCycles);*/
/*[>WAIT1_Waitns(2000);<]*/
/*[>WAIT1_Waitns(abs(ax25ToneDelay-delayFudgeCycles));<]*/
/*[>WAIT1_WaitCycles(60);<]*/
/*[>WAIT1_WaitCycles(168);<]*/
/*delayFudgeCycles = 0;*/
/*sinIndex++;*/
/*if (sinIndex >= AX25SINDATALENGTH){*/
/*sinIndex = 0;*/
/*}*/
/*sinIndexChange--;*/
/*if (sinIndexChange <=0){*/
/*if((0x80 >> ax25CurrBit) & *ax25DataPtr){ */
/*[> Then we have a 1<] */
/*oneCount++;*/
/*if (oneCount > 5){*/
/*[> Stuff a bit<] */
/*oneCount = 0;*/

/*cwSend("Z",1,ax25DacPtr);*/
/*if (ax25ToneDelay == AX25MARKDELAY){*/
/*ax25ToneDelay = AX25SPACEDELAY;*/
/*sinIndexChange = AX25SPACESINSEGMENTS;*/
/*[>LED1_Off();<]*/
/*[>cwSend("S",1,ax25DacPtr);<]*/
/*} else {*/
/*ax25ToneDelay = AX25MARKDELAY;*/
/*sinIndexChange = AX25MARKSINSEGMENTS;*/
/*[>LED1_On();<]*/
/*[>cwSend("M",1,ax25DacPtr);<]*/
/*} */


/*} else {*/

/*ax25CurrBit --;*/
/*[>Go to the next bit, bit stuffing doesnt go to the next bit. <]*/
/*cwSend("H",1,ax25DacPtr);*/
/*}*/
/*delayFudgeCycles +=8; // The above takes about 8 cycles..................*/
/*} else {*/
/*//We need to change the freq*/
/*oneCount = 0;*/
/*cwSend("S",1,ax25DacPtr);*/
/*if (ax25ToneDelay == AX25MARKDELAY){*/
/*ax25ToneDelay = AX25SPACEDELAY;*/
/*sinIndexChange = AX25SPACESINSEGMENTS;*/
/*[>LED1_Off();<]*/
/*} else {*/
/*ax25ToneDelay = AX25MARKDELAY;*/
/*sinIndexChange = AX25MARKSINSEGMENTS;*/
/*[>LED1_On();<]*/
/*}*/
/*delayFudgeCycles +=8; // The above takes about 8 cycles..................*/
/*ax25CurrBit --;*/
/*}*/
/*if (ax25CurrBit == 0){*/
/*//we need to inc the data ptr and set the currbit to 7*/
/*ax25CurrBit = 7;*/
/*ax25DataPtr++;*/
/*[>cwSend(ax25DataPtr, 1, ax25DacPtr);<]*/
/*delayFudgeCycles += 4;//The above takes about 4 cycles....*/
/*}	*/
/*}*/
/*}*/
/*[>LED1_Off();<]*/
/*return 0;*/

/*}*/
