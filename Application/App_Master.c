#include "../ECUAL/LED/LED.h"
#include "../MCAL/I2C/I2C.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/TIMER/TIMER0.h"
LED_t led0 = {PORTB, PIN4};
LED_t led1 = {PORTB, PIN5};
LED_t led2 = {PORTB, PIN6};
void App_Master(void)
{
	LED_u8Init(&led0);
	LED_u8Init(&led1);
	LED_u8Init(&led2);
	DIO_u8SetPinDirection(PORTD, PIN0, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTD, PIN1, OUTPUT_PIN);
	UART_u8Init(9600);
	I2C_Init();
	uint8_t state;
	uint8_t data;
    while (1)
    {
			UART_u8GetData(&data);
			state = I2C_u8Start(0x01, WRITE);
			if(state == 1){
				state = I2C_u8MasterSendData(data);
				if(state != 1){
					LED_u8ON(&led1);
					UART_u8SendData(state);
				}
			}
			else{
				LED_u8ON(&led2);
				UART_u8SendData(state);
			}
		I2C_Stop();
	}
}

