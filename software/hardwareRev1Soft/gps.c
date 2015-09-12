#include "uart.h"
#include "gps.h"
#include "MKL26Z4.h"
GPSData gpsData;
#define NULL 0
int temp ;
int state;

char* gpsCurField;
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
	/*PCUARTInit();*/
	state = 0;
	temp = 0;
	gpsCurField = NULL;
	return 0;
}

char fmt[]=        "$GPRMC,t,s,a,A,o,O,k,c,d,Em,MCCCE";
char nmea_test[] = "$GPRMC,144140.00,A,1233.11671,N,12435.71394,W,0.128,,310815,,,A*6D";

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

		gpsCurField = (char*) &(gpsData.time);
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
				gpsCurField = (char*) &(gpsData.time);
				gpsTerm = 1;
				break;
			case 's':
				gpsCurField = (char*) &(gpsData.stat);
				gpsTerm = 0;
				break;
			case 'a':
				gpsCurField = (char*) &(gpsData.lat);
				gpsTerm = 1;
				break;
			case 'A':
				gpsCurField = (char*) &(gpsData.latHemi);
				gpsTerm = 0;
				break;
			case 'o':
				gpsCurField = (char*) &(gpsData.lon);
				gpsTerm = 1;
				break;
			case 'O':
				gpsCurField = (char*) &(gpsData.lonHemi);
				gpsTerm = 0;
				break;
			case 'k':
				gpsCurField = (char*) &(gpsData.speed);
				gpsTerm = 1;
				break;
			case 'c':
				gpsCurField = (char*) &(gpsData.course);
				gpsTerm = 1;
				break;
			case 'd':
				gpsCurField = (char*) &(gpsData.date);
				gpsTerm = 1;
				break;
			case 'E':
				//uartDisableRx();
				gpsCurField = (char*) NULL;
				gpsTerm = 0;
				state = 0;
				temp = 0;
			default:
				gpsCurField = (char*) NULL;
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



int testParse(){
	int i;
	i = 0;
	while (nmea_test[i] != 0){
		ParseGPS(nmea_test[i++]);
	}
}
