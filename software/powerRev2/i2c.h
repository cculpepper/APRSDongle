
#ifndef i2c_h
#define i2c_h

#include "common.h"

#define I2C_READ 1
#define I2C_WRITE 0


#define I2CADDRESSLOW 0x66
#define I2CADDRESSSTATUS (I2CADDRESSLOW+2)
#define I2CADDRESSHIGH (I2CADDRESSLOW+4)
#define I2CADDRESSHIGH (I2CADDRESSLOW+4)
  /* Will match the addresses of 0x68 and 0x6a
   * Will use 6a for quick status
   * and 6a for control*/ 

void i2c_init();
uint8_t i2cFlashRead(uint16_t addr, int numBytes, char *dataPtr);
uint8_t i2cFlashWrite(uint16_t addr, int numBytes, char *dataPtr);
volatile int txIndex, rxIndex;
volatile char destAddress, dummy_read;
#define I2CBUFSIZE 30
volatile char txBuf[I2CBUFSIZE];
volatile int txBufFilled; /* The number of elements to tx */ 
volatile char rxBuf[I2CBUFSIZE];
#define I2C_REG_SIZE 10
volatile char registers[I2C_REG_SIZE];


#endif

