/*
 * icu.c
 *
 *  Created on: Feb 26, 2024
 *      Author: abdalla
 */

#include "icu.h"
#include "common_macros.h" 	/* To use the macros like SET_BIT */
#include "gpio.h" 			/* To setup the pin direction for ICU PIN (ICP1/PD6) */
#include <avr/io.h> 		/* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> 	/* For ICU ISR */


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_CallBackFunction)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions and ISRS Definitions                                  *
 *******************************************************************************/

/*
 * Description : ISR to Handle a specific function passed to the ICU.
 */
ISR(TIMER1_CAPT_vect)
{
	/* check if the pointer is not equal null */
	if (g_CallBackFunction != NULL_PTR)
	{
		/* call back the function passed to you */
		(*g_CallBackFunction)();
	}
}

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType * config_ptr)
{
	/* Configure ICP1/PD6 as input pin */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID,PIN_INPUT);

	/* Timer1 always operates in Normal Mode */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B); /* Non pwm mode */

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0x40) | (config_ptr->clock & 0x07);

	/* Select the required edge type in ICES1 bit in TCCR1B Register */
	ICU_edgeSelect (config_ptr->edge);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK, TICIE1);

}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_edgeSelect (const ICU_EdgeType edge)
{
	switch(edge)
	{
		case FALLING:
			CLEAR_BIT(TCCR1B, ICES1);/* Activate ICU with Falling Edge */
			break;
		case RISING:
			SET_BIT(TCCR1B, ICES1);  /* Activate ICU with Rising Edge */
			break;
		default:
			/* Do nothing*/
			break;
	}
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunction (void (*ptr_func)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_CallBackFunction = (void*) ptr_func;
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_resetTimer(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit (void)
{
	/* Clear All Timer1/ICU Registers Turn off the timer */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK, TICIE1);

	/* Reset the call back function pointer */
	g_CallBackFunction = NULL_PTR;
}
