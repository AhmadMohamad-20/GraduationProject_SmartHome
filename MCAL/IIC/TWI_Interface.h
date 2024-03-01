/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TWI_Interface.h
 * Date: 10 Feb 2024
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

#define MASTER_READ		1
#define MASTER_WRITE	0


void TWI_initMasterWithoutAddress(void);
void TWI_initMasterWithAddress(uint8 copy_TWI_Address);
void TWI_sendStartCondition(void);
void TWI_sendRepeatedStartCondition(void);
void TWI_sendStopCondition(void);
uint8 TWI_sendSlaveAddressAndStatWrite(uint8 copy_TWI_slaveAddress);
void TWI_sendSlaveAddressAndStatRead(uint8 copy_TWI_slaveAddress);
void TWI_sendDataByteMaster(uint8 copy_TWI_dataByte);
void TWI_recieveDataByteMaster(uint8 *copy_TWI_dataBytePtr);

void TWI_initSlave(uint8 copy_TWI_slaveAddress);
void TWI_sendDataByteSlave(uint8 copy_TWI_dataByte);
void TWI_recieveDataByteSlave(uint8 *copy_TWI_dataBytePtr);
uint8 TWI_checkIfCalled(void);
#endif /* TWI_INTERFACE_H_ */
