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

#include "HAL/KEYPAD/KEYPAD_Interfacing.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "main.h"

static void EnterPassWord(char *copy_passwordPtr);
static void adminLogIn(void);
static void userLogIn(void);

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
	static uint8 selector = 0;

	/* Choose who will sign => User or Admin*/
	LCD_clearDisplay_4bit();
	LCD_sendStringAtAddress_4bit(LCD_ROW1,3,"WELCOME !!");
	_delay_ms(1500);
	LCD_clearDisplay_4bit();
	LCD_sendStringAtAddress_4bit(LCD_ROW1,1,"1 => ADMIN LOG");
	LCD_sendStringAtAddress_4bit(LCD_ROW2,1,"2 => USER LOG");
	selector = KEYPAD_getValue();
	while (!((selector == ADMIN_SELECTED) || (selector == USER_SELECTED)))
	{
		selector = KEYPAD_getValue();
	}
	switch (selector)
	{
	case ADMIN_SELECTED:
		adminLogIn();
		break;
	case USER_SELECTED:
		userLogIn();
		break;
	default:
		break;
	}
}

static void adminLogIn(void)
{
	char local_savedPassword[4] = {};
	char local_password[4] = {};
	EEPROM_readString(ADMIN_PASSWORD,local_savedPassword);
	if (local_savedPassword[1] == '\0')
	{
		LCD_clearDisplay_4bit();
		LCD_sendStringAtAddress_4bit(LCD_ROW1,2,"FIRST TIME !");
		_delay_ms(1500);
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("ENTER A PASSWORD");
		LCD_setCursorAt_4bit(LCD_ROW2,6);
		LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING);
		EnterPassWord(local_password);
	}
	else
	{

	}
}

static void userLogIn(void)
{

}

static void EnterPassWord(char *copy_passwordPtr)
{
	char local_password[MAX_NUM_PASSWORD] = {};
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;

	for (; local_counter < MAX_NUM_PASSWORD; local_counter++)
	{
		local_buttonVal = KEYPAD_getValue();
		while ((local_buttonVal == NOT_PRESSED) || (local_buttonVal == '*') || (local_buttonVal == '#'))
		{
			local_buttonVal = KEYPAD_getValue();
		}
		local_password[local_counter] = local_buttonVal;
	}
}
