#ifndef GPS_H
#define GPS_H

#define gpsUARTEnableInterrupts() uart1EnableInterrupts()
#define gpsUARTDisableInterrupts() uart1DisableInterrupts()
typedef struct{
	char time[11];
	char stat;
	char lat[11];
	char latHemi;
	char lon[12];
	char lonHemi;
	char speed[6];
	char course[6];
	char date[7];
}GPSData;

char initGps(void);


char updatePos(void);

extern GPSData gpsData;

void ParseGPS(char c);


int testParse(void);




#endif
		
