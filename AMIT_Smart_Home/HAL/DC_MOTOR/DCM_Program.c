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

StdReturnType DCM_turnOn(uint8 copy_DCM_port, uint8 copy_DCM_pin)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(copy_DCM_port,copy_DCM_pin,HIGH);
	return local_errorSignal;
}

StdReturnType DCM_turnOff(uint8 copy_DCM_port, uint8 copy_DCM_pin)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinValue(copy_DCM_port,copy_DCM_pin,LOW);
	return local_errorSignal;
}
