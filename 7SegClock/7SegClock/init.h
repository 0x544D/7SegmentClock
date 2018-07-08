/*
 * init.h
 *
 * Created: 28.05.2016 13:12:17
 *  Author: Tobi
 */ 


#ifndef INIT_H_
#define INIT_H_

// Pin defines
#define PIN_BUZZER	PINB4
#define PIN_ALARM	PINB5
#define PIN_DATE	PINA1

#define TOGGLE_DATE	(PORTA ^= (1<<PINA1))

void init_pins(void);

void toggle_pins(void);


#endif /* INIT_H_ */