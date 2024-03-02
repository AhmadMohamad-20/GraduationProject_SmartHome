/*
 * UART_interface.h
 *
 *  Created on: 5 Jan 2024
 *      Author: Ziad Yakoot
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init(void);
void UART_transmit(uint8 copy_data);
uint8 UART_receive(void);
void UART_transmit_string(char *string);
void UART_receiveString(char *string);


#endif /* UART_INTERFACE_H_ */
