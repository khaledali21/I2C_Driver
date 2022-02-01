/*
 * LED.c
 *
 *  Created on: Jan 6, 2022
 *      Author: Khaled Ali
 */


#include "LED.h"

/*
* brief: This function is used to initialize the DIO pin as output for the led by calling DIO driver
* param.: (input) a pointer to a led structure describing which port and pin will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LED_ERR_STATE LED_u8Init(const LED_t* led){
	LED_ERR_STATE state = LED_OK;
	if(led == NULL){
		state = LED_ERR;
	}
	else{
		state = DIO_u8SetPinDirection(led->PORT, led->PIN, OUTPUT_PIN);
	}
	return state;
}
/*
* brief: This function is used to turn the led on
* param.: (input) a pointer to a led structure describing which port and pin will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LED_ERR_STATE LED_u8ON(const LED_t* led){
	LED_ERR_STATE state = LED_OK;
	if(led == NULL){
		state = LED_ERR;
	}
	else{
		state = DIO_u8SetPinData(led->PORT, led->PIN, HIGH);
	}
	return state;
}
/*
* brief: This function is used to turn the led off
* param.: (input) a pointer to a led structure describing which port and pin will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LED_ERR_STATE LED_u8OFF(const LED_t* led){
	LED_ERR_STATE state = LED_OK;
	if(led == NULL){
		state = LED_ERR;
	}
	else{
		state = DIO_u8SetPinData(led->PORT, led->PIN, LOW);
	}
	return state;
}
/*
* brief: This function is used to toggle the current state of the led
* param.: (input) a pointer to a led structure describing which port and pin will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LED_ERR_STATE LED_u8TOGGLE(const LED_t* led){
	LED_ERR_STATE state = LED_OK;
	if(led == NULL){
		state = LED_ERR;
	}
	else{
		state = DIO_u8TogglePinData(led->PORT, led->PIN);
	}
	return state;
}
