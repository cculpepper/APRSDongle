#include <stdint.h>
#include "MKL26Z4.h"
#include "PIT.h"


PITDataStruct PITData;
void startPIT0(void  (*T0ISR)(void), int ldVal){
	PITData.T0ISR = T0ISR;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;  /* Enable the PIT clock */
	PIT->MCR =  0x00; //PIT_MCR_FRZ_MASK; [> Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. <] */
	PIT->CHANNEL[0].LDVAL = ldVal;   //[> One second, for testing purpeses.  <] */
	PIT->CHANNEL[0].TFLG = 0x00000001; //[> clear the interrupt if one is pending.  <] <]*/
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	/*[>PIT_TCTRL0 = 0xC0000000;<]*/
	/*[>PIT_TCTRL0 |= PIT_TEN;<]*/
	/*enable_irq(INT_PIT - 16);*/
	NVIC_EnableIRQ(PIT_IRQn);
	__enable_irq();
}
void startPIT1(void  (*T1ISR)(void), int ldVal){
	PITData.T1ISR = T1ISR;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;  /* Enable the PIT clock */
	PIT->MCR =  0x00; //PIT_MCR_FRZ_MASK; [> Enables the timer and allows the timer to stop in debug mode? Disables timer in debug. <] */
	PIT->CHANNEL[1].LDVAL = ldVal;   //[> One second, for testing purpeses.  <] */
	PIT->CHANNEL[1].TFLG = 0x00000001; //[> clear the interrupt if one is pending.  <] <]*/
	PIT->CHANNEL[1].TCTRL = PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	/*[>PIT_TCTRL0 = 0xC0000000;<]*/
	/*[>PIT_TCTRL0 |= PIT_TEN;<]*/
	/*enable_irq(INT_PIT - 16);*/
	NVIC_EnableIRQ(PIT_IRQn);
	__enable_irq();
}

void stopPIT0(void){
	PIT->CHANNEL[0].TCTRL = 0;
	//NVIC_DisableIRQ(PIT_IRQn);
}
void stopPIT1(void){
	PIT->CHANNEL[1].TCTRL = 0;
	//NVIC_DisableIRQ(PIT_IRQn);
}
void PIT_IRQHandler(void){

	__disable_irq();
	if (PIT->CHANNEL[0].TFLG){
		PIT->CHANNEL[0].TFLG = 1;
		PITData.T0ISR();
	}
	if (PIT->CHANNEL[1].TFLG){
		PIT->CHANNEL[1].TFLG = 1;
		PITData.T1ISR();
	}
	__enable_irq();
}
