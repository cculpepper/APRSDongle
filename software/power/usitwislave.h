#ifndef	_USI_TWI_SLAVE_H_
#define	_USI_TWI_SLAVE_H_

/*	See LICENSE for Copyright etc. */

#include <stdint.h>

enum
{
	USI_TWI_BUFFER_SIZE = 32
};

void		usi_twi_slave(uint8_t slave_address, uint8_t use_sleep,
				void (*data_callback)(volatile uint8_t *input_buffer_length, volatile const uint8_t *input_buffer,
				volatile uint8_t *output_buffer_length, volatile uint8_t *output_buffer),
				void (*idle_callback)(void));

void		usi_twi_enable_stats(uint8_t onoff);
uint16_t	usi_twi_stats_start_conditions(void);
uint16_t	usi_twi_stats_stop_conditions(void);
uint16_t	usi_twi_stats_error_conditions(void);
uint16_t	usi_twi_stats_overflow_conditions(void);
uint16_t	usi_twi_stats_local_frames(void);
uint16_t	usi_twi_stats_idle_calls(void);

#endif
