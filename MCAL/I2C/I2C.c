/*
 * I2C.c
 *
 * Created: 1/25/2022 8:34:52 PM
 *  Author: Khaled Ali
 */ 

#include "I2C.h"


/*
* brief: This function is used to Initialize the I2C driver
*/
void I2C_Init(void){
	CLR_BIT(TWSR_REG, TWPS0);
	CLR_BIT(TWSR_REG, TWPS1);
	TWBR_REG = ((I2C_F_CPU/SCL_CLK) - 16UL) / 2;
}
/*
* brief: This function is used to start transmission by the master and send targeted slave address
* param.: (input) the address of the required slave
* param.: (input) the required action to be done in this transmission either WRITE or READ
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8Start(uint8_t address, ACTION action){
	uint8_t u8State = I2C_OK;
	TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 <<	TWEN); // Send Start Condition
	while(GET_BIT(TWCR_REG, TWINT) == 0);	// Wait for any Operation to finish
	if((TWSR_REG & STATUS_MASK) != START && (TWSR_REG & STATUS_MASK) != REP_START){ // Check Start or Repeated start succeed
		u8State = (TWSR_REG & STATUS_MASK);
	}
	else{
		switch(action){
			case WRITE:
			TWDR_REG = (address << 1) & 0xFE; //Slave + W
			break;
			case READ:
			TWDR_REG = (address << 1) | 0x01; // Slave + R
			break;
			default:
			u8State = I2C_ERR;
			break;
		}
		if(u8State == I2C_OK){
			TWCR_REG = (1 << TWINT) | (1 << TWEN); //Send Slave Address
			while(GET_BIT(TWCR_REG, TWINT) == 0); // Wait for any Operation to finish
			if((TWSR_REG & STATUS_MASK) != MT_SLA_ACK && (TWSR_REG & STATUS_MASK) != MR_SLA_ACK){ //Check for ACK
				u8State = (TWSR_REG & STATUS_MASK);
			}
		}
	}
	return u8State;
}
/*
* brief: This function is used to end the current transmission
*/
void I2C_Stop(void){
	TWCR_REG = (1 << TWINT) | (1 << TWSTO) | (1 <<	TWEN); // Send Start Condition
}
/*
* brief: This function is used to send data from the master to the SDA line
* param.: (input) the data to be sent
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8MasterSendData(uint8_t data){
	uint8_t u8State = I2C_OK;
	TWDR_REG = data;
	TWCR_REG = (1 << TWINT) | (1 << TWEN); // Send Data
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	if((TWSR_REG & STATUS_MASK) != MT_DATA_ACK && (TWSR_REG & STATUS_MASK) != MT_DATA_NOT_ACK){ //Check for ACK
		u8State = (TWSR_REG & STATUS_MASK);
	}
	return u8State;
}
/*
* brief: This function is used to receive data from the SDA line to the Master
* param.: (input) a pointer to a variable to hold the data that will be received
* param.: (input) the type of acknowledgement to send to the SDA line after receiving the data either ACK or NACK
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8MasterGetData(uint8_t* data, ACKNOWLEDGEMENT acknowledgement){
	uint8_t u8State = I2C_OK;
	switch(acknowledgement){
		case ACK:
		TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		if((TWSR_REG & STATUS_MASK) != MR_DATA_ACK){
			u8State = (TWSR_REG & STATUS_MASK);
		}
		else{
			*data = TWDR_REG;
		}
		break;
		case NACK:
		TWCR_REG = (1 << TWINT) | (1 << TWEN);
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		if((TWSR_REG & STATUS_MASK) != MR_DATA_NOT_ACK){
			u8State = (TWSR_REG & STATUS_MASK);
		}
		else{
			*data = TWDR_REG;
		}
		break;
		default:
		u8State = I2C_ERR;
		break;
	}
	return u8State;

}
/*
* brief: This function is used to send data from the slave to the SDA line
* param.: (input) the data to be sent
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8SlaveSendData(uint8_t data){
	uint8_t u8State = I2C_OK;
	TWDR_REG = data;
	TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Send Data
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	if((TWSR_REG & STATUS_MASK) != ST_DATA_ACK && (TWSR_REG & STATUS_MASK) != ST_DATA_NACK && (TWSR_REG & STATUS_MASK) != ST_LAST_DATA_ACK){ //Check for ACK
		u8State = (TWSR_REG & STATUS_MASK);
	}
	return u8State;
}
/*
* brief: This function is used to receive data from the SDA line to the slave
* param.: (input) a pointer to a variable to hold the data that will be received
* param.: (input) the type of acknowledgement to send to the SDA line after receiving the data either ACK or NACK
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8SlaveGetData(uint8_t* data, ACKNOWLEDGEMENT acknowledgement){
	uint8_t u8State = I2C_OK;
	switch(acknowledgement){
		case ACK:
		TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		if((TWSR_REG & STATUS_MASK) != SR_DATA_ACK){
			u8State = (TWSR_REG & STATUS_MASK);
		}
		else{
			*data = TWDR_REG;
		}
		break;
		case NACK:
		TWCR_REG = (1 << TWINT) | (1 << TWEN);
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		if((TWSR_REG & STATUS_MASK) != SR_DATA_NACK){
			u8State = (TWSR_REG & STATUS_MASK);
		}
		else{
			*data = TWDR_REG;
		}
		break;
		default:
		u8State = I2C_ERR;
		break;
	}
	return u8State;

}
/*
* brief: This function is used to listen to the SDA line checking if Own slave address has be sent to the SDA line and receving the required action
* param.: (input) a pointer to a variable to hold the action that will be received either WRITE or READ
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
I2C_ERR_STATE I2C_u8SlaveListen(ACTION* action){
	
	uint8_t u8State = I2C_OK;
	TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	if((TWSR_REG & STATUS_MASK) == SR_SLA_ACK){
		*action = WRITE;
	}
	else if((TWSR_REG & STATUS_MASK) == ST_SLA_ACK){
		*action = READ;
	}
	else{
		u8State = (TWSR_REG & STATUS_MASK);
	}
	
	return u8State;
}
/*
* brief: This function is used to set own slave address
* param.: (input) the address that will be set
*/
void I2C_SetSlaveAddress(uint8_t address){
	
	TWAR_REG = (address << 1) & 0xFE;
}