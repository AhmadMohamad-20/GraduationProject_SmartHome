/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: EEPROM_Interface.h
 * Date: 12 Feb 2024
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_init(void);
void EEPROM_writeDataByte(uint16 copy_EEPROM_address, uint8 copy_EEPROM_data);
void EEPROM_deleteByte(uint16 copy_EEPROM_address);
uint8 EEPROM_readDataByte(uint16 copy_EEPROM_address);
void EEPROM_writeString(uint16 cop_EEPROM_address, char *copy_EEPROM_ptr);
void EEPROM_readString(uint16 copy_EEPROM_ADDRESS, char *copy_EEPROM_ptr);

#endif /* EEPROM_INTERFACE_H_ */
