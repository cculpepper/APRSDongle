#include <MKL26Z4.h>
#include "PIT.h"
#include "uart2.h"
#include "gps.h"
#include "uart1.h"
#include "i2c.h"
#include <stdlib.h>
#include "gpio.h"
#include "delay.h"

extern uint32_t __heap_start[];
extern uint32_t __StackTop[];
extern uint32_t __data_start__[], __data_end__[];
extern uint32_t __bss_start__[], __bss_end__[];
extern uint32_t __etext[];                // End of code/flash


void toggle(){

	PTC->PTOR |= (1<<8);
}
void SystemInit(){
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

	//main();

}
void start(){
	//_start();
	//init_mempool();

}
int main(){
	int i;
	char c;
	
	char c2;
	char s[40];
	char s2[40];
	c = 0;
	start();
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTC->PCR[8] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PTC->PDDR |= (1 << 8);
	PTC->PDDR |= (1 << 9);
	LedPortInit();
	led4On();
	initUART1();
	for (;;){
delay(100);
		//c = 0;
		if (c & 0x08){
			led1On();
		} else led1Off();
		if (c & 0x04){
			PTC->PTOR |= (1<<9);
		} else led2Off();
		if (c & 0x02){
			PTC->PTOR |= (1<<10);
		} else led3Off();
		if (c & 0x01){
			PTC->PTOR |= (1<<11);
		} else led4Off();
		/*c++;*/
		//GPIOB_PTOR |= (1 << 18);
	}
	for (;;);
	
	
	
	startPITT0(toggle, 24000000);
	initUART2();
	i2c_init(intI2c);
	
	
	for (i = 0;i<40;i++){
		s[i] = 'A' + i;
	}
	s[40] = 0;

	for (;;){
		/*		uart2PutString("Enter a char to write: \r\n");
				uart2Wait();
				c = 0;
				while (c<'A'){
				c = uart2GetCharBlock();
				PTC->PTOR |= (1<<9);
				if (c!='f') c = 0; 
				}*/
		c = 'l';
		i2cFlashWrite(0, 40, (char*) &s);
		delay(1);
		i2cFlashRead(0, 40, (char*) &s2);
		uart2PutString("I wrote l ");
		uart2PutString(" and I read ");
		uart2PutChar(c2);
		uart2PutString("\r\n");
		//uart2Wait();
		for (i = 0;i<100000;i++){

			PTC->PDDR |= (1 << 8);
			PTC->PDDR |= (1 << 9);
			PTC->PDDR |= (1 << 10);
			PTC->PDDR |= (1 << 11);

		}
	}
	c = 0;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTC->PCR[8] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PTC->PDDR |= (1 << 8);
	PORTC->PCR[9] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PTC->PDDR |= (1 << 9);
	PORTC->PCR[10] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PTC->PDDR |= (1 << 10);
	PORTC->PCR[11] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 
	PORTE->PCR[31] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PTE->PDDR &= ~ (1 << 31);

	PTC->PDDR |= (1 << 11);
	PTC->PSOR |= (1<<8);
	PTC->PSOR |= (1<<9);
	PTC->PSOR |= (1<<10);
	PTC->PSOR |= (1<<11);
	startPITT0(toggle, 24000000);
	for (;;){
		if (PTE->PDIR & (1<<31)){
			PTC->PSOR |= (1<<9);
			PTC->PSOR |= (1<<10);
			PTC->PSOR |= (1<<11);
		} else {
			PTC->PCOR |= (1<<9);
			PTC->PCOR |= (1<<10);
			PTC->PCOR |= (1<<11);
		}
	}
	for (;;){
		for (i = 0;i<100000;i){

			PTC->PDDR |= (1 << 8);
			PTC->PDDR |= (1 << 9);
			PTC->PDDR |= (1 << 10);
			PTC->PDDR |= (1 << 11);

		}
		//c = 0;
		if (c & 0x08){
			PTC->PTOR |= (1<<8);
		} 
		if (c & 0x04){
			PTC->PTOR |= (1<<9);
		}
		if (c & 0x02){
			PTC->PTOR |= (1<<10);
		}
		if (c & 0x01){
			PTC->PTOR |= (1<<11);
		}
		c++;
		//GPIOB_PTOR |= (1 << 18);
	}
}
