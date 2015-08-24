#include <MKL26Z4.h>
#include <stdint.h>
void dacInit(void){
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[30] = PORT_PCR_MUX(0);
	DAC0->DAT[0].DATH = 0;
	DAC0->DAT[0].DATL = 0;
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACTRGSEL_MASK;
}

void dacDeInit(void) {

}
void dacSet(uint16_t val){
	DAC0->DAT[0].DATL = (uint8_t) val & 0xFF;
	DAC0->DAT[0].DATH = (uint8_t) ( val >> 8);
}




