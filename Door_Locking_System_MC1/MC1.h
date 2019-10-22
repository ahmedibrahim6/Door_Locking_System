/*
 * MC1.h
 *
 *  Created on: Oct 22, 2019
 *      Author: HP
 */

#ifndef MC1_H_
#define MC1_H_

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include <string.h>


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define SAVE_PASSWORD_COMMAND     0
#define CHECK_PASSWORD_COMMAND    1
#define LOCK_AND_BUZZER_COMMAND   2
#define OPEN_DOOR_COMMAND         3
#define PASSWORD_MATCH            4
#define PASSWORD_NOT_MATCH        5
#define PASSWORD_SAVED            6

#define ENTER_KEY        13
#define CHANGE_PASS_KEY  '+'
#define OPEN_DOOR_KEY    '-'


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void OPTION1_setNewPassword(void);

void OPTION2_ChangePassword(void);

void OPTION3_openDoor(void);

void OPTION4_mismatchPassword( void(*ptr) (void));

bool GET_passwordAndCheck();

void OPENING_door(void);

void LOCK_and_Buzzer(void);


#endif /* MC1_H_ */
