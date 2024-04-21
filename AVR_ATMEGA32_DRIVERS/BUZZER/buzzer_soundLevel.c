/*
 * buzzer.c
 *
 *  Created on: Feb 27, 2024
 *      Author: abdalla
 */

/* Include header files */
#include "buzzer_soundLevel.h" /* Include header file for buzzer functions */
#include "gpio.h" 	/* Include header file for GPIO functions */
#include "pwm.h" 	/* Include header file for PWM functions */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the buzzer
 */
void BUZZER_init(void)
{
    GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT); 	/* Set buzzer pin as output */
    GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW); 				/* Set initial state of buzzer pin to low */
}

/*
 * Description :
 * Function to produce sound with the buzzer
 */
void BUZZER_sound (uint8 sound_level)
{
    /* Limit sound level to a maximum of 30 cm distance */
    if (sound_level > MAX_DISTANCE)
    {
        /* TURN off the buzzer sound */
        PWM_Timer0_Stop();
    }
    else
    {
        /*
         * Convert distance to a sound level to a percentage value
         * 30 cm -> 0 sound level
         *  2 cm -> 100 sound level
         * */
        sound_level = ((MAX_DISTANCE - sound_level) / (MAX_DISTANCE - 2)) * 100;

        /* Start PWM generation with the calculated sound level */
        PWM_Timer0_Start(sound_level);
    }


}

