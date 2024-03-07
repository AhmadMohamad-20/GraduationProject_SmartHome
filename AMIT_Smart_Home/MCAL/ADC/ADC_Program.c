/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: ADC_program.c
 * Date: 22 Dec 2023
 */
#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../DIO/DIO_Interface.h"
#include "../G_INT/GINT_Interface.h"

#include "ADC_Reg.h"
#include "ADC_CFG.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"



static uint8 global_AsyncStatus = 0;
static uint8 ADC_available = ADC_IDLE;

static uint8 *ChainChannelID = NULL;
static uint8 *ChainReadig = NULL;
void (*ptrFun)(void) = NULL;
uint8 ChainAsyncIndex = 0;

void (*ADC_ptrFun)(void) = NULL;



void setCallBack_ADC(void (*funcPtr)(void))
{
	ADC_ptrFun = funcPtr;
}

/*void setCallBack_ADC_Chain(void (funcArr[MAX_NUM])(void))
{
	uint8 index = 0;
	for (;index < MAX_NUM; index++)
	{
		(Asensors.pfADC_CallBack[index])() = (funcArr[index])();
	}
}
*/


void ADC_init(void)
{
	/* AREF CONFIGURATIONS */
#if (ADMUX_AREF_CFG == ADMUX_AREF)
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
	CLEAR_BIT(ADMUX,ADMUX_REFS0);
#elif (ADMUX_AREF_CFG == ADMUX_AVRE_AVCC)
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#elif (ADMUX_AREF_CFG == ADMUX_AREF_INT)
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#else
#error "WRONG AREF CONFIGURATIONS , PLEASE CHOOSE CORRECT ONES !!"
#endif

	/* ADLAR CONFIGURATION */
#if (ADLAR_CFG == LEFT_ADJUST)
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif (ADLAR_CFG == RIGHT_ADJUST)
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "WRONG ADLAR CONFIGURATIONS , PLEASE CHOOSE CORRECT ONES !!"
#endif

	/* Conversion type configuration */
#if (CONVERSION_TYPE == SINGLE_CONVERSION)
	CLEAR_BIT(ADCSRA,ADCSRA_ADATE);
#else
	SET_BIT(ADCSRA,ADCSRA_ADATE);
#endif

	/*Interrupt configurations*/
#if(ADC_INT_STATUS == ADC_INT_DISABLE)
	CLEAR_BIT(ADCSRA,ADCSRA_ADIE);
#elif (ADC_INT_STATUS == ADC_INT_ENABLE)
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#else
#error "WRONG ADC INTERRUPT CONFIGURATIONS , PLEASE CHOOSE CORRECT ONES !!"
#endif
	/* PreScaling */
	ADCSRA |= DF128_MASK;

	/* ENABLE ADC */
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

uint8 ADC_startConversionSync(uint8 copy_ADC_channels, uint8 *copy_ADC_data)
{
	uint8 local_errorState = OK_STAT;
	uint32 global_ADC_timeOut = 0;
	if (ADC_available == ADC_IDLE)
	{
		if (copy_ADC_data != NULL)
			{
				ADMUX &= 0b11100000;
				ADMUX |= copy_ADC_channels;
				SET_BIT(ADCSRA,ADCSRA_ADSC);
				while ((!GET_BIT(ADCSRA,ADCSRA_ADIF)) && (global_ADC_timeOut < ADC_TIME_OUT))
				{
					global_ADC_timeOut++;
				}
				if (global_ADC_timeOut >= ADC_TIME_OUT)
				{
					local_errorState = TIMEOUT;
				}
				else
				{
					SET_BIT(ADCSRA,ADCSRA_ADIF);
					*copy_ADC_data = ADCH;
				}
				global_ADC_timeOut = 0;
			}
			else
			{
				local_errorState = NOT_OK_STAT;
			}

	}

	return local_errorState;
}

void ADC_startConversionAsync(uint8 copy_ADC_channels)
{

	if (ADC_available == ADC_IDLE)
	{
		global_AsyncStatus = NORMAL_ASYNC;
		ADMUX &= 0b11100000;
		ADMUX |= copy_ADC_channels;

		ADC_available = ADC_BUSY;
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*enable Interrupt*/

		SET_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else
	{

	}

}

uint8 ADC_startChainConversionSync(ADC_chainSync_t *chainSync)
{
	uint8 local_errorSignal = OK_STAT;
	uint8 local_counter = 0;
	uint8 *local_ptr = NULL;
	for(local_counter = 0; local_counter < MAX_NUM; local_counter++)
	{
		local_ptr = &(chainSync->ADC_Reading[local_counter]);
		chainSync->ADC_error[local_counter] = ADC_startConversionSync(chainSync->channelID[local_counter],local_ptr);
	}

	return local_errorSignal;
}

void ADC_startChainConversionAsync(ADC_chainAsync_t *chainAsync)
{
	if ((ADC_available == ADC_IDLE))
		{
			GINT_enableGlobalInterrupt();
			global_AsyncStatus = CHAIN_ASYNC;
			ChainChannelID = chainAsync->channelID;
			ChainReadig = chainAsync->ADC_Reading;
			//chainAsync->pfADC_CallBack = ADC_ptrFun;

			ADMUX &= 0b11100000;
			ADMUX |= ChainChannelID[ChainAsyncIndex];
			ADC_available = ADC_BUSY;
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*enable Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
			}
		else
		{

		}

}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
if (global_AsyncStatus == NORMAL_ASYNC)
	{
		*ADC_value = ADCH;
		ADC_ptrFun();
		CLEAR_BIT(ADCSRA,ADCSRA_ADIE);
		ADC_available = ADC_IDLE;
	}

else if (global_AsyncStatus == CHAIN_ASYNC)
	{
		ChainReadig[ChainAsyncIndex] = ADCH;
		ADC_ptrFun();

		ChainAsyncIndex++;
		if (ChainAsyncIndex == MAX_NUM)
		{

			ADC_available = ADC_IDLE;
			CLEAR_BIT(ADCSRA,ADCSRA_ADIE);
			//ChainAsyncIndex = 0;
			ChainAsyncIndex = 0;
		}
		else
		{

			ADMUX &= 0b11100000;
			ADMUX |= ChainChannelID[ChainAsyncIndex];
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}


	}
}
