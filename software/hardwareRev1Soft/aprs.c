#include "dra.h"
#include "gps.h"
#include "ax25.h"
int sendPos(){
	char str[100];
	int status ;
	status = initDRA();
	if (status) return 1;
	updateTxFreq("145.3900");
	status = programDra();
	if (status) return 2;
	strcpy((char*) str, "AB1TJ TESTING");
	draTx();
	ax25IntSend( (char*) str, 14);
	draRx();
}
	
	

