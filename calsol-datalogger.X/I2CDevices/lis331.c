/*
 * File:   lis331.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 03 Jul 2012	Ducky	Initial implementation
 *
 * @file
 * LIS331 accelerometer library
 */

#include <spi.h>

#include "../hardware.h"

#include "lis331.h"

#define DEBUG_UART
#define DEBUG_UART_DATA

#include "../debug-common.h"

uint8_t LIS331_Init() {
	ACL_SPI_CS_IO = 1;
	ACL_SPI_CS_TRIS = 0;

    CloseSPI1();
    /*OpenSPI1(ENABLE_SCK_PIN && ENABLE_SDO_PIN && SPI_MODE16_OFF
            && SPI_SMP_OFF && SPI_CKE_ON && SLAVE_ENABLE_OFF
            && CLK_POL_ACTIVE_LOW && MASTER_ENABLE_ON
            && SEC_PRESCAL_8_1 && PRI_PRESCAL_4_1,
            FRAME_ENABLE_OFF && FIFO_BUFFER_DISABLE,
            SPI_ENABLE && SPI_IDLE_STOP && SPI_RX_OVFLOW_CLR);*/

	SPI1CON1bits.MSTEN = 1;
	SPI1CON1bits.CKP = 1;
	SPI1CON1bits.CKE = 0;
	SPI1CON1bits.SPRE = 0b010;	// 6:1 SPRE
	SPI1CON1bits.PPRE = 0b11;	// 1:1 PRE

	SPI1STATbits.SPIEN = 1;
	SPI1STATbits.SPIROV = 0;

	uint8_t devId;
	devId = LIS331_Read(LIS331_ADDR_WHO_AM_I);
	if (devId == LIS331_WHO_AM_I) {
        ACL_INT1_CNPU = 1;
        uint8_t ctrlData[] = {
            0b00100111, // normal mode, 50Hz output, all axes enabled
            0b00000000, // all filtering disabled
            0b11000010, // active-low open-drain interrupt lines, INT1 as Data Ready
            0b10110000, // block data update, 8g scale
            0b00000000  // disable sleep-to-wake
            };
        LIS331_WriteMultiple(LIS331_ADDR_CTRL_REG1, 5, ctrlData);
		return 1;
	} else {
		DBG_ERR_printf("LIS331 DEVID mismatch: got %02x, expected %02x", devId, LIS331_WHO_AM_I);
		return 0;
	}
}

uint8_t LIS331_GetInt1Status() {
    return !ACL_INT1_IO;
}

void LIS331_ReadDataMbg(int16_t* dataOut) {
    LIS331_ReadData(dataOut);

    dataOut[0] /= 4;
    dataOut[1] /= 4;
    dataOut[2] /= 4;
}

void LIS331_ReadData(int16_t* dataOut) {
    uint8_t buf[6];
    LIS331_ReadMultiple(LIS331_ADDR_OUT_X_L, 6, buf);

    dataOut[0] = buf[0];
    dataOut[0] |= (int16_t)buf[1] << 8;
    dataOut[1] = buf[2];
    dataOut[1] |= (int16_t)buf[3] << 8;
    dataOut[2] = buf[4];
    dataOut[2] |= (int16_t)buf[5] << 8;
}

void LIS331_Write(uint8_t addr, uint8_t data) {
	addr = 0b00111111 & addr;	// set write bit

	ACL_SPI_CS_IO = 0;

	WriteSPI1(addr);
	while (!DataRdySPI1());
	addr = ReadSPI1();

	WriteSPI1(data);
	while (!DataRdySPI1());
	addr = ReadSPI1();

	ACL_SPI_CS_IO = 1;
}

void LIS331_WriteMultiple(uint8_t addr, uint8_t len, uint8_t *buf) {
	addr = 0b01000000 | (0b00111111 & addr);	// set write bit

	ACL_SPI_CS_IO = 0;

	WriteSPI1(addr);
	while (!DataRdySPI1());
	addr = ReadSPI1();

	while (len > 0) {
        WriteSPI1(*buf);
        while (!DataRdySPI1());
        addr = ReadSPI1();
        buf++;
        len--;
    }

	ACL_SPI_CS_IO = 1;
}

uint8_t LIS331_Read(uint8_t addr) {
	uint8_t retval;

	addr = 0b10000000 | addr;	// set read bit

	ACL_SPI_CS_IO = 0;

    SPI1BUF = addr;
    while (!SPI1STATbits.SPIRBF);
    retval = SPI1BUF;
    WriteSPI1(addr);
	while (!DataRdySPI1());
	retval = ReadSPI1();

    SPI1BUF = LIS331_SPI_DUMMY;
    while (!SPI1STATbits.SPIRBF);
    retval = SPI1BUF;
	WriteSPI1(LIS331_SPI_DUMMY);
	while (!DataRdySPI1());
	retval = ReadSPI1();

	ACL_SPI_CS_IO = 1;

	return retval;
}

void LIS331_ReadMultiple(uint8_t addr, uint8_t len, uint8_t *buf) {
	addr = 0b11000000 | addr;	// set multiple read bit

	ACL_SPI_CS_IO = 0;

	WriteSPI1(addr);
	while (!DataRdySPI1());
	addr = ReadSPI1();

	while (len > 0) {
		WriteSPI1(LIS331_SPI_DUMMY);
		while (!DataRdySPI1());
		*buf = ReadSPI1();
		buf++;
		len--;
	}

	ACL_SPI_CS_IO = 1;
}


