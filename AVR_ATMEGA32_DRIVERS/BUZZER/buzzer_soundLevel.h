/*
 * buzzer.h
 *
 *  Created on: Feb 27, 2024
 *      Author: abdalla
 */

#ifndef SRC_BUZZER_H_
#define SRC_BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT		PORTB_ID
#define BUZZER_PIN	  	PIN3_ID
#define MAX_DISTANCE 	30

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the buzzer
 */
void BUZZER_init(void);

/*
 * Description :
 * Function to produce sound with the buzzer
 */
void BUZZER_sound (uint8 sound_level);


#endif /* SRC_BUZZER_H_ */
