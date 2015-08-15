/*
* Hackaday.com AVR Tutorial firmware
* written by: Mike Szczys (@szczys)
* 10/24/2010
*
* ATmega168
* Blinks one LED conneced to PD0
*
* http://hackaday.com/2010/10/25/avr-programming-02-the-hardware/
*/
#define __AVR_ATtiny84A__

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "usitwislave.h"

#include <util/delay.h>
#include "cw.h"


volatile uint8_t *i2cOutBuf;
volatile const uint8_t *i2cInBuf;
volatile uint8_t *i2cInLen;
volatile uint8_t *i2cOutLen;
char v[2];
char cur[2];
char temp[2];



void twi_callback(volatile uint8_t *input_buffer_length, 
		volatile const uint8_t *input_buffer, volatile uint8_t *output_buffer_length, 
		volatile uint8_t *output_buffer) {
	/*PORTB ^= (1<<2);        //Use xor to toggle the LED*/
	i2cOutLen = output_buffer_length;
	i2cOutBuf = output_buffer;
	i2cInLen = input_buffer_length;
	i2cInBuf = input_buffer;
			switch (*i2cInBuf){
				case (1):
					{
						break;
					}
				case (2):
					{
						// Voltage request. 
						i2cOutBuf[0] = v[0]++;
						i2cOutBuf[1] = v[1]++;
						*i2cOutLen = 2;
						break;
					}
				case (3):
					{
						i2cOutBuf[0] = cur[0];
						i2cOutBuf[1] = cur[1];
						*i2cOutLen = 2;
						break;
					}
				case (4):
					{
						i2cOutBuf[0] = temp[0];
						i2cOutBuf[1] = temp[1];
						*i2cOutLen = 2;
						break;
					}
			}
}




void adcVinInit(void){
	// For right now, will set up for single ended, battery voltage measurement. 
	//
	PRR &= ~(1 << PRADC);
	ADCSRA &= ~(1 << ADEN);
	ADMUX = 0;

	ADCSRB = (1 << ADLAR) ;
	ADCSRA = (0x6) | (1 << ADEN);
}
int measVin(void) {
	int temp;
	while ( ADCSRA & (1 << ADSC));
	adcVinInit();
	ADCSRA |= (1 << ADSC);
	while ( ADCSRA & (1 << ADSC));
	/*v[0] = ADCH;*/
	/*v[1] = ADCL;*/
	if (v[0] == 0x00){
		PORTB ^= (1<<2);        //Use xor to toggle the LED
	}
}

void adcCurInit(void){
	// For right now, will set up for single ended, battery voltage measurement. 
	// PA1 is pos
	// PA2 is neg
	//
	PRR &= ~(1 << PRADC);
	ADCSRA &= ~(1 << ADEN);
	ADMUX = 0x0d;

	ADCSRB = (1 << ADLAR) ;
	ADCSRA = (0x6) | (1 << ADEN);
}
int measCur(void) {
	int temp;
	while ( ADCSRA & (1 << ADSC));
	adcCurInit();
	ADCSRA |= (1 << ADSC);
	while ( ADCSRA & (1 << ADSC));
	cur[0] = ADCH;
	cur[1] = ADCL;
}


int main(void)
{

	int i;
	/*for (i=0;i<7;i++){*/
	/*DDRB |= (1<<i);     //Set PortD Pin0 as an output*/
	/*DDRA |= (1<<i);     //Set PortD Pin0 as an output*/
	/*PORTB |= (1<<i);        //Set PortD Pin0 high to turn on LED*/
	/*PORTA |= (1<<i);        //Set PortD Pin0 high to turn on LED*/
	/*}*/
	DDRB |= (1<<2) | 1;
	DDRA |= (1<<7);
	measCur();
	measVin();	
	// Set PTB0 to 0 to enable power save. 
	/*PORTB &= ~(1<<0);*/
	cwSend("AB1TJ", 5);

	/*PORTB ^= (1<<2);*/
	//Setup the clock
	TCCR1B |= (1 << WGM12) | 1<<CS11 | 1<<CS10;  //Divide by 64
	OCR1A = 5000;        //Count 15624 cycles for 1 second interrupt
	/*OCR1A = 15624;        //Count 15624 cycles for 1 second interrupt*/
	TIMSK1 |= 1<<OCIE1A;        //enable timer compare interrupt
	sei();            //Enable global interrupts

	usi_twi_slave(0x68, 1, twi_callback, 0);

	cwSend("AB1TJ", 5);
	for(;;){
		if (*i2cInLen){

		}
	}
}

ISR (TIM1_COMPA_vect)      //Interrupt Service Routine
{
	PORTA ^= (1<<7);        //Use xor to toggle the LED
	measCur();
	measVin();	
}
