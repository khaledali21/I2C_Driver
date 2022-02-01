/*
 * UART.c
 *
 * Created: 1/24/2022 12:24:54 AM
 *  Author: Khaled Ali
 */ 

#include "UART.h"
//A pointer to callBack function when interrupt happens
static void (*receivce_CallBack)(uint8_t);

/*
* brief: This function is used to Initialize the UART driver with custom baudrate and 8-bit data and 1 stop bit
* param.: (input) the required BaudRate
*/
void UART_u8Init(uint32_t BaudRate){
	uint16_t UBRR_Value = ((UART_F_CPU)/(BaudRate*16UL)-1);
	UCSRC_REG =	(1 << URSEL_BIT) | (1 << UCSZ1_BIT) | (1 << UCSZ0_BIT);
	UBRRH_REG = (uint8_t) (UBRR_Value >> 8);
	UBRRL_REG = (uint8_t) UBRR_Value;
	SET_BIT(UCSRB_REG, TXEN_BIT);
	SET_BIT(UCSRB_REG, RXEN_BIT);
}
/*
* brief: This function is used to send Data to the device connected to the MCU through RXD, TXD Pins
* param.: (input) the data that will be sent
*/
void UART_u8SendData(uint8_t data){
	
	while(GET_BIT(UCSRA_REG, UDRE_BIT) != 1);
	UDR_REG = data;	
	while(GET_BIT(UCSRA_REG, TXC_BIT) != 1);
}
/*
* brief: This function is used to receive Data from the device connected to the MCU through RXD, TXD Pins
* param.: (input) a pointer to a variable to hold the data that will be received
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
UART_ERR_STATE UART_u8ReceiveData(uint8_t* data){
	UART_ERR_STATE u8Status = UART_OK;
	if(data == NULL){
		u8Status = UART_ERR;
	}
	else{
		while(GET_BIT(UCSRA_REG, RXC_BIT) != 1);
		if(GET_BIT(UCSRA_REG, FE_BIT) == 1){
			u8Status = UART_FRAME_ERR;
		}
		else if(GET_BIT(UCSRA_REG, DOR_BIT) == 1){
			u8Status = UART_DATA_OVERRUN;
		}
		else{
			*data = UDR_REG;
		}
	}	
	return u8Status;
}
/*
* brief: This function is used to send a string to the device connected to the MCU through RXD, TXD Pins
* param.: (input) a pointer to the string that will be sent
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
UART_ERR_STATE UART_u8SendString(uint8_t* str){
	UART_ERR_STATE u8Status = UART_OK;
	if(str == NULL){
		u8Status = UART_ERR;
	}
	else{
		uint8_t* itr = str;
		while(*itr != '\0'){
			UART_u8SendData(*itr);
			itr++;
		}	
	}
	return u8Status;
}
/*
* brief: This function is used to receive a string from the device connected to the MCU through RXD, TXD Pins
* param.: (input) a pointer to a string to hold the string that will be received
* param.: (input) the character at which MCU stop receiving the string
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
UART_ERR_STATE UART_u8ReceiveString(uint8_t* str, uint8_t stop_char){
	UART_ERR_STATE u8Status = UART_OK;
	if(str == NULL){
		u8Status = UART_ERR;
	}
	else{
		uint8_t chr, i = 0;
		u8Status = UART_u8ReceiveData(&chr);
		while(chr != stop_char && u8Status == UART_OK){
			str[i] = chr;
			u8Status = UART_u8ReceiveData(&chr);
			i++;
		}
		str[i] = '\0';
	}
	return u8Status;
}
/*
* brief: This function is used to enable the interrupt that occurs when the MCU receives data through UART
* param.: (input) a pointer to to the function that will be called when the interrupt occurs
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
UART_ERR_STATE UART_u8EnableReceiveInterrupt(void (*fncallBack)(uint8_t)){
	UART_ERR_STATE u8Status = UART_OK;
	if(fncallBack == NULL){
		u8Status = UART_ERR;
	}
	else{
		receivce_CallBack = fncallBack;
		SET_BIT(UCSRB_REG, RXCIE_BIT);
		SET_BIT(SREG_REG, I_BIT);
	}
	return u8Status;
}
/*
* brief: This function is used to disable the interrupt that occurs when the MCU receives data through UART
*/
void UART_u8DisableReceiveInterrupt(void){
	receivce_CallBack = NULL;
	CLR_BIT(UCSRB_REG, RXCIE_BIT);
}


void __vector_13(void){
	if(receivce_CallBack != NULL){
		receivce_CallBack(UDR_REG);
	}
}