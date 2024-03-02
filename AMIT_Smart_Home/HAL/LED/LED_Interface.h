/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: LED_Interface.h
 * Date: 17 Feb 2024
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

StdReturnType LED_turnOn(uint8 copy_LED_port, uint8 copy_LED_pin);
StdReturnType LED_turnOff(uint8 copy_LED_port, uint8 copy_LED_pin);
StdReturnType LED_toggle(uint8 copy_LED_port, uint8 copy_LED_pin);

StdReturnType LED_dimmerControl(uint8 copy_LED_port, uint8 copy_LED_pin, uint8 copy_LED_dutyCycle);
#endif /* HAL_LED_LED_INTERFACE_H_ */
