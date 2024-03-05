/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: LED_Program.c
 * Date: 17 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "LED_Config.h"
#include "LED_Private.h"
#include "LED_Interface.h"

StdReturnType LED_init(uint8 copy_LED_port, uint8 cop_LED_pin)
{
	DIO_setPinDirection(copy_LED_port,cop_LED_pin,OUTPUT);
}

StdReturnType LED_turnOn(uint8 copy_LED_port, uint8 copy_LED_pin)
{
	StdReturnType local_errorState = OK_STAT;
	local_errorState = DIO_setPinValue(copy_LED_port, copy_LED_pin, HIGH);
	return local_errorState;
}

StdReturnType LED_turnOff(uint8 copy_LED_port, uint8 copy_LED_pin)
{
	StdReturnType local_errorState = OK_STAT;
	local_errorState = DIO_setPinValue(copy_LED_port, copy_LED_pin, LOW);
	return local_errorState;
}

StdReturnType LED_toggle(uint8 copy_LED_port, uint8 copy_LED_pin)
{
	StdReturnType local_errorState = OK_STAT;
	local_errorState = DIO_togglePin(copy_LED_port, copy_LED_pin);
	return local_errorState;
}
