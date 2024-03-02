/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: ADC_Register.h
 * Date: 24 Feb 2024
 */

#ifndef MCAL_ADC_ADC_REGISTER_H_
#define MCAL_ADC_ADC_REGISTER_H_

#define ADMUX	(*(volatile uint8 *)0x27)
#define ADSRA	(*(volatile uint8 *)0x26)
#define ADC		(*(volatile uint16 *)0x24)
#define SFIOR	(*(volatile uint8 *)0x50)

#endif /* MCAL_ADC_ADC_REGISTER_H_ */
