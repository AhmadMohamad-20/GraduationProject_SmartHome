/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: EEPROM_Program.c
 * Date: 12 Feb 2024
 */

#include <util/delay.h>
#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/IIC/TWI_Interface.h"

#include "EEPROM_Private.h"
#include "EEPROM_Interface.h"

void EEPROM_init(void)
{
	TWI_initMasterWithoutAddress();
}

void EEPROM_writeDataByte(uint16 copy_EEPROM_address, uint8 copy_EEPROM_data)
{
	uint8 local_address = EEPROM_FIXED_ADDRESS  | (A2_ADDRESS << 2) | (A1_ADDRESS << 1) | (A0_ADDRESS) | (copy_EEPROM_address >> 8);
	TWI_sendStartCondition();
	TWI_sendSlaveAddressAndStatWrite(local_address);
	TWI_sendDataByteMaster((uint8)copy_EEPROM_address);
	TWI_sendDataByteMaster(copy_EEPROM_data);
	TWI_sendStopCondition();
	_delay_ms(10);
}
uint8 EEPROM_readDataByte(uint16 copy_EEPROM_address)
{
	uint8 local_data = 0;
	uint8 local_address = EEPROM_FIXED_ADDRESS  | (A2_ADDRESS << 2) | (A1_ADDRESS << 1) | (A0_ADDRESS) | (copy_EEPROM_address >> 8);
	TWI_sendStartCondition();
	TWI_sendSlaveAddressAndStatWrite(local_address);
	TWI_sendDataByteMaster((uint8)copy_EEPROM_address);
	TWI_recieveDataByteMaster(&local_data);
	TWI_sendStopCondition();
	return local_data;
}

void EEPROM_deleteByte(uint16 copy_EEPROM_address)
{
	EEPROM_writeDataByte(copy_EEPROM_address,0xFF);
}

void EEPROM_writeString(uint16 cop_EEPROM_address, char *copy_EEPROM_ptr)
{
	//uint8 counter = 0;
	while (*copy_EEPROM_ptr != '\0')
	{
		EEPROM_writeDataByte(cop_EEPROM_address,*copy_EEPROM_ptr);
		cop_EEPROM_address++;
		copy_EEPROM_ptr++;

	}
}

void EEPROM_readString(uint16 copy_EEPROM_ADDRESS, char *copy_EEPROM_ptr)
{
	uint8 byteVal = 0;
	if (copy_EEPROM_ptr != NULL)
	{
		byteVal = EEPROM_readDataByte(copy_EEPROM_ADDRESS);
		while (byteVal == 0xFF)
		{
			*copy_EEPROM_ptr = byteVal;
			copy_EEPROM_ptr++;
			copy_EEPROM_ADDRESS++;
			byteVal = EEPROM_readDataByte(copy_EEPROM_ADDRESS);
		}
	}
	else
	{

	}

}
