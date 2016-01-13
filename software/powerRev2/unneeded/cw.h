
#include "delay.h"
#ifdef AUDIOCW
#include "dac.h"
#include "sin.h"
#endif

#ifdef AUDIOCW
#define CWSINLENGTH SINLENGTH64
#define cwSinData sinData64


extern uint16_t cwSinData[CWSINLENGTH	];
//these need to be shared between the interrupt handler, which will change the delay (tone) and the initialization routine.

//extern char 	ax25CurrBit; //the index of the current bit.
//extern char* ax25DataPtr; //points to the current byte
//extern int 	ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark
//static LDD_TDeviceData *ax25DacPtr;
#endif

char cwSend(char* data, int len);

