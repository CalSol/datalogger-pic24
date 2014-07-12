/*
 * File:   hardware-run3.h
 * Author: Ducky
 *
 * Created on January 15, 2011, 5:22 PM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box,
 *						separated Run 2/3 hardware.
* 06 Jun 2012  Ducky   Refactored into IO Map.
 *
 * @file
 * Defines the hardware IO pins for the run 3 (1.2-rc1) board.
 */
#ifndef HARDWARE_H
#define HARDWARE_H

#if defined(__PIC24HJ128GP502__)
#include "C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h\p24Hxxxx.h"
#elif defined (__dsPIC33FJ128MC802__)
//#include "C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\dsPIC33F\h\p33Fxxxx.h"
#include <p33Fxxxx.h>
#else
#error "IO Map: Processor not listed"
#endif

/*
 * Clock Settings
 */
#define Fosc 40000000
#define Fcy (Fosc/2)

/*
 * Board Configuration
 */
#define DLG_NVM_EXTERNAL

/*
 * Onboard GPIO
 */
#define	LED_FAULT_IO		_RB7
#define LED_FAULT_TRIS		_TRISB7

/*
 * Analog Configuration
 */
#define ANA_CH_EXTANALOG	0
#define ANA_CH_12VDIV		1

/*
 * Peripheral Configuration
 */
// Programming pins
#define PGD_RPN			0
#define PGD_RPR			_RP0R
#define PGC_RPN			1
#define PGC_RPR			_RP1R

// UART (BRG register calculated in code)
#define UART_TX_RPN		10
#define UART_TX_RPR		_RP10R
#define UART_RX_RPN		11
#define UART_RX_RPR		_RP11R

// ECAN
#define ECAN_RXD_RPN	6
#define ECAN_RXD_RPR	_RP6R
#define ECAN_TXD_RPN	5
#define ECAN_TXD_RPR	_RP5R

// SD Card SPI Interface
#define SD_SPI_CS_IO	_RB15
#define SD_SPI_CS_TRIS	_TRISB15
#define SD_SPI_SCK_RPN	13
#define SD_SPI_SCK_RPR	_RP13R
#define SD_SPI_MOSI_RPN	14
#define SD_SPI_MOSI_RPR	_RP14R
#define SD_SPI_MISO_RPN	12
#define SD_SPI_MISO_RPR	_RP12R

// 32.768 kHz oscillator
#define SOSCI_RPN		4
#define SOSCI_RPR		_RP4R

// External expansion connection
#define EXP_EXT1_IO		_RB3
#define EXP_EXT1_TRIS	_TRISB3
#define EXP_EXT1_RPN	3
#define EXP_EXT1_RPR	_RP3R

#define EXP_EXT2_IO		_RB2
#define EXP_EXT2_TRIS	_TRISB2
#define EXP_EXT2_RPN	2
#define EXP_EXT2_RPR	_RP2R

#define EXP_EXT3_IO		_RB1
#define EXP_EXT3_TRIS	_TRISB1
#define EXP_EXT3_RPN	1
#define EXP_EXT3_RPR	_RP1R

#define EXP_EXT4_IO		_RB0
#define EXP_EXT4_TRIS	_TRISB0
#define EXP_EXT4_RPN	0
#define EXP_EXT4_RPR	_RP0R

/*
 * PPS Options
 */
#define NULL_IO		0
#define C1OUT_IO	1
#define C2OUT_IO	2
#define U1TX_IO		3
#define U1RTS_IO	4
#define U2TX_IO		5
#define U2RTS_IO	6
#define SDO1_IO		7
#define SCK1OUT_IO	8
#define SS1OUT_IO	9
#define SDO2_IO		10
#define SCK2OUT_IO	11
#define SS2OUT_IO	12

#define C1TX_IO		16

#define OC1_IO		18
#define OC2_IO		19
#define OC3_IO		20
#define OC4_IO		21
#define OC5_IO		22

#endif
