/*
 * DIO.h
 *
 *  Created on: Jan 6, 2022
 *      Author: Khaled Ali
 */

#ifndef MCAL_DIO_H_
#define MCAL_DIO_H_

#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"

#define ERR 0
#define OK 1
typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT_u8;


typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
}PIN_u8;

typedef enum{
	INPUT_PIN_PULLUP,
	INPUT_PIN_NO_PULLUP,
	INPUT_PORT_PULLUP,
	INPUT_PORT_NO_PULLUP,
	OUTPUT_PIN,
	OUTPUT_PORT
}DIR_u8;
typedef enum{
	DIO_ERR,
	DIO_OK
}DIO_ERR_STATE;
typedef enum{
	LOW,
	HIGH
}VAL_u8;

DIO_ERR_STATE DIO_u8SetPortDirection(PORT_u8 port, DIR_u8 dir);

DIO_ERR_STATE DIO_u8SetPinDirection(PORT_u8 port, PIN_u8 pin, DIR_u8 dir);

DIO_ERR_STATE DIO_u8SetPortData(PORT_u8 port, VAL_u8 data);

DIO_ERR_STATE DIO_u8SetPinData(PORT_u8 port, PIN_u8 pin, VAL_u8 data);

DIO_ERR_STATE DIO_u8GetPortData(PORT_u8 port, uint8_t* Data);

DIO_ERR_STATE DIO_u8GetPinData(PORT_u8 port, PIN_u8 pin, uint8_t* Data);

DIO_ERR_STATE DIO_u8TogglePortData(PORT_u8 port);

DIO_ERR_STATE DIO_u8TogglePinData(PORT_u8 port, PIN_u8 pin);

#endif /* MCAL_DIO_H_ */
