/*
 * DoorLocking.c
 *
 *  Created on: Oct 15, 2018
 *      Author: Ahmed
 */




#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include <string.h>

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

void OPTION1_setNewPassword(void);
void OPTION2_ChangePassword(void);
void OPTION3_openDoor(void);
void OPTION4_mismatchPassword( void(*ptr) (void));
bool GET_passwordAndCheck();
void OPENING_door(void);
void LOCK_and_Buzzer(void);

//bool g_setPasswordFirstTime = TRUE ;

uint8 *g_password;

int main()
{
	UART_init();
	LCD_init();
	timer_init();

	OPTION1_setNewPassword();
	uint8 pressedKey;

	while(1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"+ : Change Pass");
		LCD_displayStringRowColumn(1,0,"- : Open Door");

		pressedKey = KeyPad_getPressedKey();

		if( pressedKey == CHANGE_PASS_KEY )
		{
			OPTION2_ChangePassword();
		}

		else if( pressedKey == OPEN_DOOR_KEY )
		{
			OPTION3_openDoor();
		}

	}


}

void OPTION1_setNewPassword(void)
{
	uint8 key,counter =0,cmp = 0;
	uint8 Str_password1[8],Str_password2[8];
	uint8 *str1 = Str_password1 ;
	uint8 *str2 = Str_password2 ;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"New Pass :");

	key = KeyPad_getPressedKey();

	while( key != ENTER_KEY)
	{

		LCD_displayStringRowColumn(1,counter,"*");
		str1 [counter] = key;
		_delay_ms(250); /* Press time */
		counter++;
		key = KeyPad_getPressedKey(); /* get the pressed key number */
	}
	str1 [counter] = '#';
	str1 [counter+1] = '\0';
	///////////////////////////////////////
	counter =0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-enter Pass :");

	key = KeyPad_getPressedKey();
	while( key != ENTER_KEY)
	{

		LCD_displayStringRowColumn(1,counter,"*");
		str2 [counter] = key;
		_delay_ms(250); /* Press time */
		counter++;
		key = KeyPad_getPressedKey(); /* get the pressed key number */
	}
	str2 [counter] = '#';
	str2 [counter+1] = '\0';

	cmp = strcmp(str1,str2);
	if (cmp != 0)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,1,"Mismatch Pass");
		_delay_ms(2000);
		OPTION1_setNewPassword();
	}
	else   // Matched password so save it in eeprom
	{

		UART_sendByte(SAVE_PASSWORD_COMMAND);
		_delay_ms(100);
		if( UART_recieveByte() == SAVE_PASSWORD_COMMAND)
		{
			_delay_ms(100);
			UART_sendString(str2);
		}
		_delay_ms(100);
		while( UART_recieveByte() != PASSWORD_SAVED);


	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void OPTION2_ChangePassword()
{

	if( GET_passwordAndCheck() )
	{
		OPTION1_setNewPassword();
	}
	else
	{
		OPTION4_mismatchPassword(OPTION1_setNewPassword);
	}
}

void OPTION3_openDoor()
{
	if( GET_passwordAndCheck() )
	{
		OPENING_door();
	}
	else
	{
		OPTION4_mismatchPassword(OPENING_door);
	}
}


void OPTION4_mismatchPassword( void(*ptr) (void) )
{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		if( GET_passwordAndCheck() )
		{
			(*ptr)();
			return;

		}
	}

	LOCK_and_Buzzer();
}




bool GET_passwordAndCheck()
{
	uint8 key,counter =0;
	uint8 Str_passwordInput[8];
	uint8 *str1 = Str_passwordInput ;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Pass :");
	//LCD_displayStringRowColumn(1,0,"- : Open Door");
	key = KeyPad_getPressedKey();

	while( key != ENTER_KEY)
	{
		LCD_displayStringRowColumn(1,counter,"*");
		str1 [counter] = key;
		_delay_ms(250); /* Press time */
		counter++;
		key = KeyPad_getPressedKey(); /* get the pressed key number */
	}
	str1 [counter] = '#';
	str1 [counter+1] = '\0';

	UART_sendByte(CHECK_PASSWORD_COMMAND);
	_delay_ms(100);

	if( UART_recieveByte() == CHECK_PASSWORD_COMMAND)
		{
			_delay_ms(100);
			UART_sendString(str1);
		}

	_delay_ms(100);
	if(UART_recieveByte() == PASSWORD_MATCH)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




void OPENING_door()
{
	UART_sendByte(OPEN_DOOR_COMMAND);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Openning Door...");

	UART_recieveByte(); //Door Opened
}

void LOCK_and_Buzzer()
{
	Enable_Timer();

	//Turn On Buzzer
	/*
	 * Code
	 */

	start_timer(90); //Start Timer for 90 secs.

	//Turn Off Buzzer
	/*
	 * Code
	 */

	Disable_Timer();
}

