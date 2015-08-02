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

#include <util/delay.h>
#include "cw.h"
 
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
	temp = (ADCH << 2) | (ADCL >> 6);
	return temp;
}

void adcCurInit(void){
	// For right now, will set up for single ended, battery voltage measurement. 
	// PA1 is pos
	// PA2 is neg
	//
	PRR &= ~(1 << PRADC);
	ADCSRA &= ~(1 << ADEN);
	ADMUX = 0x5d;

	ADCSRB = (1 << ADLAR) ;
	ADCSRA = (0x6) | (1 << ADEN);
}
int measCur(void) {
	int temp;
	while ( ADCSRA & (1 << ADSC));
	adcCurInit();
	ADCSRA |= (1 << ADSC);
	while ( ADCSRA & (1 << ADSC));
	temp = (ADCH << 2) | (ADCL >> 6);
	return temp;
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

	// Set PTB0 to 0 to enable power save. 
	PORTB &= ~(1<<0);
	while(0){
		/*DDRB = 0xff;*/
		/*PORTB = 0xff;*/
		_delay_ms(100); 		
		PORTA ^= (1<<7);
	}
	cwSend("AB1TJ", 5);

		/*PORTB ^= (1<<2);*/
  //Setup the clock
  TCCR1B |= (1 << WGM12) | 1<<CS11 | 1<<CS10;  //Divide by 64
  OCR1A = 156;        //Count 15624 cycles for 1 second interrupt
  /*OCR1A = 15624;        //Count 15624 cycles for 1 second interrupt*/
  TIMSK1 |= 1<<OCIE1A;        //enable timer compare interrupt
  sei();            //Enable global interrupts
 
	for(;;);
 
}
 
ISR (TIM1_COMPA_vect)      //Interrupt Service Routine
{
  PORTB ^= (1<<2);        //Use xor to toggle the LED
}
