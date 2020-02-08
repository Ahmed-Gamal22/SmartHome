/*
 * uart.h
 *
 * Created: 31-Dec-19 1:19:41 PM
 *  Author: ahmed
 */ 


#ifndef UART_H_
#define UART_H_
#include "Util/delay.h"
#include "IO_AVR.h"
#include "bit_handle.h"
#include "avr\io.h"
#include "avr\interrupt.h"
#include "std_Types.h"
#define NULL ((void *)0)
extern volatile uint8 g_uartDataReg;
void setUARTCallBack(void(*funPtr)(void));
void UART_init(void);
void UART_sendData(uint8 data);
uint8 UART_recieveData(void);
uint8 UART_recieveDataNoBlock(uint8 *data2);
void UART_sendString(uint8 *str);
void UART_recieveString(uint8 *str);
void UART_sendProtocol(uint8 *str);
uint8 UART_recieveProtocol(uint8 *str, uint8 *data);

#endif /* UART_H_ */