/*
 * clock.c
 *
 * Created: 29.05.2016 13:30:55
 *  Author: Tobi
 */ 

#include <stdint.h>
#include "clock.h" 
 
uint16_t volatile year = 2000;
uint8_t volatile month = 1; 
uint8_t volatile date = 1;
uint8_t volatile hour = 13;
uint8_t volatile minute = 37;
uint8_t volatile second = 0;
 
 void clock_init(void)
 {
	 
 }
 
 void adjust_time(void)
 {
	 if (second > 59)
	 {
		 second = 0;
		 minute++;
		 
		 if (minute > 59)
		 {
			 minute = 0;
			 hour++;
			 
			 if (hour > 23)
			 {
				 hour = 0;
			 }
			  
		 }
	 }
 }