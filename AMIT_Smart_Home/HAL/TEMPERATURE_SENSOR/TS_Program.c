/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TS_Program.c
 * Date: 5 Mar 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/ADC/ADC_Interface.h"

#include "TS_Config.h"
#include "TS_Private.h"
#include "TS_Interface.h"

void TS_init(void)
{
	ADC_init();
}

uint8 TS_sendData(void)
{
	uint8 localData = 0;
	uint8 temperature = 0;
	ADC_startConversionSync(0x01,&localData);
	temperature = (uint32)localData * 150 / 256UL;
	return temperature;
}
