/*
 * File:   mcp23018.h
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 02 Jul 2012  Ducky   Initial creation and implementation
 */

#ifndef PCF8523_H
#define PCF8523_H

#include <time.h>

#include "../types.h"

#define PCF8523_ADDR_CONTROL_1          0x00
#define PCF8523_ADDR_CONTROL_2          0x01
#define PCF8523_ADDR_CONTROL_3          0x02
#define PCF8523_ADDR_SECONDS            0x03
#define PCF8523_ADDR_MINUTES            0x04
#define PCF8523_ADDR_HOURS              0x05
#define PCF8523_ADDR_DAYS               0x06
#define PCF8523_ADDR_WEEKDAYS           0x07
#define PCF8523_ADDR_MONTHS             0x08
#define PCF8523_ADDR_YEARS              0x09
#define PCF8523_ADDR_MINUTE_ALARM       0x0a
#define PCF8523_ADDR_HOUR_ALARM         0x0b
#define PCF8523_ADDR_DAY_ALARM          0x0c
#define PCF8523_ADDR_WEEKDAY_ALARM      0x0d
#define PCF8523_ADDR_OFFSET             0x0e
#define PCF8523_ADDR_TMR_CLKOUT_CTRL    0x0f
#define PCF8523_ADDR_TMR_A_FREQ_CTRL    0x10
#define PCF8523_ADDR_TMR_A_REG          0x11
#define PCF8523_ADDR_TMR_B_FREQ_CTRL    0x12
#define PCF8523_ADDR_TMR_B_REG          0x13

#define PCF8523_I2C_ADDR                0b1101000

#define PCF8523_NUM_TIME_REGISTERS      7

/**
 * Writes a single register on the PCF8523.
 * This function blocks until the transmission completes.
 *
 * @param[in] reg Register address on the PCF8523 to write to.
 * @param[in] data Data to put in the register.
 * @return Success or failure
 * @retval 1 Success.
 * @retval 0 Failure.
 */
uint8_t PCF8523_SingleRegisterWrite(uint8_t reg, uint8_t data);

/**
 * Reads a single register from the PCF8523.
 * This function blocks until the transmission completes.
 *
 * @param[in] reg Register address on the PCF8523 to read from.
 * @param[out] data Data byte read from the device.
 * @return Success or failure.
 * @retval 0 Failure - data read timed out, data byte is not valid.
 * @retval 1 Success - data byte is valid.
 */
uint8_t PCF8523_SingleRegisterRead(uint8_t reg, uint8_t *data);

/**
 * Writes multiple sequential registers from the PCF8523.
 * This function blocks until the transmission completes.
 *
 * @param[in] reg Starting register address on the PCF8523 to write to.
 * @param[out] data Pointer to where to store the data, @a dataLen bytes long.
 * @param[in] dataLen Number of bytes to write.
 * @return Success or failure.
 * @retval 0 Failure - data write timed out, register contents may not be valid.
 * @retval 1 Success.
 */
uint8_t PCF8523_MultipleRegisterWrite(uint8_t reg, uint8_t *data, uint8_t dataLen);

/**
 * Reads multiple sequential registers from the PCF8523.
 * This function blocks until the transmission completes.
 *
 * @param[in] reg Starting register address on the PCF8523 to read from.
 * @param[out] data Pointer to where to store the data, at least @a dataLen bytes long.
 * @param[in] dataLen Number of bytes to read.
 * @return Success or failure.
 * @retval 0 Failure - data read timed out, data byte is not valid.
 * @retval 1 Success - data byte is valid.
 */
uint8_t PCF8523_MultipleRegisterRead(uint8_t reg, uint8_t *data, uint8_t dataLen);

/**
 * Gets the current time from the PCF8523.
 * This assumes the device maps year 00 to 2000.
 *
 * @param[out] good Set to 1 if clock integrity is guaranteed since last read.
 * @return POSIX time (seconds since year Jan 1, 1970).
 */
time_t PCF8523_GetTime(uint8_t *good);

/**
 * Gets the current time from the PCF8523.
 * This assumes the device maps year 00 to 2000.
 *
 * @param[out] good Set to 1 if clock integrity is guaranteed since last read.
 * @return tm time struct
 */
struct tm PCF8523_GetTimeStruct(uint8_t *good);

/**
 * Writes a time from the PCF8523, and marks the oscillator as good.
 * This assumes the device maps year 00 to 2000.
 *
 * @param[in] time Time to write
 *
 * @return Success or failure
 * @retval 1 Success
 * @retval 0 Failure
 */
uint8_t PCF8523_SetTimeStruct(struct tm time);

#endif
