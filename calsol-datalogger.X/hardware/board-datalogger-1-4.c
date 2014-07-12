/*
 * File:   board-datalogger-1-4.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 02 Jun 2012	Ducky	File creation
 * 06 Jun 2012  Ducky   Added code for 4x PLL
 *
 * @file
 * Board initialization functions for the Datalogger 1.4 board.
 */
#include "..\types.h"
#include "..\hardware.h"

#if defined(HARDWARE_DATALOGGER_1_4)

void HW_Init_Clock(void) {
    // Configure primary oscillator - 4x input clock multiplication
    _PLLPOST = 0b00;    // N2 = 2
    _PLLPRE = 6;        // N1 = 8
    _PLLDIV = 62;       // M = 64

    __builtin_write_OSCCONH(0b011);
    __builtin_write_OSCCONL(OSCCON | 0b1);

    while (!OSCCONbits.OSWEN);  // wait for new clock to become active
    while (!OSCCONbits.LOCK);   // wait for PLL to lock

    // Configure 32.768kHz clock input from RTC
    SOSCO_CNPU = 1;
}

void HW_Init_Analog(void) {
    ANSELB = (uint16_t)1 << ANA_CH_5VDIV
            | (uint16_t)1 << ANA_CH_12VDIV
            | (uint16_t)1 << ANA_CH_VREF
            | (uint16_t)1 << ANA_CH_TEMP;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;
    ANSELG = 0x00;
}

void HW_Init_IO(void) {
    SD_SPI_CS_IO = 1;
    SD_SPI_CS_TRIS = 0;

    ACL_SPI_CS_IO = 1;
    ACL_SPI_CS_TRIS = 0;
    ACL_INT1_TRIS = 1;

    RTC_INT1_TRIS = 1;
    RTC_INT1_CNPU = 1;

	// Unlock Registers
//    __builtin_write_OSCCONL(OSCCON & 0xbf);

	// UART Pins
	UART_TX_RPR = U2TX_IO;
	_U2RXR = UART_RX_RPN;

	// ECAN Pins
	ECAN_TXD_RPR = C1TX_IO;
	_C1RXR = ECAN_RXD_RPN;

	// Accelerometer SPI Pins
	ACL_SPI_SCK_RPR = SCK1OUT_IO;
	ACL_SPI_MOSI_RPR = SDO1_IO;
	_SDI1R = ACL_SPI_MISO_RPN;

    // TODO WTF CLOCK
	_T3CKR = SOSCO_RPN;

	// Lock Registers
    //__builtin_write_OSCCONL(OSCCON | 0x40);
}

void HW_Init_Peripherals(void) {

}

#endif
