/************************************************************************/
/*                                                                      */
/*                      Debouncing 8 Keys                               */
/*                      Sampling 4 Times                                */
/*                      With Repeat Function                            */
/*                                                                      */
/*              Author: Peter Dannegger                                 */
/*                      danni@specs.de                                  */
/*                                                                      */
/************************************************************************/
 
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "buttons.h"
#include "sevenSeg.h"
#include "init.h"


#ifndef F_CPU
#define F_CPU           1000000UL                   // processor clock frequency
#endif
 
#define KEY_DDR         DDRB
#define KEY_PORT        PORTB
#define KEY_PIN         PINB

#define BUTTON1			0
#define BUTTON2			1
#define BUTTON3         2

#define ALL_KEYS        (1<<BUTTON1 | 1<<BUTTON2 | 1<<BUTTON3)
 
#define REPEAT_MASK     (1<<BUTTON1 | 1<<BUTTON2 | 1<<BUTTON3)   // repeat: key1, key2
#define REPEAT_START    50                        // after 500ms
#define REPEAT_NEXT     20                        // every 200ms
 
volatile uint8_t key_state;                                // debounced and inverted key state:
// bit = 1: key pressed
volatile uint8_t key_press;                                // key press detect

volatile uint8_t key_rpt;                                  // key long press and repeat

// USER VARS

uint8_t i = 0;
volatile uint8_t cnt = 0;

ISR( TIMER0_OVF_vect )                            // every 10ms
{
	if(cnt >= 39){
		cnt = 0;
	
		static uint8_t ct0, ct1, rpt;
		uint8_t i;
 
		//TCNT0 = (uint8_t)(int16_t)-(F_CPU / 1024 * 10e-3 + 0.5);  // preload for 10ms
 
		i = key_state ^ ~KEY_PIN;                       // key changed ?
		ct0 = ~( ct0 & i );                             // reset or count ct0
		ct1 = ct0 ^ (ct1 & i);                          // reset or count ct1
		i &= ct0 & ct1;                                 // count until roll over ?
		key_state ^= i;                                 // then toggle debounced state
		key_press |= key_state & i;                     // 0->1: key press detect
 
		if( (key_state & REPEAT_MASK) == 0 )            // check repeat function
			rpt = REPEAT_START;                          // start delay
		if( --rpt == 0 ){
			rpt = REPEAT_NEXT;                            // repeat delay
			key_rpt |= key_state & REPEAT_MASK;
		}
	}else{
		cnt++;
	}
}
 
///////////////////////////////////////////////////////////////////
//
// check if a key has been pressed. Each pressed key is reported
// only once
//
uint8_t get_key_press( uint8_t key_mask )
{
  cli();                                          // read and clear atomic !
  key_mask &= key_press;                          // read key(s)
  key_press ^= key_mask;                          // clear key(s)
  sei();
  return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
// check if a key has been pressed long enough such that the
// key repeat functionality kicks in. After a small setup delay
// the key is reported being pressed in subsequent calls
// to this function. This simulates the user repeatedly
// pressing and releasing the key.
//
uint8_t get_key_rpt( uint8_t key_mask )
{
  cli();                                          // read and clear atomic !
  key_mask &= key_rpt;                            // read key(s)
  key_rpt ^= key_mask;                            // clear key(s)
  sei();
  return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
// check if a key is pressed right now
//
uint8_t get_key_state( uint8_t key_mask )
{
  key_mask &= key_state;
  return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
uint8_t get_key_short( uint8_t key_mask )
{
  cli();                                          // read key state and key press atomic !
  return get_key_press( ~key_state & key_mask );
}
 
///////////////////////////////////////////////////////////////////
//
uint8_t get_key_long( uint8_t key_mask )
{
  return get_key_press( get_key_rpt( key_mask ));
}
 
 
void init_buttons()
{
	 // Configure debouncing routines
	 KEY_DDR &= ~ALL_KEYS;                // configure key port for input
	 KEY_PORT |= ALL_KEYS;                // and turn on pull up resistors
}

void checkButtons()
{
	/**** Short Buttons Presses ****/ 
	if( get_key_short( 1<<BUTTON1 ))
	{
		sevenSeg_change_brightness(brightness+10);
	}
	
	if( get_key_short( 1<<BUTTON2))
	{

	}
	
	if( get_key_short( 1<<BUTTON3))
	{
		sevenSeg_change_brightness(brightness-10);
	}
	
	
	/**** Long Button Presses ****/
	if( get_key_long( 1<<BUTTON1 ))
	{
		
	}
	
	if( get_key_long( 1<<BUTTON2))
	{
		
	}
	
	if( get_key_long( 1<<BUTTON3 ))
	{
		
	}
	

	
	/**** Single press and repeat ****/
/*	// DOWN
	if( get_key_press( 1<<DOWN ) || get_key_rpt( 1<<DOWN ))
	{
		uart1_puts("DOWN RPT\r\n");
	}
	// UP
	if( get_key_press( 1<<UP ) || get_key_rpt( 1<<UP ))
	{
		uart1_puts("UP RPT\r\n");		
	}
	// LEFT
	if( get_key_press( 1<<LEFT ) || get_key_rpt( 1<<LEFT ))
	{
		uart1_puts("LEFT RPT\r\n");		
	}
	// RIGHT
	if( get_key_press( 1<<RIGHT ) || get_key_rpt( 1<<RIGHT ))
	{
		uart1_puts("RIGHT RPT\r\n");		
	}
*/
}