#pragma once
#ifndef GPS_H
#define GPS_H
char updatePos(void);
char initGps(void);


extern char gpsAlt[6];
extern char gpsLat[10];
extern char gpsLon[11];
extern signed char gpsStat;
void ParseGPS (char c);
#endif