/*
 * twi.h
 *
 * Created: 06.06.2016 16:18:13
 *  Author: Tobi
 */ 


#ifndef TWI_H_
#define TWI_H_

#define PIN_SDA		5
#define PIN_SCL		7
#define START_CONDITION		(PORTB &= ~(1<<PIN_SDA))
#define STOP_CONDITION		(PORTB |= (1<<PIN_SDA))

void twi_init(void);
unsigned char twi_transceive(unsigned char msg);
unsigned char twi_transceive_buffer(unsigned char* buffer, uint8_t buffer_length);

#endif /* TWI_H_ */