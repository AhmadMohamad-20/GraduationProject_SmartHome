/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DIO_registers.h
 * Date: 17 Feb 2024
 */

#ifndef MCAL_DIO_DIO_REGISTERS_H_
#define MCAL_DIO_DIO_REGISTERS_H_

#define DDRA 	(*(volatile  uint8 *)0x3a)
#define DDRB 	(*(volatile  uint8 *)0x37)
#define DDRC 	(*(volatile  uint8 *)0x34)
#define DDRD 	(*(volatile  uint8 *)0x31)


#define PORTA	(*(volatile uint8 *)0x3b)
#define PORTB	(*(volatile uint8 *)0x38)
#define PORTC	(*(volatile uint8 *)0x35)
#define PORTD	(*(volatile uint8 *)0x32)


#define PINA	(*(volatile uint8 *)0x39)
#define PINB	(*(volatile uint8 *)0x36)
#define PINC	(*(volatile uint8 *)0x33)
#define PIND	(*(volatile uint8 *)0x30)

#endif /* MCAL_DIO_DIO_REGISTERS_H_ */
