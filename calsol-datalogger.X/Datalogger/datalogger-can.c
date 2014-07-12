/*
 * File:   datalogger-canrecorder.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 13 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger CAN recorder and CAN communications routines.
 */

#include "../hardware.h"

#include "../types.h"

#include "../ecan.h"
#include "../timing.h"

#include "../UserInterface/datalogger-ui-hardware.h"
#include "../UserInterface/datalogger-ui-leds.h"

#include "datalogger-stringutil.h"
#include "datalogger-file.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/CAN"
#include "../debug-common.h"

void Datalogger_ProcessCANErrors(DlgFile *dlgFile) {
	static uint32_t lastTime = 0;
    uint32_t currTime = Get32bitTime();

    static uint8_t lastRxErrCnt = 0;
    uint8_t currRxErrCnt = C1ECbits.RERRCNT;
    static uint8_t lastTxErrCnt = 0;
    uint8_t currTxErrCnt = C1ECbits.TERRCNT;

    if (lastRxErrCnt != currRxErrCnt) {
		uint32_t diffTime = currTime - lastTime;
        DlgStr buf;
        DlgStr_Init(&buf, "CRE ");
        DlgStr_AppendTimestamp(&buf, currTime);
        DlgStr_AppendChar(&buf, '/');
        DlgStr_AppendDec16(&buf, diffTime);
        DlgStr_AppendString(&buf, " RX_ERR_CNT ");
        DlgStr_AppendDec16(&buf, lastRxErrCnt);
        DlgStr_AppendString(&buf, " -> ");
        DlgStr_AppendDec16(&buf, currRxErrCnt);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
    }

    if (lastTxErrCnt != currTxErrCnt) {
		uint32_t diffTime = currTime - lastTime;
        DlgStr buf;
        DlgStr_Init(&buf, "CTE ");
        DlgStr_AppendTimestamp(&buf, currTime);
        DlgStr_AppendChar(&buf, '/');
        DlgStr_AppendDec16(&buf, diffTime);
        DlgStr_AppendString(&buf, " TX_ERR_CNT ");
        DlgStr_AppendDec16(&buf, lastTxErrCnt);
        DlgStr_AppendString(&buf, " -> ");
        DlgStr_AppendDec16(&buf, currTxErrCnt);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
    }
    
    lastRxErrCnt = currRxErrCnt;
    lastTxErrCnt = currTxErrCnt;
    lastTime = currTime;
}

#define CAN_ID_BUS_MEAS     0x501
#define CAN_ID_BUS_ACCUM    0x650
/*
 *  PAcket format <dlc=8> <4x: slope> <4x: slope> - floats
 */

void Datalogger_PostProcessStdCanMessage(DlgFile *dlgFile, uint16_t sid, uint8_t dlc, uint8_t* data) {
    uint32_t currTime = Get32bitTime();
    
    if (sid == CAN_ID_BUS_MEAS) {
        static double accumulated = 0;
        float* slope1 = (float*)(dlc+0);
        float* slope2 = (float*)(dlc+4);
        double slopeProd = *slope1 * *slope2;
        accumulated += slopeProd;
        float accumFloat = (float)accumulated;
        uint8_t* accumData = (uint8_t*)&accumFloat;

        ECAN_WriteStandardBuffer(1, CAN_ID_BUS_ACCUM, 4, accumData);
        ECAN_TransmitBuffer(0);

        DlgStr buf;
        DlgStr_Init(&buf, "CTM ");
        DlgStr_AppendTimestamp(&buf, currTime);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16(&buf, dlc);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendHex12(&buf, sid);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendHex8(&buf, accumData[0]);
        DlgStr_AppendChar(&buf, ',');
		DlgStr_AppendHex8(&buf, accumData[1]);
        DlgStr_AppendChar(&buf, ',');
        DlgStr_AppendHex8(&buf, accumData[2]);
        DlgStr_AppendChar(&buf, ',');
        DlgStr_AppendHex8(&buf, accumData[3]);
        DlgStr_AppendChar(&buf, ',');
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
    }
}

void Datalogger_ProcessMessageFunctions(DlgFile *dlgFile) {

}

void Datalogger_ProcessCANMessages(DlgFile *dlgFile) {
	static uint8_t canOverflow = 0; // CAN receive buffers overflowed
	static uint8_t msgOverflow = 0; //
	static uint32_t lastTime = 0;
    uint32_t currTime = Get32bitTime();

	int8_t nextBuf;

	while ((nextBuf = ECAN_GetNextRXBuffer()) != -1) {
		uint16_t sid;
		uint32_t eid;
		uint8_t dlc;
		uint8_t data[8];
		uint8_t i;
		uint32_t currTime = Get32bitTime();
		uint32_t diffTime = currTime - lastTime;

        // Create message header and add timestamp + uncertainty
        DlgStr buf;
        DlgStr_Init(&buf, "CRM ");
        DlgStr_AppendTimestamp(&buf, currTime);
        DlgStr_AppendChar(&buf, '/');
        DlgStr_AppendDec16(&buf, diffTime);
        DlgStr_AppendChar(&buf, ' ');

		// TODO: FIX OVERFLOW CHECKS
		// Check overflow
		if ((C1RXOVF1 != 0) || (C1RXOVF2 != 0)) {
			C1RXOVF1 = 0;
			C1RXOVF2 = 0;
			UI_LED_Pulse(&UI_LED_CAN_Error);
			canOverflow = 1;
		}
		if (canOverflow) {
            DlgStr errBuf;
            DlgStr_Init(&errBuf, "CRE ");
            DlgStr_AppendTimestamp(&errBuf, currTime);
            DlgStr_AppendChar(&errBuf, '/');
            DlgStr_AppendDec16(&errBuf, diffTime);
            DlgStr_AppendString(&errBuf, " OVF CAN_BUF\n");
			if (!DlgFile_WriteAtomicDlgStr(dlgFile, &errBuf)) {
				msgOverflow = 1;
				UI_LED_Pulse(&UI_LED_CAN_Error);
			}
			canOverflow = 0;
		}
		if (msgOverflow) {
            DlgStr errBuf;
            DlgStr_Init(&errBuf, "CRE ");
            DlgStr_AppendTimestamp(&errBuf, currTime);
            DlgStr_AppendChar(&errBuf, '/');
            DlgStr_AppendDec16(&errBuf, diffTime);
            DlgStr_AppendString(&errBuf, " OVF FILE\n");
			if (!DlgFile_WriteAtomicDlgStr(dlgFile, &buf)) {
				UI_LED_Pulse(&UI_LED_SD_Error);
			}
			msgOverflow = 0;
		}

		// Read message
		dlc = ECAN_ReadBuffer(nextBuf, &sid, &eid, 8, data);

		// Generate message contents
        DlgStr_AppendDec16(&buf, dlc);
        DlgStr_AppendChar(&buf, ' ');

        DlgStr_AppendHex12(&buf, sid);
        DlgStr_AppendChar(&buf, ' ');

        // Append data
		for (i=0;i<dlc;i++) {
            DlgStr_AppendHex8(&buf, data[i]);
            if (i < dlc-1) {
                DlgStr_AppendChar(&buf, ',');
            }
		}
        DlgStr_AppendChar(&buf, '\n');
		
		if (!msgOverflow
			&& !DlgFile_WriteAtomicDlgStr(dlgFile, &buf)) {
			msgOverflow = 1;
		}

		// User interface stuff
		UI_LED_Pulse(&UI_LED_CAN_RX);

        // Message post-processing
        Datalogger_PostProcessStdCanMessage(dlgFile, sid, dlc, data);
	}

	lastTime = currTime;
}

void Datalogger_ProcessCANCommunications(DlgFile *dlgFile) {
	static uint32_t lastTime = 0;
	static uint16_t lastOffset = 0;
	uint16_t currOffset = GetbmsecOffset();;
	static uint8_t txFailed = 0;

    // Check for and log failures
	if (C1TR01CONbits.TXERR0 && txFailed == 0) {
		uint32_t currTime = Get32bitTime();
		uint32_t diffTime = currTime - lastTime;

        DlgStr errBuf;
        DlgStr_Init(&errBuf, "CTE ");
        DlgStr_AppendTimestamp(&errBuf, currTime);
        DlgStr_AppendChar(&errBuf, '/');
        DlgStr_AppendDec16(&errBuf, diffTime);
        DlgStr_AppendString(&errBuf, " ERR TXERR0\n");
        DlgFile_WriteAtomicDlgStr(dlgFile, &errBuf);

		txFailed = 1;

		UI_LED_Pulse(&UI_LED_CAN_Error);
	}

    // Heartbeat transmission
	if (lastOffset > currOffset) {
		DBG_SPAM_printf("CAN Heartbeat");
		ECAN_TransmitBuffer(0);
		txFailed = 0;
		UI_LED_Pulse(&UI_LED_CAN_TX);
	}

	lastOffset = GetbmsecOffset();
	lastTime = Get32bitTime();
}
