/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DIM_Program.c
 * Date: 6 Mar 2024
 */
#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"
#include "../../MCAL/TIMERS/TIMER_Interface.h"
#include "DIM_Config.h"
#include "DIM_Private.h"
#include "DIM_Interface.h"

void DIMMER_start(uint8 copy_DIMMER_dutyCycle)
{
	uint8 compareValue = 0;
	compareValue = (uint16)(copy_DIMMER_dutyCycle * 256UL) / 10;
	TIMER2_initFastPWM(compareValue,T2_OC_CLEAR_ON_CMP);
	TIMER2_startTimer(T2_1024_PRESCALING);
}
