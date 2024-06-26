/*
 * spi.c
 *
 *  Created on: Mar 6, 2024
 *      Author: abdalla
 */

#include "spi.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void)
{
	/*** Configure SPI Master Pins In the MCU ***
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7)  --> Output
	 ********************************************/
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);

    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPE     = 1 Enable SPI Driver
     * DORD    = 0 Transmit the MSB first
     * MSTR    = 1 Enable Master
     * CPOL    = 0 SCK is low when idle
     * CPHA    = 0 Sample Data with the raising edge
     * SPR1:0  = 00 Choose SPI clock = Fosc/4
     ***********************************************************************/
	SPCR = (1<<SPE) | (1<<MSTR);

	/* Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	SPSR &= ~(1<<SPI2X);
}

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7)  --> Input
	 ********************************************/
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_INPUT);

    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPE     = 1 Enable SPI Driver
     * DORD    = 0 Transmit the MSB first
     * MSTR    = 0 Enable Slave
     * CPOL    = 0 SCK is low when idle
     * CPHA    = 0 Sample Data with the raising edge
     * SPR1:0  = 00 Choose SPI clock = Fosc/4
     ***********************************************************************/
	SPCR = (1<<SPE);
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = data;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;
	uint8 received_data = 0;

	/* Loop until the end of the string */
	while (str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(str[i]);
		i++;
	}
	/* Send the last STRING_END SYMBOL*/
	SPI_sendReceiveByte(STRING_END);
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the whole string until the STRING_END symbol */
	do
	{
		/* Receive the first byte */
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
		i++;

		/* Check if the last received byte is the STRING_END symbol*/
	}while(str[i - 1] != STRING_END);

	/* After receiving the whole string plus the STRING_END symbol, replace this symbol with '\0' */
	str[i - 1] = '\0';
}
