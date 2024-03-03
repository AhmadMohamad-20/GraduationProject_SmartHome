/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: GINT_Program.c
 * Date: 18 Feb 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "GINT_Register.h"
#include "GINT_Config.h"
#include "GINT_Private.h"
#include "GINT_Interface.h"

void GINT_enableGlobalInterrupt(void)
{
	SET_BIT(SREG,I_BIT);
}

void GINT_disableGlobalInterrupt(void)
{
	CLEAR_BIT(SREG,I_BIT);
}
