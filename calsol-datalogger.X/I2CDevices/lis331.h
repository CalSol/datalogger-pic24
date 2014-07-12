/*
 * File:   lis331.h
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 03 Jul 2012	Ducky	File creation, initial implementation.
 *
 * @file
 * LIS331 accelerometer library
 */

#ifndef LIS331_H
#define LIS331_H

#include "../types.h"

#define LIS331_SPI_DUMMY		0xff

#define	LIS331_ADDR_WHO_AM_I        0x0f
#define	LIS331_ADDR_CTRL_REG1       0x20
#define	LIS331_ADDR_CTRL_REG2       0x21
#define	LIS331_ADDR_CTRL_REG3       0x22
#define	LIS331_ADDR_CTRL_REG4       0x23
#define	LIS331_ADDR_CTRL_REG5       0x24
#define	LIS331_ADDR_HP_FILTER_RESET 0x25
#define	LIS331_ADDR_REFERENCE       0x26
#define	LIS331_ADDR_STATUS_REG      0x27
#define	LIS331_ADDR_OUT_X_L         0x28
#define	LIS331_ADDR_OUT_X_H         0x29
#define	LIS331_ADDR_OUT_Y_L         0x2a
#define	LIS331_ADDR_OUT_Y_H         0x2b
#define	LIS331_ADDR_OUT_Z_L         0x2b
#define	LIS331_ADDR_OUT_Z_H         0x2c
#define	LIS331_ADDR_INT1_CFG        0x30
#define	LIS331_ADDR_INT1_SOURCE     0x31
#define	LIS331_ADDR_INT1_THS        0x32
#define	LIS331_ADDR_INT1_DURATION   0x33
#define	LIS331_ADDR_INT2_CFG        0x34
#define	LIS331_ADDR_INT2_SOURCE     0x35
#define	LIS331_ADDR_INT2_THS        0x36
#define	LIS331_ADDR_INT2_DURATION   0x37

#define LIS331_WHO_AM_I         0b00110010  // expected contents of WHO_AM_I register
/*
#define LIS331_PM_POWERDOWN         0b000
#define LIS331_PM_NORMAL            0b001
#define LIS331_PM_LOWPOWER_0_5HZ    0b010
#define LIS331_PM_LOWPOWER_1HZ      0b011
#define LIS331_PM_LOWPOWER_2HZ      0b100
#define LIS331_PM_LOWPOWER_5HZ      0b101
#define LIS331_PM_LOWPOWER_10HZ     0b110
*/

/**
 * Initializes the LIS331.
 * @return 1 if successful, 0 otherwise
 */
uint8_t LIS331_Init();

/**
 * @return Status of the INT1 lint
 * @retval 1 Interrupt
 * @retval 0 No interrupt
 */
uint8_t LIS331_GetInt1Status();

/**
 * Reads acceleration data from all 3 axes, then converts them into binary mg.
 * (1/1024)ths g
 * @warning This assumes +/- 8g full scale
 * @param dataOut Pointer to location to store data, should be 3 elements long.
 *  Data will be stored in order X, Y, Z
 */
void LIS331_ReadDataMbg(int16_t* dataOut);

/**
 * Reads raw acceleration data from all 3 axes.
 * @param dataOut Pointer to location to store data, should be 3 elements long.
 *  Data will be stored in order X, Y, Z
 */
void LIS331_ReadData(int16_t* dataOut);

/**
 * Writes @a data into device register @a addr
 * @param addr Device address
 * @param data Data to write
 */
void LIS331_Write(uint8_t addr, uint8_t data);

/**
 * Writes multiple bytes of data to the device, starting at address @a addr
 * @param addr Address to start at
 * @param len Number of bytes to write
 * @param buf Pointer to buffer containing data to write, @a len bytesl long
 */
void LIS331_WriteMultiple(uint8_t addr, uint8_t len, uint8_t *buf);

/**
 * Reads data from device address @a addr
 * @param addr Address to read from
 * @return Data read from device register
 */
uint8_t LIS331_Read(uint8_t addr);

/**
 * Reads multiple bytes of data from the device, starting at address @a addr
 * @param addr Address to start at
 * @param len Number of bytes of data to read
 * @param buf Pointer to the buffer to store the results, should be at least
 *	@a len bytes long
 */
void LIS331_ReadMultiple(uint8_t addr, uint8_t len, uint8_t *buf);

#endif
