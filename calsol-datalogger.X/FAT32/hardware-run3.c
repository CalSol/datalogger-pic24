/*
 * File:   hardware-run3.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 02 Jun 2012  Ducky   File creation
 *
 * @file
 * Hardware abstraction layer for board intialization functions
 */

#include "../hardware.h"

/**
 * Initializes oscillator configuration, including setting up PLL
 */
void OscInit(void) {
	_PLLPRE = 14;	// N1=16
	_PLLPOST = 1;	// N2=4
	_PLLDIV = 126;	// M=128
	__builtin_write_OSCCONL( 0x02 );    // enable SOSC
}

/**
 * Initializes analog input configuration, including whether pins are digital or analog.
 */
void AnalogInit(void) {
	AD1PCFGL = 0b0001111111111100;	// Set unused analog pins for digital IO

	AD1CON2bits.VCFG = 0b000;		// VR+ = AVdd, VR- = AVss
	AD1CON3bits.ADCS = 63;			// 64 Tcy conversion clock
	AD1CON1bits.SSRC = 0b111;		// Auto-convert
	AD1CON3bits.SAMC = 31;			// and auto-convert time bits
	AD1CON1bits.ASAM = 1;			// Auto-sample
	AD1CON1bits.FORM = 0b00;		// Integer representation
	AD1CON2bits.SMPI = 0b0000;		// Interrupt rate, 1 for each sample/convert

	AD1CHS0bits.CH0SA = ANA_CH_12VDIV;
	AD1CHS0bits.CH0SB = ANA_CH_12VDIV;

	AD1CON1bits.ADON = 1;			// Enable A/D module
}

/**
 * Initializes both direction and initial state of all GPIO pins.
 */
void OutputInit(void) {
	SD_SPI_CS_IO = 1;
	SD_SPI_CS_TRIS = 0;
}

/**
 * Initializes PPS selections for all peripheral modules using PPS: UART, ECAN, SD SPI.
 */
void PPSInit(void) {
	// Unlock Registers
	__asm__ volatile (	"MOV #OSCCON, w1 \n"
						"MOV #0x46, w2 \n"
						"MOV #0x57, w3 \n"
						"MOV.b w2, [w1] \n"
						"MOV.b w3, [w1] \n"
						"BCLR OSCCON,#6");
	// UART Pins
	UART_TX_RPR = U2TX_IO;
	//PGC_RPR = U2TX_IO;
	_U2RXR = UART_RX_RPN;

	// ECAN Pins
	ECAN_TXD_RPR = C1TX_IO;
	_C1RXR = ECAN_RXD_RPN;

	// SD SPI Pins
	SD_SPI_SCK_RPR = SCK2OUT_IO;
	SD_SPI_MOSI_RPR = SDO2_IO;
	_SDI2R = SD_SPI_MISO_RPN;

#ifdef HARDWARE_RUN_3
	_T3CKR = SOSCI_RPN;
#endif

	// Lock Registers
	__asm__ volatile (	"MOV #OSCCON, w1 \n"
						"MOV #0x46, w2 \n"
						"MOV #0x57, w3 \n"
						"MOV.b w2, [w1] \n"
						"MOV.b w3, [w1] \n"
						"BSET OSCCON, #6" );
}
