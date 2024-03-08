/*
 * UART_Interface.h
 *
 *  Created on: 5 Jan 2024
 *      Author: MR.X
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_Init();
void UART_Transmit(uint8 Copy_Data);
uint8 UART_Receive(void);
void UART_sendString(char *copy_UART_ptr);
void  UART_recieve_string(uint8 * copy_UART_ptr);
#endif /* UART_INTERFACE_H_ */
