/*
 * lab6.c
 *
 *  This program is for controlling a DC-Motor through PWM. 
 *
 * Created: 2019-01-15 08:21:16
 *  Author: Awara
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "common.h"
#include "hmi/hmi.h"

#include "numkey/numkey.h"
#include "regulator/regulator.h"
#include "lcd/lcd.h"
#include "motor/motor.h"

/* Char strings used for the display */
char *p_OFF_str = "State: OFF";
char *p_ON_str = "State: ON";
char *p_RUNNING_str = "State: RUNNING";

/* The three states in our state machine. */
typedef enum 
{
	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
} state;

/* Enum for current state and next state */
state current_state;
state next_state;

/* Used to store characters temporarily for formatting outputs and prints them on a LCD */
char temp_str[17];

/* Prototypes */
void motor_off();
void motor_on();
void motor_running();

/* Main */
int main(void){
	/* Init */
	hmi_init();
	regulator_init();
	motor_init();
	
	/* Main loop */
    while(1){
        switch(current_state){
	        case MOTOR_OFF:
	        if(numkey_read() == '2' && getpotvalue() == 00){
		        next_state = MOTOR_ON;
	        }
	        motor_off();
	        break;
	        
	        case MOTOR_ON:
	        if(numkey_read() == '1'){
		        next_state = MOTOR_OFF;
		        } else if(getpotvalue() > 0){
		        next_state = MOTOR_RUNNING;
	        }
	        motor_on();
	        break;
	        
	        case MOTOR_RUNNING:
	        if(numkey_read() == '1'){
		        next_state = MOTOR_OFF;
	        }
			motor_running();
	        break;
        }
        current_state = next_state;
        }
	return 0;
}

/* This get called every time the state machine is MOTOR_OFF */
void motor_off(){
	sprintf(temp_str, "%u%c", getpotvalue(), 0x25);
	output_msg(p_OFF_str, temp_str, 0);
	motor_set_speed(0);
}

/* This get called every time the state machine is MOTOR_ON */
void motor_on(){
	sprintf(temp_str, "%u%c", getpotvalue(), 0x25);
	output_msg(p_ON_str, temp_str, 0);
	motor_set_speed(getpotvalue());
}

/* This get called every time the state machine is MOTOR_RUNNING */
void motor_running(){
	sprintf(temp_str, "%u%c",getpotvalue(), 0x25);
	output_msg(p_RUNNING_str, temp_str, 0);
	motor_set_speed(getpotvalue());
}