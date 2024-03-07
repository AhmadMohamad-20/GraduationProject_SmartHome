/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DCM_Program.c
 * Date: 17 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "DCM_Config.h"
#include "DCM_Private.h"
#include "DCM_Interface.h"

void DCM_init(void)
{
	DIO_setPinDirection(DCM_PORT,DCM_PIN,OUTPUT);
}

StdReturnType DCM_turnOn(void)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN,HIGH);
	return local_errorSignal;
}

StdReturnType DCM_turnOff(void)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN,LOW);
	return local_errorSignal;
}
