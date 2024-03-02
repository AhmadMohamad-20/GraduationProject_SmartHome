/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TIMER_Reg.h
 * Date: 29 Dec 2023
 */

#ifndef TIMER_REG_H_
#define TIMER_REG_H_

#define TCNT0	(*(volatile uint8*)(0x52))
#define TCNT1	(*(volatile uint16*)(0x4C))
#define TCNT2	(*(volatile uint8*)(0x44))

#define TCCR0	(*(volatile uint8*)(0x53))
#define TCCR1A	(*(volatile uint8*)(0x4F))
#define TCCR1B	(*(volatile uint8*)(0x4E))
#define TCCR2	(*(volatile uint8*)(0x45))

#define ICR1	(*(volatile uint16*)(0x46))

#define OCR0	(*(volatile uint8*)(0x5C))
#define OCR1A	(*(volatile uint16*)(0x4A))
#define OCR1B	(*(volatile uint16*)(0x48))

#define OCR2	(*(volatile uint8*)(0x43))




#define TIFR	(*(volatile uint8*)(0x58))
#define TIMSK	(*(volatile uint8*)(0x59))

#endif /* TIMER_REG_H_ */
