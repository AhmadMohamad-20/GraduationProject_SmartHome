/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TWI_Interface.h
 * Date: 10 Feb 2024
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum {
	NoError,
	StartConditionErr,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
}TWI_ErrStatus;

/*Set master address to 0 if master will not be addressed*/
void TWI_InitMaster(uint8 Copy_uint8Address);

void TWI_InitSlave(uint8 Copy_uint8Address);

TWI_ErrStatus TWI_SendStartCondition(void);

TWI_ErrStatus TWI_SendRepeatedStart(void);

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(uint8 Copy_uint8SlaveAddress);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(uint8 Copy_uint8SlaveAddress);

TWI_ErrStatus TWI_MasterWriteDataByte(uint8 Copy_uint8DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(uint8* Copy_puint8DataByte);

void TWI_SendStopCondition(void);

void DisableAck(void);

void EnableAck(void);


#endif /* TWI_INTERFACE_H_ */
