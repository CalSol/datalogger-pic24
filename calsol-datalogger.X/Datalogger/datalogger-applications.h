/*
 * File:   datalogger-applications.c
 * Author: Ducky
 *
 * Created on August 13, 2011, 4:45 PM
 *
 * Revision History
 * Date			Author	Change
 * 13 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger applications, like recording CAN and the like.
 */

#ifndef DATALOGGER_APPLICATION_H
#define DATALOGGER_APPLICATION_H

#include "../types.h"

#include "datalogger-file.h"

typedef struct {
	uint16_t sampleCount;
	uint16_t low;
	uint16_t high;
	uint32_t runningAverage;
} StatisticalMeasurement;

typedef struct {
	uint16_t sampleCount;
	uint16_t low;
	uint16_t high;
	uint32_t sum;
    uint64_t squareSum;
} StatMeas16;

typedef enum {
    TERM_LOW,
    TERM_HIGH
} AutoTerminateState;

typedef enum {
    TERM_NOOP,
    TERM_TERMINATE,
    TERM_RESTART
} AutoTerminateReturn;
/**
 * Processes the auto-termination feature.
 *
 * @return Whether to terminate or not. This will usually return TERM_NOOP
 * (do nothing), but may return TERM_TERMINATE or TERM_START ONCE per
 * filtered voltage transition.
 *
 * @retval TERM_NOOP Do not terminate.
 * @retval TERM_TERMINATE Terminate (high-to-low voltage transition detected)
 * @retval TERM_START Restart (low-to-high voltage transition detected).
 *
 */
AutoTerminateReturn Datalogger_ProcessAutoTerminate();

/**
 * Processes CAN errors, writing changes in the error counter to file.
 * @param file Datalogger file to write to.
 */
void Datalogger_ProcessCANErrors(DlgFile *dlgFile);

/**
 * Processes CAN messages, writing the received messages to the file.
 * @param file Datalogger file to write to.
 */
void Datalogger_ProcessCANMessages(DlgFile *dlgFile);

/**
 * Processes CAN communications, such as heartbeat transmission.
 */
void Datalogger_ProcessCANCommunications(DlgFile *dlgFile);

/**
 * Initializes the voltage recorder stuff.
 * @param dlgFile Datalogger file to write to.
 */
void Datalogger_InitVoltageRecorder(DlgFile *dlgFile);

/**
 * Does voltage recording functions, such as calculating statistical values
 * or recording data to disk.
 * @param dlgFile Datalogger file to write to.
 */
void Datalogger_ProcessVoltageRecorder(DlgFile *dlgFile);

/**
 * Does performance recording functions, such as logging statistical value
 * of cycle time to disk.
 * @param dlgFile Datalogger file to write to.
 */
void Datalogger_ProcessPerfLogger(DlgFile *dlgFile);

/**
 * Initializes the voltage recorder stuff.
 * @param dlgFile Datalogger file to write to.
 */
void Datalogger_InitAccelerometer(DlgFile *dlgFile);

/**
 * Does voltage recording functions, such as calculating statistical values
 * or recording data to disk.
 * @param dlgFile Datalogger file to write to.
 */
void Datalogger_ProcessAccelerometer(DlgFile *dlgFile);

#endif
