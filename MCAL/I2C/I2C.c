/*
 * I2C.c
 *
 * Created: 1/25/2022 8:34:52 PM
 *  Author: Khaled Ali
 */ 

#include "I2C.h"



void I2C_Init(void){
	CLR_BIT(TWSR_REG, TWPS0);
	CLR_BIT(TWSR_REG, TWPS1);
	TWBR_REG = ((I2C_F_CPU/SCL_CLK) - 16UL) / 2;
}
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

void I2C_Stop(void){
	TWCR_REG = (1 << TWINT) | (1 << TWSTO) | (1 <<	TWEN); // Send Start Condition
}
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

void I2C_SetSlaveAddress(uint8_t address){
	
	TWAR_REG = (address << 1) & 0xFE;
}