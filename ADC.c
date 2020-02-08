/*
 * ADC.c
 *
 * Created: 17/12/2019 11:08:32 ص
 *  Author: cisco126
 */ 

#include "ADC.h"
	/*
		1- Set ADC CLK prescaler for 50:200 kHz (128)
		2- Select ADC Vref (Vcc) 
		3- ADC enable
	*/
void ADC_Init(void)
{	
	/* Set ADC CLK prescaler for 50:200 kHz (128) */
	ADC_T ->ADCSRA_BF.ADPS = ADPS_DIV_128;
	/* Select ADC Vref (Vcc) */
	ADC_T ->ADMUX_BF.REFS = REFS_AREF;
	/* ADC enable */
	ADC_T ->ADCSRA_BF.ADEN_B =1;
}
	/*
		1- Select Channel
		2- Start Conversion 
		3- Wait until completion 
		4- Return data
	*/
INT16U ADC_Read(CH_SEL ch)
{
	/*select the channel*/
	ADC_T->ADMUX_BF.MUX = ch;
	/*start conversion*/
	ADC_T->ADCSRA_BF.ADSC_B = 1;
	/*wait until complete */
	/* wait until completion */
	while(ADC_T->ADCSRA_BF.ADSC_B!=0);
	/*return data */
	return ADC_T->ADC_R;
}