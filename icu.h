/*
 * icu.h
 *
 * Created: 08-Jan-20 2:09:34 PM
 *  Author: ahmed
 */ 


#ifndef ICU_H_
#define ICU_H_
#include "std_Types.h"
#include "common_macros.h"
#include "micro_config.h"
extern volatile uint16 distance;
void ICU_Init(void);
void ICU_DisableTimer(void);

#endif /* ICU_H_ */