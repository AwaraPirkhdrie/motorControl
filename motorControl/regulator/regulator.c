﻿#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint8_t adc = 0;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	adc = ADCH;
}

/*
 * Initialize the ADC and ISR.
 */
void regulator_init(void)
{
	// UPPGIFT: konfigurera ADC-enheten genom ställa in ADMUX och ADCSRA enligt kommentarerna nedanför!
	ADMUX |= (1<<REFS0);		// set reference voltage (internal 5V)
	ADMUX |= (1<<ADLAR);
	ADMUX |= (1<<MUX0);

	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	 // prescaler 128
	ADCSRA |= (1<<ADATE);		// enable Auto Trigger
	ADCSRA |= (1<<ADIE);		// enable Interrupt
	ADCSRA |= (1<<ADEN);		// enable ADC

	// disable digital input on ADC0 and ADC1
	DIDR0 = 3;

	// disable USB controller (to make interrupts possible)
	USBCON = 0;
	
	// enable global interrupts
	sei();

	// start initial conversion
	ADCSRA |= (1<<ADSC);
}

uint8_t getpotvalue(void){
	return ((adc * 100) / 255);
}

uint16_t getrawvalue(void){
	return adc;
}