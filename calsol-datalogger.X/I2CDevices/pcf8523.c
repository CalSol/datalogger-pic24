/*
 * File:   pcf8523.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 *
 * @file
 * Drivers for the PCF8523 RTC chip.
 */

#include <time.h>
typedef struct tm tm;

#include "i2c-hardware.h"
#include "pcf8523.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#include "../debug-common.h"

/**
 * Initializes the PCF8523 I2C Interface.
 */
void PCF8523_Init() {
	I2C_Init();
	I2C_SetSpeed(I2C_SPEED_1MHZ);
}


uint8_t PCF8523_SingleRegisterWrite(uint8_t reg, uint8_t data) {
	PCF8523_Init();
    
	if (!I2C_SendStart()) {
		return 0;
	}

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_WRITE)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_SendByte(data)) {
		I2C_SendStop(); return 0;
	}

	I2C_SendStop();
	return 1;
}

uint8_t PCF8523_SingleRegisterRead(uint8_t reg, uint8_t *data) {
	PCF8523_Init();

	if (!I2C_SendStart()) {
		return 0;
	}

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_WRITE)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop(); return 0;
	}

	I2C_SendRepeatedStart();

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_READ)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_ReadByte(I2C_SEND_NACK, data)) {
		I2C_SendStop(); return 1;
	} else {
		I2C_SendStop(); return 0;
	}
}

uint8_t PCF8523_MultipleRegisterWrite(uint8_t reg, uint8_t *data, uint8_t dataLen) {
	PCF8523_Init();

	if (!I2C_SendStart()) {
		return 0;
	}

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_WRITE)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop(); return 0;
	}

    for (; dataLen>0; dataLen--) {
        if (I2C_SendByte(*data)) {
            I2C_SendStop(); return 0;
        }
        data++;
    }

	I2C_SendStop();
	return 1;
}

uint8_t PCF8523_MultipleRegisterRead(uint8_t reg, uint8_t *data, uint8_t dataLen) {
	PCF8523_Init();

	if (!I2C_SendStart()) {
		return 0;
	}

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_WRITE)) {
		I2C_SendStop(); return 0;
	}

	if (I2C_SendByte(reg)) {
		I2C_SendStop(); return 0;
	}

	I2C_SendRepeatedStart();

	if (I2C_Send7BitAddress(PCF8523_I2C_ADDR, I2C_RW_READ)) {
		I2C_SendStop(); return 0;
	}

    for (; dataLen>0; dataLen--) {
        if (!I2C_ReadByte((dataLen > 0)?I2C_SEND_ACK:I2C_SEND_NACK, data)) {
            I2C_SendStop(); return 0;
        }
        data++;
    }
    I2C_SendStop(); return 1;
}

inline uint8_t PCF8523_Bcd8ToInt8(uint8_t bcdInt) {
    uint8_t retVal = bcdInt & 0x0f;
    bcdInt = bcdInt >> 4;   bcdInt &= 0b0011;
    retVal += bcdInt * 10;
    return retVal;
}

uint16_t daysPerMonth[] = {
    0,
    31, 28, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
};

uint16_t prefixDaysPerMonth[] = {
    0,
    31,  59,  90,  120,
    151, 181, 212, 243,
    273, 304, 334, 365
};

uint16_t daysPerMonthLeap[] = {
    0,
    31, 29, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
};

uint16_t prefixDaysPerMonthLeap[] = {
    0,
    31,  60,  91,  121,
    152, 182, 213, 244,
    274, 305, 335, 366
};

#define SECONDS_PER_LEAP_GROUP  126230400
#define SECONDS_PER_YEAR        31536000

#define DAYS_PER_YEAR           365
#define YEARS_PER_LEAP_GROUP    4
#define HOURS_PER_DAY           24
#define MINUTES_PER_HOUR        60
#define SECONDS_PER_MINUTE      60

time_t PCF8523_GetTime(uint8_t *good) {
    uint8_t regVal[PCF8523_NUM_TIME_REGISTERS]; // raw register values from device
    PCF8523_MultipleRegisterRead(PCF8523_ADDR_SECONDS, regVal, PCF8523_NUM_TIME_REGISTERS);

    PCF8523_SingleRegisterWrite(PCF8523_ADDR_SECONDS, regVal[0] & ~0x80);

    if (good != NULL) {
        *good = (regVal[0] & 0x80) == 0;
    }

    uint8_t seconds = PCF8523_Bcd8ToInt8(regVal[0] & 0b01111111);
    uint8_t minutes = PCF8523_Bcd8ToInt8(regVal[1] & 0b01111111);
    uint8_t hours = PCF8523_Bcd8ToInt8(regVal[2] & 0b00111111);
    uint8_t days = PCF8523_Bcd8ToInt8(regVal[3] & 0b00111111);
    uint8_t months = PCF8523_Bcd8ToInt8(regVal[5] & 0b00011111);
    uint8_t years = PCF8523_Bcd8ToInt8(regVal[6]);

    DBG_DATA_printf("PCF8523 read: %u years, %u months, %u days, %u hours, %u minutes, %u seconds",
            years, months, days, hours, minutes, seconds);

    // Convert years to days
    uint32_t currTime = years * DAYS_PER_YEAR;
    currTime += (years+YEARS_PER_LEAP_GROUP-1) / YEARS_PER_LEAP_GROUP;  // account for leap years

    // Add months
    if (years % YEARS_PER_LEAP_GROUP == 0) {
        currTime += prefixDaysPerMonthLeap[months];
    } else {
        currTime += prefixDaysPerMonth[months];
    }
    currTime += days;

    // Convert days to hours and add hours
    currTime *= HOURS_PER_DAY;
    currTime += hours;

    // Convert hours to minute and add minutes
    currTime *= MINUTES_PER_HOUR;
    currTime += minutes;

    // Convert minutes to seconds and add seconds
    currTime *= SECONDS_PER_MINUTE;
    currTime += seconds;

    // Convert to seconds agter 1970
    return currTime + 7*SECONDS_PER_LEAP_GROUP + 2*SECONDS_PER_YEAR;
}

tm PCF8523_GetTimeStruct(uint8_t *good) {
    uint8_t regVal[PCF8523_NUM_TIME_REGISTERS]; // raw register values from device
    PCF8523_MultipleRegisterRead(PCF8523_ADDR_SECONDS, regVal, PCF8523_NUM_TIME_REGISTERS);

    if (good != NULL) {
        *good = (regVal[0] & 0x80) == 0;
    }

    uint8_t seconds = PCF8523_Bcd8ToInt8(regVal[0] & 0b01111111);
    uint8_t minutes = PCF8523_Bcd8ToInt8(regVal[1] & 0b01111111);
    uint8_t hours = PCF8523_Bcd8ToInt8(regVal[2] & 0b00111111);
    uint8_t days = PCF8523_Bcd8ToInt8(regVal[3] & 0b00111111);
    uint8_t weekday = regVal[4] & 0b111;
    uint8_t months = PCF8523_Bcd8ToInt8(regVal[5] & 0b00011111);
    uint8_t years = PCF8523_Bcd8ToInt8(regVal[6]);

    DBG_DATA_printf("PCF8523 read: %u years, %u months, %u days, %u hours, %u minutes, %u seconds",
            years, months, days, hours, minutes, seconds);

    tm retTime;

    retTime.tm_sec = seconds;
    retTime.tm_min = minutes;
    retTime.tm_hour = hours;

    retTime.tm_mday = days;
    if (years % YEARS_PER_LEAP_GROUP == 0) {
        retTime.tm_yday = prefixDaysPerMonthLeap[months];
    } else {
        retTime.tm_yday = prefixDaysPerMonth[months];
    }
    retTime.tm_yday += days;
    retTime.tm_mon = months - 1;
    retTime.tm_year = years + 100;
    retTime.tm_wday = weekday;

    retTime.tm_isdst = 0;

    return retTime;
}

inline uint8_t PCF8523_Int8ToBcd8(uint8_t inInt) {
    uint8_t retVal = (inInt % 10) & 0x0f;
    retVal |= ((inInt / 10) & 0x0f) << 4;
    return retVal;
}

uint8_t PCF8523_SetTimeStruct(struct tm time) {
    uint8_t regVal[PCF8523_NUM_TIME_REGISTERS]; // raw register values from device

    regVal[0] = PCF8523_Int8ToBcd8(time.tm_sec);
    regVal[1] = PCF8523_Int8ToBcd8(time.tm_min);
    regVal[2] = PCF8523_Int8ToBcd8(time.tm_hour);
    regVal[3] = PCF8523_Int8ToBcd8(time.tm_mday);
    regVal[4] = PCF8523_Int8ToBcd8(time.tm_wday);
    regVal[5] = PCF8523_Int8ToBcd8(time.tm_mon - 1);
    regVal[6] = PCF8523_Int8ToBcd8(time.tm_year - 100);

    DBG_DATA_printf("PCF8523 write: %u years, %u months, %u days, %u hours, %u minutes, %u seconds",
            time.tm_year-100, time.tm_mon-1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);

    return PCF8523_MultipleRegisterWrite(PCF8523_ADDR_SECONDS, regVal, PCF8523_NUM_TIME_REGISTERS);
}
