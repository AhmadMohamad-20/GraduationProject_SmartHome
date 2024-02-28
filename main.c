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

uint8 m = 0;

void loginToSystem(void);

int main(void)
{

	KEYPAD_init();
	//LCD_init4bit();
	LCD_init_4bit();

	while(1)
	{
		loginToSystem();
	}
}

void loginToSystem(void)
{
	uint8 localButtonVal = 0;
	LCD_clearDisplay_4bit(LCD_DATA_PORT);
	LCD_sendString_4bit(LCD_DATA_PORT,"1 => ADMIN MODE");
	LCD_setCursorAt_4bit(LCD_DATA_PORT,LCD_ROW2,1);
	LCD_sendString_4bit(LCD_DATA_PORT,"2 => USER MODE");
	localButtonVal = KEYPAD_getValue();
	while (!(localButtonVal == '1' || localButtonVal == '2'))
	{
		localButtonVal = KEYPAD_getValue();
	}
	LCD_clearDisplay_4bit(LCD_DATA_PORT);
	//LCD_setCursorAt_4bit(LCD_DATA_PORT,8,LCD_ROW1);
	//LCD_sendString_4bit(LCD_DATA_PORT," PASSWORD");
	LCD_sendStringAtAddress_4bit(LCD_DATA_PORT,LCD_ROW1,5,"PASSWORD");

}
