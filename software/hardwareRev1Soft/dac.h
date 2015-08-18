#include <MKL26Z4.h>
#include <stdint.h>
#ifndef dac_h
#define dac_h
void dacInit(void);

void dacDeInit(void) ;
void dacSet(uint16_t val);


#endif


