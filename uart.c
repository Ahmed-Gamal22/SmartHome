/*
 * uart.c
 *
 * Created: 31-Dec-19 1:19:57 PM
 *  Author: ahmed
 */ 
#include "uart.h"
#include "avr/interrupt.h"
#include "lcd.h"
volatile uint8 g_uartDataReg = 0;
static volatile void(*g_uartFunPtr)(void) = NULL;
void UART_init(void)
{
	/*character 8 bit*/
	setBit(UCSR0C,UCSZ00);
	setBit(UCSR0C,UCSZ01);
	/*baud rate*/
	UBRR0L=51;
	setBit(UCSR0B,RXEN0);
	/*enable interrupt*/
	setBit(UCSR0B,RXCIE0);
}
void UART_sendData(uint8 data)
{
	while(!(getBit(UCSR0A,UDRE0)));
	UDR0 = data;
}
uint8 UART_recieveData(void)
{
	while(!(getBit(UCSR0A,RXC0)));
	return UDR0;
}
uint8 UART_recieveDataNoBlock(uint8 *data2)
{
	uint8 status = 0;
	if(getBit(UCSR0A,RXC0))
	{
		*data2 = UDR0;
		status = 1;
	}
	else
	{
		status = 0;
	}
	return status;
}
void UART_sendString(uint8 *str)
{
	uint8 i = 0 ;
	while(str[i] != '\0')
	{
		UART_sendData(str[i]);
		i++;
	}
}
void UART_recieveString(uint8 *str)
{
	uint8 i = 0;
	str[i] = UART_recieveData();
	while(str[i] != '#')
	{
		i++;
		str[i] = UART_recieveData();
	}
	str[i] = '\0';
}
/*
 * function to send frame protocol
 * start with LDC(length data code) --> 1 Digit
 * Data with the same length as LDC --> 0:9 Digits
 * terminate your message with '#'
 */
void UART_sendProtocol(uint8 *str)
{
	uint8 counter = 0;
	uint8 i = 0;
	uint16 checkSum = 0;
	uint8 highNipple = 0;
	uint8 lowNipple = 0; 
	while(str[i] != '\0')
	{
		counter++;
		checkSum += str[i];
		i++;
	}
	i++;	
	str[i] = '\0';
	highNipple = (uint8)(checkSum>>8);
	lowNipple = (uint8)checkSum;
	UART_sendData(counter);
	UART_sendString(str);
	UART_sendData(highNipple); /*high nipple*/
	UART_sendData(lowNipple);/*low nipple*/
}
/*
 * function to receive frame protocol
 * start with LDC(length data code) --> 1 Digit
 * Data with the same length as LDC --> 0:9 Digits
 * two bytes checksum for your message
 * fill up new array with only data elements in message
 * check for checksum in your message and return 1 or 0 based on it.
 */
uint8 UART_recieveProtocol(uint8 *str, uint8 *data)
{
	uint8 i = 0;
	uint8 counter = str[0];
	uint16 checkSum = 0;
	uint8 highNipple = 0;
	uint8 lowNipple = 0;
	uint8 status = 0;
	for(i = 0 ; i < counter ; i++)
	{
		data[i] = str[i+1];
	}
	data[i] = '\0';
	highNipple = str[i+1];
	lowNipple = str[i+2];
	i = 0;
	while(data[i] != '\0')
	{
		checkSum += data[i];
		i++;
	}
	if((((uint8)checkSum) == lowNipple) && ((uint8)(checkSum>>8) == highNipple) )
	{
		status = 1;
		return status;
	} 
	else
	{
		return 0;
	}
}
uint8 UART_ledRecieve(uint8 *str)
{
	uint8 *ptr="LEDON ";
	uint8 i=0;
	uint8 bit;
	while(str[i] == ptr[i])
	{
		if(str[i] != ptr[i])
		{
			return 0;
		}
		i++;
	}
	bit = str[i]-'0';
	return bit;
}
void setUARTCallBack(void(*funPtr)(void))
{
	g_uartFunPtr = funPtr;
}
ISR(USART0_RX_vect)
{
	g_uartDataReg = UDR0;
	if(g_uartFunPtr != NULL)
	{
		(*g_uartFunPtr)();	
	}
}