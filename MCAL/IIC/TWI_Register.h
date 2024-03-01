/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TWI_Register.h
 * Date: 10 Feb 2024
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_



#define TWBR	(*(volatile uint8 *)0x20)
#define TWSR	(*(volatile uint8 *)0x21)
#define TWDR	(*(volatile uint8 *)0x23)
#define TWAR	(*(volatile uint8 *)0x22)
#define TWCR	(*(volatile uint8 *)0x56)

#endif /* TWI_REGISTER_H_ */
