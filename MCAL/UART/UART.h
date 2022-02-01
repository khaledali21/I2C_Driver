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
/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0


typedef enum{
	UART_ERR,
	UART_OK,
	UART_FRAME_ERR,
	UART_DATA_OVERRUN	
}UART_ERR_STATE;

void UART_u8Init(uint32_t BaudRate);

void UART_u8SendData(uint8_t data);

UART_ERR_STATE UART_u8GetData(uint8_t* data);

UART_ERR_STATE UART_u8SendString(uint8_t* str);


#endif /* UART_H_ */