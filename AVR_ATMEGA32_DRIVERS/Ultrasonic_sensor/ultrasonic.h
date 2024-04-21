/*
 * ultrasonic.h
 *
 *  Created on: Feb 27, 2024
 *      Author: abdalla
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT_ID PORTB_ID
#define TRIGGER_PIN_ID PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the Ultrasonic sensor
 * 	1. initialize the ICU driver.
 * 	2. Set the ICU call back function.
 * 	3.  Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void ULTRASONIC_init(void);

/*
 * Description : Function to trigger Ultrasonic sensor.
 */
void ULTRASONIC_trigger(void);

/*
 * Description :  Function to read distance in centimeter from Ultrasonic sensor.
 */
uint16 ULTRASONIC_readDistance(void);

/*
 * Description :  Callback function for edge processing.
 */
void ULTRASONIC_edgeProcessing(void);




#endif /* SRC_ULTRASONIC_H_ */
