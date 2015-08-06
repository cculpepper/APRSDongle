#include "uart1.h"
#include "gpio.h"
#include "gps.h"
char gpsAlt[6];
char gpsLat[10];
char gpsLon[11];
signed char gpsStat;

// Example: $GPRMC,194509.000,A,4042.6142,N,07400.4168,W,2.03,221.11,160412,,,A*77
char fmt[]="$GPRMC,dddtdd.ddm,A,eeae.eeee,l,eeeae.eeee,o,djdk,ddd.dc,dddy??,,,?*??";

int state = 0;
unsigned int temp;
long ltmp;

// GPS variables
volatile unsigned int Time, Msecs, Knots, Course, Date;
volatile long Lat, Long;
volatile char Fix;

void ParseGPS (char c) {
	char d;
	char mode;
  if (c == '$') { state = 0; temp = 0; }
  mode = fmt[state++];
  // If received character matches format string, or format is '?' - return
  if ((mode == c) || (mode == '?')) return;
  // d=decimal digit
  d = c - '0';
  if (mode == 'd') temp = temp*10 + d;
  // e=long decimal digit
  else if (mode == 'e') ltmp = ltmp*10 + d;
  // a=angular measure
  else if (mode == 'a') ltmp = ltmp*6 + d;
  // t=Time - hhmm
  else if (mode == 't') { Time = temp*10 + d; temp = 0; }
  // m=Millisecs
  else if (mode == 'm') { Msecs = temp*10 + d; ltmp=0; }
  // l=Latitude - in minutes*1000
  else if (mode == 'l') { if (c == 'N') Lat = ltmp; else Lat = -ltmp; ltmp = 0; }
  // o=Longitude - in minutes*1000
  else if (mode == 'o') { if (c == 'E') Long = ltmp; else Long = -ltmp; temp = 0; }
   // j/k=Speed - in knots*100
  else if (mode == 'j') { if (c != '.') { temp = temp*10 + d; state--; } }
  else if (mode == 'k') { Knots = temp*10 + d; temp = 0; }
  // c=Course (Track) - in degrees*100
  else if (mode == 'c') { Course = temp*10 + d; temp = 0; }
  // y=Date - ddmm
  else if (mode == 'y') { Date = temp*10 + d ; Fix = 1; }
  else state = 0;
	led4Toggle();
}
char updatePos(){	 /* 
signed char gpsStat;$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

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
	/*uart1GetString(buf, 80);*/
	while (count++ > 0){
		/*uart1GetString(buf, 800);*/
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
	initUART1();
}

	



		
