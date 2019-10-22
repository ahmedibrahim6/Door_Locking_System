/*
 * DoorLocking.c
 *
 *  Created on: Oct 15, 2018
 *      Author: Ahmed
 */




#include "MC2.h"


int main()
{
	timer_init();

	UART_init();
	EEPROM_init();

//	DDRB  = 0xFF;
//	PORTB = 0x00;

	//MOTOR Pin Initialization
	/* configure pin PC0 and PC1 as output pins */
	DDRC |= (1<<PC2);
	DDRC |= (1<<PC3);

	/* Motor is stopped at the beginning */
	PORTC &= ~(1<<PC0);
	PORTC &= ~(1<<PC1);

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

			case	CHECK_PASSWORD_COMMAND :
					Check_Password();
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
	//Check Indicator On Leds
//	if (cmp == 0) //match
//		PORTB = 1<<0;
//	else
//		PORTB = 1<<1;

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

	//Check Indicator On Leds
	if (cmp == 0) //match
	{
		UART_sendByte(PASSWORD_MATCH);
//		PORTB = 1<<2;
	}
	else
	{
		UART_sendByte(PASSWORD_NOT_MATCH);
//		PORTB = 1<<3;
	}
}



void Open_Door()
{
	Enable_Timer();

	// MOTOR clockwise Opening
	PORTC &= (~(1<<PC2));
	PORTC |= (1<<PC3);

	start_timer(15); //Count from to 0 to 15 Secs

	// MOTOR Anticlockwise Closing
	PORTC |= (1<<PC2);
	PORTC &= (~(1<<PC3));

	start_timer(15); //Count from to 0 to 15 Secs

	// MOTOR Stopping
	PORTC &= (~(1<<PC2));
	PORTC &= (~(1<<PC3));

	UART_sendByte(OPEN_DOOR_COMMAND); //Door Opened

	Disable_Timer(); //disable timer clock
}
