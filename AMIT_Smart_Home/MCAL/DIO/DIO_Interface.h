/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DIO_Interface.h
 * Date: 17 Feb 2024
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3


#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

#define INPUT	0
#define OUTPUT	1

#define HIGH	1
#define LOW		0

#define PORT_OUTPUT 0xFF
#define PORT_INPUT 0

#define PORT_HIGH	0xFF
#define PORT_LOW	0

void DIO_portsInit(void);

StdReturnType DIO_setPinDirection(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_direction);
StdReturnType DIO_setPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_value);
StdReturnType DIO_readPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 *copy_DIO_pValue);
StdReturnType DIO_togglePin(uint8 copy_DIO_port, uint8 copy_DIO_pin);
StdReturnType DIO_setIntPullUpRes(uint8 copy_DIO_port, uint8 copy_DIO_pin);

StdReturnType DIO_setPortDirection(uint8 copy_DIO_port, uint8 copy_DIO_direction);
StdReturnType DIO_setPortValue(uint8 copy_DIO_port,  uint8 copy_DIO_value);
StdReturnType DIO_ReadPortValue(uint8 copy_DIO_port,  uint8 *copy_DIO_pValue);
StdReturnType DIO_togglePort(uint8 copy_DIO_port);



#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
