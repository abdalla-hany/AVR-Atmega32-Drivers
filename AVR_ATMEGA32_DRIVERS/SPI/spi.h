/*
 * spi.h
 *  Description: Header file for the SPI AVR driver
 *  Created on: Mar 6, 2024
 *      Author: abdalla
 */

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Define the character used to denote the end of a string */
#define STRING_END '@'

/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 0xFF

/* Define the a byte to indicate that the MCU is ready to receive DATA */
#define READY_TO_RECEVIE 0xFE

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void);

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);


#endif /* SPI_H_ */
