/*
 * KEYPAD_Program.c
 *
 *  Created on: 15 Dec 2023
 *      Author: user
 */
#include <util/delay.h>

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/DIO/DIO_Interface.h"


#include "KEYPAD_CFG.h"
#include "KEYPAD_Reg.h"
#include "KEYPAD_Private.h"
#include "KEYPAD_Interfacing.h"

static uint8 buttonsArray[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = KEYPAD_BUTTONS;
static uint8 rowPins[KEYPAD_ROW_NUM] = KEYPAD_ROW_PINS;
static uint8 colPins[KEYPAD_COL_NUM] = KEYPAD_COL_PINS;

void KEYPAD_init(void)
{
	/* OUTPUT PART*/

	DIO_setPinDirection(KEYPAD_COL_PORT,KEYPAD_COL_PIN0,OUTPUT);
	DIO_setPinDirection(KEYPAD_COL_PORT,KEYPAD_COL_PIN1,OUTPUT);
	DIO_setPinDirection(KEYPAD_COL_PORT,KEYPAD_COL_PIN2,OUTPUT);

	/*INOUT PART*/

	DIO_setPinDirection(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN0,INPUT);
	DIO_setPinDirection(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN1,INPUT);
	DIO_setPinDirection(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN2,INPUT);
	DIO_setPinDirection(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN3,INPUT);

	DIO_setIntPullUpRes(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN0);
	DIO_setIntPullUpRes(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN1);
	DIO_setIntPullUpRes(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN2);
	DIO_setIntPullUpRes(KEYPAD_ROW_PORT,KEYPAD_ROW_PIN3);
}

uint8 KEYPAD_getValue(void)
{
	uint8 local_pressed_button = BUTTON_NOT_PRESSED;
	uint8 local_row_counter = 0;
	uint8 local_col_counter = 0;

	for (local_col_counter = 0; local_col_counter < KEYPAD_COL_NUM; local_col_counter++)
	{
		DIO_setPinValue(KEYPAD_COL_PORT,colPins[local_col_counter],LOW);
		for (local_row_counter = 0; local_row_counter < KEYPAD_ROW_NUM; local_row_counter++)
		{
			DIO_readPinValue(KEYPAD_ROW_PORT,rowPins[local_row_counter],&local_pressed_button);
			if (local_pressed_button == LOW)
			{
				while (local_pressed_button == LOW)
				{
					DIO_readPinValue(KEYPAD_ROW_PORT,rowPins[local_row_counter],&local_pressed_button);
				}
				local_pressed_button = buttonsArray[local_row_counter][local_col_counter];
				return local_pressed_button;
			}
		}
		DIO_setPinValue(KEYPAD_COL_PORT,colPins[local_col_counter],HIGH);
	}
	local_pressed_button = BUTTON_NOT_PRESSED;
	return local_pressed_button;
}

void KEYPAD_getString(char *copy_KEYPAD_ptr, uint8 copy_KEYPAD_max)
{
	uint8 local_counter = 0;
	for (; local_counter < copy_KEYPAD_max; local_counter++)
	{
		copy_KEYPAD_ptr[local_counter] = KEYPAD_getValue();
	}
}
