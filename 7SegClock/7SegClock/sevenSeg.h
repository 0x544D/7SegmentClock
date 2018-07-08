/*
 * sevenSeg.h
 *
 * Created: 28.05.2016 13:19:07
 *  Author: Tobi
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_

// Pin defines
#define PIN_DIGIT1		PINB6
#define PIN_DIGIT2		PIND6
#define PIN_DIGIT3		PINB3
#define PIN_DIGIT4		PINA0

#define PIN_BIN1		PIND0
#define PIN_BIN2		PIND1
#define PIN_BIN4		PIND2
#define PIN_BIN8		PIND3

#define PIN_DP			PIND4

#define PORT_BIN		PORTD


#define DIGIT1_OFF		(PORTB |= (1<<PINB6))
#define DIGIT2_OFF		(PORTD |= (1<<PIND6))
#define DIGIT3_OFF		(PORTB |= (1<<PINB3))
#define DIGIT4_OFF		(PORTA |= (1<<PINA0))
#define DP_OFF			(PORTD &= ~(1<<PIND4))

#define DIGIT1_ON		(PORTB &= ~(1<<PINB6))
#define DIGIT2_ON		(PORTD &= ~(1<<PIND6))
#define DIGIT3_ON		(PORTB &= ~(1<<PINB3))
#define DIGIT4_ON		(PORTA &= ~(1<<PINA0))
#define DP_ON			(PORTD |= (1<<PIND4))

extern volatile uint8_t brightness;

void sevenSeg_init(void);

uint8_t sevenSeg_val_to_tens(uint8_t val);
uint8_t sevenSeg_val_to_ones(uint8_t val, uint8_t tens);

void sevenSeg_val_to_binary(uint8_t val);

void sevenSeg_change_brightness(uint8_t brightness);

#endif /* SEVENSEG_H_ */