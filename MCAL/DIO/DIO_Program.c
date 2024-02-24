/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DIO_Program.c
 * Date: 17 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "DIO_registers.h"
#include "DIO_Config.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

void DIO_portsInit(void)
{
	DDRA = DDRA_VALUE;
	DDRB = DDRB_VALUE;
	DDRC = DDRC_VALUE;
	DDRD = DDRD_VALUE;

	PORTA = PORTA_VALUE;
	PORTB = PORTB_VALUE;
	PORTC = PORTC_VALUE;
	PORTD = PORTD_VALUE;
}

StdReturnType DIO_setPinDirection(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_direction)
{
	StdReturnType local_errorState = OK_STAT;
	if (copy_DIO_pin <= PIN7)
	{
		if (copy_DIO_direction == OUTPUT)
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					SET_BIT(DDRA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					SET_BIT(DDRB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					SET_BIT(DDRC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					SET_BIT(DDRD,copy_DIO_pin);
					break;
				default:
					local_errorState = NOT_OK_STAT;
			}
		}
		else if (copy_DIO_direction == INPUT)
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					CLEAR_BIT(DDRA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					CLEAR_BIT(DDRB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					CLEAR_BIT(DDRC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					CLEAR_BIT(DDRD,copy_DIO_pin);
					break;
				default:
					local_errorState = NOT_OK_STAT;
			}
		}
		else
		{
			local_errorState = NOT_OK_STAT;
		}
	}
	else
	{
		local_errorState = NOT_OK_STAT;
	}

	return local_errorState;
}

StdReturnType DIO_setPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin, uint8 copy_DIO_value)
{
	StdReturnType local_errorSignal = OK_STAT;
	if (copy_DIO_pin <= PIN7)
	{
		if (copy_DIO_value == HIGH)
		{
			switch(copy_DIO_port)
			{
				case DIO_PORTA:
					SET_BIT(PORTA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					SET_BIT(PORTB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					SET_BIT(PORTC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					SET_BIT(PORTD,copy_DIO_pin);
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
		else if(copy_DIO_value == LOW)
		{
			switch(copy_DIO_port)
			{
				case DIO_PORTA:
					CLEAR_BIT(PORTA,copy_DIO_pin);
					break;
				case DIO_PORTB:
					CLEAR_BIT(PORTB,copy_DIO_pin);
					break;
				case DIO_PORTC:
					CLEAR_BIT(PORTC,copy_DIO_pin);
					break;
				case DIO_PORTD:
					CLEAR_BIT(PORTD,copy_DIO_pin);
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
		else
		{
			local_errorSignal = NOT_OK_STAT;
		}
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

StdReturnType DIO_readPinValue(uint8 copy_DIO_port, uint8 copy_DIO_pin,  uint8 *copy_DIO_pValue)
{
	StdReturnType local_errorState = OK_STAT;
	if ((copy_DIO_pin <= PIN7) && (copy_DIO_pValue != NULL))
	{
		switch (copy_DIO_port)
		{
			case DIO_PORTA:
				*copy_DIO_pValue = GET_BIT(PINA,copy_DIO_pin);
				break;
			case DIO_PORTB:
				*copy_DIO_pValue = GET_BIT(PINB,copy_DIO_pin);
				break;
			case DIO_PORTC:
				*copy_DIO_pValue = GET_BIT(PINC,copy_DIO_pin);
				break;
			case DIO_PORTD:
				*copy_DIO_pValue = GET_BIT(PIND,copy_DIO_pin);
				break;
			default:
				local_errorState = NOT_OK_STAT;
				break;
		}
	}
	else
	{
		local_errorState = NOT_OK_STAT;
	}
	return local_errorState;
}

StdReturnType DIO_setIntPullUpRes(uint8 copy_DIO_port, uint8 copy_DIO_pin)
{
	StdReturnType local_errorSignal = OK_STAT;
	local_errorSignal = DIO_setPinDirection(copy_DIO_port,copy_DIO_pin,INPUT);
	if (local_errorSignal == OK_STAT)
	{
		local_errorSignal = DIO_setPinValue(copy_DIO_port,copy_DIO_pin,HIGH);
	}
	return local_errorSignal;
}

StdReturnType DIO_togglePin(uint8 copy_DIO_port, uint8 copy_DIO_pin)
{
	StdReturnType local_errorSignal = OK_STAT;
	if (copy_DIO_pin <= PIN7)
	{
		switch(copy_DIO_port)
		{
		case DIO_PORTA:
			TOGGLE_BIT(PORTA,copy_DIO_pin);
			break;
		case DIO_PORTB:
			TOGGLE_BIT(PORTB,copy_DIO_pin);
			break;
		case DIO_PORTC:
			TOGGLE_BIT(PORTC,copy_DIO_pin);
			break;
		case DIO_PORTD:
			TOGGLE_BIT(PORTD,copy_DIO_pin);
			break;
		default:
			local_errorSignal = NOT_OK_STAT;
			break;
		}
	}
	else
	{
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

StdReturnType DIO_setPortDirection(uint8 copy_DIO_port,  uint8 copy_DIO_direction)
{
	StdReturnType local_errorSignal = OK_STAT;
	if ((copy_DIO_direction == PORT_OUTPUT) || (copy_DIO_direction == PORT_INPUT))
		{
			switch (copy_DIO_port)
			{
				case DIO_PORTA:
					DDRA = copy_DIO_direction;
					break;
				case DIO_PORTB:
					DDRB = copy_DIO_direction;
					break;
				case DIO_PORTC:
					DDRC = copy_DIO_direction;
					break;
				case DIO_PORTD:
					DDRD = copy_DIO_direction;
					break;
				default:
					local_errorSignal = NOT_OK_STAT;
					break;
			}
		}
	return local_errorSignal;
}

StdReturnType DIO_setPortValue(uint8 copy_DIO_port, uint8 copy_DIO_value)
{
	StdReturnType local_errorSignal = OK_STAT;

	switch (copy_DIO_port)
	{
		case DIO_PORTA:
			PORTA = copy_DIO_value;
			break;
		case DIO_PORTB:
			PORTB = copy_DIO_value;
			break;
		case DIO_PORTC:
			PORTC = copy_DIO_value;
			break;
		case DIO_PORTD:
			PORTD = copy_DIO_value;
			break;
		default:
			local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

StdReturnType DIO_ReadPortValue(uint8 copy_DIO_port,  uint8 *copy_DIO_pValue)
{
	StdReturnType local_errorSignal = OK_STAT;
	if ((copy_DIO_port <= DIO_PORTD) && (copy_DIO_pValue != NULL))
	{
		switch (copy_DIO_port)
		{
			case DIO_PORTA:
				*copy_DIO_pValue = PINA;
				break;
			case DIO_PORTB:
				*copy_DIO_pValue = PINB;
				break;
			case DIO_PORTC:
				*copy_DIO_pValue = PINC;
				break;
			case DIO_PORTD:
				*copy_DIO_pValue = PIND;
				break;
			default:
				local_errorSignal = NOT_OK_STAT;
				break;
		}
	}

	return local_errorSignal;
}

StdReturnType DIO_togglePort(uint8 copy_DIO_port)
{
	StdReturnType local_errorSignal = OK_STAT;
	switch (copy_DIO_port)
	{
	case DIO_PORTA:
		PORTA ^= 0xFF;
		break;
	case DIO_PORTB:
		PORTB ^= 0xFF;
		break;
	case DIO_PORTC:
		PORTC ^= 0xFF;
		break;
	case DIO_PORTD:
		PORTD ^= 0xFF;
		break;
	default:
		local_errorSignal = NOT_OK_STAT;
	}
	return local_errorSignal;
}

