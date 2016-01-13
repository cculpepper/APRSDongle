#ifndef COMMON_H
#define COMMON_H

#include <MKL03Z4.h>
#include <stdint.h>
#include <system_MKL03Z4.h>




#if (DEFAULT_SYSTEM_CLOCK == 48000000u)
#define DEFAULT_BUS_CLOCK 24000000u
#elif (DEFAULT_SYSTEM_CLOCK == 4000000u)
#define DEFAULT_BUS_CLOCK 2000000u
#elif (DEFAULT_SYSTEM_CLOCK == 32768u )
#define DEFAULT_BUS_CLOCK 32768u 
#else
#define DEFAULT_BUS_CLOCK 1000000u

#endif

#endif
