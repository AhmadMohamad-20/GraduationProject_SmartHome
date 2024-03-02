/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TWI_Program.c
 * Date: 10 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"
#include "TWI_Register.h"
#include "TWI_Config.h"
#include "TWI_Private.h"
#include "TWI_Interface.h"


/*Set master address to 0 if master will not be addressed*/
void TWI_InitMaster(uint8 Copy_uint8Address)
{
	/*set prescaler */
	CLEAR_BIT(TWSR,TWSR_TWPS0);
	CLEAR_BIT(TWSR,TWSR_TWPS1);

	/*Clear status code*/
	TWSR &=0x07;

	/*set bit rate to get SCL =400KHz*/
	TWBR=62;

	/*Check if the master node will be addressed*/
	if(Copy_uint8Address !=0)
	{
		/*Set the required address in the 7 MSB of TWAR*/
		TWAR= Copy_uint8Address<<1;
	}
	else
	{
		/* Do Nothing */

	}

	/*Enable Acknowledge*/
//	SETBIT(TWCR,TWCR_TWEA);      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}


void TWI_InitSlave(uint8 Copy_uint8Address)
{
	/*Set the Slave address in the 7 MSB of TWAR*/
	TWAR= Copy_uint8Address<<1;

	/*Enable Acknowledge*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}


TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*send start condition*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	/*Check value of TWI Status Register*/
	if ((TWSR & 0xF8) != START_ACK)
	{
		LocalErrorStatus=StartConditionErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return LocalErrorStatus;
}


TWI_ErrStatus TWI_SendRepeatedStart(void)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	/*send start condition*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	/*Check value of TWI Status Register*/
	if ((TWSR & 0xF8) != REP_START_ACK)
	{
		LocalErrorStatus=RepeatedStartError;
	}
	else
	{
		/*Do Nothing*/
	}
	return LocalErrorStatus;
}


TWI_ErrStatus TWI_SendSlaveAddressWithWrite(uint8 Copy_uint8SlaveAddress)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	/*send slave address*/
	TWDR=Copy_uint8SlaveAddress<<1;
	/*send write request*/
	CLEAR_BIT(TWDR,0);
	/*Clear the start condition bit*/
	CLEAR_BIT(TWCR,TWCR_TWSTA);
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	if( (TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK)
	{
		LocalErrorStatus=SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do Nothing*/
	}

	return LocalErrorStatus;
}


TWI_ErrStatus TWI_SendSlaveAddressWithRead(uint8 Copy_uint8SlaveAddress)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	/*send slave address*/
	TWDR=Copy_uint8SlaveAddress<<1;
	/*send write request*/
	SET_BIT(TWDR,0);
	/*Clear the start condition bit*/
	CLEAR_BIT(TWCR,TWCR_TWSTA);
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	if( (TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK)
	{
		LocalErrorStatus= SlaveAddressWithReadErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return LocalErrorStatus;
}


TWI_ErrStatus TWI_MasterWriteDataByte(uint8 Copy_uint8DataByte)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	TWDR= Copy_uint8DataByte;

	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	if( (TWSR & 0xF8) != MSTR_WR_BYTE_ACK)
	{
		LocalErrorStatus= MasterWriteByteErr ;
	}
	else
	{
		/*Do Nothing*/
	}
	return LocalErrorStatus;

}


TWI_ErrStatus TWI_MasterReadDataByte(uint8* Copy_puint8DataByte)
{
	TWI_ErrStatus LocalErrorStatus= NoError;
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait for TWINT Flag set*/
	while( (GET_BIT(TWCR,TWCR_TWINT))  == 0);
	//*Copy_puint8DataByte=TWDR;
	if( (TWSR & 0xF8) != MSTR_RD_BYTE_WITH_NACK)
	{
		LocalErrorStatus= MasterReadByteErr ;
	}
	else
	{
		*Copy_puint8DataByte=TWDR;
	}
	return LocalErrorStatus;
}

void TWI_SendStopCondition(void)
{
	/*send stop condition*/
	SET_BIT(TWCR,TWCR_TWSTO);
	/*Clear TWINT flag*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

void DisableAck(void)
{
	/*Disable Acknowledge*/
	CLEAR_BIT(TWCR,TWCR_TWEA);
}
void EnableAck(void)
{
	/*Enable Acknowledge*/
	SET_BIT(TWCR,TWCR_TWEA);
}
