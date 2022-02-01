/*
 * UART.c
 *
 * Created: 1/24/2022 12:24:54 AM
 *  Author: Khaled Ali
 */ 

#include "UART.h"


void UART_u8Init(uint32_t BaudRate){
	uint16_t UBRR_Value = ((UART_F_CPU)/(BaudRate*16UL)-1);
	UCSRC_REG =	(1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRH_REG = (uint8_t) (UBRR_Value >> 8);
	UBRRL_REG = (uint8_t) UBRR_Value;
	SET_BIT(UCSRB_REG, TXEN);
	SET_BIT(UCSRB_REG, RXEN);
}
void UART_u8SendData(uint8_t data){
	
	while(GET_BIT(UCSRA_REG, UDRE) != 1);
	UDR_REG = data;	
	while(GET_BIT(UCSRA_REG, TXC) != 1);
}
UART_ERR_STATE UART_u8GetData(uint8_t* data){
	UART_ERR_STATE u8State = UART_OK;
	if(data == NULL){
		u8State = UART_ERR;
	}
	else{
		while(GET_BIT(UCSRA_REG, RXC) != 1);
		if(GET_BIT(UCSRA_REG, FE) == 1){
			u8State = UART_FRAME_ERR;
		}
		else if(GET_BIT(UCSRA_REG, DOR) == 1){
			u8State = UART_DATA_OVERRUN;
		}
		else{
			*data = UDR_REG;
		}
	}	
	return u8State;
}

UART_ERR_STATE UART_u8SendString(uint8_t* str){
	UART_ERR_STATE u8State = UART_OK;
	if(str == NULL){
		u8State = UART_ERR;
	}
	else{
		uint8_t* itr = str;
		while(*itr != '\0'){
			UART_u8SendData(*itr);
			itr++;
		}	
	}
	return u8State;
}