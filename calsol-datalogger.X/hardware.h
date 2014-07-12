/*
 * File:   hardware.h
 * Author: Ducky
 *
 * Created on July 21, 2011, 9:48 PM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	File creation.
 * 02 Jun 2012  Ducky   Refactoring - changed hardware-*.h to iomap-*.h and
 *                      added generic hardware initializtion function prototypes.
 *
 * @file
 * Defines the hardware platform upon which the code runs.
 * As a general note, only the latest hardware platform will be fully supported
 * although backwards compatibility will remain a goal.
 *
 * The define macro to select the hardware should be set in the project options.
 *
 * Additionally, configuration functions are defined here.
 */

#ifndef HARDWARE_DATALOGGER_1_4
#define HARDWARE_DATALOGGER_1_4
#endif

/**
 * IO mappings
 */
#if defined(HARDWARE_RUN_3)
	#include "hardware\iomap-run3.h"
#elif defined(HARDWARE_DATALOGGER_1_4)
	#include "hardware\iomap-datalogger-1-4.h"
#elif defined(HARDWARE_CANBRIDGE)
	#include "hardware\iomap-canbridge.h"
#endif

/**
 * Initializes clock sources including the primary oscillator and 32.768 kHz clock.
 */
void HW_Init_Clock();

/**
 * Sets pins as analog/digital and initializes the ADC.
 */
void HW_Init_Analog();

/**
 * Initializes IO pins - sets initial state (for outputs) and pin directionality.
 * Also sets peripheral pin select.
 */
void HW_Init_IO();

/**
 * Initializes board peripherals. This should only do board-specific init, and
 * tasks like initializing the UART would be handled by the UART module.
 */
void HW_Init_Peripherals();
