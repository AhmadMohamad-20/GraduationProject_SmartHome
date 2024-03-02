/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: SM_Program.c
 * Date: 17 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/TIMERS/TIMER_Interface.h"

#include "SM_Config.h"
#include "SM_Private.h"
#include "SM_Interface.h"

uint16 MAP(uint16 X1, uint16 X2, uint16 Y1, uint16 Y2, uint16 M, uint16 X)
{
	uint16 localSlope = 0;
	uint16 localOutput = 0;

	localSlope = (Y2 - Y1)/(X2 - X1);
	localOutput = (localSlope * X) + M;

	return localOutput;
}

void SM_rotateAngle(uint8 copy_SM_angle)
{
	uint16 local_timeValue = 0;
	local_timeValue = MAP(0,180,2000,4000,2000,copy_SM_angle);
	TIMER1_initFastPWM_ICR1(local_timeValue,local_timeValue,40000,T1A_OC_CLEAR_ON_CMP,T1B_OC_CLEAR_ON_CMP);
	TIMER1_startTimer(T1_8_PRESCALING);
}
