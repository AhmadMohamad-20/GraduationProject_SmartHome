/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: TWI_Private.h
 * Date: 10 Feb 2024
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWWC	3
#define TWEN	2
#define TWIE	0

#define TWPS1	1
#define TWPS0	0

#define STATUS_MODE 				(TWSR & 0xF8)
/* Master Transimitter */
#define START_CONDITION_STATUS		0x08	/* master start condition */
#define REPEATED_CONDITION_STATUS	0x10	/* master repeated start condition */
#define SLAVE_ADDRESS_WRITE_ACK		0x18	/* master send slave address + write => slave ack */
#define SLAVE_ADDRESS_WRITE_NACK	0x20	/* master send slave address + write => slave not ack */
#define MSTR_WR_BYTE_ACK         	0x28 	/* Master transmit data ACK */
#define MSTR_WR_BYTE_NACK         	0x30 	/* Master transmit data Not ACK */

/* Master Reciever */
#define SLAVE_ADDRESS_READ_ACK		0x40	/* master send slave address + read => slave ack */
#define SLAVE_ADDRESS_READ_NACK		0x48	/* master send slave address + read => slave not ack */
#define MSTR_RD_BYTE_WITH_ACK   	0x50 	/* Master received data with ACK */
#define MSTR_RD_BYTE_WITH_NACK   	0x58 	/* Master received data with not ACK */

#endif /* TWI_PRIVATE_H_ */
