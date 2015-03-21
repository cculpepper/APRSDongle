
#include "WAIT1.h"
#include "DA1.h"

#define DATA_LENGTH 10                                                  /* Output data array length */
#define SINUS_LENGTH 64


//these need to be shared between the interrupt handler, which will change the delay (tone) and the initialization routine.

//extern char 	ax25CurrBit; //the index of the current bit.
//extern char* ax25DataPtr; //points to the current byte
//extern int 	ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark
//static LDD_TDeviceData *ax25DacPtr;

char ax25Send(char* data, int len, LDD_TDeviceData* ax25DacPtr);
char ax25TimerIntHand(void);
char ax25TimerInit(void);

