#include "MKL26Z4.h"
#include "PIT.h"
#include "uart.h"
#include "gps.h"
#include "i2c.h"
#include <stdlib.h>
#include "gpio.h"
#include "delay.h"
#include "dra.h"
#include "aprs.h"
#include "cw.h"
#define inline __inline

//#include "ff.h"

int main(void);


extern uint32_t __heap_start[];
extern uint32_t __StackTop[];
extern uint32_t __data_start__[], __data_end__[];
extern uint32_t __bss_start__[], __bss_end__[];
extern uint32_t __etext[];                // End of code/flash
//FATFS FatFs;
//FIL Fil;

void clockInit(){

	// Time to play with clocks. 
	// Starting off in FEI mode. Need to switch to FBE
	// Set bits in C2. 
	SIM->SOPT1 = 0;
	OSC0->CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;
	MCG->C2 = 0x14;
	// Clear C1[IREF], Switch to external reference
	// MCG->C1 = 0x98; // This is wrong. Need to divide by 256 instead of 128
	// C1[CLKS] to 01
	MCG->C1 = 0x9A;
	//Wait for S[IREFST] to clear and S[CLKST] to change to 10. 
	// Wait for S[OSCINT0], S[IREFST] to be 0, S[CLKST] is 10
	while ((~MCG->S & MCG_S_OSCINIT0_MASK));
	while ((MCG->S & MCG_S_IREFST_MASK));
	while ((~MCG->S & 0x0A));
	// Set C5[PRDIV] to get 2MHz
	MCG->C5 = 0x03;

	// Now transisition to PBE. 
	MCG->C6 = 0x40;
	//loop until S[PLLST] and S[LOCK0]
	while ((~MCG->S & MCG_S_PLLST_MASK));
	while ((~MCG->S & MCG_S_LOCK0_MASK));
	MCG->C1 = 0x10;
	//Loop until S[CLKST] is 11
	while ((~MCG->S & 0x0C));
	SIM->CLKDIV1 = 1 << SIM_CLKDIV1_OUTDIV4_SHIFT; // Divide the core clock by two for the bus clock. 

}
void SystemInit(){
//	PTC->PCOR = 0xf00;
//	main();

}
void start(){
	//_start();
	//init_mempool();
	SIM->COPC = 0; // Disable the COP
	clockInit();
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTC->PCR[8] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PTC->PDDR |= (1 << 8);
	PTC->PDDR |= (1 << 9);
	LedPortInit();
	//led4On();
	initGps();
	testParse();
	initUART1();
	
	i2c_init(intI2c);
//	initUART2();
//	if (f_mount(0,&FatFs)){
//		uart2PutString("Failure to mount the FAT filesystem.");
//	}
}
int main(){

	uint32_t bw;
	
	//delay(10000);
	
	start();
	initDRA();
	draRx();
	checkDRA();
	programDra();
	delay(10000);
	for (;;){
		//PTC->PCOR = 0xf00;
		//draTx();
		draTx();
		delay(500);
		cwSend("AB1TJ", 5);
		
		delay(100);
		cwSend("LAT",3);
		delay(200);
		cwSend(gpsData.lat, 10);
		delay(1000);
		cwSend("LON",3);
		delay(200);
		cwSend(gpsData.lon, 11);
		delay(200);
		sendPos();
		
		delay(200);
		draRx();
		getPos();
		
		delay(40000);draTx();
		delay(500);
		cwSend("AB1TJ", 5);
		
		delay(100);
		sendPos();
		
		delay(200);
		draRx();
		delay(50000);
		
	}
}
