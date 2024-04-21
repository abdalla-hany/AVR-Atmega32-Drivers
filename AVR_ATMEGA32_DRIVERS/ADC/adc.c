/*
 * adc.c
 *	Description: source file for the ADC driver
 *  Created on: Feb 16, 2024
 *      Author: abdalla
 */

#include "adc.h"	/* Include ADC header file */

#include <avr/io.h> /* For registers and Bits */

#include "common_macros.h" /* Include common macros header file for Clear and set bit commands */


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function to initialize the ADC */
void ADC_init (const ADC_ConfigType * Config_Ptr)
{
	ADMUX = 0;
	ADMUX |= (((Config_Ptr->ref_volt) & 0x03) << 6); 			  /* Set the reference voltage bits (REFS1:0) based on the configuration */
	SET_BIT(ADCSRA, ADEN);										  /* Enable the ADC module */
	ADCSRA = ((ADCSRA & 0xF8) | ((Config_Ptr->prescaler) &0x07)); /* Set the ADC prescaler bits (ADPS2:0) based on the configuration */
}

/* Function to read from a specific ADC channel */
uint16 ADC_readChannel(uint8 ch_num)
{
	ADMUX = ((ADMUX & 0xE0) | (ch_num &0x07)); /* Configure the ADC channel to read from */
	SET_BIT(ADCSRA, ADSC);					   /* Start the ADC conversion */
	while(BIT_IS_CLEAR(ADCSRA, ADIF));		   /* Wait for the conversion to complete */
	CLEAR_BIT(ADCSRA, ADIF);				   /* Clear the ADC interrupt flag */
	return ADC;
}
