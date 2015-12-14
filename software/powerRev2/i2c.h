
#ifndef i2c_h
#define i2c_h

#include "common.h"

#define I2C_READ 1
#define I2C_WRITE 0


#define I2CADDRESSLOW 0x66
#define I2CADDRESSHIGH 0x6A
  /* Will match the addresses of 0x68 and 0x6a
   * Will use 6a for quick status
   * and 6a for control*/ 

void i2c_init(I2C_Type *p);
uint8_t i2cFlashRead(uint16_t addr, int numBytes, char *dataPtr);
uint8_t i2cFlashWrite(uint16_t addr, int numBytes, char *dataPtr);

#endif

