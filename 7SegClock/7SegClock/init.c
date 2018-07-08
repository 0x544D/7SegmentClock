/*
 * init.c
 *
 * Created: 28.05.2016 13:12:25
 *  Author: Tobi
 */ 
#include <avr/io.h>
#include <stdint.h>
#include "init.h"

uint8_t toggle = 0;

void init_pins(void)
{
	DDRB |= (1<<PIN_BUZZER) | (1<<PIN_ALARM);
	DDRA |= (1<<PIN_DATE);
	
	PORTB &= ~((1<<PIN_ALARM));
	PORTA &= ~((1<<PIN_DATE));
}

void toggle_pins(void)
{
	if (toggle)
	{
		PORTB |=  (1<<PIN_BUZZER) | (1<<PIN_ALARM) | (1<<PIN_DATE);
		toggle = 0;
	}else{
		PORTB &= ~((1<<PIN_BUZZER) | (1<<PIN_ALARM) | (1<<PIN_DATE));
		toggle = 1;
	}
}