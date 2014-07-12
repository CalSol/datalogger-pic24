/*
 * File:   datalogger-voltagelogger.c
 * Author: Ducky
 *
 * Created on August 13, 2011, 6:59 PM
 *
 * Revision History
 * Date			Author	Change
 * 13 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger voltage logging functions.
 */

#include <stdlib.h>
#include <string.h>

#include "../types.h"

#include "../timing.h"

#include "../I2CDevices/lis331.h"

#include "datalogger-stringutil.h"
#include "datalogger-file.h"
#include "datalogger-applications.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/Accelerometer"
#include "../debug-common.h"


void Datalogger_InitAccelerometer(DlgFile *dlgFile) {
	uint8_t status = LIS331_Init();
    
    if (status == 0) {
        DlgFile_WriteAtomic(dlgFile, (uint8_t*)"ACL INIT FAIL\n", 14);
    } else {
        DlgFile_WriteAtomic(dlgFile, (uint8_t*)"ACL INIT GOOD\n", 14);
    }
}

void Datalogger_ProcessAccelerometer(DlgFile *dlgFile) {
    // Do not log data before file is initialized
    // otherwise this takes up buffer space
    uint8_t fileReady = (dlgFile->file->state != FILE_Uninitialized)
            && (dlgFile->file->state != FILE_Creating)
			&& (dlgFile->file->state != FILE_Closed);

    if (LIS331_GetInt1Status() && fileReady) {
        uint32_t currTime = Get32bitTime();
        int16_t aclData[3];
        LIS331_ReadDataMbg(aclData);

        DlgStr buf;
        DlgStr_Init(&buf, "ACL ");
        DlgStr_AppendTimestamp(&buf, currTime);
        DlgStr_AppendString(&buf, " X ");
        DlgStr_AppendDec16Dec(&buf, aclData[0], 3);
        DlgStr_AppendString(&buf, " Y ");
        DlgStr_AppendDec16Dec(&buf, aclData[1], 3);
        DlgStr_AppendString(&buf, " Z ");
        DlgStr_AppendDec16Dec(&buf, aclData[2], 3);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
    }
}
