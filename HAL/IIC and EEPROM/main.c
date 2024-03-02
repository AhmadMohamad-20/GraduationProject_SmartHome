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
#include "main.h"
uint8 UArray[4]="FKKK";

uint8 User1_ID_Array[4]="1111";
uint8 User1_Pass_Array[4]="2222";
uint8 User2_ID_Array[4]="3333";
uint8 User2_Pass_Array[4]="4444";
uint8 User3_ID_Array[4]="5555";
uint8 User3_Pass_Array[4]="6666";
void add_user(void);
void RemoveUser(uint8* copy_userID);

int main (void)
{

	EEPROM_INIT();
	EEPROM_voidSend4Numbers(0x9C,UArray);
/*	add_user();
	add_user();
	add_user();
	_delay_ms(1000);
	RemoveUser(User1_ID_Array);
	_delay_ms(1000);
	RemoveUser(User2_ID_Array);
	_delay_ms(1000);
	RemoveUser(User3_ID_Array);
*/
	while(1)
	{

	}
	return 0;
}


void add_user(void)
{

	static uint8 usersCounter = 0;
	switch (usersCounter)
	{
	case 0:
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Array*/
		EEPROM_voidSend4Numbers(USER1_ID,User1_ID_Array);
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Pass*/
		EEPROM_voidSend4Numbers(USER1_PASS,User1_Pass_Array);
		usersCounter++;
		break;
	case 1:
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Array*/
		EEPROM_voidSend4Numbers(USER2_ID,User2_ID_Array);
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Pass*/
		EEPROM_voidSend4Numbers(USER2_PASS,User2_Pass_Array);
		usersCounter++;
		break;
	case 2:
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Array*/
		EEPROM_voidSend4Numbers(USER3_ID,User3_ID_Array);
		/* send by bluetooth to mobile app "Enter User ID"*/
		/*Read from mobile and save it in User1_ID_Pass*/
		EEPROM_voidSend4Numbers(USER3_PASS,User3_Pass_Array);
		usersCounter++;
		break;
	default:
		/*send by bluetooth "you have reached maximum number of users"*/
		break;
	}
}

void RemoveUser(uint8* copy_userID)
{
	uint8* localID=copy_userID;
		if(localID[0]==EEPROM_uint8ReadDataByte(USER1_ID) &&\
			localID[1]==EEPROM_uint8ReadDataByte(USER1_ID+1)&&\
			localID[2]==EEPROM_uint8ReadDataByte(USER1_ID+2)&&\
			localID[3]==EEPROM_uint8ReadDataByte(USER1_ID+3))
		{
			EEPROM_voidRemoveUser(USER1_ID);
		}
		else if(localID[0]==EEPROM_uint8ReadDataByte(USER2_ID) &&\
			localID[1]==EEPROM_uint8ReadDataByte(USER2_ID+1)&&\
			localID[2]==EEPROM_uint8ReadDataByte(USER2_ID+2)&&\
			localID[3]==EEPROM_uint8ReadDataByte(USER2_ID+3))
		{
			EEPROM_voidRemoveUser(USER2_ID);
		}
		else if(localID[0]==EEPROM_uint8ReadDataByte(USER3_ID) &&\
				localID[1]==EEPROM_uint8ReadDataByte(USER3_ID+1)&&\
				localID[2]==EEPROM_uint8ReadDataByte(USER3_ID+2)&&\
				localID[3]==EEPROM_uint8ReadDataByte(USER3_ID+3))
			{
				EEPROM_voidRemoveUser(USER3_ID);
			}
		else
		{
			/*Send by uart "ID does not exist"*/
		}
}
/*
uint8 arr_S[4]={8,16,32,64};
uint8 arr_R[4];
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
EEPROM_voidCLear4Locations(0x90);
EEPROM_voidCLear4Locations(0x94);
*/
