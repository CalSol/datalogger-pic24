/*
 * File:   mcp23018.c
 * Author: Ducky
 *
 * Created on January 30, 2011, 5:05 PM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box,
 *						changed chip to MCP23018 (although code is similar),
 *						did some refactoring.
 *
 * @file
 * MCP23018 GPIO expander library.
 */

#include "i2c-hardware.h"
#include "mcp23018.h"

/**
 * Initializes the MCP23018 I2C Interface.
 */
void MCP23018_Init() {
	I2C_Init();
	I2C_SetSpeed(I2C_SPEED_400KHZ);
}

/**
 * Puts the 7-bit device address plus R/W bit on the I2C bus.
 * This function blocks until the transmission completes.
 *
 * @param[in] addr 3-bit MCP23018 address set by A2, A1, A0 pins in the lowest 3 bits.
 * @param[in] rw Read or /Write (1 for read, 0 for write).
 * @return The ACK bit from the device.
 * @retval 0 Device has sent an acknowledge.
 * @retval 1 Device has not sent an acknowledge.
 */
inline uint8_t MCP23018_SendControlByte(uint8_t addr, uint8_t rw) {
	MCP23018_Init();
	return I2C_Send7BitAddress(MCP23018_I2C_ADDR | addr, rw);
}

uint8_t MCP23018_SingleRegisterWrite(uint8_t addr, uint8_t reg, uint8_t data) {
	MCP23018_Init();
	if (!I2C_SendStart()) {
		return 0;
	}

	if (MCP23018_SendControlByte(addr, I2C_RW_WRITE)) {
		I2C_SendStop();
		return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop();
		return 0;
	}

	if (I2C_SendByte(data)) {
		I2C_SendStop();
		return 0;
	}

	I2C_SendStop();
	
	return 1;
}

uint8_t MCP23018_SingleRegisterRead(uint8_t addr, uint8_t reg, uint8_t *data) {
	MCP23018_Init();
	if (!I2C_SendStart()) {
		return 0;
	}

	if (MCP23018_SendControlByte(addr, I2C_RW_WRITE)) {
		I2C_SendStop();
		return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop();
		return 0;
	}

	I2C_SendRepeatedStart();

	if (MCP23018_SendControlByte(addr, I2C_RW_READ)) {
		I2C_SendStop();
		return 0;
	}

	if (I2C_ReadByte(I2C_SEND_NACK, data)) {
		I2C_SendStop();

		return 1;
	} else {
		I2C1CONbits.I2CEN = 0;

		return 0;
	}
}
