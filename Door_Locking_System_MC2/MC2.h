/*
 * MC2.h
 *
 *  Created on: Oct 23, 2019
 *      Author: HP
 */

#ifndef MC2_H_
#define MC2_H_

#include "i2c.h"
#include "uart.h"
#include "external_eeprom.h"
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


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void Save_Password(void);

void Check_Password(void);

void Open_Door(void);


#endif /* MC2_H_ */
