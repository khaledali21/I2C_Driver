#include "../ECUAL/LED/LED.h"
#include "../MCAL/I2C/I2C.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/DIO/DIO.h"
LED_t led0 = {PORTB, PIN4};
LED_t led1 = {PORTB, PIN5};
LED_t led2 = {PORTB, PIN6};
LED_t led3 = {PORTB, PIN7};

void App_Slave(void)
{
	LED_u8Init(&led0);
	LED_u8Init(&led1);
	LED_u8Init(&led2);
	LED_u8Init(&led3);
	DIO_u8SetPinDirection(PORTD, PIN0, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTD, PIN1, OUTPUT_PIN);
	UART_u8Init(9600);
	I2C_Init();
	I2C_SetSlaveAddress(0x01);
	uint8_t data;
	uint8_t action;
	uint8_t state;
    while (1) 
    {
		state = I2C_u8SlaveListen(&action);
		if(state == 1){
			if(action == WRITE){
				state = I2C_u8SlaveGetData(&data, ACK);
				if(state == 1){
					UART_u8SendData(data);
				}
				else{
					LED_u8ON(&led0);
					UART_u8SendData(state);
				}
			}
			else{
				UART_u8ReceiveData(&data);
				state = I2C_u8SlaveSendData(data);
				if(state != 1){
					LED_u8ON(&led1);
					UART_u8SendData(state);
				}
			}
		}
		else{
			LED_u8ON(&led2);
			UART_u8SendData(state);
		}
}

}
