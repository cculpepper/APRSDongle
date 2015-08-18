#include "uart.h"
#include "gps.h"

char updatePos(){
	 /* 
$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

Where:
     GGA          Global Positioning System Fix Data
     123519       Fix taken at 12:35:19 UTC
     4807.038,N   Latitude 48 deg 07.038' N
     01131.000,E  Longitude 11 deg 31.000' E
     1            Fix quality: 0 = invalid
                               1 = GPS fix (SPS)
                               2 = DGPS fix
                               3 = PPS fix
			       4 = Real Time Kinematic
			       5 = Float RTK
                               6 = estimated (dead reckoning) (2.3 feature)
			       7 = Manual input mode
			       8 = Simulation mode
     08           Number of satellites being tracked
     0.9          Horizontal dilution of position
     545.4,M      Altitude, Meters, above mean sea level
     46.9,M       Height of geoid (mean sea level) above WGS84
                      ellipsoid
     (empty field) time in seconds since last DGPS update
     (empty field) DGPS station ID number
     *47          the checksum data, always begins with **/ 
	char buf[80];
	char count;
	char SearchStr[] = "$GPGGA";
	int lcv;
	int index;
	count = 0;
	if (gpsStat >0){
		/*We need to init the gps.*/
		initGps();
	}
	gpsStat = -1;
	gpsLat[0] = 0x00;
	gpsAlt[0] = 0x00;
	gpsLon[0] = 0x00;
	GetString(buf);
	while (count++ > 0){
		GetString(buf);
		for (lcv=0;lcv<6;lcv++){
			if (buf[lcv] != SearchStr[lcv]){
				continue;
			}
		}
		 /* We probz have a nice string available. */ 
		lcv = 7;
		while(buf[lcv++] != ',');
		 /* I believe lcv should point to the start of the fix data. MAY BE OFF BY ONE!!!!!!*/ 
		index = 0;
		while(buf[lcv++] != ','){
			gpsLat[index++] = buf[lcv];
		}
		 /* Pointing at the comma.*/ 
		lcv++;
		gpsLat[index++] = buf[lcv++]; /* North or south*/ 
		gpsLat[index] = 0x00;  /* Null terminate*/ 
		index = 0;
		while(buf[lcv++] != ','){
			gpsLon[index++] = buf[lcv];
		}
		 /* Pointing at the comma.*/ 
		lcv++;
		gpsLon[index++] = buf[lcv++]; /* East or west*/ 
		gpsLon[index] = 0x00;
		if (buf[lcv++] == '0'){
			/* No fix*/ 
			gpsStat = -2;
			return -2;
		} else {
			gpsStat = 0;  /* Standard unixy codes*/ 
		}
		lcv += 7;  /* Pointing at the comma in front of the altitude*/ 
		index = 0;
		while (buf[++lcv] != ','){
			gpsAlt[index++] = buf[lcv];
		}
		gpsAlt[index] = 0x00;
		return 0;
	}
	gpsStat = -3;
	return -3;  /* Not good, cannot get a good recieve. */ 
}
char initGps(void){
	gpsStat = -1;  /* Not updated*/ 
	/*Need to select PTB4 as a rxd pin for uart0*/
	 /* Thats ALT3, 0x3*/ 
	PORTB_PCR4 = PORT_PCR_MUX(3) || PORT_PCR_ISF_MASK;
	/*PORTB_PCR1 = PORT_PCR_MUX(2); Dont need TX for gps*/
/* Also need to disable the rxd for the other pins. I think?*/ 
	/*Might as well initialize the UART too. */
	SIM_SOPT5 &= ~ SIM_SOPT5_UART0_EXTERN_MASK_CLEAR;
	SIM_SCGC4 |= SIM_SCGC4_UART0CGC_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTECGC_MASK;  /* THIS IS WRONG*/ 
	UART_BDH_REG = UART_BDH_38400;
	UART_BDL_REG = UART_BDL_38400;
	UART_C1_REG = UART_C1_8N1;
	UART_C3_REG = UART_C3_NO_TXINV;
	UART_C4_REG = UART_C4_NO_DMA;
	UART_S2_REG = UART_S2_NO_RXINV_BRK10_NO_LBKDETECT;
	UART_C2_REG = UART_C2_T_RI;
}

	



		
