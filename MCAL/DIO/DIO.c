/*
 * DIO.c
 *
 *  Created on: Jan 7, 2022
 *      Author: Khaled Ali
 */


/*
 * DIO.C
 *
 *  Created on: Jan 6, 2022
 *      Author: Khaled Ali
 */

#include "DIO.h"


/*
* brief: This function is used to set the direction of the given port to input or output
* param.: (input) the port that will be used
* param.: (input) the direction to be set and setup pull up resistance or not in case the direction is input
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8SetPortDirection(PORT_u8 port, DIR_u8 dir){
	DIO_ERR_STATE state = DIO_OK;
	switch(port){
	case PORTA:
		switch(dir){
			case INPUT_PORT_NO_PULLUP:
			DDRA_REG = 0x00;
			break;
			case INPUT_PORT_PULLUP:
			DDRA_REG = 0x00;
			PORTA_REG = 0xFF;
			break;
			case OUTPUT_PORT:
			DDRA_REG = 0xFF;
			break;
			default:
			state = DIO_ERR;
			break; 
		}
		break;
	case PORTB:
		switch(dir){
			case INPUT_PORT_NO_PULLUP:
			DDRB_REG = 0x00;
			break;
			case INPUT_PORT_PULLUP:
			DDRB_REG = 0x00;
			PORTB_REG = 0xFF;
			break;
			case OUTPUT_PORT:
			DDRB_REG = 0xFF;
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	case PORTC:
		switch(dir){
			case INPUT_PORT_NO_PULLUP:
			DDRC_REG = 0x00;
			break;
			case INPUT_PORT_PULLUP:
			DDRC_REG = 0x00;
			PORTC_REG = 0xFF;
			break;
			case OUTPUT_PORT:
			DDRC_REG = 0xFF;
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	case PORTD:
		switch(dir){
			case INPUT_PORT_NO_PULLUP:
			DDRD_REG = 0x00;
			break;
			case INPUT_PORT_PULLUP:
			DDRD_REG = 0x00;
			PORTD_REG = 0xFF;
			break;
			case OUTPUT_PORT:
			DDRD_REG = 0xFF;
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	default:
		state = DIO_ERR;
		break;
	}
	return state;
}
/*
* brief: This function is used to set the direction of the given pin to input or output
* param.: (input) the port containing the pin
* param.: (input) the pin that will be used
* param.: (input) the direction to be set and setup pull up resistance or not in case the direction is input
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8SetPinDirection(PORT_u8 port, PIN_u8 pin, DIR_u8 dir){
	DIO_ERR_STATE state = DIO_OK;
	if(pin > PIN7 || pin < PIN0){
		state = DIO_ERR;
	}
	else{
	switch(port){
	case PORTA:
		switch(dir){
			case INPUT_PIN_NO_PULLUP:
			CLR_BIT(DDRA_REG, pin);
			break;
			case INPUT_PIN_PULLUP:
			CLR_BIT(DDRA_REG, pin);
			SET_BIT(PORTA_REG, pin);
			break;
			case OUTPUT_PIN:
			SET_BIT(DDRA_REG, pin);
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	case PORTB:
		switch(dir){
			case INPUT_PIN_NO_PULLUP:
			CLR_BIT(DDRB_REG, pin);
			break;
			case INPUT_PIN_PULLUP:
			CLR_BIT(DDRB_REG, pin);
			SET_BIT(PORTB_REG, pin);
			break;
			case OUTPUT_PIN:
			SET_BIT(DDRB_REG, pin);
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	case PORTC:
		switch(dir){
			case INPUT_PIN_NO_PULLUP:
			CLR_BIT(DDRC_REG, pin);
			break;
			case INPUT_PIN_PULLUP:
			CLR_BIT(DDRC_REG, pin);
			SET_BIT(PORTC_REG, pin);
			break;
			case OUTPUT_PIN:
			SET_BIT(DDRC_REG, pin);
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	case PORTD:
		switch(dir){
			case INPUT_PIN_NO_PULLUP:
			CLR_BIT(DDRD_REG, pin);
			break;
			case INPUT_PIN_PULLUP:
			CLR_BIT(DDRD_REG, pin);
			SET_BIT(PORTD_REG, pin);
			break;
			case OUTPUT_PIN:
			SET_BIT(DDRD_REG, pin);
			break;
			default:
			state = DIO_ERR;
			break;
		}
		break;
	default:
		state = DIO_ERR;
		break;
	}
	}
	return state;
}
/*
* brief: This function is used to set the value of the given port
* param.: (input) the port that will be used
* param.: (input) the value to be assigned to the given port
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8SetPortData(PORT_u8 port, VAL_u8 Data){
	DIO_ERR_STATE state = DIO_OK;
	switch(port){
	case PORTA:
		PORTA_REG = Data;
		break;
	case PORTB:
		PORTB_REG = Data;
		break;
	case PORTC:
		PORTC_REG = Data;
		break;
	case PORTD:
		PORTD_REG = Data;
		break;
	default:
		state = DIO_ERR;
		break;
	}

	return state;
}
/*
* brief: This function is used to set the value of the given pin
* param.: (input) the port containing the pin
* param.: (input) the pin that will be used
* param.: (input) the value to set the pin to
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8SetPinData(PORT_u8 port, PIN_u8 pin, VAL_u8 Data){
	DIO_ERR_STATE state = DIO_OK;
	if(pin > PIN7 || pin < PIN0){
		state = DIO_ERR;
	}
	else{
	switch(port){
	case PORTA:
		if(Data == LOW){
			CLR_BIT(PORTA_REG, pin);
		}
		else if(Data == HIGH){
			SET_BIT(PORTA_REG, pin);
		}
		else{
			state = DIO_ERR;
		}
		break;
	case PORTB:
		if(Data == LOW){
			CLR_BIT(PORTB_REG, pin);
		}
		else if(Data == HIGH){
			SET_BIT(PORTB_REG, pin);
		}
		else{
			state = DIO_ERR;
		}
		break;
	case PORTC:
		if(Data == LOW){
			CLR_BIT(PORTC_REG, pin);
		}
		else if(Data == HIGH){
			SET_BIT(PORTC_REG, pin);
		}
		else{
			state = DIO_ERR;
		}
		break;
	case PORTD:
		if(Data == LOW){
			CLR_BIT(PORTD_REG, pin);
		}
		else if(Data == HIGH){
			SET_BIT(PORTD_REG, pin);
		}
		else{
			state = DIO_ERR;
		}
		break;
	default:
		state = DIO_ERR;
		break;
	}
	}
	return state;
}
/*
* brief: This function is used to get the value of the given port
* param.: (input) the port that will be used
* param.: (input) a pointer to a variable to contain the value of the given port
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8GetPortData(PORT_u8 port, uint8_t* Data){
	DIO_ERR_STATE state = DIO_OK;
	if(Data == NULL){
		state = DIO_ERR;
	}
	else{	
	switch(port){
	case PORTA:
		*Data = PINA_REG;
		break;
	case PORTB:
		*Data = PINB_REG;
		break;
	case PORTC:
		*Data = PINC_REG;
		break;
	case PORTD:
		*Data = PIND_REG;
		break;
	default:
		state = DIO_ERR;
		break;
	}
	}
	return state;
}
/*
* brief: This function is used to get the value of the given pin
* param.: (input) the port containing the pin
* param.: (input) the pin that will be used
* param.: (input) a pointer to a variable to contain the value of the pin
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8GetPinData(PORT_u8 port, PIN_u8 pin, uint8_t* Data){
	DIO_ERR_STATE state = DIO_OK;
	if(Data == NULL || pin > PIN7 || pin < PIN0){
		state = DIO_ERR;
	}
	else{
	switch(port){
	case PORTA:
		*Data = GET_BIT(PINA_REG, pin);
		break;
	case PORTB:
		*Data = GET_BIT(PINB_REG, pin);
		break;
	case PORTC:
		*Data = GET_BIT(PINC_REG, pin);
		break;
	case PORTD:
		*Data = GET_BIT(PIND_REG, pin);
		break;
	default:
		state = DIO_ERR;
		break;
	}
	}
	return state;
}
/*
* brief: This function is used to toggle the value of the given port
* param.: (input) the port that will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8TogglePortData(PORT_u8 port){
	DIO_ERR_STATE state = DIO_OK;
	switch(port){
	case PORTA:
		PORTA_REG = ~PORTA_REG;
		break;
	case PORTB:
		PORTB_REG = ~PORTB_REG;
		break;
	case PORTC:
		PORTC_REG = ~PORTC_REG;
		break;
	case PORTD:
		PORTD_REG = ~PORTD_REG;
		break;
	default:
		state = DIO_ERR;
		break;
	}
	return state;
}
/*
* brief: This function is used to toggle the state of the given pin
* param.: (input) the port containing the pin
* param.: (input) the pin that will be used
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
DIO_ERR_STATE DIO_u8TogglePinData(PORT_u8 port, PIN_u8 pin){
	DIO_ERR_STATE state = DIO_OK;
	if(pin > PIN7 || pin < PIN0){
		state = DIO_ERR;
	}
	else{
	switch(port){
	case PORTA:
		Toggle_BIT(PORTA_REG, pin);
		break;
	case PORTB:
		Toggle_BIT(PORTB_REG, pin);
		break;
	case PORTC:
		Toggle_BIT(PORTC_REG, pin);
		break;
	case PORTD:
		Toggle_BIT(PORTD_REG, pin);
		break;
	default:
		state = DIO_ERR;
		break;
	}
	}
	return state;
}
