/*
 * twi.c
 *
 * Created: 06.06.2016 16:18:22
 *  Author: Tobi
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"

void twi_init(void)
{
	// set pins as outputs
	DDRB |= (1<<PIN_SDA) | (1<<PIN_SCL);
	// set twi mode and software clock
	USICR = (1<<USIWM1) | (1<<USICLK);
	
}

unsigned char twi_transceive(unsigned char msg)
{
	// put msg in data registers
	USIDR = msg;
	//Issue Start Condition
	START_CONDITION;
	uint8_t i = 0;
	for (i=0;i<8;i++)
	{
		USICR |= (1<<USITC);
		_delay_us(1);
	}
	
	return USIDR;
}

unsigned char twi_transceive_buffer(unsigned char* buffer, uint8_t buffer_length)
{
	uint8_t cnt = 0;
	while (cnt <= buffer_length)
	{
		buffer[cnt] = twi_transceive(buffer[cnt]);
		cnt++;
	}
	return 1;
}