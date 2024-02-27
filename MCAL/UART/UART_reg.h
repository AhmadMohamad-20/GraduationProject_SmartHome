/*
 * UART_reg.h
 *
 *  Created on: 5 Jan 2024
 *      Author: Ziad yakoot
 */

#ifndef UART_REG_H_
#define UART_REG_H_

#define UDR     (*(volatile uint8*)0x2c)
#define USCRA   (*(volatile uint8*)0x2b)
#define USCRB   (*(volatile uint8*)0x2a)
#define USCRC   (*(volatile uint8*)0x40)
#define UBRRL   (*(volatile uint8*)0x29)
#define UBRRH   (*(volatile uint8*)0x40)

#endif /* UART_REG_H_ */
