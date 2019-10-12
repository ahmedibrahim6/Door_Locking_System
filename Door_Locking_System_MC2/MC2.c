/*
 * DoorLocking.c
 *
 *  Created on: Oct 15, 2018
 *      Author: Ahmed
 */




#include "i2c.h"
#include "uart.h"
#include "external_eeprom.h"
#include <string.h>


#define SAVE_PASSWORD_COMMAND     0
#define CHECK_PASSWORD_COMMAND    1
#define LOCK_AND_BUZZER_COMMAND   2
#define OPEN_DOOR_COMMAND         3
#define PASSWORD_MATCH            4
#define PASSWORD_NOT_MATCH        5
#define PASSWORD_SAVED            6

void Save_Password(void);
void Check_Password(void);
void Lock_And_Buzzer(void);
void Open_Door(void);


int main()
{


	UART_init();
	EEPROM_init();
//	TWI_init();
	DDRB  = 0xFF;
	PORTB = 0x00;

	uint8 command;

	while(1)
	{
		 command = UART_recieveByte();
		_delay_ms(100);
		switch(command)
		{
		    case SAVE_PASSWORD_COMMAND :
		    		Save_Password();
		    		break;

//			case	7 :
//					PORTB = 1<<2;
//					break;
//			case	0 :
//								PORTB = 1<<5;
//								break;
//			case	9:
////					Save_Password();
//					PORTB = 1<<1;
//					break;

			case	CHECK_PASSWORD_COMMAND :
					Check_Password();
					break;

			case	LOCK_AND_BUZZER_COMMAND :
					Lock_And_Buzzer();
					break;

			case	OPEN_DOOR_COMMAND :
					Open_Door();
					break;

			default : break ;

		}

	}


}





void Save_Password()
{
	uint8 str[8]; //For Storing
	uint8 val[8]; //For Checking

	UART_sendByte(SAVE_PASSWORD_COMMAND);
	_delay_ms(100);
	UART_recieveString(str);

	EEPROM_writeString(0x0311, str);
	_delay_ms(100);

	UART_sendByte(PASSWORD_SAVED);
	_delay_ms(100);

	EEPROM_readString(0x0311, val);

	//Compare Stored String With Received String
	uint8 cmp = strcmp((const char*)val,(const char*)str);

	//Check If Password Is Stored Correctly
	if (cmp == 0) //match
		PORTB = 1<<0;
	else
		PORTB = 1<<1;

}



void Check_Password()
{
	uint8 str[8];
	uint8 val[8];

	UART_sendByte(CHECK_PASSWORD_COMMAND);
	_delay_ms(100);
	UART_recieveString(str);

	//Read Stored String in EEPROM
	EEPROM_readString(0x0311, val);


	//Compare Received String with Stored String
	uint8 cmp = strcmp((const char*)val,(const char*)str);

	if (cmp == 0) //match
	{
		UART_sendByte(PASSWORD_MATCH);
		PORTB = 1<<2;
	}
	else
	{
		UART_sendByte(PASSWORD_NOT_MATCH);
		PORTB = 1<<3;
	}



}



void Lock_And_Buzzer()
{




}



void Open_Door()
{



}
