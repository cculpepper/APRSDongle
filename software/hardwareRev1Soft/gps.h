#ifndef GPS_H
#define GPS_H
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

char initGps();


char updatePos();

extern GPSData gpsData;

void ParseGPS(char c);


volatile unsigned int Time, Msecs, Knots, Course, Date;
volatile long Lat, Long;
volatile char Fix;
int testParse();




#endif
		
