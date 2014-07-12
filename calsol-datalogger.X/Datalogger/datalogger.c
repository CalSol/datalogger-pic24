/*
 * File:   datalogger.c
 * Author: Ducky
 *
 * Created on August 12, 2011, 12:44 AM
 *
 * Revision History
 * Date			Author	Change
 * 12 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger application.
 */

#include <string.h>

#include "../hardware.h"
#include "../version.h"

#include "../ecan.h"
#include "../timing.h"

#include "../SD-SPI-DMA/sd-spi-dma.h"
#include "../FAT32/fat32.h"
#include "../FAT32/fat32-file.h"

#include "../UserInterface/datalogger-ui-hardware.h"
#include "../UserInterface/datalogger-ui-leds.h"

#include "../I2CDevices/pcf8523.h"

#include "datalogger.h"
#include "datalogger-stringutil.h"
#include "datalogger-file.h"
#include "datalogger-applications.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/Main"
#include "../debug-common.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

char *MonthLookup[] = {
	"Unk",
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec"
};

#define DLG_BUFFER_SIZE		16384
uint8_t dlgBuffer[DLG_BUFFER_SIZE] __attribute__((far));

SD_Card card;
FS_FAT32 fs;
FS_File file;
DlgFile dlgFile;

#define DLG_MAX_CARD_INIT_TRIES 16

uint8_t cardInfoWritten;
uint8_t cardInitTries = 0;

void Datalogger_TryFileInit() {
	if (!UI_Switch_GetCardDetect()) {
		UI_LED_SetState(&UI_LED_SD_Error, LED_On);
		card.State = SD_UNINITIALIZED;
		fs.State = FS_UNINITIALIZED;
		file.state = FILE_Uninitialized;
		cardInitTries = 0;
	}

	// Continue with the initializtaion process
	if (card.State == SD_UNINITIALIZED) {
		if (UI_Switch_GetCardDetect() && cardInitTries < DLG_MAX_CARD_INIT_TRIES) {
			UI_LED_SetState(&UI_LED_SD_Error, LED_Off);
			SD_Initialize(&card);
		}
	}
	if (card.State == SD_INITIALIZING) {
		sd_result_t result = SD_GetInitializeResult(&card);
		DBG_SPAM_printf("SD_GetInitializeResult -> 0x%02x, substate %u", result, card.SubState);
		if (result == SD_BUSY) {
		} else if (result == SD_SUCCESS) {
			DBG_DATA_printf("SD Card initialized");
			FAT32_Initialize(&fs, &card);
		} else if (result == SD_INITIALIZE_NOSUPPORT) {
			DBG_DATA_printf("SD Card initialialization failed: unsupported card, got 0x%02x", result);
			cardInitTries = DLG_MAX_CARD_INIT_TRIES;
			UI_LED_SetState(&UI_LED_SD_Error, LED_Blink);
		}
		else {
			DBG_DATA_printf("SD Card initialialization failed, got 0x%02x", result);
			cardInitTries++;
			UI_LED_SetState(&UI_LED_SD_Error, LED_Blink);
		}
	}
	if (fs.State == FS_INITIALIZING) {
		fs_result_t result = FAT32_GetInitializeResult(&fs);
		DBG_SPAM_printf("FAT32_GetInitializeResult -> 0x%02x, substate %u", result, fs.SubState);
		if (result == FS_BUSY) {
		} else if (result == FS_SUCCESS) {
			DBG_DATA_printf("FS initialized");
			FS_CreateFileSeqName(&fs, &fs.rootDirectory, &file, "DLG0000", "DLA", 3, 4);
		} else {
			DBG_DATA_printf("FS initialialization failed, got 0x%02x", result);
			cardInitTries++;
			UI_LED_SetState(&UI_LED_SD_Error, LED_Blink);
		}
	}
	if (file.state == FILE_Creating) {
		fs_result_t result = FS_GetCreateFileResult(&file);
		DBG_SPAM_printf("FS_GetCreateFileResult -> 0x%02x, substate %u", result, file.subState);
		if (result == FS_BUSY) {
		} else if (result == FS_SUCCESS) {
			DBG_DATA_printf("File created");
		} else {
			DBG_DATA_printf("File creation failed, got 0x%02x", result);
			cardInitTries++;
			UI_LED_SetState(&UI_LED_SD_Error, LED_Blink);
		}
	}
}

/**
 * Writes the header at the beginning of the file specifying file format, etc.
 * @param file Datalogger file to write to.
 * @return Result.
 * @retval 0 Failure - nothing was written, try again later.
 * @retval 1 Success.
 */
uint8_t Datalogger_WriteCardInfo(DlgFile *dlgFile) {
	SD_Card *card = dlgFile->file->fs->card;
    DlgStr buf;

    DlgStr_Init(&buf, "CRD ");

    DlgStr_AppendTimestamp(&buf, Get32bitTime());
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendHex8(&buf, card->MID);
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendStringLen(&buf, card->OID, 2);
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendStringLen(&buf, card->PNM, 5);
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendHex4(&buf, card->PRV >> 4);
    DlgStr_AppendChar(&buf, '.');
    DlgStr_AppendHex4(&buf, card->PRV);
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendHex32(&buf, card->PSN);
    DlgStr_AppendChar(&buf, ' ');

    DlgStr_AppendString(&buf, MonthLookup[(card->MDT >> 00) & 0b1111]);
    DlgStr_AppendChar(&buf, ' ');
    DlgStr_AppendDec16(&buf, (uint16_t)((card->MDT >> 4) & 0xff)+2000);
    DlgStr_AppendChar(&buf, '\n');
    
	return DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
}

void Datalogger_Init() {
	uint8_t i=0;

	DBG_printf("Datalogger Initialize");

    // Initialize SD card structs
	card = SD_CreateCard();
	fs.State = FS_UNINITIALIZED;
	file.state = FILE_Uninitialized;
	DlgFile_Init(&dlgFile, &file, dlgBuffer, DLG_BUFFER_SIZE);

	cardInfoWritten = 0;
	cardInitTries = 0;

    // Write header
    DlgStr buf;

    DlgStr_Init(&buf, "");
    DlgStr_AppendString(&buf, "PRM FMT 1\n");

    DlgStr_AppendString(&buf, "PRM SW ");
    DlgStr_AppendDec16(&buf, VERSION_MAJ);
    DlgStr_AppendChar(&buf, '.');
    DlgStr_AppendDec16(&buf, VERSION_MIN);
    DlgStr_AppendChar(&buf, '\n');
    DlgStr_AppendString(&buf, "PRM BUILD ");
    DlgStr_AppendString(&buf, "C30 v" STR(__C30_VERSION__) " " __DATE__ " " __TIME__ "\n");

    DlgStr_AppendString(&buf, "PRM TIMEBASE 1/1024s\n");

	DlgFile_WriteAtomicDlgStr(&dlgFile, &buf);

    // Initialize Datalogger applications
	Datalogger_InitVoltageRecorder(&dlgFile);
	Datalogger_InitAccelerometer(&dlgFile);

    // Log RTC time
    uint8_t good;
    struct tm time;
    uint32_t readTime;
    readTime = Get32bitTime();
    PCF8523_SingleRegisterWrite(PCF8523_ADDR_CONTROL_3, 0);
    time = PCF8523_GetTimeStruct(&good);

    DlgStr_Init(&buf, "T_RTC ");
    DlgStr_AppendTimestamp(&buf, readTime);
    DlgStr_AppendChar(&buf, ' ');
    DlgStr_AppendChar(&buf, good? 'G' : 'F');
    DlgStr_AppendChar(&buf, ' ');
    DlgStr_AppendTmStruct(&buf, time);
    DlgStr_AppendChar(&buf, '\n');

	DlgFile_WriteAtomicDlgStr(&dlgFile, &buf);

    // Initialize transmit buffers
	uint8_t canDat1[] = {0xca, 0xfe, 0x0d, 0x06, 0xf0, 0x0d};   // "cafe dog food"
	uint8_t canDat2[] = {0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe, 0xf0, 0x0d};   // "dead beef cafe food"
	//uint8_t canDat3[] = {0x1b, 0xad, 0xb0, 0x07}; // "1 bad boot"
	uint8_t canDat4[] = {0x13, 0x37};               // "1337"
    
    ECAN_WriteStandardBuffer(0, 0x47, 0, NULL);     // heartbeat signal

	ECAN_WriteStandardBuffer(1, 0x137, 6, canDat1); // test packets
	ECAN_WriteStandardBuffer(2, 0x138, 8, canDat2); // test packets
	ECAN_WriteStandardBuffer(3, 0x139, 2, canDat4); // test packets

    // UI LED Initialization
	for (i=0;i<UI_LED_Count;i++) {
		UI_LED_SetState(UI_LED_List[i], LED_Off);
	}

	UI_LED_SetBlinkPeriod(&UI_LED_Fault, 512);
	UI_LED_SetState(&UI_LED_Fault, LED_Blink);

	UI_LED_SetBlinkPeriod(&UI_LED_Status_Waiting, 512);
	UI_LED_SetOnTime(&UI_LED_Status_Waiting, 64);
	UI_LED_SetBlinkPeriod(&UI_LED_Status_Operate, 512);
	UI_LED_SetOnTime(&UI_LED_Status_Operate, 64);
	UI_LED_SetState(&UI_LED_Status_Operate, LED_Blink);

	UI_LED_Update();

	DBG_printf("Initialization complete")
}

void Datalogger_Loop() {
	static uint16_t lastTxTimer = 0;
	AutoTerminateReturn autoTerminate;

	UI_Switch_Update();

#ifdef DEBUG_MODE
	if (UI_Switch_GetTest()) {
		if (lastTxTimer > GetbmsecOffset()) {
			lastTxTimer = 0;
		}
		if (GetbmsecOffset() - lastTxTimer >= 1) {
			static char bufferTErr[35] = "TS xxxxxxxx/xx Test Test Duck Duck\n";
			DBG_SPAM_printf("CAN Transmit");
			ECAN_TransmitBuffer(1);
			ECAN_TransmitBuffer(2);
			ECAN_TransmitBuffer(3);
			UI_LED_Pulse(&UI_LED_CAN_TX);
			lastTxTimer = GetbmsecOffset();

			uint32_t currTime = Get32bitTime();
			Int32ToString(currTime, bufferTErr+3);
			uint16_t i = 0;
			for (i=0;i<32;i++) {
				DlgFile_WriteAtomic(&dlgFile, (uint8_t*)bufferTErr, 35);
				DlgFile_Tasks(&dlgFile);
			}
		}
	}
#endif

    Datalogger_ProcessCANErrors(&dlgFile);
	Datalogger_ProcessCANCommunications(&dlgFile);
    Datalogger_ProcessCANMessages(&dlgFile);
	Datalogger_ProcessAccelerometer(&dlgFile);
	Datalogger_ProcessVoltageRecorder(&dlgFile);
	Datalogger_ProcessPerfLogger(&dlgFile);
	autoTerminate = Datalogger_ProcessAutoTerminate();
	
	// If file is ready to go
	fs_result_t result = DlgFile_Tasks(&dlgFile);

	if (file.state == FILE_Uninitialized && file.state == FILE_Creating 
			&& file.state != FILE_Closed
			&& result != FS_BUSY && result != FS_IDLE) {
		DBG_DATA_printf("Error performing file tasks, got 0x%02x", result);
		UI_LED_Pulse(&UI_LED_Status_Error);
	}

	if (!dlgFile.requestClose) {
		if (!cardInfoWritten
				&& (file.state != FILE_Uninitialized && file.state != FILE_Creating)) {
			DBG_DATA_printf("Attempting to write card information");
			if (Datalogger_WriteCardInfo(&dlgFile)) {
				cardInfoWritten = 1;
			}
		}
	}

	if (file.state == FILE_Uninitialized || file.state == FILE_Creating) {
		Datalogger_TryFileInit();
	} else if (file.state == FILE_Closed) {
		UI_LED_SetState(&UI_LED_SD_Read, LED_On);
		UI_LED_SetState(&UI_LED_Status_Operate, LED_Off);
		UI_LED_SetState(&UI_LED_Status_Waiting, LED_Blink);

		if (!UI_Switch_GetCardDetect()) {
			Datalogger_Init();
		}
        if (autoTerminate == TERM_RESTART) {
            Datalogger_Init();
        }
	} else {
		// Process file-based user inputs
		if (UI_Switch_GetCardDismount()) {
			static char buffer[] = "DM xxxxxxxx Switch-initiated dismount\n";
			uint32_t currTime = Get32bitTime();
			Int32ToString(currTime, buffer+3);
			DBG_DATA_printf("Switch-initiated dismount");
			DlgFile_WriteAtomic(&dlgFile, (uint8_t*)buffer, strlen(buffer));

			DlgFile_RequestClose(&dlgFile);
		}
		if (autoTerminate == TERM_TERMINATE) {
			static char buffer[] = "DM xxxxxxxx Autotermination dismount\n";
			uint32_t currTime = Get32bitTime();
			Int32ToString(currTime, buffer+3);
			DlgFile_WriteAtomic(&dlgFile, (uint8_t*)buffer, strlen(buffer));
			DlgFile_RequestClose(&dlgFile);
            DBG_DATA_printf("Autotermination dismount");
		}
	}

	UI_LED_Update();
}
