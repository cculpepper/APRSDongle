
#ifndef i2c_h
#define i2c_h

#include <stdint.h>
#include <MKL26Z4.h>

#define I2C_READ 1
#define I2C_WRITE 0

#define I2C0_B  I2C0
#define intI2c I2C0

#define i2cFlashAddr 0xA0

void i2c_init(I2C_Type *p);
uint8_t i2cFlashRead(uint16_t addr, int numBytes, char *dataPtr);
uint8_t i2cFlashWrite(uint16_t addr, int numBytes, char *dataPtr);

#endif

