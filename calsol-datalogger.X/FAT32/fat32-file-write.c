/*
 * File:   fat32-file-write.c
 * Author: Ducky
 *
 * Created on August 7, 2011, 3:57 PM
 *
 * Revision History
 * Date			Author	Change
 * 07 Arg 2011	Ducky	Initial implementation.
 *
 * @file
 * File write and buffering code.
 */

#include <string.h>

//#define DEBUG_UART
//#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "File/Write"
#include "../debug-common.h"
#include "../debug-log.h"

#include "fat32-file.h"

fs_length_t FS_WriteFile(FS_File *file, uint8_t *data, fs_length_t dataLen) {
	fs_length_t dataLeft = dataLen;

	if (file->requestClose) {
		return 0;
	}

	// Fill buffers until there are no more left
	while ((file->dataBufferNumFilled < FS_NUM_DATA_BUFFERS) && (dataLeft > 0)) {
		// There is a free buffer, check out much space is left
		uint8_t *buf = file->dataBuffer[file->dataBufferFill] + file->dataBufferPos;
		fs_length_t blockDataLen = dataLeft;

		if (blockDataLen > file->dataBufferSize - file->dataBufferPos) {
			blockDataLen = file->dataBufferSize - file->dataBufferPos;
		} else {
			blockDataLen = dataLeft;
		}

		DBG_SPAM_printf("Copying block of %u to file buffer", blockDataLen);

		memcpy((void*)buf, (void*)data, blockDataLen);
		dataLeft -= blockDataLen;
		data += blockDataLen;

		file->dataBufferPos += blockDataLen;
		// Advance buffer if necessary
		if (file->dataBufferPos >= file->dataBufferSize) {
			file->dataBufferFill++;
			if (file->dataBufferFill == FS_NUM_DATA_BUFFERS) {
				file->dataBufferFill = 0;
			}
			file->dataBufferNumFilled++;
			file->dataBufferPos = 0;
		}
	}
	file->size += dataLen - dataLeft;

	return dataLen - dataLeft;
}
