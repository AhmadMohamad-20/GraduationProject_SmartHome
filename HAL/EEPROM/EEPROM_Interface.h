/*
 * EEPROM_Interface.h
 *
 *  Created on: Jan 23, 2024
 *      Author: Sherif
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataByte(uint16 Copy_uint16LocationAddress, uint8 Copy_uint8DataByte);
uint8 EEPROM_uint8ReadDataByte(uint16 Copy_uint16LocationAddress);
void EEPROM_voidSend4Numbers(uint16 Copy_uint16LocationAddress, char* Array_Recieve_Str);
void EEPROM_voidRead4Numbers(uint16 Copy_uint16LocationAddress, char* Array_Recieve_Str);
void EEPROM_voidSendString(uint16 Copy_uint16LocationAddress, char* str);

#endif /* EEPROM_INTERFACE_H_ */
