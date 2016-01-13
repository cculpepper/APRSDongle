/*
* Rochester Institute of Technology
* Department of Computer Engineering
*  CMPE 460  Interfacing Digital Electronics
Spring 2015

*
*
* Filename: main.c
*/
#ifndef ADC_H
#define ADC_H
#include "common.h"

void ADC0_INIT(void) ;

// ADC0 Conversion Complete ISR
void ADC0_IRQHandler(void) ;
#define ADC_NUM_SOURCES 8
const extern uint8_t ADCSourceBytes[ADC_NUM_SOURCES];
volatile extern int ADCResultIndex;
volatile extern int16_t ADC0Results[ADC_NUM_SOURCES];
volatile extern int ADCResultDirty;

/* ADC pin assignments:
 * PTA8 Switch Voltage 		ADC0_SE3, 0x03
 * PTA9 Battery Voltage 	ADC0_SE2, 0x02
 * PTA12 Main current2 		ADC0_SE0, 0x00
 * PTA0 External Temp 		ADC0_SE15,0x0F
 * PTB5 Input Voltage 		ADC0_SE1, 0x01
 * PTB1 Or current2 , switch current ADC0_SE8, 0x08
 * PTB0 OR current 1, batter current ADC0_SE9, 0x09
 * internal Temp 		0x1A
 * 
 */
#define SCswitchV 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(3)
#define SCbatteryV 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(2)
#define SCmainI 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0)
#define SCexternT 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(15)
#define SCinputV 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(1)
#define SCswitchI 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(8)
#define SCbatI 		ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(9)
#define SCinternT 	ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(26)
#define MULTSWITCHV 	

#define resswitchV 	0
#define resbatteryV 	1
#define resmainI 	2
#define resexternT 	3
#define resinputV 	4
#define resswitchI 	5
#define resbatI 	6
#define resinternT 	7

#endif
