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


void TWI_initMasterWithoutAddress(void)
{
	/*set speed to 400 kHz*/
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
	TWBR = 12;

	/*enabling acknowledge bit*/
	SET_BIT(TWCR,TWEA);

	/*enabling TWI*/
	SET_BIT(TWCR,TWEN);
}

void TWI_initMasterWithAddress(uint8 copy_TWI_Address)
{
	/*Putting an address*/
	TWAR = copy_TWI_Address;

	/*set speed to 400 kHz*/
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
	TWBR = 12;

	/*enabling acknowledge bit*/
	SET_BIT(TWCR,TWEN);

	/*enabling TWI*/
	SET_BIT(TWCR,TWEN);
}

void TWI_sendStartCondition(void)
{
	/* enable start bit */
	SET_BIT(TWCR,TWSTA);
	/* clear interrupt */
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);


	while(STATUS_MODE != START_CONDITION_STATUS);
}

void TWI_sendRepeatedStartCondition(void)
{
	/* enable start bit */
	SET_BIT(TWCR,TWSTA);
	/* clear interrupt */
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);

	while(STATUS_MODE != REPEATED_CONDITION_STATUS);
}

void TWI_sendStopCondition(void)
{
	/* enable start bit */
	SET_BIT(TWCR,TWSTO);
	/* clear interrupt */
//	while(GET_BIT(TWCR,TWINT) == 0);
//	SET_BIT(TWCR,TWINT);
}

uint8 TWI_sendSlaveAddressAndStatWrite(uint8 copy_TWI_slaveAddress)
{
	uint8 local_errorCheck = NOT_OK_STAT;
	TWDR = (copy_TWI_slaveAddress << 1);
	CLEAR_BIT(TWDR,0);
	CLEAR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);

	if (STATUS_MODE == SLAVE_ADDRESS_WRITE_ACK)
	{
		local_errorCheck = OK_STAT;
	}
	else if (STATUS_MODE == SLAVE_ADDRESS_WRITE_NACK)
	{
		/* Nothing */
	}
	return local_errorCheck;

}
void TWI_sendSlaveAddressAndStatRead(uint8 copy_TWI_slaveAddress)
{
	TWDR = (copy_TWI_slaveAddress << 1);
	SET_BIT(TWDR,0);
	CLEAR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);

	if (STATUS_MODE == SLAVE_ADDRESS_WRITE_ACK);
	else if (STATUS_MODE == SLAVE_ADDRESS_WRITE_NACK);
}

void TWI_sendDataByteMaster(uint8 copy_TWI_dataByte)
{
	TWDR = copy_TWI_dataByte;
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);

	if (STATUS_MODE == MSTR_WR_BYTE_ACK);
}
void TWI_recieveDataByteMaster(uint8 *copy_TWI_dataBytePtr)
{
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);

	if (STATUS_MODE == MSTR_RD_BYTE_WITH_ACK)
	{
		*copy_TWI_dataBytePtr = TWDR;
	}
	else
	{
		/* NOTHING */
	}

}

void TWI_initSlave(uint8 copy_TWI_slaveAddress)
{
	TWAR = (copy_TWI_slaveAddress << 1);
	/*enabling acknowledge bit*/
	SET_BIT(TWCR,TWEA);

	/*enabling TWI*/
	SET_BIT(TWCR,TWEN);
}
void TWI_sendDataByteSlave(uint8 copy_TWI_dataByte)
{

}
void TWI_recieveDataByteSlave(uint8 *copy_TWI_dataBytePtr)
{

}
uint8 TWI_checkIfCalled(void)
{
//A8   60
	uint8 local_checkValue = FALSE;
	while(GET_BIT(TWCR,TWINT) == 0);
	SET_BIT(TWCR,TWINT);
	if ((STATUS_MODE != 0xA8) && (STATUS_MODE != 0x60))
	{
		/* Nothing */
	}
	else
	{
		local_checkValue = TRUE;
	}
	return local_checkValue;
}
