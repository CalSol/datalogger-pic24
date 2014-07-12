/*
 * File:   i2c-hardware.c
 * Author: Ducky
 *
 * Created on January 30, 2011, 1:17 AM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box,
 *						did some refactoring.
 *
 * @file
 * I2C hardware abstraction layer implementation for the dsPIC33 chip.
 */
#include "i2c-hardware.h"

#define I2C_BRG_100KHZ	((Fcy/100000-Fcy/7692308)-1)
#define I2C_BRG_400KHZ	((Fcy/400000-Fcy/7692308)-1)
#define I2C_BRG_1MHZ	((Fcy/1000000-Fcy/7692308)-1)

#if (I2C_BRG_100KHZ < 2) || (I2C_BRG_400KHZ < 2) || (I2C_BRG_1MHZ < 2)
	#error "I2CxBRG register values of less than 2 are not supported"
#endif

inline void I2C_Init() {
	I2C1CONbits.I2CEN = 1;
}

inline void I2C_SetSpeed(uint8_t speed) {
	switch (speed) {
		case I2C_SPEED_100KHZ:
		default:
			I2C1BRG = I2C_BRG_100KHZ;
			break;
		case I2C_SPEED_400KHZ:
			I2C1BRG = I2C_BRG_400KHZ;
			break;
		case I2C_SPEED_1MHZ:
			I2C1BRG = I2C_BRG_1MHZ;
			break;
	}
}

inline uint8_t I2C_SendStart() {
	if (!I2C1STATbits.P && I2C1STATbits.S) {
		return 0;
	}
	I2C1CONbits.SEN = 1;
	while (I2C1CONbits.SEN);	// wait for start condition to end

	return 1;
}

inline void I2C_SendRepeatedStart() {
	while ((I2C1CON & 0b11111) != 0);
	
	I2C1CONbits.RSEN = 1;
	while (I2C1CONbits.RSEN);	// wait for start condition to end
}

inline void I2C_SendStop() {
	while ((I2C1CON & 0b11111) != 0);
	
	I2C1CONbits.PEN = 1;
	while(I2C1CONbits.PEN);
}

inline uint8_t I2C_SendByte(uint8_t data) {
	// TODO Error checking I2C IWCOL
	I2C1TRN = data;
	while(I2C1STATbits.TRSTAT);

	return I2C1STATbits.ACKSTAT;
}

inline uint8_t I2C_Send7BitAddress(uint8_t address, uint8_t rw) {
	return I2C_SendByte((address << 1) | (rw & 0x01));
}

// TODO Implement 10bit I2C support


inline uint8_t I2C_ReadByte(uint8_t nack, uint8_t *data) {
	uint16_t timeout;
	
	while ((I2C1CON & 0b11111) != 0);
	
	I2C1CONbits.RCEN = 1;
	for (timeout=0; timeout<I2C_TIMEOUT*I2C1BRG && !I2C1STATbits.RBF; timeout++);
	if (I2C1STATbits.RBF) {
		*data = I2C1RCV;
	} else {
		return 0;
	}
	
	// Generate Acknowledge
	while ((I2C1CON & 0b11111) != 0);
	I2C1CONbits.ACKDT = nack;
	I2C1CONbits.ACKEN = 1;

	while (I2C1CONbits.ACKEN);

	return 1;
}
