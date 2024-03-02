/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DIO_Private.h
 * Date: 17 Feb 2024
 */

#ifndef MCAL_DIO_DIO_PRIVATE_H_
#define MCAL_DIO_DIO_PRIVATE_H_



#define CONC_HELP(A,B,C,D,E,F,G,H)	0##b##A##B##C##D##E##F##G##H
#define CONC(Z,X,C,V,B,N,M,K)		CONC_HELP(Z,X,C,V,B,N,M,K)

#define DDRA_VALUE	CONC(DDRA_PIN0,DDRA_PIN1,DDRA_PIN2,DDRA_PIN3,DDRA_PIN4,DDRA_PIN5,DDRA_PIN6,DDRA_PIN7)
#define DDRB_VALUE	CONC(DDRB_PIN0,DDRB_PIN1,DDRB_PIN2,DDRB_PIN3,DDRB_PIN4,DDRB_PIN5,DDRB_PIN6,DDRB_PIN7)
#define DDRC_VALUE	CONC(DDRC_PIN0,DDRC_PIN1,DDRC_PIN2,DDRC_PIN3,DDRC_PIN4,DDRC_PIN5,DDRC_PIN6,DDRC_PIN7)
#define DDRD_VALUE	CONC(DDRD_PIN0,DDRD_PIN1,DDRD_PIN2,DDRD_PIN3,DDRD_PIN4,DDRD_PIN5,DDRD_PIN6,DDRD_PIN7)

#define PORTA_VALUE	CONC(PORTA_PIN0,PORTA_PIN1,PORTA_PIN2,PORTA_PIN3,PORTA_PIN4,PORTA_PIN5,PORTA_PIN6,PORTA_PIN7)
#define PORTB_VALUE	CONC(PORTB_PIN0,PORTB_PIN1,PORTB_PIN2,PORTB_PIN3,PORTB_PIN4,PORTB_PIN5,PORTB_PIN6,PORTB_PIN7)
#define PORTC_VALUE	CONC(PORTC_PIN0,PORTC_PIN1,PORTC_PIN2,PORTC_PIN3,PORTC_PIN4,PORTC_PIN5,PORTC_PIN6,PORTC_PIN7)
#define PORTD_VALUE	CONC(PORTD_PIN0,PORTD_PIN1,PORTD_PIN2,PORTD_PIN3,PORTD_PIN4,PORTD_PIN5,PORTD_PIN6,PORTD_PIN7)
#endif /* MCAL_DIO_DIO_PRIVATE_H_ */
