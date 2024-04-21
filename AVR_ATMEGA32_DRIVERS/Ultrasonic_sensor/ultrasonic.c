/*
 * ultrasonic.c
 *
 *  Created on: Feb 27, 2024
 *      Author: abdalla
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/* Global variables to track edge count and time taken */
volatile uint8 g_edgeCount = 0;
volatile uint16 g_timeTaken = 0;

/*******************************************************************************
 *                      Functions  Definitions                                 *
 *******************************************************************************/

/*
 * Description : Function to initialize the Ultrasonic sensor
 * 	1. initialize the ICU driver.
 * 	2. Set the ICU call back function.
 * 	3.  Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void ULTRASONIC_init(void)
{
    /* Configure ICU with prescaler F_CPU/8 and rising edge detection */
    ICU_ConfigType configurations = {F_CPU_8, RISING};
    ICU_init(&configurations);

    /* Set callback function for edge processing */
    ICU_setCallBackFunction(ULTRASONIC_edgeProcessing);

    /* Set trigger pin as output and initialize it to low logic level */
    GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
    GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * Description : Function to trigger Ultrasonic sensor.
 */
void ULTRASONIC_trigger(void)
{
    /* Send trigger signal by setting trigger pin high for 15 microseconds */
    GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
    _delay_us(15);
    GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}


/*
 * Description :  Function to read distance from Ultrasonic sensor.
 */
uint16 ULTRASONIC_readDistance(void)
{
    uint16 distance = 0;

    /* Trigger Ultrasonic sensor */
    ULTRASONIC_trigger();

    /* Wait until both rising and falling edges are detected */
    while(g_edgeCount != 2);

    /* Calculate distance in centimeters
     * distance = speed of sound * time
     * distance = 34300 * (g_timeTaken(in sec) / 2)
     * distance = 17150 * g_timeTaken(in sec)
     * distance = 0.01715 * g_timeTaken (in microseconds)
     */
    distance = (uint16)(g_timeTaken * 0.01715);

    /* Reset edge count and timer */
    g_edgeCount = 0;
    ICU_resetTimer();

    return distance;
}

/*
 * Description :  Callback function for edge processing.
 */
void ULTRASONIC_edgeProcessing(void)
{
    g_edgeCount++;
    if (g_edgeCount == 1)
    {
        /* Reset timer and set edge detection to falling */
        ICU_resetTimer();
        ICU_edgeSelect(FALLING);
    }
    else if (g_edgeCount == 2)
    {
        /* Get time taken from input capture unit and reset timer */
        g_timeTaken = ICU_getInputCaptureValue();
        ICU_resetTimer();
        ICU_edgeSelect(RISING);
    }
}
