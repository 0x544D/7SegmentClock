/*
 * clock.h
 *
 * Created: 29.05.2016 13:30:45
 *  Author: Tobi
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

extern volatile uint8_t hour;
extern volatile uint8_t minute;
extern volatile uint8_t second;

void clock_init(void);
 void adjust_time(void);



#endif /* CLOCK_H_ */