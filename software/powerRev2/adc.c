/*
 * Rochester Institute of Technology
 * Department of Computer Engineering
 *  CMPE 460  Interfacing Digital Electronics
 Spring 2015

 *
 *
 * Filename: main.c
 */

#include "common.h"
#include "adc.h"

const uint8_t ADCSourceBytes[ADC_NUM_SOURCES] = {SCswitchV, SCbatteryV, SCmainI, SCexternT, SCinputV, SCswitchI, SCbatI, SCinternT};
const float ADCConversionMult[ADC_NUM_SOURCES];// = {};
volatile int16_t ADCResults[ADC_NUM_SOURCES];
volatile int ADCResultIndex;
volatile int ADCResultDirty;
void VREF_init(void){
	SIM->SCGC4 |= SIM_SCGC4_VREF_MASK;
	VREF->SC = VREF_SC_VREFEN_MASK | VREF_SC_REGEN_MASK | VREF_SC_MODE_LV(2);
}
void ADC0_INIT(void) {
	unsigned int calib;
	VREF_init();
	// This should work. I hope....

	// Turn on ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADCResultDirty = 1;

	ADCResultIndex = 0;
	/* Uses the Bus clock. */ 
	// Configure CFG Registers
	// Configure ADC to divide 24 MHz down to 3 MHz AD Clock, 12-bit single ended
	//adiv3 is divide by 8, cfgmode1 is 12 bits. 
	ADC0->CFG1 = ADC_CFG1_ADIV(3) | ADC_CFG1_MODE(1);


	// Do ADC Calibration for Singled Ended ADC. Do not touch.
	// I configured for 32 samples. Will waste a shittone of cycles. But 
	// Sholud remove the noise on inputs. 
	ADC0_SC3 = ADC_SC3_CAL_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
	while ( (ADC0_SC3 & ADC_SC3_CAL_MASK) != 0 );
	calib = ADC0_CLP0;
	calib += ADC0_CLP1;
	calib += ADC0_CLP2;
	calib += ADC0_CLP3;
	calib += ADC0_CLP4;
	calib += ADC0_CLPS;
	calib = calib >> 1;
	calib |= 0x8000;
	ADC0_PG = calib;

	// Configure SC registers.
	// Select hardware trigger.
	//ADC0->SC2 |= ADC_SC2_ADTRG_MASK;



	// Configure SC1A register.
	// Select ADC Channel and enable interrupts. Use ADC0 channel DAD3  in single ended mode.
	//(Insert your code here.)

	ADCResultIndex = 0;

	ADC0_SC1A = ADCSourceBytes[ADCResultIndex];
	// Enable NVIC interrupt
	NVIC_EnableIRQ(ADC0_IRQn);//ADC0 Interrupt
	__enable_irq();
}

// ADC0 Conversion Complete ISR
void ADC0_IRQHandler(void) {
	// Read the result (upper 12-bits). This also clears the Conversion complete flag.
	__disable_irq();
	ADCResultDirty = 1;
	if (ADCResultIndex > ADC_NUM_SOURCES || ADCResultIndex < 0){
		ADCResultIndex = 0;
		ADC0_SC1A = ADCSourceBytes[ADCResultIndex];
		return;
	}
		ADCResults[ADCResultIndex++] = ADC0_RA;
		ADC0_SC1A = ADCSourceBytes[ADCResultIndex];
		__enable_irq();
		if (ADCResultIndex == ADC_NUM_SOURCES){
			ADCResultIndex = 0;
			// Disable the module. 
			ADC0_SC1A = ADC_SC1_ADCH(31);
			ADCResultDirty = 0;
			// Let the thingy know that the results are good to go. 
		}
}

