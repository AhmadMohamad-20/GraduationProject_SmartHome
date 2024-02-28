/*
 * KEYPAD_Interfacing.h
 *
 *  Created on: 15 Dec 2023
 *      Author: user
 */

#ifndef KEYPAD_INTERFACING_H_
#define KEYPAD_INTERFACING_H_

void KEYPAD_init(void);
uint8 KEYPAD_getValue(void);
void KEPAD_getString(char *copy_KEYPAD_ptr, uint8 copy_KEYPAD_max);
#endif /* KEYPAD_INTERFACING_H_ */
