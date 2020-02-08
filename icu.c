/*
 * icu.c
 *
 * Created: 08-Jan-20 2:09:19 PM
 *  Author: ahmed
 */ 
#include "icu.h"
#include <avr/interrupt.h>
volatile uint8 icuflag = 0;
volatile uint16 distance=0;
void ICU_Init(void)
{
	/*Timer 1*/
	/*ICP1 -->PD4 input pin*/
	DDRD&=~(1<<PD4);
	/*8 prescalar -- rising edge -- */
	TCCR1B = (1<<CS11)|(1<<ICES1);
	/*initial*/
	TCNT1 = 0;
	ICR1 = 0;
	/*ICU interrupt enable*/
	TIMSK = (1<<TICIE1);
}
void ICU_DisableTimer(void)
{
	TCCR1B &=~(1<<CS11);
}
ISR(TIMER1_CAPT_vect)
{
	icuflag++;
	if(icuflag == 1)
	{
		TCNT1 = 0;
		TCCR1B&=~(1<<ICES1);
	}
	else if(icuflag == 2)
	{
		distance = ICR1;
		TCNT1 = 0;
		TCCR1B |=(1<<ICES1);
		icuflag = 0;
	}
}