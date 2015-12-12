
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

void i2c_init(I2C_Type *p)
{
    // Enable clocks
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;      
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    
    // Configure GPIO for I2C
    PORTE->PCR[24] = PORT_PCR_MUX(5);
    PORTE->PCR[25] = PORT_PCR_MUX(5);
    
    p->F  = 0x14;                   // Baudrate settings:  ICR=0x14, MULT=0
    p->C1 = I2C_C1_IICEN_MASK;      // Enable:  IICEN=1
}


__inline void i2c_set_tx(I2C_Type *p)     {p->C1 |= I2C_C1_TX_MASK;}
__inline void i2c_set_rx(I2C_Type *p)     {p->C1 &= ~I2C_C1_TX_MASK;}
__inline void i2c_set_slave(I2C_Type *p)  {p->C1 &= ~I2C_C1_MST_MASK;}
__inline void i2c_set_master(I2C_Type *p) {p->C1 |=  I2C_C1_MST_MASK;}
__inline void i2c_give_nack(I2C_Type *p)  {p->C1 |= I2C_C1_TXAK_MASK;}
__inline void i2c_give_ack(I2C_Type *p)   {p->C1 &= ~I2C_C1_TXAK_MASK;}
__inline void i2c_repeated_start(I2C_Type *p){p->C1     |= I2C_C1_RSTA_MASK;}
__inline uint8_t i2c_read(I2C_Type *p)    {return p->D;}

__inline void i2c_start(I2C_Type *p)
{
    i2c_set_master(p);
    i2c_set_tx(p);
}

__inline void i2c_stop(I2C_Type *p)
{
    i2c_set_slave(p);
    i2c_set_rx(p);
}

__inline void i2c_wait(I2C_Type *p)
{
    // Spin wait for the interrupt flag to be set
    while((p->S & I2C_S_IICIF_MASK) == 0)
        ;

    p->S |= I2C_S_IICIF_MASK;           // Clear flag
}

__inline int i2c_write(I2C_Type *p, uint8_t data)
{
    // Send data, wait, and return ACK status
    p->D = data;
    i2c_wait(p);
    return ((p->S & I2C_S_RXAK_MASK) == 0);
}

uint8_t i2cFlashRead(uint16_t addr, int numBytes, char *dataPtr){
	int ret;
	int index;
	index = 0; 
	numBytes--;
	i2c_start(intI2c);
	ret = i2c_write(intI2c, i2cFlashAddr | I2C_WRITE);
	//if (ret) return 1;
	ret = i2c_write(intI2c, ((addr) >> 8));// upper byte first
	//if (ret) return 1;
	ret = i2c_write(intI2c, ((addr) & 0xFF));
	//if (ret) return 1;
	i2c_repeated_start(intI2c);
	i2c_write(intI2c, i2cFlashAddr | I2C_READ); // Send the read. 
	i2c_set_rx(intI2c);
	dataPtr[0] = i2c_read(intI2c); // Dummy read 
	i2c_wait(intI2c);
	while (numBytes--){
		
		dataPtr[index++] = i2c_read(intI2c);
		i2c_give_ack(intI2c);
		i2c_wait(intI2c);
	}
	dataPtr[index++] = i2c_read(intI2c);
	i2c_give_nack(intI2c);
	i2c_stop(intI2c);
	return index;
}
uint8_t i2cFlashWrite(uint16_t addr, int numBytes, char *dataPtr){
	int index;
		index = 0; 
	i2c_start(intI2c);
	i2c_write(intI2c, i2cFlashAddr | I2C_WRITE);
	//if (ret) return 1;
	i2c_write(intI2c, ((addr) >> 8));// upper byte first
	//if (ret) return 1;
	i2c_write(intI2c, ((addr) & 0xFF));
	//if (ret) return 1;
	while (numBytes--){
		i2c_write(intI2c, dataPtr[index++]);
		if (addr == 0x1F3F) break; // Then we are at the end of the flash region. 
		addr++;
		if (((addr % 32) == 0 )){
			// Then we need to write a new address. We are on the edge of a page. 
			i2c_stop(intI2c);
			delay(1);
			
				i2c_start(intI2c);
				i2c_write(intI2c, i2cFlashAddr | I2C_WRITE);
				//if (ret) return 1;
				i2c_write(intI2c, ((addr) >> 8));// upper byte first
				//if (ret) return 1;
				i2c_write(intI2c, ((addr) & 0xFF));
				//if (ret) return 1;
		}
	}
	i2c_stop(intI2c);
	return 0;
}

