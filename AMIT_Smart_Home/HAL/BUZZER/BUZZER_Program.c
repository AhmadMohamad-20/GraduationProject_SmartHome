/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: BUZZER_Program.c
 * Date: 7 Mar 2024
 */


#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "BUZZER_Config.h"
#include "BUZZER_Private.h"
#include "BUZZER_Interface.h"

void BUZZER_init(void)
{
	DIO_setPinDirection(BUZZER_PORT,BUZZER_PIN,OUTPUT);
}

void BUZZER_ON(void)
{
	DIO_setPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
}
