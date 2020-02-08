/*
 * twi.c
 *
 * Created: 08-Jan-20 11:54:53 AM
 *  Author: ahmed
 */ 
#include "twi.h"
void TWI_Init(void)
{
	TWBR = 0x02;	//400KHZ
	TWSR = 0xfc;
	TWAR = 0x10; //address
	TWCR = (1<<TWEN); //module enable
}
void TWI_Start(void)
{	
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
void TWI_Stop(void)
{
	TWCR = (1<<TWSTO)|(1<<TWEN)|(1<<TWINT);	
}
uint8 TWI_ReadAck(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;	
}
uint8 TWI_ReadNotAck(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
void TWI_Write(uint8 data)
{
	TWDR = data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));	
}
uint8 TWI_GetStatus(void)
{
	return (TWSR & 0xf8);
}