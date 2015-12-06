#include "dra.h"
#include "gps.h"
#include "ax25.h"

int astringCpy(char* dst, char* src){
	int i;
	i = 0;
	do {
		dst[i] = src[i];
	} while (src[i++]!= 0);
	return i;
}
int sendPos(){
	char str[100];
	int status ;
	int i;
	int j;
	char* strPtr;
	//status = initDRA();
	//if (status) return 1;
	//updateTxFreq("146.3900");
	//status = programDra();
	//if (status) return 2;
	//draTx();
	i = astringCpy((char*) str, "AB1TJ-1>APRS,WIDE1-1,\x03,\xf0,");
	i--;
	j+= i;
	strPtr = (str + i);
	i = astringCpy(strPtr, gpsData.time);
	i--;
	j+= i;
	strPtr = (str + i);
	*strPtr = 'h';
	strPtr++;
	i = astringCpy(strPtr, gpsData.lat);
	i--;
	j+= i;
	strPtr = (str + i);
	*strPtr = 'N';
	strPtr++;
	j+= i;
	i = astringCpy(strPtr, gpsData.lon);
	i--;
	j+= i;
	strPtr = (str + i);
	*strPtr = 'W';
	strPtr++;
	j+= 3;
	i = strPtr - str;
	
	
	ax25IntSend(str, j);
	delay(300);
	ax25IntSend("AB1TJ-1>APRS,WIDE1-1\x03\xf0,TESTING TESTING TESTING TESTING", 61);
	//draRx();
}
	
	

