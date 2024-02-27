/*
 * UART_program.c
 *
 *  Created on: 5 Jan 2024
 *      Author: Ziad Yakoot
 */
#include "STD_types.h"
#include "bitMath.h"
#include "UART_reg.h"
#include "UART_priv.h"
#include "UART_interface.h"
#include "UART_cfg.h"

void UART_init(void)
{
	uint8 USCRC_val =0u;
  SET_BIT(USCRB,USCRB_RXEN);
  SET_BIT(USCRB,USCRB_TXEN);

  /*aSYNC*/
  CLR_BIT(USCRC,USCRC_UMSEL);


  /*character size mode*/
  CLR_BIT(USCRB,USCRB_UCSZ2);
  SET_BIT(USCRC,USCRC_UCSZ1);
  SET_BIT(USCRC,USCRC_UCSZ0);



  /*parity disable*/

  CLR_BIT(USCRC,USCRC_UPM0);
  CLR_BIT(USCRC,USCRC_UPM1);


  /*Stop bit mode 1 bit*/
  CLR_BIT(USCRC,USCRC_USBS);


  /*register select */
SET_BIT(USCRC,USCRC_URSEL);
USCRC= USCRC_val;
/*NORMAL SPEED MODE*/
CLR_BIT(USCRA,USCRA_U2X);
/*BAUD RATE 9600*/
UBRRL =103U;
}
void UART_transmit(uint8 copy_data)
{
	while((GET_BIT(USCRA,USCRA_UDRE)) == 0);
	UDR = copy_data;
}
uint8 UART_receive(void)
{
	while(GET_BIT(USCRA,USCRA_RXC)==0);
	return UDR;
}

void UART_transmit_string(char *string)
{
	for(;*string != '\0'; string++)
	{
		UART_transmit(*string);
	}
}
void UART_receiveString(char *string)
{
	do
	{
		UART_receive();
	}while(*string != '\0');

}
