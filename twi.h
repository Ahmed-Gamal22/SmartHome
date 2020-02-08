/*
 * twi.h
 *
 * Created: 08-Jan-20 11:55:05 AM
 *  Author: ahmed
 */ 


#ifndef TWI_H_
#define TWI_H_
#include "std_Types.h"
#include "common_macros.h"
#include "micro_config.h"
void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
uint8 TWI_ReadAck(void);
uint8 TWI_ReadNotAck(void);
void TWI_Write(uint8 data);
uint8 TWI_GetStatus(void);

#endif /* TWI_H_ */