/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: main.h
 * Date: 29 Feb 2024
 */

#ifndef MAIN_H_
#define MAIN_H_

#define ADMIN_SELECTED	0x31
#define USER_SELECTED	0x32

#define ADMIN_PASSWORD	0x00

#define USER1_ID		0x30
#define USER1_PASSWORD	0x34

#define MAX_NUM_ID    	 3
#define MAX_NUM_PASSWORD 4


void systemInit(void);
void loginToSystem(void);
void add_user(void);
void RemoveUser(uint8* copy_userID);

#endif /* MAIN_H_ */
