/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: RTOS_Interface.h
 * Date: 3 Mar 2024
 */

#ifndef HAL_RTOS_RTOS_INTERFACE_H_
#define HAL_RTOS_RTOS_INTERFACE_H_

#define PRIORITY_TAKEN	2
#define PRIORITY_FREE	1

void RTOS_init(void);
void RTOS_start(void);
void RTOS_addTask(uint8 copy_uint8_priority, uint16 copy_uint16_periodicity, uint16 copy_uint8_firstDelay, void (*pvTaskFunc)(void));
void RTOS_suspendTask(uint8 copy_RTOS_priority);
void RTOS_resumeTask(uint8 copy_RTOS_priority);
void RTOS_removeTask(uint8 copy_RTOS_priority);

#endif /* HAL_RTOS_RTOS_INTERFACE_H_ */
