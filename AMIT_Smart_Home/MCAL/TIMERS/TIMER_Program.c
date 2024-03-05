/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TIMER_Program.c
 * Date: 18 Feb 2024
 */


#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../DIO/DIO_Interface.h"
#include "../G_INT/GINT_Interface.h"

#include "TIMER_Reg.h"
#include "TIMER_CFG.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

static void (*Timer0_pvCompareMatchCallBackFun)(void) = NULL;

/*		TIMER0 FUNCTIONS	*/

StdReturnType TIMER0_initNormal(uint8 copy_TIMER0_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER0_cmpOutMode)
	{
	case T0_OC_DISCONNECTED:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_SET_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	SET_BIT(TCCR0,TCCR0_FOC0);

	DIO_setPinDirection(DIO_PORTB,PIN3,OUTPUT);
	return local_errorSignal;
}

StdReturnType TIMER0_initCTC(uint8 copy_TIMER0_limit, uint8 copy_TIMER0_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER0_cmpOutMode)
	{
	case T0_OC_DISCONNECTED:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_SET_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR0 = copy_TIMER0_limit;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	SET_BIT(TCCR0,TCCR0_FOC0);

	DIO_setPinDirection(DIO_PORTB,PIN3,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER0_initFastPWM(uint8 copy_TIMER0_cmp, uint8 copy_TIMER0_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);


	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER0_cmpOutMode)
	{
	case T0_OC_DISCONNECTED:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_SET_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR0 = copy_TIMER0_cmp;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	CLEAR_BIT(TCCR0,TCCR0_FOC0);

	DIO_setPinDirection(DIO_PORTB,PIN3,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER0_initPCPWM(uint8 copy_TIMER0_cmp, uint8 copy_TIMER0_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	SET_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);



	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER0_cmpOutMode)
	{
	case T0_OC_DISCONNECTED:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	case T0_OC_SET_ON_CMP:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR0 = copy_TIMER0_cmp;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	CLEAR_BIT(TCCR0,TCCR0_FOC0);

	DIO_setPinDirection(DIO_PORTB,PIN3,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER0_readValue(uint8 *copy_TIMER0_ptr)
{
	StdReturnType local_errorSignal = OK_STAT;

		if (copy_TIMER0_ptr == NULL)
		{
			local_errorSignal = NOT_OK_STAT;
		}
		else
		{
			*copy_TIMER0_ptr = TCNT0;
		}

		return local_errorSignal;
}

StdReturnType TIMER0_startTimer(uint8 copy_TIMER0_preScaling)
{
	StdReturnType local_errorSignal = OK_STAT;
	if (copy_TIMER0_preScaling < 6)
	{
		TCCR0 &= 0xF8;
		TCCR0 |= copy_TIMER0_preScaling;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

StdReturnType TIMER0_stopTimer(void)
{
	StdReturnType local_errorSignal = OK_STAT;

	TCCR0 &= 0xF8;
	TCCR0 |= T0_NO_CLK;

	return local_errorSignal;
}

StdReturnType TIMER0_initInterruptOutputCompare(void)
{
	SET_BIT(TIMSK,TIMSK_OCIE0);
}

StdReturnType TIMER0_initInterruptOverflow(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE0);
}


/*		TIMER1 FUNCTIONS	*/

StdReturnType TIMER1_initNormal(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	SET_BIT(TCCR1A,TCCR1A_FOC1A);
	SET_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initCTC_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimit)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR1A = copy_TIMER1_topLimit;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	SET_BIT(TCCR1A,TCCR1A_FOC1A);
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}


StdReturnType TIMER1_initCTC_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_topA,  uint16 copy_TIMER1_topB,	uint16 copy_TIMER1_limit)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}


	ICR1 = copy_TIMER1_limit;
	OCR1A = copy_TIMER1_topA;
	OCR1B = copy_TIMER1_topB;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	SET_BIT(TCCR1A,TCCR1A_FOC1A);
	SET_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}


StdReturnType TIMER1_initFastPWM8bit(uint8 copy_TIMER1_cmpA, uint8 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR1A = copy_TIMER1_cmpA;
	OCR1B = copy_TIMER1_cmpB;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}


StdReturnType TIMER1_initFastPWM9bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	if ((copy_TIMER1_cmpA <= 0x01FF) && (copy_TIMER1_cmpB <= 0x01FF))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}


StdReturnType TIMER1_initFastPWM10bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	if ((copy_TIMER1_cmpA <= 0x03FF) && (copy_TIMER1_cmpB <= 0x03FF))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}


StdReturnType TIMER1_initFastPWM_ICR1(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint16 copy_TIMER1_limit, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	ICR1 = copy_TIMER1_limit;
	if ((copy_TIMER1_cmpA <= copy_TIMER1_limit) && (copy_TIMER1_cmpB <= copy_TIMER1_limit))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	//CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	//CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initFastPWM_OCR1A(uint16 copy_TIMER1_cmpLimitA, uint8 copy_TIMER1_cmpOutModeA)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR1A = copy_TIMER1_cmpLimitA;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPCPWM8bit(uint8 copy_TIMER1_cmpA, uint8 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR1A = copy_TIMER1_cmpA;
	OCR1B = copy_TIMER1_cmpB;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPCPWM9bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */

	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}


	if ((copy_TIMER1_cmpA <= 0x01FF) && (copy_TIMER1_cmpB <= 0x01FF))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPCPWM10bit(uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	if ((copy_TIMER1_cmpA <= 0x03FF) && (copy_TIMER1_cmpB <= 0x03FF))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPCPWM_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB,uint16 copy_TIMER1_limit)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	ICR1 = copy_TIMER1_limit;
	if ((copy_TIMER1_cmpA <= copy_TIMER1_limit) && (copy_TIMER1_cmpB <= copy_TIMER1_limit))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPCPWM_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimitA)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}
	OCR1A = copy_TIMER1_cmpOutModeA;

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPFCPWM_ICR1(uint8 copy_TIMER1_cmpOutModeA, uint8 copy_TIMER1_cmpOutModeB, uint16 copy_TIMER1_cmpA, uint16 copy_TIMER1_cmpB, uint16 copy_TIMER1_limit)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	CLEAR_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	switch (copy_TIMER1_cmpOutModeB)
	{
	case T1B_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	case T1B_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	ICR1 = copy_TIMER1_limit;
	if ((copy_TIMER1_cmpA <= copy_TIMER1_limit) && (copy_TIMER1_cmpB <= copy_TIMER1_limit))
	{
		OCR1A = copy_TIMER1_cmpA;
		OCR1B = copy_TIMER1_cmpB;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}

	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLEAR_BIT(TCCR1A,TCCR1A_FOC1B);

	DIO_setPinDirection(DIO_PORTD,PIN4,OUTPUT);		//	B
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_initPFCPWM_OCR1A(uint8 copy_TIMER1_cmpOutModeA, uint16 copy_TIMER1_topLimitA)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION MODE  */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*	COMPARE MATCH OUTPUT MODE  */

	switch (copy_TIMER1_cmpOutModeA)
	{
	case T1A_OC_DISCONNECTED:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	case T1A_OC_SET_ON_CMP:
		SET_BIT(TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR1A = copy_TIMER1_cmpOutModeA;


	/*	FORCE OUTPUT COMPARE CONFIG  */

	CLEAR_BIT(TCCR1A,TCCR1A_FOC1A);
	DIO_setPinDirection(DIO_PORTD,PIN5,OUTPUT);		//	A

	return local_errorSignal;
}

StdReturnType TIMER1_readValue(uint16 *copy_TIMER1_ptr)
{
	StdReturnType local_errorSignal = OK_STAT;

	if(NULL == copy_TIMER1_ptr)
	{
		local_errorSignal = NOT_OK_STAT;
	}
	else
	{
		*copy_TIMER1_ptr = TCNT1;
	}
	return local_errorSignal;
}

StdReturnType TIMER1_startTimer(uint8 copy_TIMER1_prescaling)
{
	StdReturnType local_errorSignal = OK_STAT;
		if (copy_TIMER1_prescaling < 6)
		{
			TCCR1B &= 0xF8;
			TCCR1B |= copy_TIMER1_prescaling;
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}
		return local_errorSignal;
}

StdReturnType TIMER1_stopTimer(void)
{
	StdReturnType local_errorSignal = OK_STAT;

	TCCR1B &= 0xF8;
	TCCR1B |= T1_NO_CLK;

	return local_errorSignal;
}


/*		TIMER2 FUNCTIONS	*/

StdReturnType TIMER2_initNormal(uint8 copy_TIMER2_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	CLEAR_BIT(TCCR2,TCCR2_WGM20);
	CLEAR_BIT(TCCR2,TCCR2_WGM21);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER2_cmpOutMode)
	{
	case T2_OC_DISCONNECTED:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_SET_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	SET_BIT(TCCR2,TCCR2_FOC2);

	DIO_setPinDirection(DIO_PORTD,PIN7,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER2_initCTC(uint8 copy_TIMER2_limit, uint8 copy_TIMER2_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	CLEAR_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER2_cmpOutMode)
	{
	case T2_OC_DISCONNECTED:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_TOGGLE_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_SET_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR2 = copy_TIMER2_limit;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	SET_BIT(TCCR2,TCCR2_FOC2);

	DIO_setPinDirection(DIO_PORTD,PIN7,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER2_initFastPWM(uint8 copy_TIMER2_cmp, uint8 copy_TIMER2_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	SET_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER2_cmpOutMode)
	{
	case T2_OC_DISCONNECTED:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_SET_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR2 = copy_TIMER2_cmp;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	CLEAR_BIT(TCCR2,TCCR2_FOC2);

	DIO_setPinDirection(DIO_PORTD,PIN7,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER2_initPCPWM(uint8 copy_TIMER2_cmp, uint8 copy_TIMER2_cmpOutMode)
{
	StdReturnType local_errorSignal = OK_STAT;

	/*	WAVEFORM GENERATION FORM 	*/

	SET_BIT(TCCR2,TCCR2_WGM20);
	CLEAR_BIT(TCCR2,TCCR2_WGM21);

	/*	COMPARE MATCH OUTPUT MODE	*/

	switch (copy_TIMER2_cmpOutMode)
	{
	case T2_OC_DISCONNECTED:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		CLEAR_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_CLEAR_ON_CMP:
		CLEAR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	case T2_OC_SET_ON_CMP:
		SET_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
		break;
	}

	OCR2 = copy_TIMER2_cmp;

	/*	FORCE OUTPUT COMPARE CONFIG	*/

	CLEAR_BIT(TCCR2,TCCR2_FOC2);

	DIO_setPinDirection(DIO_PORTD,PIN7,OUTPUT);

	return local_errorSignal;
}

StdReturnType TIMER2_readValue(uint8 *copy_TIMER2_ptr)
{
	StdReturnType local_errorSignal = OK_STAT;

	if (copy_TIMER2_ptr == NULL)
	{
		local_errorSignal = NOT_OK_STAT;
	}
	else
	{
		*copy_TIMER2_ptr = TCNT2;
	}

	return local_errorSignal;
}

StdReturnType TIMER2_startTimer(uint8 copy_TIMER2_preScaling)
{
	StdReturnType local_errorSignal = OK_STAT;
	if (copy_TIMER2_preScaling < 6)
	{
		TCCR2 &= 0xF8;
		TCCR2 |= copy_TIMER2_preScaling;
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

StdReturnType TIMER2_stopTimer(void)
{
	StdReturnType local_errorSignal = OK_STAT;

	TCCR2 &= 0xF8;
	TCCR2 |= T2_NO_CLK;

	return local_errorSignal;
}

uint8 Timer0_uint8_CompareMatchSetCallBack(void (*copy_pv_CallBackFunc)(void))
{
	uint8 local_uint8_error = OK_STAT;
	if(copy_pv_CallBackFunc != NULL)
	{
		Timer0_pvCompareMatchCallBackFun = copy_pv_CallBackFunc;
	}
	else
	{
		local_uint8_error = NOT_OK_STAT;
	}
	return local_uint8_error;
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(Timer0_pvCompareMatchCallBackFun != NULL)
	{
		Timer0_pvCompareMatchCallBackFun();
	}
}
