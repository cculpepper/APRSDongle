#ifndef gpio_h
#define gpio_h


#define LedPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; LedDirInit(); PORTC->PCR[8] = PORT_PCR_MUX(1) ; PORTC->PCR[9] = PORT_PCR_MUX(1) ; PORTC->PCR[10] = PORT_PCR_MUX(1) ; PORTC->PCR[11] = PORT_PCR_MUX(1) ; 
//#define LedPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; LedDirInit(); PORTC->PCR[8] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[9] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[10] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; PORTC->PCR[11] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 

#define LedDirInit() PTB->PDDR |= LED1 | LED2 
#define SwPortInit() SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK
#define LED1 (1<<6) // PTB6
#define LED2 (1<<7) // PTB7
#define IRQ  (1<<13) // PTB13
#define ORENABLE1 (1<<11) // PTB11, Switching supply
#define ORENABLE2 (1<<10) // PTB10, Battery


#define ORWARN1 (1<<3) // PTA3
#define ORWARN2 (1<<4) // PTA4
#define CHARGE  (1<<5) // PTA5
#define CHARGERSHUTDOWN  (1<<6) // PTA6
#define CHARGERFAULT  (1<<7) // PTA7

#define INPUT
#define SWF (1<<1)
#define SWB (1<<31)
#define initSWF() PORTE->PCR[31] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
#define initSWb() PORTE->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
#define led1On() PTA->PSOR = LED1
#define led1Off() PTA->PCOR =  LED1
#define led1Toggle() PTA->PTOR =  LED1

#define led2On() PTC->PSOR = LED2
#define led2Off() PTC->PCOR =  LED2
#define led2Toggle() PTC->PTOR =  LED2

#define led3On() PTC->PSOR = LED3
#define led3Off() PTC->PCOR =  LED3
#define led3Toggle() PTC->PTOR =  LED3

#define led4On() PTC->PSOR = LED4
#define led4Off() PTC->PCOR =  LED4
#define led4Toggle() PTC->PTOR =  LED4

#define ledData(x) PTC->PDO |= (x<<7) | (PTC->PDO & ~ (0xF << 7))

#define getSwF() PTE->PDIR & SWF
#define getSwB() PTE->PDIR & SWB
#endif


