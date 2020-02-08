/*
 * lcd.c
 *
 * Created: 12/12/2019 11:38:30 ص
 *  Author: PC
 */ 
#include "lcd.h"
/* Basic Function static Declarations */
 void lcd_SendCMD(INT8U cmd);
 void lcd_SendData(INT8U data);
 void lcd_Gotoxy(INT8U x,INT8U y);


 void lcd_SendCMD(INT8U cmd)
{
	/*
		1-command mode 
		2-load the most 4-bits of "cmd"
		3-start the data write (EN-> high to low ) 
		4-load the least 4-bits of "cmd"
		5-start the data write (EN-> high to low )
		6-wait for command execution (40 us)
		
	*/
	clearBit(LCD_CTRL_PORT,LCD_CTRL_RS);
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(cmd&LCD_DATA_MSK);
	setBit(LCD_CTRL_PORT,LCD_CTRL_EN);
	clearBit(LCD_CTRL_PORT,LCD_CTRL_EN);
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((cmd<<4));
	setBit(LCD_CTRL_PORT,LCD_CTRL_EN);
	clearBit(LCD_CTRL_PORT,LCD_CTRL_EN);
	_delay_us(40);
	
	
}
 void lcd_SendData(INT8U data)
{
	/*
		1-data mode 
		2-load the most 4-bits of "cmd"
		3-start the data write (EN-> high to low ) 
		4-load the least 4-bits of "cmd"
		5-start the data write (EN-> high to low )
		6-wait for command execution (40 us)
		
	*/
		setBit(LCD_CTRL_PORT,LCD_CTRL_RS);
		LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(data&LCD_DATA_MSK);
		setBit(LCD_CTRL_PORT,LCD_CTRL_EN);
		clearBit(LCD_CTRL_PORT,LCD_CTRL_EN);
		LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((data<<4));
		setBit(LCD_CTRL_PORT,LCD_CTRL_EN);
		clearBit(LCD_CTRL_PORT,LCD_CTRL_EN);
		_delay_us(40);
	
}
 void lcd_Gotoxy(INT8U x,INT8U y)
{
	/*
		x (Line) range :  1:2
		y (col) range :   1:16
	*/
	if(x==1)
	{
		/*	send command "set DDRAM Address with the specified x and y	*/
		lcd_SendCMD(0x80+y-1);
	}
	else
	{
		lcd_SendCMD(0xC0+y-1);
		
	}
}


void lCD_Init(void)
{
	/*Directions */ 
	setBit(LCD_BL_DDR,LCD_BL_NUM);
	setMBits(LCD_CTRL_DDR,LCD_CTRL_MSK);
	setMBits(LCD_DATA_DDR,LCD_DATA_MSK);
	
	/* Defaults */ 
	setBit(LCD_BL_PORT,LCD_BL_NUM);
	clearMBits(LCD_CTRL_PORT,LCD_CTRL_MSK);
	clearMBits(LCD_DATA_PORT,LCD_DATA_MSK);
	_delay_ms(20);  /* lcd power delay */
	lcd_SendCMD(0x02);
	lcd_SendCMD(CMD_FUN_SET);
	lcd_SendCMD(CMD_DISP_CTRL);
	lcd_SendCMD(CMD_MODE_SET);
	lcd_Clear();
	
}
void lcd_Clear(void)
{
	lcd_SendCMD(CMD_CLEAR);
	_delay_ms(5); /* commands activation delay */
}
void lcd_DispChar(INT8U data)
{
	lcd_SendData(data);
}
void lcd_DispCharXY(INT8U x,INT8U y,INT8U data)
{
	lcd_Gotoxy(x,y);
	lcd_DispChar(data);
}
void lcd_DispStr(INT8U* str)
{
	while(str[0])
	{
		lcd_DispChar(str[0]);
		str++;
	}
}
void lcd_DispStrXY(INT8U x,INT8U y,INT8U* str)
{
	lcd_Gotoxy(x,y);
	lcd_DispStr(str);
}
	
void lCD_DispInt(INT32U num)
{
	char str[16];
	int i=0;
	if(num>0)
	{
		while(num!=0)
		{
			str[i]=(num%10)+48;
			num/=10;
			i++;
		}
		while(i>0)
		{
			lcd_DispChar(str[i-1]);
			i--;
		}
	}
	else
	{
		lcd_DispChar('0');
	}
}
void lcd_DispIntXY(INT8U x,INT8U y,INT32U valueInt)
{
	lcd_Gotoxy(x,y);
	lCD_DispInt(valueInt);
	
}