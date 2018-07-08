/*
 * 7SegClock.c
 *
 * Created: 28.05.2016 12:57:46
 * Author : Tobi
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "init.h"
#include "clock.h"
#include "sevenSeg.h"
#include "buttons.h"
#include "twi.h"

char buffer[10];

int main(void)
{
	init_pins();
	init_buttons();
	sevenSeg_init();
	twi_init();
	
	sei();
	
	buffer[0] = 0xC1;
	buffer[1] = 0x00;
	buffer[2] = 0x00;
	buffer[3] = 0x00;
	
	twi_transceive_buffer(buffer,4);
	minute = buffer[3];
	
// 	uint8_t tmp = sevenSeg_val_to_tens(20);
// 	sevenSeg_val_to_binary(tmp);
// 	DIGIT1_ON;
// 	uint16_t i = 10;

	
	
    while (1) 
    {
		checkButtons();
		
		twi_transceive_buffer(buffer,4);
		_delay_ms(1000);
		
		
		
// 		if (i>90)
// 		{
// 			i=0;
// 		}
// 		
// 		uint8_t tmp_tens = sevenSeg_val_to_tens(i);
// 		uint8_t tmp_ones = sevenSeg_val_to_ones(i,tmp_tens);
// 		sevenSeg_val_to_binary(tmp_ones);
// 		DIGIT1_ON;
// 		i++;
// 		_delay_ms(1000);
// 
     }
}

