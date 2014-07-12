/*
 * File:   datalogger-autoterminate.c
 * Author: Ducky
 *
 * Created on August 13, 2011, 4:47 PM
 *
 * Revision History
 * Date			Author	Change
 * 13 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger automatic file closing routine.
 */

#define TERM_THRES_HIGH         7000		// mV
#define TERM_THRES_LOW          6000		// mV

#define TERM_TIME               4096

#include "../UserInterface/datalogger-ui-leds.h"
#include "../timing.h"

#include "datalogger-applications.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/AutoTerm"
#include "../debug-common.h"

extern uint16_t currVoltage;

AutoTerminateReturn Datalogger_ProcessAutoTerminate() {
	static AutoTerminateState stableState = TERM_LOW;
	static uint32_t stableTime = 0;

    AutoTerminateState currState;
    uint32_t currTime = Get32bitTime();

    if (stableState == TERM_HIGH) {
        if (currVoltage > TERM_THRES_LOW) {
            currState = TERM_HIGH;
        } else {
            currState = TERM_LOW;
        }
    } else {
        if (currVoltage > TERM_THRES_HIGH) {
            currState = TERM_HIGH;
        } else {
            currState = TERM_LOW;
        }
    }

    if (stableState != currState) {
        if (currTime - stableTime > TERM_TIME) {
            stableState = currState;
            if (currState == TERM_LOW) {
                DBG_DATA_printf("Autotermination terminate");
                return TERM_TERMINATE;
            } else {
                DBG_DATA_printf("Autotermination restart");
                return TERM_RESTART;
            }
        } else {
            return TERM_NOOP;
        }
    } else {
        stableTime = currTime;
        return TERM_NOOP;
    }
}
