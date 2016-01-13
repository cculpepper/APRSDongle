
// accel.c -- Accelerometer support
//
//  Copyright (c) 2012-2013 Andrew Payne <andy@payne.org>
//

// Based on demo example from Freescale

#include "i2c.h"
#include "common.h"

// ---------------------------------------------------------------------------
// I2C bus control functions
//

void i2c_init(void)
{
    // Enable clocks
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;      
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    
    // Configure GPIO for I2C
    PORTB->PCR[4] = PORT_PCR_MUX(2);
    PORTB->PCR[3] = PORT_PCR_MUX(2);

    I2C0->A1 = I2CADDRESSLOW;
    I2C0->RA = I2CADDRESSHIGH;

    I2C0->C2 = I2C_C2_RMEN_MASK;

/* We run off the system clock. Well divide down to get to 100 khz
 * Which means we need to divide by... 480. Which means ICR in hex needs to be
 * 0x27. 
 * */ 
    I2C0->F = 0x27;
    
     /* Enable the module, 
      * Enable interrupts
      * Enable wakeup. */ 
    I2C0->C1  = I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK | I2C_C1_WUEN_MASK;

    
}

void i2cSetupStatus(void){
	/* Dont know if this should be defined here or not. 
	 * It should do a few things:
	 * 	setup the tx buffer to transmit the required stati
	 * 	Setup the the txBufFilled variable
	 * And thats about it. 
	 * Im thinking transmit a uint16_t for each of the required statuses. */ 
	txBufFilled = 0;
	txBuf[0] = 0;
}

void I2C0_IRQHandler(void){
	/* Do stuff here. 
	 * Firstly. Check what kinda interrupt.
	 * Address match: 
	 * 	send ack. 
	 * 	Check address. 
	 * 	If quick status, 
	 * 		setup pointers and data lenghts
	 * 		Initiate first write
	 * 	If general address,
	 * 		if write,
	 * 			Save in write to status register
	 * 		if read,
	 * 			send current pointer data.
	 * Byte received:
	 * 	If were master is writing to us, 
	 * 		ack
	 * 		If weve got an adress already
	 * 			Write to that register. 
	 * 		Else, save the current data as the register. 
	 */
	if (I2C0->S & I2C_S_IAAS_MASK){
		/* Then we have been addressed as a slave.  */ 
		if (I2C0->S & I2C_S_SRW_MASK){
			/* Then we are in tx mode. Master wants data */ 
			I2C0->C1 |= I2C_C1_TX_MASK;
			if (I2C0->D == I2CADDRESSSTATUS){
				i2cSetupStatus();
			}
			txIndex = 0;
			I2C0->D = txBuf[txIndex++];
		} else {
			/* Then we are going to recieve data.  */ 
			I2C0->C1 &= ~I2C_C1_TX_MASK;
			rxIndex = I2C0->D;
		}
	} else {
		/* Then we received a myte, and its not the address.  */ 
		if (I2C0->C1 & I2C_C1_TX_MASK){
			/* If in transmit mode? */ 
			if (I2C0->S & I2C_S_RXAK_MASK){
				/* This may be wrong. 
				 * We should only stop if we get a NAK
				 * But I stole this from the sample code.*/ 
				I2C0->C1 &= !I2C_C1_TX_MASK;
				dummy_read = I2C0->D;
			} else {
				/* Otherwise actually send the next data.
				 * Master shouuuuuuld stop us before the end
				 * of the buffer but to be safe...*/ 
				if ((txIndex >= I2CBUFSIZE) || (txIndex >= txBufFilled)){
					I2C0->D = 0;
				} else {
					I2C0->D = txBuf[txIndex++];
				}
			}
		} else {
			/* Then we are in receive mode */ 
			if (rxIndex + 2 >= I2CBUFSIZE){
				/* Check if we are on the second to lant byte,
				 * if so we need to nack the last byte. We
				 * is full. */ 
				I2C0->C1 |= I2C_C1_TXAK_MASK;
			} 
			rxBuf[rxIndex++] = I2C0->D;
			/* If at the end of the buffer, send a NACK, 
			 * Not gonna do this for now. */ 
		}
	}
}

