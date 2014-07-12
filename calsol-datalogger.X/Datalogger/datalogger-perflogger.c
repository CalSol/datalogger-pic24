/*
 * File:   datalogger-perflogger.c
 * Author: Ducky
 *
 * Created on August 14, 2011, 11:18 AM
 */

#include <stdlib.h>
#include <string.h>

#include "../types.h"

#include "../ecan.h"
#include "../timing.h"

#include "../UserInterface/datalogger-ui-hardware.h"
#include "../UserInterface/datalogger-ui-leds.h"

#include "datalogger-stringutil.h"
#include "datalogger-file.h"
#include "datalogger-applications.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/PerfLog"
#include "../debug-common.h"

StatisticalMeasurement Performance = {0,0,0,0};

void Datalogger_ProcessPerfLogger(DlgFile *dlgFile) {
	static uint16_t lastSecOffset = 0;
	uint32_t currSecOffset = GetbmsecOffset();
	
	if (lastSecOffset > currSecOffset) {
        uint16_t sampleCount = Performance.sampleCount;
		uint16_t average = (Performance.runningAverage/Performance.sampleCount);
		uint16_t high = Performance.high;
		uint16_t low = Performance.low;
        
		DBG_SPAM_printf("Loop time: Low %u, Avg %u, High %u, Samp %u", low, average, high, Performance.sampleCount);

        DlgStr buf;

        DlgStr_Init(&buf, "PFM ");
        DlgStr_AppendTimestamp(&buf, Get32bitTime());
        DlgStr_AppendString(&buf, " LPTM ");
        DlgStr_AppendUDec16(&buf, sampleCount);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendUDec16(&buf, average);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendUDec16(&buf, low);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendUDec16(&buf, high);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);

		// Reset statistical counters
		Performance.sampleCount = 0;
		Performance.low = 65535;
		Performance.high = 0;
		Performance.runningAverage = 0;
	}

    // Sample this loop's timing
    uint16_t diffTime;
    if (lastSecOffset > currSecOffset) {
        diffTime = currSecOffset + 1024 - lastSecOffset;
    } else {
        diffTime = currSecOffset - lastSecOffset;
    }


	Performance.runningAverage += diffTime;
	Performance.sampleCount += 1;
	if (diffTime > Performance.high) {
		Performance.high = diffTime;
	}
	if (diffTime < Performance.low) {
		Performance.low = diffTime;
	}

	lastSecOffset = currSecOffset;
}
