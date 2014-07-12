/*
 * File:  datalogger-file.c
 * Author: Ducky
 *
 * Created on August 12, 2011, 1:15 PM
 *
 * Revision History
 * Date			Author	Change
 * 12 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger file operations, including a large circular buffer in RAM.
 */

#include <string.h>

#include "datalogger-file.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/File"
#include "../debug-common.h"
#include "datalogger-stringutil.h"

void DlgFile_Init(DlgFile *dlgFile, FS_File *file,
		uint8_t *buffer, uint16_t bufferSize) {
	dlgFile->file = file;
	dlgFile->buffer = buffer;
	dlgFile->bufferSize = bufferSize;
	dlgFile->bufferFree = bufferSize;
	dlgFile->readPos = 0;
	dlgFile->writePos = 0;
	dlgFile->requestClose = 0;
}

uint16_t DlgFile_WriteAtomic(DlgFile *dlgFile, uint8_t *data,
		uint16_t dataLen) {
	// Check if there is enough free space in the buffer for an atomic write
	if (dataLen > dlgFile->bufferFree) {
		return 0;
	}
	if (dlgFile->requestClose) {
		return 0;
	}

	// If the buffer is clear and the file is ready, write directly to the file
	if (dlgFile->bufferFree == dlgFile->bufferSize
			&& dlgFile->file->state != FILE_Uninitialized
			&& dlgFile->file->state != FILE_Creating) {
		fs_length_t writeLength = FS_WriteFile(dlgFile->file, data, dataLen);
		data += writeLength;
		dataLen -= writeLength;

		DBG_SPAM_printf("DLGFile: write->card %u bytes", writeLength);
	}
	while (dataLen > 0) {
		fs_length_t writeLength;
		// Determine maximum contigious write length
		if (dlgFile->readPos > dlgFile->writePos) {
			writeLength = dlgFile->bufferFree;
		} else {
			writeLength = dlgFile->bufferSize - dlgFile->writePos;
		}
		// Cap write length at data length
		if (dataLen < writeLength) {
			writeLength = dataLen;
		}
		// Write data and update buffer variables
		memcpy(dlgFile->buffer + dlgFile->writePos, data, writeLength);
		dlgFile->writePos += writeLength;
		if (dlgFile->writePos >= dlgFile->bufferSize) {
			dlgFile->writePos = 0;
		}
		dlgFile->bufferFree -= writeLength;

		// Update remaining data
		dataLen -= writeLength;
		data += writeLength;

		DBG_SPAM_printf("DLGFile: write->buffer %u bytes, bufFree = %u", writeLength, dlgFile->bufferFree);
	}

	return 1;
}

uint16_t DlgFile_WriteAtomicDlgStr(DlgFile *dlgFile, DlgStr* dlgStr) {
    return DlgFile_WriteAtomic(dlgFile, (uint8_t*)dlgStr->string, dlgStr->pos - dlgStr->string);
}

fs_result_t DlgFile_Tasks(DlgFile *dlgFile) {
	// Check if there is data to write
	if (dlgFile->file->state != FILE_Uninitialized
			&& dlgFile->file->state != FILE_Creating) {
		while (dlgFile->bufferFree != dlgFile->bufferSize) {
			fs_length_t writeLength;

			if (dlgFile->writePos > dlgFile->readPos) {
				writeLength = dlgFile->writePos - dlgFile->readPos;
			} else {
				writeLength = dlgFile->bufferSize - dlgFile->readPos;
			}
			writeLength = FS_WriteFile(dlgFile->file, dlgFile->buffer + dlgFile->readPos, writeLength);
			if (writeLength > 0) {
				dlgFile->readPos += writeLength;
				if (dlgFile->readPos >= dlgFile->bufferSize) {
					dlgFile->readPos = 0;
				}
				dlgFile->bufferFree += writeLength;

				DBG_SPAM_printf("DLGFile: buffer->card %u bytes, bufFree = %u", writeLength, dlgFile->bufferFree);
			} else {
				// No data written (no filesystem file buffer left), we're done
				break;
			}
		}
	}

	// Check if we want to close the file
	if (dlgFile->requestClose && !dlgFile->file->requestClose
			&& dlgFile->bufferFree == dlgFile->bufferSize) {
		DBG_DATA_printf("DLGFile: Request file close");
		FS_RequestFileClose(dlgFile->file);
	}

	// Do filesystem tasks
	if (dlgFile->file->state != FILE_Uninitialized
			&& dlgFile->file->state != FILE_Creating) {
		return FS_FileTasks(dlgFile->file);
	} else {
		return FS_UNREADY;
	}
}

void DlgFile_RequestClose(DlgFile *dlgFile) {
	dlgFile->requestClose = 1;
}
