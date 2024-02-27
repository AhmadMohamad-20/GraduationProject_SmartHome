/*
 * main.c
 *
 *  Created on: Jan 24, 2024
 *      Author: hp
 */
#include <util/delay.h>
#include "STD.h"
#include "EEPROM_Interface.h"
#include "IIC_Interface.h"
#include "DIO_Interface.h"

int main (void)
{
	char arr_S[4]={8,16,32,64};
	char arr_R[4];
	uint8 Local_uint8ReceivedData;
	DIO_SetPortDirection(DIO_PORTD,PORT_OUTPUT);
	DIO_SetPortDirection(DIO_PORTB,PORT_OUTPUT);
	DIO_SetPortDirection(DIO_PORTA,PORT_OUTPUT);


	TWI_InitMaster(0);
	EEPROM_voidSendDataByte(0x10, 0x55);
	EEPROM_voidSendDataByte(0x11, 0x66);
	Local_uint8ReceivedData = EEPROM_uint8ReadDataByte(0x10);

	DIO_SetPortValue(DIO_PORTD , Local_uint8ReceivedData);
	Local_uint8ReceivedData = EEPROM_uint8ReadDataByte(0x11);
	DIO_SetPortValue(DIO_PORTB , Local_uint8ReceivedData);

	EEPROM_voidSend4Numbers(0x30,arr_S);
	EEPROM_voidRead4Numbers(0x30,arr_R);
	int j=0;
	for(j=0;j<4;j++)
	{
		DIO_SetPortValue(DIO_PORTA,arr_R[j]);
		_delay_ms(1000);

	}

	while(1)
	{

	}
	return 0;
}
