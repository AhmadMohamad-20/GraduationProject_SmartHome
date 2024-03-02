/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: ADC_Private.h
 * Date: 24 Feb 2024
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADCMUX_REFS1	7
#define ADCMUX_REFS0	6
#define ADCMUX_ADLAR	5

/* MUX 4-0 */

#define ADCSRA_ADEN		7
#define ADCSRA_ADSC		6
#define ADCSRA_ADATE	5
#define ADCSRA_ADIF		4
#define ADCSRA_ADIE		3

/* ADPS 2-0 */


#define SE_ADC0			0
#define SE_ADC1			1
#define SE_ADC2			2
#define SE_ADC3			3
#define SE_ADC4			4
#define SE_ADC5			5
#define SE_ADC6			6
#define SE_ADC7			7
#define D_ADC00x10		8
#define D_ADC10x10		9
#define D_ADC00x200		10
#define D_ADC10x200		11
#define D_ADC22x10		12
#define D_ADC32x10		13
#define D_ADC22x200		14
#define D_ADC32x200		15
#define D_ADC01x1		16
#define D_ADC11x1		17
#define D_ADC21x1		18
#define D_ADC31x1		19
#define D_ADC41x1		20
#define D_ADC51x1		21
#define D_ADC61x1		22
#define D_ADC71x1		23
#define D_ADC02x1		24
#define D_ADC12x1		25
#define D_ADC22x1		26
#define D_ADC32x1		27
#define D_ADC42x1		28
#define D_ADC52x1		29
#define SE_122V			30
#define SE_GND			31

#define ADC_PRESCALER_2			0
#define ADC_PRESCALER_2			1
#define ADC_PRESCALER_4			2
#define ADC_PRESCALER_8			3
#define ADC_PRESCALER_16		4
#define ADC_PRESCALER_32		5
#define ADC_PRESCALER_64		6
#define ADC_PRESCALER_128		7

#define ADC_FREERUNNING			0
#define ADC_ANALOGCOMPARATOR	1
#define ADC_EXT0				2
#define ADC_T0_CMP				3
#define ADC_T0_OV				4
#define ADC_T1B_CMP				5
#define ADC_T1_OV				6
#define ADC_T1_CE				7



#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
