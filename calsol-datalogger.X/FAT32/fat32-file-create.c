/*
 * File:   fat32-file-create.c
 * Author: Ducky
 *
 * Created on July 29, 2011, 7:48 PM
 *
 * Revision History
 * Date			Author	Change
 * 29 Jul 2011	Ducky	Initial implementation.
 *
 * TODO
 * 01 Aug 2011	Ducky	TODO Check FAT before allocating - latest allocated
 *						cluster doesn't seem to work.
 *
 * @file
 * File creation operations for FAT32 filesystem files.
 */

#include <string.h>

#include "fat32-util.h"
#include "fat32-file-util.h"

#include "fat32-file.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#define DEBUG_UART_SPAM
#define DBG_MODULE "File/Create"
#include "../debug-common.h"
#include "../debug-log.h"

#define FILE_CREATE_SUB_BEGIN			0	/// Operation beginning
#define FILE_CREATE_SUB_READDIRTABLE	1	/// Reading directory table looking for an empty entry

/**
 * Parses a directory sturcture, looking for an empty entry. If one is found,
 * the details are populated into the file data structure and this function
 * return 1.
 * If the file has the sequential naming option (nameNumDigits != 0), this also
 * checks each existing entry and increments the name as necessary.
 *
 * @param file File structure.
 * @param data Data block of the sector containing the directory table.
 * @return Whether an empty entry was found.
 * @retval 1 An empty entry was found.
 * @retval 0 An empty entry was not found.
 */
uint8_t ProcessDirectoryTableBlock(FS_File *file, uint8_t *data) {
	uint16_t pos = 0;
	for (pos=0;pos<file->fs->bytesPerSector;pos+=32) {
		DBG_SPAM_printf("Searching record '%8.8s.%3.3s'.", data+pos, data+pos+8);
		if (data[pos] == 0x00 || data[pos] == 0xe5) {	// available entry
			file->dirTableBlockOffset = pos;
			return 1;
		} else {
			if (file->nameNumDigits != 0
					&& !strncmp((char*)data+pos, file->name, file->nameMatchChars)
					&& !strncmp((char*)data+pos+8, file->ext, 3)) {
				uint8_t isSmaller = 1;
				uint8_t i;
				
				for (i=file->nameMatchChars;i<file->nameMatchChars+file->nameNumDigits;i++) {
					if (data[pos+i] < file->name[i]) {
						isSmaller = 1;
						break;
					} else if (data[pos+i] > file->name[i]) {
						isSmaller = 0;
						break;
					}
				}
				if (isSmaller) {
					uint8_t carry = 1;
					for (i=file->nameMatchChars+file->nameNumDigits-1;i>=file->nameMatchChars;i--) {
						if (carry) {
							file->name[i] = data[pos+i] + 1;
							if (file->name[i] == '9' + 1) {
								file->name[i] = 'A';
								carry = 0;
							} else if (file->name[i] > 'F') {
								file->name[i] = '0';
								carry = 1;
							} else {
								carry = 0;
							}
						} else {
							file->name[i] = data[pos+i];
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
 * Initializes the non-filesystem dependent portions of a file struct.
 * @param file File structure to initialize.
 */
void FAT32_InitializeEmptyFileStruct(FS_File *file) {
	SD_Card *card = file->fs->card;
    uint8_t i = 0;

	file->size = 0;
	file->position = 0;
	
	file->currFATData = file->currFATDataAlloc;
	file->currFATData = file->currFATDataAlloc;
	file->currFATLBA = 0xffffffff;

	file->fsBuffer = card->DataBlocks[0].Data + 2;
    for (i=0; i<FS_NUM_DATA_BUFFERS; i++) {
        file->dataBuffer[i] = card->DataBlocks[i+1].Data + 2;
    }
	file->dataBufferSize = card->BlockSize;
	
	file->dataBufferWrite = 0;
	file->dataBufferFill = 0;
	file->dataBufferNumFilled = 0;
	file->dataBufferPos = 0;

	file->startCluster = 0;

	file->dirTableDirty = 0;
	file->requestClose = 0;
}

fs_result_t FS_CreateFile(FS_FAT32 *fs, FS_Directory *dir, FS_File *file, char *name, char *ext) {
	uint8_t i = 0;

	file->dir = dir;
	file->fs = fs;

	// Initialize the file structure
	FAT32_InitializeEmptyFileStruct(file);

	file->state = FILE_Creating;
	file->subState = FILE_CREATE_SUB_BEGIN;

	file->dirTableCluster = file->fs->rootDirectory.directoryTableBeginCluster;
	file->dirTableLBA = GetClusterLBA(fs, file->dirTableCluster);
	file->dirTableLBAClusterOffset = 0;

	for (i=0;i<8 && *name != 0;i++) {
		file->name[i] = name[i];
	}
	for (i=0;i<3 && *ext != 0;i++) {
		file->ext[i] = ext[i];
	}

	file->nameMatchChars = 0;
	file->nameNumDigits = 0;

	return FS_GetCreateFileResult(file);
}

fs_result_t FS_CreateFileSeqName(FS_FAT32 *fs, FS_Directory *dir, FS_File *file,
		char *name, char *ext, uint8_t prefixLength, uint8_t digitLength) {
	uint8_t i = 0;

	file->dir = dir;
	file->fs = fs;

	// Initialize the file structure
	FAT32_InitializeEmptyFileStruct(file);

	file->state = FILE_Creating;
	file->subState = FILE_CREATE_SUB_BEGIN;

	file->dirTableCluster = file->fs->rootDirectory.directoryTableBeginCluster;
	file->dirTableLBA = GetClusterLBA(fs, file->dirTableCluster);
	file->dirTableLBAClusterOffset = 0;

	for (i=0;i<8 && *name != 0;i++) {
		file->name[i] = name[i];
	}
	for (i=0;i<3 && *ext != 0;i++) {
		file->ext[i] = ext[i];
	}

	file->nameMatchChars = prefixLength;
	file->nameNumDigits = digitLength;

	return FS_GetCreateFileResult(file);
}

fs_result_t FS_GetCreateFileResult(FS_File *file) {
	sd_result_t result = SD_BUSY;

	if (file->state != FILE_Creating) {
		DBG_ERR_printf("Failed: File not in Creating state, got 0x%02x", file->state);
	}

	if (file->subState == FILE_CREATE_SUB_BEGIN) {
		// Initialize the file structure
		file->startCluster = 0x0000;
		file->currCluster = file->fs->mostRecentCluster + 1;
		file->currLBA = GetClusterLBA(file->fs, file->currCluster);
		file->currLBAClusterOffset = 0;
		file->currFATClusterEnd = 0;

		// Start reading in Directory Table blocks
		file->subState = FILE_CREATE_SUB_READDIRTABLE;
		DBG_SPAM_printf("Read directory table at LBA 0x%08lx", file->dirTableLBA);
		result = SD_DMA_SingleBlockRead(file->fs->card, file->dirTableLBA, &file->fs->card->DataBlocks[0]);
		if (result == SD_BUSY) {
			return FS_BUSY;
		}
	}

	while (file->subState == FILE_CREATE_SUB_READDIRTABLE) {
		if (result == SD_BUSY) {
			result = SD_DMA_GetSingleBlockReadResult(file->fs->card);
		}

		if (result == SD_BUSY) {
			return FS_BUSY;
		} else if (result != SD_SUCCESS) {
			DBG_ERR_printf("Failed: Error reading directory table at LBA 0x%08lx, got 0x%02x", file->dirTableLBA, result);
			file->state = FILE_Uninitialized;
			return FS_PHY_ERR;
		}

		if (ProcessDirectoryTableBlock(file, file->fsBuffer)) {
			// Empty entry found, populate data and continue reading next block
			DBG_SPAM_printf("Empty directory table entry found");

			// Fill in the directory table entry
			FAT32_WriteDirectoryTableEntry(file, file->fsBuffer);
			memcpy(file->dirTableBlockData, file->fsBuffer, file->fs->bytesPerSector);

			file->state = FILE_Idle;
			file->subState = 0;
			return FS_SUCCESS;
		} else {
			// Empty entry not found in this block, read next block
			DBG_SPAM_printf("Empty directory table entry not found");

			file->dirTableLBAClusterOffset++;
			file->dirTableLBA++;
			if (file->dirTableLBAClusterOffset == file->fs->sectorsPerCluster) {
				// Todo: implement fat pointer following
				DBG_ERR_printf("Failed: directory table cluster following not implemented");
				file->state = FILE_Uninitialized;
				return FS_FAILED;
			} else {
				DBG_SPAM_printf("Read directory table at LBA 0x%08lx", file->dirTableLBA);
				result = SD_DMA_SingleBlockRead(file->fs->card, file->dirTableLBA, &file->fs->card->DataBlocks[0]);
				if (result == SD_BUSY) {
					return FS_BUSY;
				}
				// Otherwise continue on for another loop...
			}
		}
	}

	// Code should never reach this
	DBG_DATA_printf("Failed: Bad substate 0x%02x", file->subState);
	return SD_FAILED;
}
