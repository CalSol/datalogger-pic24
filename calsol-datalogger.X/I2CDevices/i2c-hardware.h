/*
 * File:   i2c-hardware.h
 * Author: Ducky
 *
 * Created on a long time ago in a galaxy far far away...
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Refactoring changes.
 *
 * @file
 * I2C hardware abstraction layer and interface definition.
 */

#ifndef I2C_HARDWARE_H
#define I2C_HARDWARE_H

#include "../types.h"
#include "../hardware.h"

#define I2C_TIMEOUT		16		/// Number of BRG loops before timeout.

/**
 * One-time initialization of the I2C transceiver.
 * The I2C BRG is not set here since it is device dependent.
 */
inline void I2C_Init();

/**
 * Sets the I2C bus speed.
 * 
 * @param[in] speed I2C speed.
 */
inline void I2C_SetSpeed(uint8_t speed);
#define I2C_SPEED_100KHZ	1
#define I2C_SPEED_400KHZ	2
#define I2C_SPEED_1MHZ      3

/**
 * Sends a start bit. This function blocks until the start bit completes.
 *
 * @return Whether it was successful or not.
 * @retval 0 Start bit not sent - bus busy.
 * @retval 1 Start bit sent successfully.
 */
inline uint8_t I2C_SendStart();

/**
 * Sends a repeated start bit.
 * This function blocks until the stop bit completes.
 */
inline void I2C_SendRepeatedStart();

/**
 * Sends a stop bit.
 * This function blocks until the stop bit completes.
 */
inline void I2C_SendStop();

/**
 * Puts a data byte on the I2C bus.
 * This function blocks until the transmission completes.
 *
 * @param[in] data Data byte to transmit.
 * @return The ACK bit from the device.
 * @retval 0 Device has sent an acknowledge.
 * @retval 1 Device has not sent an acknowledge.
 */
inline uint8_t I2C_SendByte(uint8_t data);

/**
 * Puts the 7-bit device address plus R/W bit on the I2C bus.
 * This function blocks until the transmission completes.
 *
 * @param[in] address 7-bit I2C device address.
 * @param[in] rw Read or /Write (1 for read, 0 for write).
 * @return The NACK bit from the device.
 * @retval 0 Device has sent an acknowledge.
 * @retval 1 Device has not sent an acknowledge.
 */
inline uint8_t I2C_Send7BitAddress(uint8_t address, uint8_t rw);
#define I2C_RW_WRITE	0		/// R/W bit value for a write operation.
#define I2C_RW_READ		1		/// R/W bit balue for a read operation.

/**
 * Puts the 11-bit device address plus R/W bit on the I2C bus.
 * This function blocks until the transmission completes.
 *
 * @param[in] address 11-bit I2C device address.
 * @param[in] rw Read or /Write (1 for read, 0 for write).
 * @return The NACK bit from the device.
 * @retval 0 Device has sent an acknowledge.
 * @retval 1 Device has not sent an acknowledge.
 */
inline uint8_t I2C_Send11BitAddress(uint16_t address, uint8_t rw);

/**
 * Reads a byte from a I2C device.
 * This function blocks until the transmission is complete.
 *
 * @param[in] nack Generate a ACK (0) or NACK (1) bit at the end of the message.
 * Typically, an NACK is generated on the last read.
 * @param[out] data Data byte read from the device.
 * @return Success or failure.
 * @retval 0 Failure - data read timed out, data byte is not valid.
 * @retval 1 Success - data byte is valid.
 *
 * @bug It is up to the user to handle a timeout and to possibly initiate recovery procedures.
 * As it is, a timeout will return from this function, but will cause further I2C fucntion calls to
 * go into an infinite loop.
 */
inline uint8_t I2C_ReadByte(uint8_t nack, uint8_t *data);
#define I2C_SEND_ACK	0		/// Parameter value to send a ACK after an operation.
#define I2C_SEND_NACK	1		/// Parameter value to send a NACK after an operation.

#endif
