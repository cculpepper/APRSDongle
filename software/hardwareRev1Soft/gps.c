#include "uart.h"
#include "gps.h"
#include "LED1.h"
#include "msp430.h"
GPSData gpsData;
int strInStr(char *big, char *little)
{
	int bi, li;
	bi = 0;
	li = 0;
	while (big[bi] != 0) {
		if (big[bi] == little[li]) {
			bi++;
			li++;
			if (little[li] == 0) {
				return 1;
			}
		} else if (li != 0) {
			// Then we need to reset the big index to the one after the first char was found.
			// big: ',.pyffgcrl/= little: fgcr
			//           fgcr li=1 != bi
			//            fgcr
			bi -= (li - 1);
			li = 0;
		} else {
			bi++;
		}
	}
	return 0;
}

char updatePos()
{
	/* 
	   $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A

	   Where:
	   RMC          Recommended Minimum sentence C
	   123519       Fix taken at 12:35:19 UTC
	   A            Status A=active or V=Void.
	   4807.038,N   Latitude 48 deg 07.038' N
	   01131.000,E  Longitude 11 deg 31.000' E
	   022.4        Speed over the ground in knots
	   084.4        Track angle in degrees True
	   230394       Date - 23rd of March 1994
	   003.1,W      Magnetic Variation
	   *6A          The checksum data, always begins with *        

	 */
	char buf[80];
	char SearchStr[] = "$GPRMC";
	int index, index2, retryCount, found;
	index = 0;
	found = 0;
	index2 = 0;
	retryCount = 0;
	getString(buf, 80);
	getString(buf, 80);
	// The second one is to ensure that we have a complete string
#define MAXRETRIES 5
	while (retryCount < MAXRETRIES) {
		if (strInStr(buf, SearchStr)) {
			found = 1;
			break;
		} else {
			getString(buf, 80);
			retryCount++;
			continue;
		}
	}
	if (found == 0) {
		return 1;
	}
	// Buf contains the string were looking for. 
	while (buf[index] != ',') {
		index++;
	}
	//Points to the comma now. 
	//
	index++;
	//Points to the start of the time feild. 
	if (buf[index] != ',') {
		//GPS module doesnt fill in fields so you get ,,,,,,,,,,n,,,,..... Which makes it hard to parse.
		while (buf[index] != ',') {
			gpsData.time[index2++] = buf[index++];
		}
		gpsData.time[index2] = 0;
		// we leave the index pointing at the start of the status section. 
		index++;
	} else {
		index++;
		// this should leave the index pointing at the status.
	}
	gpsData.stat = buf[index];
	if (buf[index] != 'A') {
		return 2;
	}
	index += 2;
	// Should now be yointing at the start ef the latitude of a valid string. 
	index2 = 0;
	while (buf[index] != ',') {
		gpsData.lat[index2++] = buf[index++];
	}			// leaving off with the pointer at the comma at the end of the latitude. 
	index += 1;
	gpsData.lat[index2++] = buf[index++];
	// The north indicator. 
	index++;
	// Should now be yointing at the start ef the longitude of a valid string. 
	index2 = 0;
	while (buf[index] != ',') {
		gpsData.lon[index2++] = buf[index++];
	}			// leaving off with the pointer at the comma at the end of the longitude. 
	index++;
	gpsData.lon[index2++] = buf[index++];
	// The east indicator. 
	index++;
	// Meh. Dont feel like implementing the rest...

	return 0;
}

char initGps(void)
{
	/*Need to select PTB4 as a rxd pin for uart0
	   /* Thats ALT3, 0x3
	   PORTB_PCR4 = PORT_PCR_MUX(3) || PORT_PCR_ISF_MASK;
	   /*PORTB_PCR1 = PORT_PCR_MUX(2); Dont need TX for gp
	   /* Also need to disable the rxd for the other pins. I think?
	   /*Might as well initialize the UART too.
	   SIM_SOPT5 &= ~ SIM_SOPT5_UART0_EXTERN_MASK_CLEAR;
	   SIM_SCGC4 |= SIM_SCGC4_UART0CGC_MASK;
	   SIM_SCGC5 |= SIM_SCGC5_PORTECGC_MASK;  /* THIS IS WRONG*
	   UART_BDH_REG = UART_BDH_38400;
	   UART_BDL_REG = UART_BDL_38400;
	   UART_C1_REG = UART_C1_8N1;
	   UART_C3_REG = UART_C3_NO_TXINV;
	   UART_C4_REG = UART_C4_NO_DMA;
	   UART_S2_REG = UART_S2_NO_RXINV_BRK10_NO_LBKDETECT;
	   UART_C2_REG = UART_C2_T_RI; */
	PCUARTInit();
	return 0;
}

//char fmt[]=        "$GPRMC,tttttt,s,aaaaaaaa,A,ooooooooo,O,kkkkk,ccccc,dddddd,mmmmm,MCCCE";
// t: time
// s: status
// a: latitude
// A: Latitude (N or S)
// o: longitude 
// O: Longitude (E or W)
// k: speed in knots
// c: Course made good
// d: date
// m: Magnetic deviation
// M: Magnetic deviation ( E or W)
// C: checksum. 
//Example: "$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68";
#if 0
void ParseGPSOld(char c){
	char pos;
	if (state <=6 && c != fmt[state]) {
		state = 0;
		temp = 0;
		return;
	}
	if (state <= 6){

		state++;
		return;
	}

	//We are now processing data.
	pos = fmt[state++];
	if (c == ',' && pos != ','){
		// Testing the case when we have empty data.
		state = 0;
		return;
	}
	switch ( pos ){
	case ',':
		temp = 0;
		if (c != ','){
			state = 0; // The data didnt match.
		}
		break;
	case 't':
		// Then were filling in the time array.
		gpsData.time[temp++] = c;
		break;
	case 's':
		gpsData.stat = c;
		break;
	case 'a':
		// Latitude
		gpsData.lat[temp++] = c;
		break;
	case 'A':
		gpsData.latHemi = c;
		break;
	case 'o':
		gpsData.lon[temp++] = c;
		break;
	case 'O':
		gpsData.lonHemi = c;
		break;
	case 'k':
		gpsData.speed[temp++] = c;
		break;
	case 'c':
		gpsData.course[temp++] = c;
		break;
	case 'd':
		gpsData.date[temp++] = c;
		break;
	case 'E':
		state = 0;
		temp = 0;
		break;
	default:
		break;
	}
	return;
}
#endif
char fmt[]=        "$GPRMC,t,s,a,A,o,O,k,c,d,Em,MCCCE";
char nmea_test[] = "$GPRMC,144140.00,A,1233.11671,N,12435.71394,W,0.128,,310815,,,A*6D";
#define NULL 0
int temp = 0;
int state = 0;
char* gpsCurField = NULL;
char gpsTerm;
void ParseGPS(char c){
	char pos;
	if (state <=6 && c != fmt[state]) {
		state = 0;
		temp = 0;
		return;
	}
	if (state < 6){
		state++;
		return;
	} else if (state == 6 && c == ','){
		state++;
		temp = 0;

		gpsCurField = &(gpsData.time);
		gpsTerm = 0;
		return;
	}
	if (c == ','){
		// At the end of a field.
		// Terminate the string
		state++;
		if (fmt[state] == ','){
			state++;
			if (gpsTerm){
				gpsCurField[temp] = 0;
			}
			temp = 0;
			switch(fmt[state]){
			case 't':
				gpsCurField = &(gpsData.time);
				gpsTerm = 1;
				break;
			case 's':
				gpsCurField = &(gpsData.stat);
				gpsTerm = 0;
				break;
			case 'a':
				gpsCurField = &(gpsData.lat);
				gpsTerm = 1;
				break;
			case 'A':
				gpsCurField = &(gpsData.latHemi);
				gpsTerm = 0;
				break;
			case 'o':
				gpsCurField = &(gpsData.lon);
				gpsTerm = 1;
				break;
			case 'O':
				gpsCurField = &(gpsData.lonHemi);
				gpsTerm = 0;
				break;
			case 'k':
				gpsCurField = &(gpsData.speed);
				gpsTerm = 1;
				break;
			case 'c':
				gpsCurField = &(gpsData.course);
				gpsTerm = 1;
				break;
			case 'd':
				gpsCurField = &(gpsData.date);
				gpsTerm = 1;
				break;
			case 'E':
				uartDisableRx();
				gpsCurField = NULL;
				gpsTerm = 0;
				state = 0;
				temp = 0;
			default:
				gpsCurField = NULL;
				gpsTerm = 0;
				break;
			}// switch.
		} else{
			// Then we have two chars in a row. Probably bad.
			state = 0;
			temp = 0;
		}
	} else {
		// Then we have a character.
		if (gpsCurField != NULL){
			gpsCurField[temp++] = c;
		}
	}
}




#if 0
void gpsTerm(){
	gpsData.time[6] = 0;
	gpsData.lat[8] = 0;
	gpsData.lon[9] = 0;
	gpsData.speed[5] = 0;
	gpsData.course[5] = 0;
	gpsData.date[7] = 0;
}
#endif
int testParse(){
	int i;
	i = 0;
	while (nmea_test[i] != 0){
		ParseGPS(nmea_test[i++]);
	}
}
