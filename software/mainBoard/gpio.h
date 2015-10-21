#ifndef gpio_h
#define gpio_h


#define LedPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; LedDirInit(); PORTC->PCR[8] = PORT_PCR_MUX(1) ; PORTC->PCR[9] = PORT_PCR_MUX(1) ; PORTC->PCR[10] = PORT_PCR_MUX(1) ; PORTC->PCR[11] = PORT_PCR_MUX(1) ; 
//#define LedPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; LedDirInit(); PORTC->PCR[8] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[9] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[10] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[11] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 

#define LedDirInit() PTC->PDDR |= LED1 | LED2 | LED3 | LED4
#define SwPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK
#define LED1 (1<<8)
#define LED2 (1<<9)
#define LED3 (1<<10)
#define LED4 (1<<11)
#define SWF (1<<1)
#define SWB (1<<31)
#define initSWF() PORTE->PCR[31] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
#define initSWb() PORTE->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
#define led1On() PTC->PSOR = LED1
#define led1Off() PTC->PCOR =  LED1
#define led1Toggle() PTC->PTOR =  LED1

#define led2On() PTC->PSOR = LED2
#define led2Off() PTC->PCOR =  LED2
#define led2Toggle() PTC->PTOR =  LED2

#define led3On() PTC->PSOR = LED3
#define led3Off() PTC->PCOR =  LED3
#define led3Toggle() PTC->PTOR =  LED3

#define led4On() PTC->PSOR = LED4
#define led4Off() PTC->PCOR =  LED4
#define led4Toggle() PTC->PTOR =  LED4

/*#define led1On() PTC->PSOR = LED1*/
/*#define led1Off() PTC->PCOR =  LED1*/
/*#define led1Toggle() PTC->PTOR =  LED1*/

/*#define led2On() PTC->PSOR = LED2*/
/*#define led2Off() PTC->PCOR =  LED2*/
/*#define led2Toggle() PTC->PTOR =  LED2*/

#define gpsLedOn() PTC->PSOR = LED3
#define gpsLedOff() PTC->PCOR =  LED3
#define gpsLedToggle() PTC->PTOR =  LED3

#define txLedOn() PTC->PSOR = LED4
#define txLedOff() PTC->PCOR =  LED4
#define txLedToggle() PTC->PTOR =  LED4

#define ledData(x) PTC->PDO |= (x<<7) | (PTC->PDO & ~ (0xF << 7))

#define getSwF() PTE->PDIR & SWF
#define getSwB() PTE->PDIR & SWB
#endif


