/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DCM_Interface.h
 * Date: 17 Feb 2024
 */

#ifndef HAL_DC_MOTOR_DCM_INTERFACE_H_
#define HAL_DC_MOTOR_DCM_INTERFACE_H_

#define DCM_PORT DIO_PORTD
#define DCM_PIN	PIN3

void DCM_init(void);
StdReturnType DCM_turnOn(void);
StdReturnType DCM_turnOff(void);

#endif /* HAL_DC_MOTOR_DCM_INTERFACE_H_ */
