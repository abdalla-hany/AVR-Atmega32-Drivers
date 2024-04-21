/*
 * adc.h
 *	Description: header file for the ADC driver
 *  Created on: Feb 16, 2024
 *      Author: abdalla
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include "std_types.h" /* Include standard types header file */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_REF_VOLT_VALUE 2.56 	/* Reference voltage value (not used in the header) */
#define ADC_MAXIMUM_VALUE  1023 	/* Maximum ADC value (not used in the header) */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enumeration for ADC reference voltage selection */
typedef enum
{
	AREF,        	 	/* External voltage reference at pin AREF */
	AVCC,        	 	/* AVCC (supply voltage) as reference */
	INTERNAL_2V = 3  	/* Internal 2.56V voltage reference */
} ADC_ReferenceVoltage;

/* Enumeration for ADC prescaler selection */
typedef enum
{
	F_CPU_DIV_2 = 1,   /* Divide CPU frequency by 2   */
	F_CPU_DIV_4,       /* Divide CPU frequency by 4   */
	F_CPU_DIV_8,       /* Divide CPU frequency by 8   */
	F_CPU_DIV_16,      /* Divide CPU frequency by 16  */
	F_CPU_DIV_32,      /* Divide CPU frequency by 32  */
	F_CPU_DIV_64,      /* Divide CPU frequency by 64  */
	F_CPU_DIV_128      /* Divide CPU frequency by 128 */
} ADC_Prescaler;

/* Configuration structure for ADC */
typedef struct
{
	ADC_ReferenceVoltage ref_volt;  /* ADC reference voltage selection */
	ADC_Prescaler prescaler;        /* ADC prescaler selection */
} ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 ch_num);

#endif /* SRC_ADC_H_ */
