/*
 * eeprom.c
 *
 * Created: 08-Jan-20 12:44:10 PM
 *  Author: ahmed
 */ 
#include "eeprom.h"
#include "twi.h"

void EEPROM_Init(void)
{
	TWI_Init();
}
void EEPROM_Write(uint16 address, uint8 data)
{
	TWI_Start();
	TWI_Write((uint8)(0xa0 | ((address & 0x0700)>>7)));
	TWI_Write((uint8)address);
	TWI_Write(data);
	TWI_Stop();
}
uint8 EEPROM_Read(uint16 address)
{
	TWI_Start();
	TWI_Write((uint8)((0xa0 | ((address & 0x0700)>>7))));
	TWI_Write((uint8)address);
	TWI_Start();
	TWI_Write((uint8)((0xa0 | ((address & 0x0700)>>7)) | (0x01)));
	uint8 data = TWI_ReadNotAck();
	TWI_Stop();
	return data;
}