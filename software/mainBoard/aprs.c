#include "dra.h"
#include "gps.h"
#include "ax25.h"
int sendPos(){
	char str[100];
	int status ;
	//status = initDRA();
	//if (status) return 1;
	//updateTxFreq("146.3900");
	//status = programDra();
	//if (status) return 2;
	//draTx();
	ax25IntSend("AB1TJ TESTING Lat: ", 12);
	ax25IntSend(gpsData.lat, 6);
	ax25IntSend(", lon: ", 7);
	//ax25IntSend("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 200);
	ax25IntSend(gpsData.lon, 6);
	//draRx();
}
	
	

