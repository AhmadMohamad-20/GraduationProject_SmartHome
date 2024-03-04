/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: BM_Interface.h
 * Date: 4 Mar 2024
 */

#ifndef HAL_BLUETOOTH_MODULE_BM_INTERFACE_H_
#define HAL_BLUETOOTH_MODULE_BM_INTERFACE_H_

void BM_init(void);
void BM_sendByte(uint8 copy_BM_dataByte);
uint8 BM_recieveByte(void);
void BM_sendString(uint8 *copy_BM_stringPtr);
void BM_recieveString(uint8 *copy_BM_stringPtr);

#endif /* HAL_BLUETOOTH_MODULE_BM_INTERFACE_H_ */
