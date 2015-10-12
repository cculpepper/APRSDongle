#include <stdint.h>
#pragma once
#ifndef __AX25HEAD
#define __AX25HEAD

#define DATA_LENGTH 10                                                  /* Output data array length */
#define AX25SINDATALENGTH 64

//these need to be shared between the interrupt handler, which will change the delay (tone) and the initialization routine.

//extern char 	ax25CurrBit; //the index of the current bit.
//extern char* ax25DataPtr; //points to the current byte
//extern int 	ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark
//static LDD_TDeviceData *ax25DacPtr;



volatile extern signed int ax25BytesLeft;
volatile extern char* ax25DataPtr;
volatile extern int ax25SinIndex;
volatile extern signed char ax25CurrBit;
volatile extern char ax25Padding;
volatile extern uint16_t ax25CRC; /* Not sure about this*/ 
volatile extern signed char ax25CurrByte;
volatile extern char ax25Sending;
volatile extern uint32_t ax25CurrDelay;  /* Ticks of a 24 MHz clock we are currently delaying.  */ 
volatile extern char ax25OnesCount;
extern uint16_t ax25CrcPoly;
#define AX25MARKDELAY 300  /* .5 */ 
#define AX25SPACEDELAY 300  /* .45  */ 
#define AX25BAUDTIME 20000000

extern int ax25IntSend(char* data, int len);
extern char ax25SendNoInt(char* data, int len);
extern char ax25TimerIntHand(void);
extern char ax25TimerInit(void);
extern void ax25SwitchFreq(void);
extern void ax25ChangeBit(void);
extern void ax25ChangeDac(void);
extern void ax25UpdateCrc(char bit);
void ax25StopTimers(void);
/*const short SinusOutputDatafull[AX25SINDATALENGTH] = {*/
/*2248u, 2447u, 2642u, 2831u, 3013u, 3185u, 3347u, 3496u, 3631u, 3750u, 3854u, 3940u, 4007u, 4056u, 4086u, 4096u, 4086u, 4056u, 4007u, 3940u, 3854u, 3750u, 3631u, 3496u, 3347u, 3185u, 3013u, 2831u, 2642u, 2447u, 2248u, 2048u, 1847u, 1648u, 1453u, 1264u, 1082u, 910u, 748u, 599u, 464u, 345u, 241u, 155u, 88u, 39u, 9u, 0u, 9u, 39u, 88u, 155u, 241u, 345u, 464u, 599u, 748u, 910u, 1082u, 1264u, 1453u, 1648u, 1847u, 2048u,*/

/*};*/
extern const short ax25SinData[AX25SINDATALENGTH];

#endif
