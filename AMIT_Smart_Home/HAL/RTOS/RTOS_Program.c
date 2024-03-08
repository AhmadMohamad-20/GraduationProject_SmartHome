/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: RTOS_Program.c
 * Date: 3 Mar 2024
 */

#include "../../LIBRARIES/STD_Types.h"
#include "../../LIBRARIES/bitmath.h"

#include "../../MCAL/G_INT/GINT_Interface.h"
#include "../../MCAL/TIMERS/TIMER_Interface.h"

#include "RTOS_Config.h"
#include "RTOS_Private.h"
#include "RTOS_Interface.h"

task_t systemTasks[MAX_NUM] = {{0}};


void RTOS_init(void)
{
	Timer0_uint8_CompareMatchSetCallBack(&Schedular);
	GINT_enableGlobalInterrupt();
	TIMER0_initCTC(125,T0_OC_DISCONNECTED);
	TIMER0_initInterruptOutputCompare();
}

void RTOS_start(void)
{
	TIMER0_startTimer(0x03);
}

void RTOS_addTask(uint8 copy_uint8_priority, uint16 copy_uint16_periodicity, uint16 copy_uint8_firstDelay, void (*pvTaskFunc)(void))
{
	uint8 local_uint8_errorStatus = PRIORITY_FREE;

	copy_uint8_priority--;

	if (systemTasks[copy_uint8_priority].taskFunc == NULL)
	{
		systemTasks[copy_uint8_priority].periodicity = copy_uint16_periodicity;
		systemTasks[copy_uint8_priority].firstDelay = copy_uint8_firstDelay;
		systemTasks[copy_uint8_priority].taskstate = TASK_RUNNING;
		systemTasks[copy_uint8_priority].taskFunc = pvTaskFunc;
	}
	else
	{
		local_uint8_errorStatus = PRIORITY_TAKEN;
	}
}

void RTOS_suspendTask(uint8 copy_RTOS_priority)
{
	copy_RTOS_priority--;
	systemTasks[copy_RTOS_priority].taskstate = TASK_SUSPENDED;
}

void RTOS_resumeTask(uint8 copy_RTOS_priority)
{
	copy_RTOS_priority--;
	systemTasks[copy_RTOS_priority].taskstate = TASK_RUNNING;
}

void RTOS_removeTask(uint8 copy_RTOS_priority)
{
	copy_RTOS_priority--;
	systemTasks[copy_RTOS_priority].taskFunc = NULL;
}

static void Schedular(void)
{
	uint8 local_uint8_taskCounter;

		/*loop on all tasks to check their periodicity*/
		for(local_uint8_taskCounter = OK_STAT ; local_uint8_taskCounter < MAX_NUM ; local_uint8_taskCounter++)
		{
			/*checking if task is running execute it else do nothing*/
			if (systemTasks[local_uint8_taskCounter].taskstate == TASK_RUNNING)
			{
				if(systemTasks[local_uint8_taskCounter].firstDelay == 0)
				{
					if(systemTasks[local_uint8_taskCounter].taskFunc != NULL)
					{
						systemTasks[local_uint8_taskCounter].taskFunc();

						/*assign the first delay parameter to periodicity -1*/
						systemTasks[local_uint8_taskCounter].firstDelay = systemTasks[local_uint8_taskCounter].periodicity - OFFSET;
					}
					else
					{
						/*do nothing*/
					}
				}
				else
				{
					systemTasks[local_uint8_taskCounter].firstDelay--;
				}
			}
			else
			{
				/*task is suspended do nothing*/
			}

		}
}
