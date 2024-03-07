/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TS_Interface.h
 * Date: 5 Mar 2024
 */

#ifndef HAL_TEMPERATURE_SENSOR_TS_INTERFACE_H_
#define HAL_TEMPERATURE_SENSOR_TS_INTERFACE_H_

#define TS_PORT DIO_PORTA
#define TS_PIN	PIN0

void TS_init(void);
uint8 TS_sendData(void);
#endif /* HAL_TEMPERATURE_SENSOR_TS_INTERFACE_H_ */
