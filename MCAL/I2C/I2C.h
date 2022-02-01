/*
 * I2C.h
 *
 * Created: 1/25/2022 8:34:37 PM
 *  Author: Khaled Ali
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#define I2C_F_CPU 8000000UL
#define SCL_CLK	  200000UL
/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

//Status 
#define MT_ARB_LOST   0x38
#define MR_ARB_LOST   0x38
#define START         0x08
#define REP_START     0x10
#define MT_SLA_ACK    0x18
#define MT_DATA_ACK   0x28
#define MR_DATA_NOT_ACK  0x58
#define MR_SLA_NOT_ACK   0x48
#define MT_SLA_NOT_ACK   0x20
#define MT_DATA_NOT_ACK  0x30
#define MR_DATA_ACK   0x50
#define MR_SLA_ACK    0x40
#define SR_SLA_ACK		0x60
#define ST_SLA_ACK		0xA8
#define SR_DATA_ACK		0x80
#define SR_DATA_NACK	0x88
#define ST_DATA_ACK		0xB8
#define ST_DATA_NACK	0xC0
#define ST_LAST_DATA_ACK	0xC8


#define STATUS_MASK 0xF8
typedef enum{
	WRITE,
	READ	
}ACTION;
typedef enum{
	I2C_ERR,
	I2C_OK
}I2C_ERR_STATE;

typedef enum{
	NACK,
	ACK	
}ACKNOWLEDGEMENT;
void I2C_Init(void);

I2C_ERR_STATE I2C_u8Start(uint8_t address, ACTION action);

void I2C_Stop(void);

I2C_ERR_STATE I2C_u8MasterSendData(uint8_t data);

I2C_ERR_STATE I2C_u8MasterGetData(uint8_t* data, ACKNOWLEDGEMENT acknowledgement);

I2C_ERR_STATE I2C_u8SlaveSendData(uint8_t data);

I2C_ERR_STATE I2C_u8SlaveGetData(uint8_t* data, ACKNOWLEDGEMENT acknowledgement);

I2C_ERR_STATE I2C_u8SlaveListen(ACTION* action);

void I2C_SetSlaveAddress(uint8_t address);


#endif /* I2C_H_ */