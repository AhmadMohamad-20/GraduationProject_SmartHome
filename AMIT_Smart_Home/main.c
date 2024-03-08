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
#include "MCAL/UART/UART_interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/KEYPAD/KEYPAD_Interfacing.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/BLUETOOTH_MODULE/BM_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "HAL/TEMPERATURE_SENSOR/TS_Interface.h"
#include "HAL/RTOS/RTOS_Interface.h"
#include "HAL/ServoMotor/SM_Interface.h"
#include "HAL/DC_MOTOR/DCM_Interface.h"
#include "HAL/DIMMER/DIM_Interface.h"
#include "HAL/BUZZER/BUZZER_Interface.h"
#include "main.h"

uint8 ID[3] = {0};
uint8 savedID[3] = {0};
uint8 password[4] = {0};
uint8 savedPassword[4] = {0};
static uint8 usersNum = 0;
static uint8 selector = 0;
static uint8 checkk = 0;

static uint8 checkLatestUser(void);
static void registerPassWord(void);
static void registerAdminPassWord(void);
static uint8 checkPassword(uint16 copy_u16EEPROM_PASS_Location);
static uint8 checkPasswordAdmin(uint16 copy_u16EEPROM_PASS_Location);
void loginToSystem (void);
static void adminLogIn(void);
static void userLogIn(void);
static uint8 checkUserID(void);
static void adminSetupMode(void);
static void ac_control(void);
static void door_control(void);
static void led_control(void);
static void led_control_UART(void);

int main(void)
{
	/* initialize System */
	systemInit();
	loginToSystem();
	if (checkk == CORRECT_PASSWORD)
	{
		showOptions();
		RTOS_start();
		while(1);
	}
	else if (checkk == INCORRECT_PASSWORD)
	{
		BUZZER_ON();
	}
	//SM_rotateAngle(50);
	//_delay_ms(1550);
	//SM_rotateAngle(70);
}

void systemInit(void)
{
	UART_Init();
	KEYPAD_init();
	LCD_init_4bit();
	EEPROM_INIT();
	RTOS_init();
	//RTOS_addTask(1,50,0,adminSetupModeCheck);
	RTOS_addTask(1,1,0,adminSetupModeCheck);
	RTOS_addTask(2,1,0,ac_control);
	RTOS_addTask(3,1,0,led_controlCheck);
	RTOS_addTask(4,1,0,led_controlAdminCheck);
	RTOS_addTask(5,1,0,door_controlCheck);

	TS_init();
	LED_init(LED1_PORT,LED1_PIN);
	LED_init(LED2_PORT,LED2_PIN);
	LED_init(LED3_PORT,LED3_PIN);
	LED_init(LED4_PORT,LED4_PIN);
	LED_init(LED5_PORT,LED5_PIN);
	LED_init(LED6_PORT,LED6_PIN);
	BUZZER_init();
}

void loginToSystem(void)
{
	/* Choose who will sign => User or Admin */
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

void showOptions(void)
{
	switch (selector)
	{
	case ADMIN_SELECTED:
		RTOS_suspendTask(3);
		LCD_clearDisplay_4bit();
		LCD_sendStringAtAddress_4bit(LCD_ROW1,3,"OPTIONS !!");
		_delay_ms(1500);
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("1=>SETUP");
		LCD_sendStringAtAddress_4bit(1,11,"2=>LED");
		LCD_sendStringAtAddress_4bit(2,1,"3=>DOOR");
		break;

	case USER_SELECTED:
		RTOS_suspendTask(1);
		RTOS_suspendTask(4);
		RTOS_suspendTask(5);
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("TO CONTROL LED => 1");
		break;
	}

}

static uint8 checkLatestUser(void)
{
	uint8 local_latestUser = 0;

	while (EEPROM_uint8ReadDataByte((USER1_ID + 0x10 * local_latestUser)) != 0xFF)
	{
		local_latestUser++;
	}

	return local_latestUser;
}

static void adminLogIn(void)
{

	EEPROM_voidRead4Numbers(ADMIN_PASSWORD, savedPassword, MAX_SIZE_PASSWORD);

	/* if there is no password for admin , it will :
 		- display "First time " for 1.5 sec 
   		- Insert Password for the first time
     	- Sign the admin using same password
    */

	if (*savedPassword == 0xFF)
	{
		LCD_clearDisplay_4bit();
		LCD_sendStringAtAddress_4bit(LCD_ROW1,2,"FIRST TIME !");
		_delay_ms(1500);
		registerAdminPassWord();
		checkk = checkPasswordAdmin(ADMIN_PASSWORD);
		if (checkk == INCORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("System Fail !!");
		}
		else if (checkk == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
			_delay_ms(1500);
		}
	}

	/* 
 	if there is  password for admin , it will :
    	- Sign the admin password
    */

	else
	{
		checkk = checkPasswordAdmin(ADMIN_PASSWORD);
		if (checkk == INCORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("System Fail !!");
		}
		else if (checkk == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME ADMIN !!");
			_delay_ms(1500);

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
	_delay_ms(100);

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
		localCheck--;
		uint16 User_Password = USER1_PASSWORD + 0x10 * localCheck;
		checkk = checkPassword(User_Password);
		if (checkk == CORRECT_PASSWORD)
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("WELCOME USER !!");
			_delay_ms(1500);
		}
		else
		{
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("Wrong Password !!");
			_delay_ms(1500);
		}

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
	_delay_ms(100);
	EEPROM_voidSend4Numbers(ADMIN_PASSWORD,(uint8 *)password,MAX_SIZE_PASSWORD);
}
static void registerAdminPassWord(void)
{
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("PASSWORD : ");
	UART_sendString("PASSWORD: ");
	LCD_setCursorAt_4bit(LCD_ROW1,12);
	LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
	UART_recieve_string(password);
	EEPROM_voidSend4Numbers(ADMIN_PASSWORD,password,MAX_SIZE_PASSWORD);
	LCD_sendString_4bit("****");
}

static uint8 checkPassword(uint16 copy_u16EEPROM_PASS_Location)
{
	uint8 local_counter = 0;
	uint8 local_buttonVal = 0;
	uint8 local_counterCheck = 2;
	uint8 local_check = 0;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("PASSWORD : ");
	LCD_setCursorAt_4bit(LCD_ROW1,12);
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
	_delay_ms(100);
	/* compare the typed password with the stored password */
	local_check = strncmp((char *)password, (char *)savedPassword, MAX_SIZE_PASSWORD);
	while ((local_check != 0) && (local_counterCheck))
	{
		/* DISPLAY INVALID PASSWORD AND ENTER PASSWORD AGAIN FOR 3 TIMES*/
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("INVALID PASSWORD");
		_delay_ms(1000);
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("PASSWORD : ");
		LCD_setCursorAt_4bit(LCD_ROW1,12);
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
	if (strncmp((char *)password, (char *)savedPassword, MAX_SIZE_PASSWORD))
	{
		return INCORRECT_PASSWORD;
	}
	else
	{
		return CORRECT_PASSWORD;
	}
}

static uint8 checkPasswordAdmin(uint16 copy_u16EEPROM_PASS_Location)
{
	//registerAdminPassWord();
	uint8 trials=3;
	while(trials !=0)
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("PASSWORD: ");
		UART_sendString("PASSWORD: ");
		LCD_setCursorAt_4bit(LCD_ROW2,5);
		LCD_sendCommand_4bit(DISPLAY_CURSOR_BLINKING_ON);
		UART_recieve_string(password);
		LCD_sendString_4bit("****");
		EEPROM_voidRead4Numbers(copy_u16EEPROM_PASS_Location, savedPassword,MAX_SIZE_PASSWORD);
		if (strncmp(password,savedPassword, MAX_SIZE_PASSWORD))
		{
			trials--;
			LCD_clearDisplay_4bit();
			LCD_sendString_4bit("Wrong PASSWORD! ");
			_delay_ms(500);
		}
		else
		{
			return CORRECT_PASSWORD;
		}
	}
	return INCORRECT_PASSWORD;
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
			localCheck = strncmp((char *)ID,(char *)savedID,MAX_SIZE_ID);
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

void add_user(void)
{
	static uint8 usersCounter = 0;
	usersCounter = checkLatestUser();
	/* send by bluetooth to mobile app "Enter User ID" and display it on lcd*/
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("Enter User ID ");
	UART_sendString("Enter User ID ");
	/*Read from mobile and save it in ID Array*/
	UART_recieve_string(ID);
	/*Save the ID in EEPROM*/
	EEPROM_voidSend4Numbers( USER1_ID+ 0x10 * usersCounter , ID , MAX_SIZE_ID);
	/* send by bluetooth to mobile app "Enter User password"*/
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("Enter Password ");
	UART_sendString("Enter Password ");
	/*Read from mobile and save it in Password Array*/
	UART_recieve_string(password);
	/*Read from mobile and save it in password array*/
	/*Save the password in EEPROM*/
	EEPROM_voidSend4Numbers( USER1_PASSWORD+10*usersCounter , password , MAX_SIZE_PASSWORD);
}

/* To delete user you have to send the user id to RemoveUser function */
void RemoveUser(uint8* copy_userID)
{   /* this function deletes 8 consequent locations (ID + Password) in eeprom */
	uint8 local_temp_ID_Arr[4]={0};
	uint8 i=0;
	for(i=0;i<MAX_USER_NUM;i++)
	{
		EEPROM_voidRead4Numbers(USER1_ID+10*i ,local_temp_ID_Arr,4);
		/*check if id exist?*/
		if (strncmp((char *)copy_userID, (char *)local_temp_ID_Arr, MAX_SIZE_PASSWORD)!= 0 )
		{
			continue;
		}
		else
		{
			/*remove user id and password*/
			EEPROM_voidRemoveUser(USER1_ID + 0x10 * i);
			LCD_sendString_4bit("User's been deleted Successfully");
			UART_sendString("User's been deleted Successfully");
			break;
		}
	}
	if (i == (MAX_USER_NUM - 1))
	{
		/*Send by uart "ID does not exist"*/
		LCD_sendString_4bit("ID does not exist");
		UART_sendString("ID does not exist");
	}
}

void adminSetupModeCheck(void)
{
	uint8 local_choice = 0;
	uint8 local_counter = 0;

		local_choice = KEYPAD_getValue();
		while ((local_counter < MAX_TIME) && (local_choice != '1'))
		{
			local_counter++;
			local_choice = BM_recieveByte();
		}
		if (local_choice == '1')
		{
			adminSetupMode();
		}
		else
		{
			/* NOTHING */
		}
}

void ac_controlCheck(void)
{
	uint8 local_choice = 0;
	uint8 local_counter = 0;

	local_choice = KEYPAD_getValue();
	while ((local_counter < MAX_TIME) && (local_choice != '2'))
	{
		local_counter++;
		local_choice = KEYPAD_getValue();
	}

	if (local_choice == '2')
	{
		ac_control();
	}
	else
	{
		/* NOTHING */
	}
}

void door_controlCheck(void)
{
	uint8 local_choice = 0;
	uint8 local_counter = 0;

		local_choice = KEYPAD_getValue();
		while (((local_counter < MAX_TIME) && (local_choice != '3')))
		{
			local_counter++;
			local_choice = BM_recieveByte();
		}

		if (local_choice == '3')
		{
			door_control();
		}
		else
		{
			/* NOTHING */
		}
}

void led_controlCheck(void)
{
	uint8 local_choice = 0;
	uint8 local_counter = 0;

	local_choice = KEYPAD_getValue();
	while ((local_counter < MAX_TIME) && (local_choice != '4'))
	{
		local_counter++;
		local_choice = KEYPAD_getValue();
	}

	if (local_choice == '4')
	{
		led_control();
	}
	else
	{
		/* NOTHING */
	}
}

void led_controlAdminCheck(void)
{
	uint8 local_choice = 0;
	uint8 local_counter = 0;

	local_choice = BM_recieveByte();
	while ((local_counter < MAX_TIME) && (local_choice != '4'))
	{
		local_counter++;
		local_choice = BM_recieveByte();
	}

	if (local_choice == '4')
	{
		led_control_UART();
	}
	else
	{
		/* NOTHING */
	}
}
static void adminSetupMode(void)
{
	uint8 userSetting = 0;
	uint8 Local_tempID_Array[MAX_SIZE_ID]={0};
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("1 => ADD USER");
	LCD_sendStringAtAddress_4bit(2,0,"2 => REMOVE USER");
	UART_sendString("1 => ADD USER");
	_delay_ms(200);
	UART_sendString("2 => REMOVE USER");
	/* UART RECIEVE*/
	userSetting = UART_Receive();
	if (userSetting == '1')
	{
		add_user();
	}
	else if (userSetting == '2')
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("Delete > Enter ID");
		UART_sendString("Delete > Enter ID");
		UART_recieve_string(Local_tempID_Array);
		RemoveUser(Local_tempID_Array);
	}
	showOptions();
	RTOS_start();
}

static void ac_control(void)
{
	uint8 AC_Temp = 0;
	//LCD_clearDisplay_4bit();
	AC_Temp = TS_sendData();

	if (AC_Temp >= MAX_TEMP)
	{
		DCM_turnOn();
	}
	else if (AC_Temp <= MIN_TEMP)
	{
		DCM_turnOff();
	}
	//showOptions();
	RTOS_start();
}

static void door_control(void)
{
	uint8 localDoorController = DOOR_CLOSED;

	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("  DOOR CONTROL");
	_delay_ms(1500);
	LCD_clearDisplay_4bit();
	LCD_sendStringAtAddress_4bit(1,1,"1 => CLOSE DOOR");
	LCD_sendStringAtAddress_4bit(2,1,"2 => OPEN DOOR");

	localDoorController = UART_Receive();
	while (!((localDoorController == '1') || (localDoorController == '2')))
	{
		localDoorController = UART_Receive();
	}
	if (localDoorController == DOOR_OPEN)
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("   DOOR OPEN");
		SM_rotateAngle(90);
	}
	else if (localDoorController == DOOR_CLOSED)
	{
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("   DOOR CLOSE");
		SM_rotateAngle(0);
	}
	showOptions();
	RTOS_start();
}

static void led_control(void)
{
	uint8 ledNumber = 0;
	uint8 brightnessLevel = 0;
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("SELECT THE LED : ");
	ledNumber = KEYPAD_getValue();
	while (!((ledNumber <= '1') && (ledNumber >= '6')))
	{
		ledNumber = KEYPAD_getValue();
	}
	switch (ledNumber)
	{
	case '1':
		LED_toggle(LED1_PORT,LED1_PIN);
		break;
	case '2':
		LED_toggle(LED2_PORT,LED2_PIN);
		break;
	case '3':
		LED_toggle(LED3_PORT,LED3_PIN);
		break;
	case '4':
		LED_toggle(LED4_PORT,LED4_PIN);
		break;
	case '5':
		LED_toggle(LED5_PORT,LED5_PIN);
		break;
	case '6':
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("CHOOSE BRIGHT LEVEL");
		LCD_sendStringAtAddress_4bit(LCD_ROW2,1,"(0 - 9)");
		brightnessLevel = KEYPAD_getValue();
		while (!((brightnessLevel >= '0') && (brightnessLevel <= '9')))
		{
			brightnessLevel = KEYPAD_getValue();
		}
		DIMMER_start((brightnessLevel - 0x30));
		break;
	}
	showOptions();
	RTOS_start();
}

static void led_control_UART(void)
{
	uint8 ledNumber = 0;
	uint8 brightnessLevel = 0;
	LCD_clearDisplay_4bit();
	LCD_sendString_4bit("SELECT THE LED : ");
	UART_sendString("SELECT THE LED : ");
	ledNumber = UART_Receive();
	while (!((ledNumber <= '1') && (ledNumber >= '6')))
	{
		ledNumber = UART_Receive();
	}
	switch (ledNumber)
	{
	case '1':
		LED_toggle(LED1_PORT,LED1_PIN);
		break;
	case '2':
		LED_toggle(LED2_PORT,LED2_PIN);
		break;
	case '3':
		LED_toggle(LED3_PORT,LED3_PIN);
		break;
	case '4':
		LED_toggle(LED4_PORT,LED4_PIN);
		break;
	case '5':
		LED_toggle(LED5_PORT,LED5_PIN);
		break;
	case '6':
		LCD_clearDisplay_4bit();
		LCD_sendString_4bit("CHOOSE BRIGHT LEVEL");
		LCD_sendStringAtAddress_4bit(LCD_ROW2,1,"(0 - 9)");
		UART_sendString("CHOOSE BRIGHT LEVEL from 0 - 9 ");
		brightnessLevel = UART_Receive();
		while (!((brightnessLevel >= '0') && (brightnessLevel <= '9')))
		{
			brightnessLevel = UART_Receive();
		}
		DIMMER_start((brightnessLevel - 0x30));
		break;
	}
	showOptions();
	RTOS_start();
}
