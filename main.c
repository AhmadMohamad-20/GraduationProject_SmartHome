/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: main.c
 * Date: 27 Feb 2024
 */
#include "LIBRARIES/STD_Types.h"
#include "LIBRARIES/bitmath.h"

#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/KEYPAD/KEYPAD_Interfacing.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "main.h"
uint8 m = 0;



int main(void)
{

	KEYPAD_init();
	//LCD_init4bit();
	LCD_init_4bit();

	loginToSystem();
	while(1)
	{

	}
}

void loginToSystem(void)
{
	uint8 localButtonVal = 0;
	uint8 selector = 0;
	uint8 counter = 0;
	char password[4] = {0};
	char savedPassword[4] = {0};

	LCD_clearDisplay_4bit(LCD_DATA_PORT);
	LCD_sendString_4bit(LCD_DATA_PORT,"1 => ADMIN MODE");
	LCD_setCursorAt_4bit(LCD_DATA_PORT,LCD_ROW2,1);
	LCD_sendString_4bit(LCD_DATA_PORT,"2 => USER MODE");
	selector = KEYPAD_getValue();
	while (!(selector == '1' || selector == '2'))
	{
		selector = KEYPAD_getValue();
	}
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
	if (selector == 1)
	{
		EEPROM_voidRead4Numbers(0X4545,savedPassword);
	}
	else if (selector == 2)
	{

	}
}
