/*
 * File:   hardware-datalogger-1-4.h
 * Author: Ducky
 *
 * Revision History
 * Date         Author  Change
 * 06 Jun 2012  Ducky   Created IO mappings for the Datalogger 1.4 board.
 *
 * @file
 * Defines the hardware IO pins for the run 4 (1.4-rc1) board.
 */
#ifndef HARDWARE_H
#define HARDWARE_H

#include <p33Exxxx.h>

/*
 * Clock Settings
 */
#define Fosc                    120000000
#define Fcy                     (Fosc/2)

/*
 * LED GPIO
 */
#define LED_ON                  0
#define LED_OFF                 1

#define	LED_STAT_RED_IO         _RE1
#define LED_STAT_RED_TRIS       _TRISE1
#define	LED_STAT_GRN_IO         _RE0
#define LED_STAT_GRN_TRIS       _TRISE0
#define	LED_STAT_BLU_IO         _RF1
#define LED_STAT_BLU_TRIS       _TRISF1

#define LED_CAN_GRN_IO          _RE2
#define LED_CAN_GRN_TRIS        _TRISE2
#define LED_CAN_RED_IO          _RE3
#define LED_CAN_RED_TRIS        _TRISE3

#define LED_SD_GRN_IO           _RB5
#define LED_SD_GRN_TRIS         _TRISB5
#define LED_SD_RED_IO           _RB4
#define LED_SD_RED_TRIS         _TRISB4

#define LED_PWM_RPN             84
#define LED_PWM_RPR             _RP84R

/*
 * Button GPIO
 */
#define BTN_TEST_IO             _RD11
#define BTN_TEST_TRIS           _TRISD11
#define BTN_TEST_CNPU           _CNPUD11

#define BTN_DISMOUNT_IO         _RE5
#define BTN_DISMOUNT_TRIS       _TRISE5
#define BTN_DISMOUNT_CNPU       _CNPUE5

/*
 * Analog Configuration
 */
#define ANA_CH_12VDIV           0
#define ANA_CH_5VDIV            1
#define ANA_CH_VREF             2
#define ANA_CH_TEMP             3
#define ANA_SEN_CVR             8
#define ANA_SEN_EXT1            9

/*
 * Peripheral Configuration
 */
// Programming pins
#define PGD_RPN			39      // input only pin
#define PGC_RPN			38      // input only pin

// UART (BRG register calculated in code)
#define UART_TX_RPN		101
#define UART_TX_RPR		_RP101R
#define UART_RX_RPN		100
#define UART_RX_RPR		_RP100R

// ECAN
#define ECAN_RXD_RPN            47      // input only pin
#define ECAN_TXD_RPN            99
#define ECAN_TXD_RPR            _RP99R

// SD Card SPI Interface
// Note: Datalogger 1.4 has the SD SPI pins on non-remappable fast SPI2
#define SD_CD_IO                _RE7
#define SD_CD_TRIS              _TRISE7
#define SD_CD_CNPU              _CNPUE7

#define SD_WP_IO                _RE6
#define SD_WP_TRIS              _TRISE6
#define SD_WP_CNPU              _CNPUE6

#define SD_SPI_CS_IO            _RG9
#define SD_SPI_CS_TRIS          _TRISG9

// Accelerometer SPI Interface
#define ACL_SPI_CS_IO           _RD4
#define ACL_SPI_CS_TRIS         _TRISD4

#define ACL_SPI_MOSI_RPN        70
#define ACL_SPI_MOSI_RPR        _RP70R

#define ACL_SPI_MISO_RPN        69
#define ACL_SPI_MISO_RPR        _RP69R

#define ACL_SPI_SCK_RPN         71
#define ACL_SPI_SCK_RPR         _RP71R

#define ACL_INT1_IO             _RF0
#define ACL_INT1_TRIS           _TRISF0
#define ACL_INT1_CNPU           _CNPUF0
#define ACL_INT1_RPN            96
#define ACL_INT1_RPR            _RP96R

// RTC Interface
#define RTC_INT1_IO             _RD8
#define RTC_INT1_TRIS           _TRISD8
#define RTC_INT1_RPN            72
#define RTC_INT1_CNPU           _CNPUD8

// 32.768 kHz input
#define SOSCO_RPN               62     // input only pin
#define SOSCO_CNPU              _CNPUC14

// External expansion connection
#define EXP_EXT1_IO             _RD0
#define EXP_EXT1_TRIS           _TRISD0
#define EXP_EXT1_RPN            64
#define EXP_EXT1_RPR            _RP64R

#define EXP_EXT2_IO             _RD1
#define EXP_EXT2_TRIS           _TRISD1
#define EXP_EXT2_RPN            65
#define EXP_EXT2_RPR            _RP65R

#define EXP_EXT3_IO             _RD2
#define EXP_EXT3_TRIS           _TRISD2
#define EXP_EXT3_RPN            66
#define EXP_EXT3_RPR            _RP66R

#define EXP_EXT4_IO             _RD3
#define EXP_EXT4_TRIS           _TRISD3
#define EXP_EXT4_RPN            67
#define EXP_EXT4_RPR            _RP67R

/*
 * PPS Options
 */
#define NULL_IO		0
#define U1TX_IO		1
#define U1RTS_IO	2
#define U2TX_IO		3
#define U2RTS_IO	4
#define SDO1_IO		5
#define SCK1OUT_IO	6
#define SS1OUT_IO	7
#define SS2OUT_IO	10

#define C1TX_IO		14
#define C2TX_IO		15

#define OC1_IO		16
#define OC2_IO		17
#define OC3_IO		18
#define OC4_IO		19
#define OC5_IO		20
#define OC6_IO		21
#define OC7_IO		22
#define OC8_IO		23

#endif
