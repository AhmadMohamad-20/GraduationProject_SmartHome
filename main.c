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

char ID[3] = {0};
char savedID[3] = {0};
char password[4] = {0};
char savedPassword[4] = {0};

static uint8 usersNum = 0;

static void registerPassWord(void);
static uint8 checkPassword(void);
static void adminLogIn(void);
static void userLogIn(void);
static uint8 passwordCompare(void);
static uint8 checkUserID(void);
static void checkUserPassword(void);

int main(void)
{
	systemInit();
	//EEPROM_clearMemory();
	//EEPROM_writeString(ADMIN_PASSWORD,"ZOOBRY YA KOSOMAK");
	//savedPassword[0] = EEPROM_uint8ReadDataByte(ADMIN_PASSWORD);
	//EEPROM_voidRead4Numbers(ADMIN_PASSWORD, savedPassword, MAX_SIZE_PASSWORD);

	loginToSystem();

	while(1)
	{

	}
}

void systemInit(void)
{
	KEYPAD_init();
	LCD_init_4bit();
	EEPROM_INIT();
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
	uint8 local_checkVal = 0;
	EEPROM_voidRead4Numbers(ADMIN_PASSWORD,(uint8 *)savedPassword, MAX_SIZE_PASSWORD);
	if (*savedPassword == '\0')
	{
		LCD_clearDisplay_4bit();
		LCD_sendStringAtAddress_4bit(LCD_ROW1,2,"FIRST TIME !");
		_delay_ms(1500);
		registerPassWord();
		local_checkVal = checkPassword();
		if (local_checkVal == INCORRECT_PASSWORD)
		{

		}
		else if (local_checkVal == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
		}
	}
	else
	{
		local_checkVal = checkPassword();
		if (local_checkVal == INCORRECT_PASSWORD)
		{

		}
		else if (local_checkVal == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
		}
	}
}

static void userLogIn(void)
{
	uint8 localCheck = 0;
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("ID : ");
	LCD_setCursorAt_4bit(LCD_ROW1,6);
	LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
	for (; local_counter < MAX_NUM_ID; local_counter++)
	{
		local_buttonVal = KEYPAD_getValue();
		while ((local_buttonVal == NOT_PRESSED) || (local_buttonVal == '*') || (local_buttonVal == '#'))
		{
			local_buttonVal = KEYPAD_getValue();
		}
		ID[local_counter] = local_buttonVal;
		LCD_sendData_4bit(local_buttonVal);
	}
	localCheck = checkUserID();
	if (localCheck == 0)
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("NOT FOUND !!!");
	}
	else
	{
		checkUserPassword();
	}
}

static void registerPassWord(void)
{
	//char local_password[MAX_NUM_PASSWORD] = {};
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("ENTER A PASSWORD");
	LCD_setCursorAt_4bit(LCD_ROW2,6);
	LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
	for (; local_counter < MAX_NUM_PASSWORD; local_counter++)
	{
		local_buttonVal = KEYPAD_getValue();
		while ((local_buttonVal == NOT_PRESSED) || (local_buttonVal == '*') || (local_buttonVal == '#'))
		{
			local_buttonVal = KEYPAD_getValue();
		}
		password[local_counter] = local_buttonVal;
		LCD_sendData_4bit('*');
	}
	EEPROM_voidSend4Numbers(ADMIN_PASSWORD,(uint8 *)password,MAX_SIZE_PASSWORD);
}

static uint8 checkPassword(void)
{
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;
	uint8 local_counterCheck = 2;
	uint8 local_check = 0;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("ENTER PASSWORD");
	LCD_setCursorAt_4bit(LCD_ROW2,6);
	LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
	EEPROM_voidRead4Numbers(ADMIN_PASSWORD,(uint8 *)savedPassword,MAX_SIZE_PASSWORD);
	for (; local_counter < MAX_NUM_PASSWORD; local_counter++)
	{
		local_buttonVal = KEYPAD_getValue();
		while ((local_buttonVal == NOT_PRESSED) || (local_buttonVal == '*') || (local_buttonVal == '#'))
		{
			local_buttonVal = KEYPAD_getValue();
		}
		password[local_counter] = local_buttonVal;
		LCD_sendData_4bit('*');
	}
	local_check = strncmp(password, savedPassword, MAX_SIZE_PASSWORD);
	while ((local_check != 0) && (local_counterCheck))
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("ENTER PASSWORD");
		LCD_setCursorAt_4bit(LCD_ROW2,6);
		LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
		for (local_counter = 0; local_counter < MAX_NUM_PASSWORD; local_counter++)
		{
			local_buttonVal = KEYPAD_getValue();
			while ((local_buttonVal == NOT_PRESSED) || (local_buttonVal == '*') || (local_buttonVal == '#'))
			{
				local_buttonVal = KEYPAD_getValue();
			}
			password[local_counter] = local_buttonVal;
			LCD_sendData_4bit('*');
		}
		local_counterCheck--;
	}
	if (strncmp(password, savedPassword, MAX_SIZE_PASSWORD))
	{
		return INCORRECT_PASSWORD;
	}
	else
	{
		return CORRECT_PASSWORD;
	}
}

static uint8 checkUserID(void)
{
	uint8 local_counter = 0;
	uint8 localCheck = 0;
	if (usersNum == 0)
	{
		return 0;
	}
	else
	{
		for (; local_counter < usersNum; local_counter++)
		{
			EEPROM_voidRead4Numbers((USER1_ID + (0x10 * local_counter)),savedID, MAX_SIZE_ID);
			localCheck = strncmp(ID,savedID,MAX_SIZE_ID);
			if (localCheck != 0)
			{
				continue;
			}
			else
			{
				return (local_counter + 1);
			}
		}
		return 0;
	}
}

static void checkUserPassword(void)
{
	uint8 localCheck = 0;

	localCheck = checkPassword();
	if (localCheck == INCORRECT_PASSWORD)
	{

	}
	else if (localCheck == CORRECT_PASSWORD)
	{

	}
}
