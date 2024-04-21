/*
 * icu.h
 *
 *  Created on: Feb 26, 2024
 *      Author: abdalla
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/* Enumeration for ICU clock types */
typedef enum
{
	NO_CLOCK,       /* No clock source */
	F_CPU_CLOCK,    /* Clock source equals CPU frequency */
	F_CPU_8,        /* Clock source equals CPU frequency divided by 8 */
	F_CPU_64,       /* Clock source equals CPU frequency divided by 64 */
	F_CPU_256,      /* Clock source equals CPU frequency divided by 256 */
	F_CPU_1024      /* Clock source equals CPU frequency divided by 1024 */
} ICU_ClockType;

/* Enumeration for ICU edge types */
typedef enum
{
	FALLING,    /* Falling edge detection */
	RISING      /* Rising edge detection */
} ICU_EdgeType;

/* Configuration structure for ICU module */
typedef struct
{
	ICU_ClockType clock;    /* Selected clock source for ICU module */
	ICU_EdgeType edge;      /* Selected edge type for input capture */
} ICU_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * config_ptr);

/*
 * Description: Function to set the required edge detection.
 */
void ICU_edgeSelect (const ICU_EdgeType edge);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunction (void (*ptr_func)(void));

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_resetTimer(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit (void);

#endif /* ICU_H_ */
