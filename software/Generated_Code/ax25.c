
#include "WAIT1.h"
#include "DA1.h"
#include "ax25.h"
#include "TI1.h"
#define AX25MARKDELAY 3255
#define AX25SPACEDELAY 1775

char 	ax25CurrBit; //the index of the current bit.
char* ax25DataPtr; //points to the current byte
int 	ax25ToneDelay; //ns delay between tone changes. 1775 for the space and 3255 for mark

const short SinusOutputData[SINUS_LENGTH] = {
        2047U,  2097U,  2147U,  2198U,  2248U,  2298U,  2347U,  2397U,  2446U,  2496U,  2544U,  2593U,  2641U,  2689U,
        2737U,  2784U,  2830U,  2877U,  2922U,  2967U,  3012U,  3056U,  3099U,  3142U,  3184U,  3226U,  3266U,  3306U,
        3346U,  3384U,  3422U,  3458U,  3494U,  3530U,  3564U,  3597U,  3629U,  3661U,  3691U,  3721U,  3749U,  3776U,
        3803U,  3828U,  3852U,  3875U,  3897U,  3918U,  3938U,  3957U,  3974U,  3991U,  4006U,  4020U,  4033U,  4044U,
        4055U,  4064U,  4072U,  4079U,  4084U,  4088U,  4092U,  4093U,  4094U,  4093U,  4092U,  4088U,  4084U,  4079U,
        4072U,  4064U,  4055U,  4044U,  4033U,  4020U,  4006U,  3991U,  3974U,  3957U,  3938U,  3918U,  3897U,  3875U,
        3852U,  3828U,  3803U,  3776U,  3749U,  3721U,  3691U,  3661U,  3629U,  3597U,  3564U,  3530U,  3494U,  3458U,
        3422U,  3384U,  3346U,  3306U,  3266U,  3226U,  3184U,  3142U,  3099U,  3056U,  3012U,  2967U,  2922U,  2877U,
        2830U,  2784U,  2737U,  2689U,  2641U,  2593U,  2544U,  2496U,  2446U,  2397U,  2347U,  2298U,  2248U,  2198U,
        2147U,  2097U,  2047U,  1997U,  1947U,  1896U,  1846U,  1796U,  1747U,  1697U,  1648U,  1598U,  1550U,  1501U,
        1453U,  1405U,  1357U,  1310U,  1264U,  1217U,  1172U,  1127U,  1082U,  1038U,  995U,   952U,   910U,   868U,
        828U,   788U,   748U,   710U,   672U,   636U,   600U,   564U,   530U,   497U,   465U,   433U,   403U,   373U,
        345U,   318U,   291U,   266U,   242U,   219U,   197U,   176U,   156U,   137U,   120U,   103U,   88U,    74U,
        61U,    50U,    39U,    30U,    22U,    15U,    10U,    6U,     2U,     1U,     0U,     1U,     2U,     6U,
        10U,    15U,    22U,    30U,    39U,    50U,    61U,    74U,    88U,    103U,   120U,   137U,   156U,   176U,
        197U,   219U,   242U,   266U,   291U,   318U,   345U,   373U,   403U,   433U,   465U,   497U,   530U,   564U,
        600U,   636U,   672U,   710U,   748U,   788U,   828U,   868U,   910U,   952U,   995U,   1038U,  1082U,  1127U,
        1172U,  1217U,  1264U,  1310U,  1357U,  1405U,  1453U,  1501U,  1550U,  1598U,  1648U,  1697U,  1747U,  1796U,
        1846U,  1896U,  1947U,  1997U
};


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
	while (*(data+len) > *ax25DataPtr){
		Error = DA1_SetValue(ax25DacPtr, SinusOutputData[sinIndex]);
		WAIT1_Waitns(ax25ToneDelay);
		sinIndex++;
		if (sinIndex > 256){
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
