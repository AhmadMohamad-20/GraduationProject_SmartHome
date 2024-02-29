/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: main.c
 * Date: 27 Feb 2024
 */

#include <util/delay.h>
#include <string.h>

#include "LIBRARIES/STD_Types.h"
#include "LIBRARIES/bitmath.h"

//#include "MCAL/DIO/DIO_Interface.h"
//#include "MCAL/IIC/IIC_Interface.h"
#include "HAL/KEYPAD/KEYPAD_Interfacing.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "main.h"

uint8 m = 0;



int main(void)
{
	systemInit();
	loginToSystem();
	while(1)
	{

	}
}

void systemInit(void)
{
	KEYPAD_init();
	LCD_init_4bit();
	EEPROM_init();
}

void loginToSystem(void)
{
	uint8 localButtonVal = 0;
	uint8 selector = 0;
	uint8 counter = 0;
	uint8 passwordCheck = 3;
	char password[4] = {0};
	char savedPassword[4] = {0};

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("1 => ADMIN MODE");
	LCD_setCursorAt_4bit(LCD_ROW2,1);
	LCD_sendString_4bit("2 => USER MODE");
	selector = KEYPAD_getValue();
	while (!(selector == '1' || selector == '2'))
	{
		selector = KEYPAD_getValue();
	}
	/*
	LCD_clearDisplay_4bit(LCD_DATA_PORT);
	LCD_setCursorAt_4bit(LCD_DATA_PORT,LCD_ROW1,4);
	LCD_sendString_4bit(LCD_DATA_PORT," PASSWORD");
	LCD_setCursorAt_4bit(LCD_DATA_PORT,LCD_ROW2,6);
	LCD_sendCommand_4bit(LCD_DATA_PORT,DISPLAY_CURSOR_BLINKING_ON);
	for (;counter < 4; counter++)
	{
		localButtonVal = KEYPAD_getValue();
		while (((localButtonVal == BUTTON_NOT_PRESSED) || (localButtonVal == '*') || (localButtonVal == '#')))
		{
			localButtonVal = KEYPAD_getValue();
		}
		password[counter] = localButtonVal;
		LCD_sendData_4bit(LCD_DATA_PORT,'*');
	}
	*/
	if (selector == ADMIN_SELECTED)
	{
		if (EEPROM_uint8ReadDataByte(ADMIN_PASSWORD_LOCATION) == 0xFF)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("FIRST TIME !!!");
			_delay_ms(500);
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("ENTER PASSWORD");
			LCD_setCursorAt_4bit(LCD_ROW2,6);
			LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
			localButtonVal = KEYPAD_getValue();
			while (((localButtonVal == BUTTON_NOT_PRESSED) || (localButtonVal == '*') || (localButtonVal == '#')))
			{
				localButtonVal = KEYPAD_getValue();
			}
			password[counter] = localButtonVal;
			EEPROM_voidSendString(ADMIN_PASSWORD_LOCATION,password);
		}
		else
		{
			EEPROM_voidRead4Numbers(ADMIN_PASSWORD_LOCATION,savedPassword);
			LCD_clearDisplay_4bit();
			LCD_setCursorAt_4bit(LCD_ROW1,4);
			LCD_sendString_4bit("PASSWORD");
			LCD_setCursorAt_4bit(LCD_ROW2,6);
			LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
			while (passwordCheck)
			{
				for (counter = 0;counter < 4; counter++)
				{
					localButtonVal = KEYPAD_getValue();
					while (((localButtonVal == BUTTON_NOT_PRESSED) || (localButtonVal == '*') || (localButtonVal == '#')))
					{
						localButtonVal = KEYPAD_getValue();
					}
					password[counter] = localButtonVal;
					LCD_sendData_4bit('*');
				}
				if (strcmp(password,savedPassword))
				{
					passwordCheck--;
				}
				else
				{
					break;
				}
			}
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
		}
	}
	else if (selector == USER_SELECTED)
	{

	}


}
