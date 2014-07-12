/*
 * File:   datalogger-file.h
 * Author: Ducky
 *
 * Created on August 12, 2011, 1:16 PM
 *
 * Revision History
 * Date			Author	Change
 * 12 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger file operations, including a large circular buffer in RAM.
 */

#ifndef DATALOGGER_FILE_H
#define DATALOGGER_FILE_H

#include "datalogger-stringutil.h"
#include "../FAT32/fat32-file.h"

typedef struct {
	FS_File *file;			/// Pointer to the open file.

	// Buffering variables
	uint8_t *buffer;		/// Pointer to the beginning of the data block.
	uint16_t bufferSize;	/// Size, in bytes, of the circular buffer.
	uint16_t bufferFree;	/// Number of free bytes left in the buffer;
	uint16_t readPos;		/// Position to read from, the beginning of the buffer.
	uint16_t writePos;		/// Position to write to, the end of the buffer.

	// Random
	uint8_t requestClose;	/// If the file is requested to be closed.
} DlgFile;

/**
 * Initializes the Datalogger file.
 *
 * @param[in] dlgFile Datalogger file to initialize.
 * @param[in] file Filesystem file to write to. Can be uninitialized, and disk
 * operations will not start until the file has been successfully initialized.
 * @param[in] buffer RAM buffer
 * @param[in] bufferSize Size of the RAM buffer, in bytes, or 0 if a RAM buffer
 * is not being used.
 */
void DlgFile_Init(DlgFile *dlgFile, FS_File *file,
		uint8_t *buffer, uint16_t bufferSize);

/**
 * Writes data to a Datalogger file.
 * This either writes the entire string or nothing at all. Partial writes
 * will NOT happen.
 *
 * @param[in] dlgFile Datalogger file to be written to,
 * @param[in] data Data to write.
 * @param[in] dataLen Data length, in bytes.
 * @return Result of the write operation.
 * @retval 0 Write failed - not enough space in the buffer.
 * @retval 1 Write successful, entire data written.
 */
uint16_t DlgFile_WriteAtomic(DlgFile *dlgFile, uint8_t *data,
		uint16_t dataLen);

/**
 * Writes the contents of a DlgStr object to this file.
 * This either writes the entire string or nothing at all. Partial writes
 * will NOT happen.
 *
 * @param[in] dlgFile Datalogger file to be written to,
 * @param[in] dlgStr String contents to write.
 * @return Result of the write operation.
 * @retval 0 Write failed - not enough space in the buffer.
 * @retval 1 Write successful, entire data written.
 */
uint16_t DlgFile_WriteAtomicDlgStr(DlgFile *dlgFile, DlgStr* dlgStr);

/**
 * Called periodically to perform tasks for the Datalogger file, such as
 * writing the RAM buffer to the file and performing filesystem file tasks.
 *
 * @param[in] dlgFile Datalogger file to process.
 * @return Result of the call to FS_FileTasks.
 */
fs_result_t DlgFile_Tasks(DlgFile *dlgFile);

/**
 * Requests that the file be closed.
 *
 * @param[in] dlgFile Datalogger file to process.
 */
void DlgFile_RequestClose(DlgFile *dlgFile);

#endif
