/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: LED_Interface.h
 * Date: 17 Feb 2024
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

#define LED1_PORT	2
#define LED1_PIN	3

#define LED2_PORT	2
#define LED2_PIN	4


#define LED3_PORT	2
#define LED3_PIN	5

#define LED4_PORT	2
#define LED4_PIN	6

#define LED5_PORT	2
#define LED5_PIN	7

#define LED6_PORT	3
#define LED6_PIN	8

StdReturnType LED_init(uint8 copy_LED_port, uint8 cop_LED_pin);
StdReturnType LED_turnOn(uint8 copy_LED_port, uint8 copy_LED_pin);
StdReturnType LED_turnOff(uint8 copy_LED_port, uint8 copy_LED_pin);
StdReturnType LED_toggle(uint8 copy_LED_port, uint8 copy_LED_pin);

StdReturnType LED_dimmerControl(uint8 copy_LED_port, uint8 copy_LED_pin, uint8 copy_LED_dutyCycle);
#endif /* HAL_LED_LED_INTERFACE_H_ */
