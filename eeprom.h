/*
 * eeprom.h
 *
 * Created: 08-Jan-20 12:44:24 PM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "std_Types.h"
#include "common_macros.h"
#include "micro_config.h"
void EEPROM_Init(void);
void EEPROM_Write(uint16 address, uint8 data);	//11 bit address
uint8 EEPROM_Read(uint16 address);


#endif /* EEPROM_H_ */