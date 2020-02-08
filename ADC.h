/*
 * ADC.h
 *
 * Created: 17/12/2019 11:08:12 ص
 *  Author: cisco126
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "io_avr.h"
#include "bit_handle.h"
#include "std_Types.h"

#define F_CPU 8000000UL
#include "util/delay.h"

void ADC_Init(void);
INT16U ADC_Read(CH_SEL ch);




#endif /* ADC_H_ */