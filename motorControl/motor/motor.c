/*
 * motor.c
 *
 * Created: 2019-01-15 10:03:10
 *  Author: Awara
 */

#include <avr/io.h>
#include <inttypes.h>
#include "motor.h"
#include "../common.h"


/* Initlize motor */
void motor_init(void){
	DDRC |= 1 << PC6; // set PC6 (digital pin ) as output
	// Set OC3A (PC6) to be cleared on Compare Match (Channel A)
	// COM3A1 = 1, COM3A0 = 0.
	//TCCR3A |= 80;
	TCCR3A |= (1<<COM3A1);
	//TCCR3A |= (1<<COM3A0);
	
	// Waveform Generation Mode 5, Fast PWM (8-bit)
	
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32);
	
	// Timer Clock, 16/64 MHz = 1/4 MHz
	TCCR3B |= (1<<CS30);
	TCCR3B |= (1<<CS31);
}

/* Set the motor speed */
void motor_set_speed(uint8_t speed){
	uint16_t motorspeed = speed * 255;

	uint8_t motor = (motorspeed / 100);

	OCR3AL = (uint8_t)motor;
	OCR3AH = 0;
}