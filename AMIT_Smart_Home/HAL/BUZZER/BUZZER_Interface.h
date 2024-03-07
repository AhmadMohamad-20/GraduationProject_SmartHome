/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: BUZZER_Interface.h
 * Date: 7 Mar 2024
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_

#define BUZZER_PORT	DIO_PORTD
#define BUZZER_PIN	PIN2

void BUZZER_init(void);
void BUZZER_ON(void);

#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
