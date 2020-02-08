/*
 * timer.h
 *
 * Created: 08/01/2020 22:01:29
 *  Author: SHADY
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "std_Types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "avr/io.h"
#include "avr/interrupt.h"

void Timer0_CTCInit(void);
void Timer3_PWMInit(uint16 duty);
void Timer1_OVFInit(void);
void setCallback(void(*funPtr)(void));
#endif /* TIMER_H_ */