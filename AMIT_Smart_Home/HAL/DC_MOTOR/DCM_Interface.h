/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: DCM_Interface.h
 * Date: 17 Feb 2024
 */

#ifndef HAL_DC_MOTOR_DCM_INTERFACE_H_
#define HAL_DC_MOTOR_DCM_INTERFACE_H_

StdReturnType DCM_turnOn(uint8 copy_DCM_port, uint8 copy_DCM_pin);
StdReturnType DCM_turnOff(uint8 copy_DCM_port, uint8 copy_DCM_pin);

#endif /* HAL_DC_MOTOR_DCM_INTERFACE_H_ */
