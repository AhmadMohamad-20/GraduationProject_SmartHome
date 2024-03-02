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

uint8 ID[3] = {0};            // changed char to uint8
uint8 savedID[3] = {0};
uint8 password[4] = {0};
uint8 savedPassword[4] = {0};

static uint8 usersNum = 0;

static void registerPassWord(void);
static uint8 checkPassword(uint16 copy_u16EEPROM_PASS_Location);
static void adminLogIn(void);
static void userLogIn(void);
//static uint8 passwordCompare(void);
static uint8 checkUserID(void);
//static void checkUserPassword(void);

int main(void)
{
	/* initialize System */
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
	/* if there is no password for admin , it will :
 		- display "First time " for 1.5 sec 
   		- Insert Password for the first time
     	- Sign the admin using same password
    */

	if (*savedPassword == '\0')
	{
		LCD_clearDisplay_4bit();
		LCD_sendStringAtAddress_4bit(LCD_ROW1,2,"FIRST TIME !");
		_delay_ms(1500);
		registerPassWord();
		local_checkVal = checkPassword(ADMIN_PASSWORD);
		if (local_checkVal == INCORRECT_PASSWORD)
		{

		}
		else if (local_checkVal == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
		}
	}
	/* 
 	if there is  password for admin , it will :
    		- Sign the admin password 
      */
	else
	{
		local_checkVal = checkPassword(ADMIN_PASSWORD);
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

	/* Sign the user ID and Password */
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

	/* Check if the user ID is present or Not 
  		NOTE : THE ID has 3 Numbers
    	*/
	localCheck = checkUserID();
	if (localCheck == 0)
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("NOT FOUND !!!");
	}
	else
	{
			uint16 User_Password= USER1_PASSWORD -10 + 10*localCheck;
			checkPassword(User_Password);
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

static uint8 checkPassword (uint16 copy_u16EEPROM_PASS_Location)
{
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;
	uint8 local_counterCheck = 2;
	uint8 local_check = 0;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("PASSWORD : ");
	LCD_setCursorAt_4bit(LCD_ROW1,8);
	LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
	/* read the saved password from the eeprom */
	EEPROM_voidRead4Numbers(copy_u16EEPROM_PASS_Location,(uint8 *)savedPassword,MAX_SIZE_PASSWORD);
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
	/* compare the typed password with the stored password */
	local_check = strncmp(password, savedPassword, MAX_SIZE_PASSWORD);
	while ((local_check != 0) && (local_counterCheck))
	{
		/* DISPLAY INVALID PASSWORD AND ENTER PASSWORD AGAIN FOR 3 TIMES*/
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("INVALID PASSWORD");
		_delay_ms(1000);
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("PASSWORD : ");
		LCD_setCursorAt_4bit(LCD_ROW1,8);
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
/*
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
*/

void add_user(void)
{

	static uint8 usersCounter = 0;

	/* send by bluetooth to mobile app "Enter User ID"*/
	/*Read from mobile and save it in ID Array*/
	EEPROM_voidSend4Numbers( USER1_ID+10*usersCounter , ID , 4);
	/* send by bluetooth to mobile app "Enter User ID"*/
	/*Read from mobile and save it in password array*/
	EEPROM_voidSend4Numbers( USER1_PASSWORD+10*usersCounter , password , 4);
}


void RemoveUser(uint8* copy_userID)
{   /* this function deletes 8 consequent locations (ID + Password) in eeprom */
	uint8 i=0;
	uint8 local_temp_ID_Arr[4]={0}
	for(i=0;i<MAX_NUM_ID;i++)
	{
		EEPROM_voidRead4Numbers(USER1_ID+10*i ,local_temp_ID_Arr,4);
		/*check if id exist?*/
		if (strncmp(copy_userID, local_temp_ID_Arr, MAX_SIZE_PASSWORD)!=0 )
		{
			continue;
		}
		else
		{
			/*remove user id and password*/
			EEPROM_voidRemoveUser(USER1_ID+10*i);
			break;
		}
	}
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
