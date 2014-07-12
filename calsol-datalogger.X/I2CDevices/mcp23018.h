/*
 * File:   mcp23018.h
 * Author: Ducky
 *
 * Created on a while ago.
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

#ifndef MCP23018_H
#define MCP23018_H

#include "../types.h"

/**
 * MCP23018 Register Addresses
 * (when IOCON.BANK=0)
 */
#define MCP23018_ADDR_IODIRA	0x00
#define MCP23018_ADDR_IODIRB	0x01
#define MCP23018_ADDR_IPOLA		0x02
#define MCP23018_ADDR_IPOLB		0x03
#define MCP23018_ADDR_GPINTENA	0x04
#define MCP23018_ADDR_GPINTENB	0x05
#define MCP23018_ADDR_DEFVALA	0x06
#define MCP23018_ADDR_DEFVALB	0x07
#define MCP23018_ADDR_INTCONA	0x08
#define MCP23018_ADDR_INTCONB	0x09
#define MCP23018_ADDR_IOCON_1	0x0A
#define MCP23018_ADDR_IOCON_2	0x0B
#define MCP23018_ADDR_GPPUA		0x0C
#define MCP23018_ADDR_GPPUB		0x0D
#define MCP23018_ADDR_INTFA		0x0E
#define MCP23018_ADDR_INTFB		0x0F
#define MCP23018_ADDR_INTCAPA	0x10
#define MCP23018_ADDR_INTCAPB	0x11
#define MCP23018_ADDR_GPIOA		0x12
#define MCP23018_ADDR_GPIOB		0x13
#define MCP23018_ADDR_OLATA		0x14
#define MCP23018_ADDR_OLATB		0x15

#define MCP23018_I2C_ADDR		0b0100000	/// Device I2C address, where last 3
											/// bytes are hardware-dependent.

/**
 * Writes a single register on the MCP23018.
 * This function blocks until the transmission completes.
 *
 * @param[in] addr 3-bit MCP23018 address set by A0, A1, A2 pins.
 * @param[in] reg Register address on the MCP23018 to write.
 * @param[in] data Data to put in the register.
 * @return Success or failure
 * @retval 1 Success.
 * @retval 0 Failure.
 */
uint8_t MCP23018_SingleRegisterWrite(uint8_t addr, uint8_t reg, uint8_t data);

/**
 * Reads a single register from the MCP23018.
 * This function blocks until the transmission completes.
 *
 * @param[in] addr 3-bit MCP23018 address set by A0, A1, A2 pins.
 * @param[in] reg Register address on the MCP23018 to read from.
 * @param[out] data Data byte read from the device.
 * @return Success or failure.
 * @retval 0 Failure - data read timed out, data byte is not valid.
 * @retval 1 Success - data byte is valid.
 */
uint8_t MCP23018_SingleRegisterRead(uint8_t addr, uint8_t reg, uint8_t *data);

#endif
