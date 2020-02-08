/*
 * io_avr.h
 *
 * Created: 10/12/2019 02:04:25 
 *  Author: cisco126
 */ 


#ifndef IO_AVR_H_
#define IO_AVR_H_

#include "datatypes.h"

/********************************************
              GPIO Section
*********************************************/
/*
	PORTA to PORTF
	A:
	PINA  -> 0x39
	DDRA  -> 0x3A
	PORTA -> 0x3B
	
	PINF  -> 0x20
	dummy -> 0x40(64 byte in between)
	DDRF  -> 0x61
	PORTF -> 0x62
*/
typedef struct gpio
{
	INT8U	PIN;
	INT8U	DDR;
	INT8U	PORT;		
}GPIO;

typedef struct gpiof
{
	INT8U	PIN;
	const INT8U   dummy[64];
	INT8U	DDR;
	INT8U	PORT;
}GPIOf;

#define GPIOA	 ((volatile GPIO*)(0x39))

#define GPIOB	 ((volatile GPIO*)(0x36))

#define GPIOC	 ((volatile GPIO*)(0x33))

#define GPIOD	 ((volatile GPIO*)(0x30))

#define GPIOE	 ((volatile GPIO*)(0x21))

#define GPIOF    ((volatile GPIOf*)(0x20))

#define GPIOG	 ((volatile GPIO*)(0x63))

/********************************************
              ADC Section
*********************************************/
/*
	Naming conventions : 
	1- _BFD -> Bit field structure declaration of predefined one in io.h 
	2- _B   -> for individual bit naming inside a bit field structure to avoid io.h
	3- Group of bits(>1) has the same name without numbering 
	4- _BF -> for a definition of an _BFD 
	5- _T -> For new structure data type to avoid io.h
	6- dummy -> to fill the gap between the register's addresses (constanat declaration to avoid write on it )  
	7- _R ->for defination of a register that found in io.h
	8- _TD -> A declaration of the _T.
	
*/

typedef struct 
{
	INT8U MUX :5;         /* Analog Channel ADC */
	INT8U ADLAR_B:1;      /* ADC Left Adjust Result  */
	INT8U REFS :2 ;       /* Reference Selections */
	
}ADMUX_BFD;

/*
	REFS *> 0b00 for external AREF 
	REFS *> 0b01 for AVcc
	REFS *> 0b11 for internal 2.56v.
*/
typedef enum{
	REFS_AREF,REFS_AVCC,REFS_INTERNAL=0b11
	}REFS_Type;
	
/* 0 ->Right , 1 ->Left */	
typedef enum{
	ADLAR_RIGHT,ADLAR_LEFT	
}ADLAR_Type;

/* Channel Selection */

typedef enum{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}CH_SEL;


typedef struct
{
	INT8U ADPS   :3; /* ADC Prescaler Select Bits */
	INT8U ADIE_B :1; /* Interrupt Enable */ 
	INT8U ADIF_B :1;  /* Interrupt Flag */ 
	INT8U ADFR_B :1;  /* Free Running Select */ 
	INT8U ADSC_B :1;  /* Start Conversion */ 
	INT8U ADEN_B :1;  /* ADC Enable */ 	
	
}ADCSRA_BFD;

/* 
	ADPS_DIV
*/
typedef enum{
	ADPS_DEFAULT,
	ADPS_DIV_2,
	ADPS_DIV_4,
	ADPS_DIV_8,
	ADPS_DIV_16,
	ADPS_DIV_32,
	ADPS_DIV_64,
	ADPS_DIV_128
}ADPS_SEL;


/*
	0x24 ->ADCL
	0x25 ->ADCH
	0x26 ->ADCSRA
	0x27 ->ADMUX
	
*/
typedef struct{
	INT16U ADC_R;
	ADCSRA_BFD ADCSRA_BF;
	ADMUX_BFD ADMUX_BF;
	
}ADC_TD;
	
	
#define  ADC_T ((volatile ADC_TD*)(0x24))


/**********************************************
	External Interrupt
**********************************************/
 /*	
	EIFR   -> 0x58
	EIMSK  -> 0x59 
	EICRB  -> 0x5A
	EICRA  -> 0x6A
 */
 typedef struct{
	 INT8U ISC0:2; /* ISC01 ISC00 for INT0 */
	 INT8U ISC1:2; 
	 INT8U ISC2:2;
	 INT8U ISC3:2;
	 
	 
}EICRA_BFD;

 typedef struct{
	 INT8U ISC4:2; /* ISC01 ISC00 for INT0 */
	 INT8U ISC5:2;
	 INT8U ISC6:2;
	 INT8U ISC7:2;
	 
	 
 }EICRB_BFD;
 
 typedef enum{
	 ISC_LOW_LEVEL,ISC_ANY_CHANGE,ISC_FALLING_EDGE,ISC_RISING_EDGE
	 
}ISC_Type;
 
 typedef struct{
	 INT8U INT0_B:1; /*  INT0 mask bit */
	 INT8U INT1_B:1;
	 INT8U INT2_B:1;
	 INT8U INT3_B:1;
	 INT8U INT4_B:1;  
	 INT8U INT5_B:1;
	 INT8U INT6_B:1;
	 INT8U INT7_B:1;
	   
	 
 }EIMSK_BFD;
 
 typedef struct{
	 INT8U INTF0_B:1; /*  INT0 mask bit */
	 INT8U INTF1_B:1;
	 INT8U INTF2_B:1;
	 INT8U INTF3_B:1;
	 INT8U INTF4_B:1;
	 INT8U INTF5_B:1;
	 INT8U INTF6_B:1;
	 INT8U INTF7_B:1;
	 
	 
 }EIFR_BFD;
 
 typedef struct{
	 EIFR_BFD  EIFR_BF;
	 EIMSK_BFD EIMSK_BF;
	 EICRB_BFD EICRB_BF;
	 const INT8U dummmy[15];
	 EICRA_BFD EICRA_BF;	 	 
	 
}EXT_INT_TD;

#define EXT_INT_T ((volatile EXT_INT_TD*)(0x58))


/*****************************************************
	Timers - Timer0
*****************************************************/
/*
ASSR  0x50
OCR0  0x51
TCNT0 0x52
TCCR0 0x53

TIFR 0x56
TIMSK 0x57
SFIOR 0x40
*/
typedef struct{
	INT8U CS_0     :3;
	INT8U WGM01_B  :1;
	INT8U COM_0    :2;
	INT8U WGM00_B  :1;
	INT8U FOC0_B   :1;
	
}TCCR0_BFD;

typedef enum {
	COM_NON_NORMAL,COM_NON_TOGGLE,COM_NON_CLEAR,COM_NON_SET
	
}COM_NON_PWM;

typedef enum {
	COM_FAST_NORMAL,COM_FAST_NON_INV=0b10,COM_FAST_INV
	
}COM_FAST_PWM;

typedef enum {
	COM_PHASE_NORMAL,COM_PHASE_NON_INV=0b10,COM_PHASE_INV
	
}COM_PHASE_PWM;

typedef enum{
	CS_STOPPED,
	CS_DIV_1,
	CS_DIV_8,
	CS_DIV_32,
	CS_DIV_64,
	ACS_DIV_128,
	CS_DIV_256,
	CS_DIV_1024
}TIM_CS;

typedef struct {
	INT8U ASSR_R ;
	INT8U OCR0_R ;
	INT8U TCNT0_R ;
	
	TCCR0_BFD TCCR0_BF ;
	
	
	
}TIMER0_TD;
#define TIMER0_T  ((volatile TIMER0_TD*)(0x50))

typedef struct{
	INT8U TOIE0_B:1; /*   timer0 overflow interrupts enable */
	INT8U OCIE0_B:1; /*   timer0 compare match interrupts enable */
	INT8U TOIE1_B:1; /*   timer1 overflow interrupts enable */
	INT8U OCIE1B_B:1; /*   timer1 compare match B interrupts enable */
	INT8U OCIE1A_B:1;  /*   timer1 compare match A interrupts enable */
	INT8U TICIE1_B:1; /*   Timer1 input capture interrupts enable */
	INT8U TOIE2_B:1; /* Timer2 overflow interrupt enable */
	INT8U OCIE2_B:1; /*  timer2 compare match interrupts enable */ 
		
}TIMSK_BFD;

#define TIMSK_BF  ((volatile TIMSK_BFD*)(0x57))

typedef struct{
	INT8U TOV0_B:1; /*   timer0 overflow flag */
	INT8U OCF0_B:1; /*   timer0 compare match flag */
	INT8U TOV1_B:1; /*   timer1 overflow flag */
	INT8U OCF1B_B:1; /*   timer1 compare match B flag */
	INT8U OCF1A_B:1;  /*   timer1 compare match A flag */
	INT8U ICF1_B:1; /*   Timer1 input capture flag */
	INT8U TOV2_B:1; /* Timer2 overflow flag */
	INT8U OCF2_B:1; /*  timer2 compare match flag */
	
}TIFR_BFD;

#define TIFR_BF  ((volatile TIMSK_BFD*)(0x56))
#endif /* IO_AVR_H_ */