/*
 * lcd.h
 *
 * Created: 12/12/2019 11:38:01 ص
 *  Author: PC
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "io_avr.h"
#include "bit_handle.h"

#define F_CPU	8000000UL
#include "util/delay.h"

#define CMD_FUN_SET     0x28
#define CMD_DISP_CTRL   0x0C
#define CMD_MODE_SET    0x06
#define CMD_CLEAR       0x01

/* Interfaces */

/* Control */
#define LCD_CTRL_DDR     GPIOB->DDR
#define LCD_CTRL_PORT    GPIOB->PORT
#define LCD_CTRL_MSK     0xE0
#define LCD_CTRL_RS      5
#define LCD_CTRL_RW      6
#define LCD_CTRL_EN      7

/* Data  */ 
#define LCD_DATA_DDR    GPIOC->DDR
#define LCD_DATA_PORT   GPIOC->PORT
#define LCD_DATA_MSK    0xF0
/*Back light */
#define LCD_BL_DDR      GPIOE->DDR
#define LCD_BL_PORT     GPIOE->PORT 
#define LCD_BL_NUM      4 


/* Extra Functions */ 
void lCD_Init(void);
void lcd_Clear(void);
void lcd_DispChar(INT8U data);
void lcd_DispCharXY(INT8U x,INT8U y,INT8U data);
void lcd_DispStr(INT8U* str);
void lcd_DispStrXY(INT8U x,INT8U y,INT8U* str);
void lCD_DispInt(INT32U valueInt);
void lcd_DispIntXY(INT8U x,INT8U y,INT32U valueInt);


#endif /* LCD_H_ */