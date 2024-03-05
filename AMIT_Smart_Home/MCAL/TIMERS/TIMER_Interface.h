/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TIMER_Interface.h
 * Date: 29 Dec 2023
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define T0_OC_DISCONNECTED		1
#define T0_OC_TOGGLE_ON_CMP		2
#define T0_OC_CLEAR_ON_CMP		3
#define T0_OC_SET_ON_CMP		4

#define T0_NO_CLK			0
#define T0_NO_PRESCALING	1
#define T0_8_PRESCALING		2
#define T0_64_PRESCALING	3
#define T0_256_PRESCALING	4
#define T0_1024_PRESCALING	5

#define T1A_OC_DISCONNECTED			1
#define T1A_OC_TOGGLE_ON_CMP		2
#define T1A_OC_CLEAR_ON_CMP			3
#define T1A_OC_SET_ON_CMP			4

#define T1B_OC_DISCONNECTED			1
#define T1B_OC_TOGGLE_ON_CMP		2
#define T1B_OC_CLEAR_ON_CMP			3
#define T1B_OC_SET_ON_CMP			4

#define T1_NO_CLK			0
#define T1_NO_PRESCALING	1
#define T1_8_PRESCALING		2
#define T1_64_PRESCALING	3
#define T1_256_PRESCALING	4
#define T1_1024_PRESCALING	5


#define T2_OC_DISCONNECTED		1
#define T2_OC_TOGGLE_ON_CMP		2
#define T2_OC_CLEAR_ON_CMP		3
#define T2_OC_SET_ON_CMP		4

#define T2_NO_CLK			0
#define T2_NO_PRESCALING	1
#define T2_8_PRESCALING		2
#define T2_32_PRESCALING	3
#define T2_64_PRESCALING	4
#define T2_128_PRESCALING	5
#define T2_256_PRESCALING	6
#define T2_1024_PRESCALING	7


StdReturnType TIMER0_initNormal(uint8 copy_TIMER0_cmpOutMode);
StdReturnType TIMER0_initCTC(uint8 copy_TIMER0_limit, uint8 copy_TIMER0_cmpOutMode);
StdReturnType TIMER0_initFastPWM(uint8 copy_TIMER0_cmp, uint8 copy_TIMER0_cmpOutMode);
StdReturnType TIMER0_initPCPWM(uint8 copy_TIMER0_cmp, uint8 copy_TIMER0_cmpOutMode);
StdReturnType TIMER0_readValue(uint8 *copy_TIMER0_ptr);
StdReturnType TIMER0_startTimer(uint8 copy_TIMER0_preScaling);
StdReturnType TIMER0_stopTimer(void);
StdReturnType TIMER0_initInterruptOutputCompare(void);
StdReturnType TIMER0_initInterruptOverflow(void);

StdReturnType TIMER1_initNormal(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initCTC_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimit);
StdReturnType TIMER1_initCTC_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_topA,  uint16 copy_TIMER1_topB,	uint16 copy_TIMER1_limit);
StdReturnType TIMER1_initFastPWM8bit(uint8 copy_TIMER1_cmpA, uint8 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initFastPWM9bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initFastPWM10bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initFastPWM_ICR1(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint16 copy_TIMER1_limit, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initFastPWM_OCR1A(uint16 copy_TIMER1_cmpLimitA, uint8 copy_TIMER1_cmpOutModeA);
StdReturnType TIMER1_initPCPWM8bit(uint8 copy_TIMER1_cmpA, uint8 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initPCPWM9bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initPCPWM10bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB);
StdReturnType TIMER1_initPCPWM_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB,uint16 copy_TIMER1_limit);
StdReturnType TIMER1_initPCPWM_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimitA);
StdReturnType TIMER1_initPFCPWM_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint16 copy_TIMER1_limit);
StdReturnType TIMER1_initPFCPWM_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimitA);
StdReturnType TIMER1_readValue(uint16 *copy_TIMER1_ptr);
StdReturnType TIMER1_startTimer(uint8 copy_TIMER1_prescaling);
StdReturnType TIMER1_stopTimer(void);

StdReturnType TIMER2_initNormal(uint8 copy_TIMER2_cmpOutMode);
StdReturnType TIMER2_initCTC(uint8 copy_TIMER2_limit, uint8 copy_TIMER2_cmpOutMode);
StdReturnType TIMER2_initFastPWM(uint8 copy_TIMER2_cmp, uint8 copy_TIMER2_cmpOutMode);
StdReturnType TIMER2_initPCPWM(uint8 copy_TIMER2_cmp, uint8 copy_TIMER2_cmpOutMode);
StdReturnType TIMER2_readValue(uint8 *copy_TIMER2_ptr);
StdReturnType TIMER2_startTimer(uint8 copy_TIMER2_preScaling);
StdReturnType TIMER2_stopTimer(void);

#endif /* TIMER_INTERFACE_H_ */
