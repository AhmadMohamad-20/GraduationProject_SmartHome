/*
 * UART_priv.h
 *
 *  Created on: 5 Jan 2024
 *      Author: Ziad Yakoot
 */

#ifndef UART_PRIV_H_
#define UART_PRIV_H_

#define USCRA_RXC       7
#define USCRA_TXC       6
#define USCRA_UDRE      5
#define USCRA_FE        4
#define USCRA_DOR       3
#define USCRA_PE        2
#define USCRA_U2X       1
#define USCRA_MPCM      0

#define USCRB_RXCIE     7
#define USCRB_TXCIE     6
#define USCRB_UDRIE     5
#define USCRB_RXEN      4
#define USCRB_TXEN      3
#define USCRB_UCSZ2     2
#define USCRB_RXB8      1
#define USCRB_TXB8      0

#define USCRC_URSEL     7
#define USCRC_UMSEL     6
#define USCRC_UPM1      5
#define USCRC_UPM0      4
#define USCRC_USBS      3
#define USCRC_UCSZ1     2
#define USCRC_UCSZ0     1
#define USCRC_UCPOL     0

#endif /* UART_PRIV_H_ */
