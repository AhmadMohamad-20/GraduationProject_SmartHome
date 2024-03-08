/*
 * UART_Program.c
 *
 *  Created on: 5 Jan 2024
 *      Author: MR.X
 */
#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "UART_Register.h"
#include "UART_Config.h"
#include "UART_Interface.h"

void UART_Init()
{
	uint8 ucsrc=0u;
	CLEAR_BIT(ucsrc,UMSEL);//ASYNCRONAS

	CLEAR_BIT(ucsrc,UPM1); /*PARTIY DISABLED*/
	CLEAR_BIT(ucsrc,UPM0);

	SET_BIT(ucsrc,UCSZ0);/*8 BIT MODE*/
	SET_BIT(ucsrc,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);

	SET_BIT(UCSRB,TXEN);/* TRANSMIT ENABLE*/
	SET_BIT(UCSRB,RXEN); /*RECIVE ENABLE*/

	SET_BIT(ucsrc,URSEL);

	UCSRC = ucsrc;

	UBRRL=103;
}

void UART_Transmit(uint8 Copy_Data)
{

	while((GET_BIT(UCSRA,UDRE)) == 0);

	UDR = Copy_Data;
}
uint8 UART_Receive(void)
{
	uint8 local_counter = 0;

	while(((GET_BIT(UCSRA,RXC)) == 0));

	return UDR;
}

void UART_sendString(char *copy_UART_ptr)
{
	if (copy_UART_ptr != NULL)
	{
		while (*copy_UART_ptr != '\0')
		{
			UART_Transmit(*copy_UART_ptr);
			copy_UART_ptr++;
		}
	}
	else
	{
		/* Do Nothing */
	}
}

void  UART_recieve_string(uint8 * copy_UART_ptr)
{
	uint8 i=0;
	//uint8* local_ptr = copy_UART_ptr;
	if(copy_UART_ptr != NULL)
	{
		copy_UART_ptr[i]=UART_Receive();
		while(copy_UART_ptr[i] != 0x0D) // Enter key =0x0D in Ascii
		{
			i++;
			copy_UART_ptr[i]=UART_Receive();
		}
	}
	else
	{
		/* Do Nothing*/
	}

}
