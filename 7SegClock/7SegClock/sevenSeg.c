/*
 * sevenSeg.c
 *
 * Created: 28.05.2016 13:19:18
 *  Author: Tobi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "sevenSeg.h"
#include "clock.h"
#include "init.h"


volatile uint8_t brightness = 100;
uint8_t current_digit = 1;
uint8_t dp = 0;
uint16_t ms = 0;


ISR(TIMER1_COMPA_vect)
{
	// Frequency 1kHz = 1ms
	
	// increment second
	ms++;
	if (ms > 999)
	{
		ms = 0;
		second++;
		adjust_time();
		dp ^= 1;
	}
	
	
	//TOGGLE_DATE;
	
	uint8_t tmp_tens, tmp_ones;
	DIGIT1_OFF;
	DIGIT2_OFF;
	DIGIT3_OFF;
	DIGIT4_OFF;
	DP_OFF;
	
	switch (current_digit)
	{
	case 1:
		tmp_tens = sevenSeg_val_to_tens(hour);
		sevenSeg_val_to_binary(tmp_tens);
		DIGIT1_ON;
		current_digit = 2;
		break;
		
	case 2:
		tmp_tens = sevenSeg_val_to_tens(hour);
		tmp_ones = sevenSeg_val_to_ones(hour,tmp_tens);
		sevenSeg_val_to_binary(tmp_ones);
		if (dp)
		{
			DP_ON;
		}
		DIGIT2_ON;
		current_digit = 3;
		break;	
	
	case 3:
		tmp_tens = sevenSeg_val_to_tens(minute);
		sevenSeg_val_to_binary(tmp_tens);
		if (dp)
		{
			DP_ON;
		}
		DIGIT3_ON;
		current_digit = 4;
		break;
		
	case 4:
		tmp_tens = sevenSeg_val_to_tens(minute);
		tmp_ones = sevenSeg_val_to_ones(minute,tmp_tens);
		sevenSeg_val_to_binary(tmp_ones);
		DIGIT4_ON;
		current_digit = 1;
		break;
		
	default:
		
		break;
	}
	
}



void sevenSeg_init(void)
{
	// init DIGIT and BINARY Pins
	DDRB |= (1<<PIN_DIGIT1) | (1<<PIN_DIGIT3);
	DDRD |= (1<<PIN_DIGIT2) | (1<<PIN_BIN1) | (1<<PIN_BIN2) | (1<<PIN_BIN4) | (1<<PIN_BIN8) | (1<<PIN_DP);
	DDRA |= (1<<PIN_DIGIT4);
	
	PORTD |= (1<<PIN_DIGIT2);
	PORTB |= (1<<PIN_DIGIT1) | (1<<PIN_DIGIT3);
	PORTA |= (1<<PIN_DIGIT4);

	// set BINARY Pins low
	PORT_BIN &= ~((1<<PIN_BIN1) | (1<<PIN_BIN2) | (1<<PIN_BIN4) | (1<<PIN_BIN8));
	
	// init PWM Timer (Timer 0)
	DDRD |= (1<<DDD5);
	
	TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B = (1 << CS00);   // clock source = CLK, start PWM
	OCR0B = brightness;

	TIMSK |= (1<<TOV0);
	
	
	// Digit switching timer - 1kHz = 1ms
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
	
	ICR1 = 1000;
	
	TIMSK |= (1<<OCIE1A);

}

uint8_t sevenSeg_val_to_tens(uint8_t val)
{
    if(val < 10){
        return 0;
    }else if(val < 20){
        return 1;
    }else if (val < 30){
        return 2;
    }else if (val < 40){
        return 3;
    }else if (val < 50){
        return 4;
    }else if (val < 60){
		return 5;
    }else if (val < 70){
		return 6;
    }else if (val < 80){
		return 7;
    }else if (val < 90){
		return 8;
    }else{
		return 9;
	}
}

uint8_t sevenSeg_val_to_ones(uint8_t val, uint8_t tens)
{
    return val - (tens*10);
}

void sevenSeg_val_to_binary(uint8_t val)
{
	// clear all
	PORT_BIN &= ~((1<<PIN_BIN1) | (1<<PIN_BIN2) | (1<<PIN_BIN4) | (1<<PIN_BIN8));
	// set according to value
	uint8_t test = ((val & ((uint8_t)1))<<PIN_BIN1);
    PORT_BIN |= test;
	test = (((val & ((uint8_t)2))>>1)<<PIN_BIN2);
    PORT_BIN |= test;
	test = (((val & ((uint8_t)4))>>2)<<PIN_BIN4);
    PORT_BIN |= test;
    test = (((val & ((uint8_t)8))>>3)<<PIN_BIN8);
	PORT_BIN |= test;
}

void sevenSeg_change_brightness(uint8_t bright)
{
	if (bright >= 255)
	{
		brightness = 255;
		
	}else if (bright <= 0)
	{
		brightness = 0;
		
	}else{
		
		brightness = bright;	
	}
	OCR0B = brightness;
}