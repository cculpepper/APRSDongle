#include <MKL26Z4.h>
void SystemInit(){}
int main(){
	int i;
	char c;
	c = 0;
	  SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
  PORTC->PCR[8] = PORT_PCR_MUX(1); 
  PTC->PDDR |= (1 << 8);
  PORTC->PCR[9] = PORT_PCR_MUX(1); 
  PTC->PDDR |= (1 << 9);
  PORTC->PCR[10] = PORT_PCR_MUX(1); 
  PTC->PDDR |= (1 << 10);
  PORTC->PCR[11] = PORT_PCR_MUX(1); 
  PTC->PDDR |= (1 << 11);


	for (;;){
		for (i = 0;i<100000;i++){
			
  PTC->PDDR |= (1 << 8);
	PTC->PDDR |= (1 << 9);
			PTC->PDDR |= (1 << 10);
			PTC->PDDR |= (1 << 11);
			
		}
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
