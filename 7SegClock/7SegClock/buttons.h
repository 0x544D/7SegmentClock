/*
 * buttons.h
 *
 * Created: 31.08.2015 15:26:11
 *  Author: Tobi
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#ifdef __cplusplus
extern "C" {
#endif

// #define BUTTON1 0
// #define BUTTON2 1
// #define BUTTON3 2
// #define BUTTON4 3
// #define BUTTON5 4
// #define BUTTON6 5
// #define BUTTON7 6
// #define BUTTON8 7

/**
 * check if a key has been pressed. Each pressed key is reported
 * only once
 */
uint8_t get_key_press( uint8_t key_mask );


/**
 * check if a key has been pressed long enough such that the
 * key repeat functionality kicks in. After a small setup delay
 * the key is reported being pressed in subsequent calls
 * to this function. This simulates the user repeatedly
 * pressing and releasing the key
 */
uint8_t get_key_rpt( uint8_t key_mask );


/**
 * check if a key is pressed right now
 */
uint8_t get_key_state( uint8_t key_mask );


uint8_t get_key_short( uint8_t key_mask );
uint8_t get_key_long( uint8_t key_mask );




/**
 * @brief initializes buttons, uses Timer0 for debouncing purposes
 */
void init_buttons();


/**
 * @brief  checks if a button was pressed and saves the event.
 * needs to get called in main loop periodically
 */
void checkButtons();


#ifdef __cplusplus
}
#endif


#endif /* BUTTONS_H_ */