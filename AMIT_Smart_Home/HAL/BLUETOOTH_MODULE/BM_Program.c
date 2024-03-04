/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: BM_Program.c
 * Date: 4 Mar 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/UART/UART_Interface.h"

#include "BM_Config.h"
#include "BM_Private.h"
#include "BM_Interface.h"

void BM_init(void)
{
	UART_Init();
}

void BM_sendByte(uint8 copy_BM_dataByte)
{
	UART_Transmit(copy_BM_dataByte);
}

uint8 BM_recieveByte(void)
{
	uint8 local_dataByte = 0;

	local_dataByte = UART_Receive();

	return local_dataByte;
}

void BM_sendString(uint8 *copy_BM_stringPtr)
{
	UART_sendString(copy_BM_stringPtr);
}

void BM_recieveString(uint8 *copy_BM_stringPtr)
{
	UART_recieve_string(copy_BM_stringPtr);
}
