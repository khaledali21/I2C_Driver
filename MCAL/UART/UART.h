/*
 * UART.h
 *
 * Created: 1/24/2022 12:24:46 AM
 *  Author: Khaled Ali
 */ 


#ifndef UART_H_
#define UART_H_
#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#define UART_F_CPU 8000000UL

typedef enum{
	UART_ERR,
	UART_OK,
	UART_FRAME_ERR,
	UART_DATA_OVERRUN	
}UART_ERR_STATE;

void UART_u8Init(uint32_t BaudRate);

void UART_u8SendData(uint8_t data);

UART_ERR_STATE UART_u8EnableReceiveInterrupt(void (*fncallBack)(uint8_t));

void UART_u8DisableReceiveInterrupt(void);

UART_ERR_STATE UART_u8ReceiveData(uint8_t* data);

UART_ERR_STATE UART_u8SendString(uint8_t* str);

UART_ERR_STATE UART_u8ReceiveString(uint8_t* str, uint8_t stop_char);

void __vector_13(void) __attribute__ ((signal, used));

#endif /* UART_H_ */