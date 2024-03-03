/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: RTOS_Private.h
 * Date: 3 Mar 2024
 */

#ifndef HAL_RTOS_RTOS_PRIVATE_H_
#define HAL_RTOS_RTOS_PRIVATE_H_

#define TASK_SUSPENDED	1
#define TASK_RUNNING	2
#define OFFSET			1

typedef struct
{
	uint16 periodicity;
	uint8 taskstate;
	uint16 firstDelay;
	void (*taskFunc)(void);
}task_t;

static void Schedular(void);

#endif /* HAL_RTOS_RTOS_PRIVATE_H_ */
