/*
 * timer.c
 *
 *  Created on: Oct 13, 2019
 *      Author: ahmez
 */

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

void timer_init(void)
{
	OCR1A = 15625; //1sec
	TCCR1B = (1<<WGM12);
	TCCR1B |= (1<<CS11) | (1<<CS10);
}

void start_timer(uint8 secs)
{
	TCNT1 = 0; //Initialize Counter
	for(uint8 i = 0; i<secs; i++)
	{
		while(! (TIFR & 1<<OCF1A)); //Wait For Match Flag

		TIFR |= (1<<OCF1A);//Clear Compare Match Flag
	}
}

void Enable_Timer(void)
{
	TCCR1B |= (1<<CS11) | (1<<CS10);
}

void Disable_Timer(void)
{
        TCCR1B = (1<<WGM12);
}
