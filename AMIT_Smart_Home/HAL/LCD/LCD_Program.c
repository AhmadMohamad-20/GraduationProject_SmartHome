/*
 * LCD_Program.c
 *
 *  Created on: 10 Dec 2023
 *      Author: user
 */
#include <util/delay.h>
#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "LCD_cfg.h"
#include "LCD_Private.h"
#include "LCD_Interface.h"

static char string[3] = "000";

static uint8 DIO_set4bitsValue(uint8 copy_DIO_value);
static void convertNumToString(uint8 copy_num);

void LCD_init4bit(void)
{
	DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN0,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN1,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN2,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN3,OUTPUT);

	DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT);
	DIO_setPinDirection(LCD_CONTROL_PORT,LCD_ENABLE_PIN,OUTPUT);
}
uint8 LCD_sendCommand_4bit(uint8 copy_LCD_command)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_set4bitsValue((copy_LCD_command >> 4));

	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	local_errorSignal = DIO_set4bitsValue(copy_LCD_command);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	return local_errorSignal;
}

uint8 LCD_sendData_4bit(uint8 copy_LCD_data)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,LOW);
	local_errorSignal = DIO_set4bitsValue((copy_LCD_data >> 4));

	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);

	local_errorSignal = DIO_set4bitsValue(copy_LCD_data);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,HIGH);
	_delay_ms(2);
	local_errorSignal = DIO_setPinValue(LCD_CONTROL_PORT,LCD_ENABLE_PIN,LOW);
	return local_errorSignal;

}

uint8 LCD_init_4bit(void)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN0,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN1,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN2,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_DATA_PORT,LCD_DATA_4BIT_PIN3,OUTPUT);

	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT);
	local_errorSignal = DIO_setPinDirection(LCD_CONTROL_PORT,LCD_ENABLE_PIN,OUTPUT);
	_delay_ms(35);
	local_errorSignal = LCD_sendCommand_4bit((FUNCTION_SET_4BIT >> 4));
	local_errorSignal = LCD_sendCommand_4bit(FUNCTION_SET_4BIT);
	local_errorSignal = LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING);
	local_errorSignal = LCD_sendCommand_4bit(DISPLAY_CLEAR);
	local_errorSignal = LCD_sendCommand_4bit(ENTRY_MODE);
	local_errorSignal = LCD_sendCommand_4bit(PORT_LOW);

	return local_errorSignal;

}

uint8 LCD_sendDataAtAddress_4bit(uint8 copy_LCD_row, uint8 copy_LCD_column,uint8 copy_LCD_data)
{
		uint8 local_errorSignal = OK_STAT;

		if (copy_LCD_column <= 16)
		{
			copy_LCD_column--;
			switch (copy_LCD_row)
			{
				case 1:
					local_errorSignal = LCD_sendCommand_4bit((LCD_DDRAM_ROW1 + copy_LCD_column));
					break;
				case 2:
					local_errorSignal = LCD_sendCommand_4bit((LCD_DDRAM_ROW2 + copy_LCD_column));
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
			local_errorSignal = LCD_sendData_4bit(copy_LCD_data);
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}

		return local_errorSignal;
}

uint8 LCD_sendString_4bit(const char *copy_LCD_str)
{
	uint8 local_errorString = OK_STAT;
	for (;*copy_LCD_str;copy_LCD_str++)
	{
		local_errorString = LCD_sendData_4bit(*copy_LCD_str);
	}
	return local_errorString;
}

uint8 LCD_sendStringAtAddress_4bit(uint8 copy_LCD_row, uint8 copy_LCD_column,const char *copy_LCD_string)
{
	uint8 local_errorSignal = OK_STAT;

	if (copy_LCD_column <= 16)
	{
		copy_LCD_column--;
		switch (copy_LCD_row)
		{
		case 1:
			local_errorSignal = LCD_sendCommand_4bit((LCD_DDRAM_ROW1 + copy_LCD_column));
			break;
		case 2:
			local_errorSignal = LCD_sendCommand_4bit((LCD_DDRAM_ROW2 + copy_LCD_column));
			break;
		default:
			local_errorSignal = NOT_OK_STAT;
			break;
		}
		local_errorSignal = LCD_sendString_4bit(copy_LCD_string);
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	return local_errorSignal;
}

StdReturnType LCD_sendNumber_4Bit(uint8 copy_LCD_num)
{
	convertNumToString(copy_LCD_num);
	LCD_sendString_4bit(string);
}

StdReturnType LCD_sendNumberAtAddress_4Bit(uint8 copy_LCD_row, uint8 copy_LCD_column, uint8 copy_LCD_num)
{
	convertNumToString(copy_LCD_num);
	LCD_sendStringAtAddress_4bit(copy_LCD_row, copy_LCD_column,string);
}

StdReturnType LCD_clearDisplay_4bit(void)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = LCD_sendCommand_4bit(DISPLAY_CLEAR);
	local_errorSignal = LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING);
	LCD_sendCommand_4bit(LCD_DDRAM_ROW1);

	return local_errorSignal;
}

StdReturnType LCD_setCursorAt_4bit(uint8 copy_LCD_row, uint8 copy_LCD_col)
{
	StdReturnType local_errorSignal = OK_STAT;

	if (copy_LCD_col <= 16)
	{
		copy_LCD_col--;
		switch (copy_LCD_row)
		{
		case LCD_ROW1:
			LCD_sendCommand_4bit((LCD_DDRAM_ROW1 + copy_LCD_col));
			break;
		case LCD_ROW2:
			LCD_sendCommand_4bit((LCD_DDRAM_ROW2 + copy_LCD_col));
			break;
		default:
			local_errorSignal = NOT_OK_STAT;
		}
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	return local_errorSignal;
}

static uint8 DIO_set4bitsValue(uint8 copy_DIO_value)
{
	uint8 local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(LCD_DATA_PORT,LCD_DATA_4BIT_PIN0,GET_BIT(copy_DIO_value,0));
	local_errorSignal = DIO_setPinValue(LCD_DATA_PORT,LCD_DATA_4BIT_PIN1,GET_BIT(copy_DIO_value,1));
	local_errorSignal = DIO_setPinValue(LCD_DATA_PORT,LCD_DATA_4BIT_PIN2,GET_BIT(copy_DIO_value,2));
	local_errorSignal = DIO_setPinValue(LCD_DATA_PORT,LCD_DATA_4BIT_PIN3,GET_BIT(copy_DIO_value,3));
	return local_errorSignal;
}

static void convertNumToString(uint8 copy_num)
{
	for(uint8 counter = 2; copy_num != 0; copy_num /= 10 , counter--)
	{
		string[counter] = (copy_num % 10) + '0';
	}
}
