/*
 * File:   fat32-file-tasks.c
 * Author: Ducky
 *
 * Created on August 7, 2011, 3:57 PM
 *
 * Revision History
 * Date			Author	Change
 * 07 Arg 2011	Ducky	Initial implementation.
 *
 * @file
 * File background tasks.
 */

#include <string.h>

#include "fat32-util.h"
#include "fat32-file.h"
#include "fat32-file-util.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "File/Tasks"
#include "../debug-common.h"
#include "../debug-log.h"

fs_result_t FS_File_ProcessIdle(FS_File *file);
fs_result_t FS_File_ProcessWritingData(FS_File *file);
fs_result_t FS_File_ProcessSendingData(FS_File *file);
fs_result_t FS_File_ProcessTerminatingData(FS_File *file);
fs_result_t FS_File_ProcessWritingFAT(FS_File *file);
fs_result_t FS_File_ProcessWritingFSInformation(FS_File *file);
fs_result_t FS_File_ProcessWritingDirTable(FS_File *file);

/**
 * Goes to a state and processes the functions for that state.
 *
 * @param file File.
 * @param state State to change to.
 * @param stateProcessor The function which processes the target state.
 * @return The result of the processing of the target state.
 */
inline fs_result_t FS_File_GotoState(FS_File *file, FileState state, fs_result_t(*stateProcessor)(FS_File*)) {
	file->state = state;
	file->subState = 0;
	return (*stateProcessor)(file);
}

/**
 * Goes to a state without processing the functions for that state.
 * Useful for changing states during errors, so that an error code is returned
 * rather than the output of that process.
 *
 * @param file File.
 * @param state State to change to.
 * @param stateProcessor The function which processes the target state.
 */
inline void FS_File_GotoStateNoInvoke(FS_File *file, FileState state, fs_result_t(*stateProcessor)(FS_File*)) {
	file->state = state;
	file->subState = 0;
}

/**
 * Tasks in the Idle state - mostly involving going to a state which actually
 * does something.
 *
 * @pre /a file is in the FILE_WritingData state.
 * @param file File.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessIdle(FS_File *file) {
	if ((file->currCluster > file->currFATClusterEnd)
			|| (file->requestClose && (file->currFATClusterEnd != FAT32_CLUSTER_EOC))) {
		if (file->currCluster > file->currFATClusterEnd) {
			DBG_SPAM_printf("Idle -> WriteFAT: exceeding allocated cluster");
		}
		if (file->requestClose && (file->currFATClusterEnd != FAT32_CLUSTER_EOC)) {
			DBG_SPAM_printf("Idle -> WriteFAT: termination");
		}
		return FS_File_GotoState(file, FILE_WritingFAT, &FS_File_ProcessWritingFAT);
	} else if (file->fs->fsInfoDirty) {
		DBG_SPAM_printf("Idle -> WritingFSInformation");
		return FS_File_GotoState(file, FILE_WritingFSInformation, &FS_File_ProcessWritingFSInformation);
	} else if (file->dirTableDirty) {
		DBG_SPAM_printf("Idle -> WritingDirTable");
		return FS_File_GotoState(file, FILE_WritingDirTable, &FS_File_ProcessWritingDirTable);
	} else if (!file->requestClose || file->dataBufferNumFilled > 0) {
		DBG_SPAM_printf("Idle -> WritingData");
		return FS_File_GotoState(file, FILE_WritingData, &FS_File_ProcessWritingData);
	} else if (file->requestClose) {
		DBG_SPAM_printf("Idle -> Closed");
		file->state = FILE_Closed;
		return FS_CLOSED;
	} else {
		return FS_IDLE;
	}

}

/**
 * Periodically called when in the writing data state.
 * This starts sending data blocks (when available) to the card, and terminates
 * the operation when the allocated block limits have been reached in order to
 * allocate a new block.
 *
 * @pre /a file is in the FILE_WritingData state.
 * @param file File.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessWritingData(FS_File *file) {
	if (file->state != FILE_WritingData) {
		DBG_ERR_printf("File operation failed: file not in the WritingData state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	uint8_t sdresult;

	if (file->subState == 0) {
		DBG_SPAM_printf("Beginning data write at LBA %lu", file->currLBA);
		sdresult = SD_DMA_MBW_Begin(file->fs->card, file->currLBA);
		if (sdresult == SD_SUCCESS) {
			file->subState = 1;
		} else {
			DBG_ERR_printf("File operation failed: SD operation error, returned 0x%02x", sdresult);
			FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
			return FS_PHY_ERR;
		}
	}

	// Check if allocation exceeded
	if (file->currCluster > file->currFATClusterEnd) {
		DBG_SPAM_printf("WritingData -> TerminatingData (allocation exceeded)");
		return FS_File_GotoState(file, FILE_TerminatingData, &FS_File_ProcessTerminatingData);
	}
	// Check if there are blocks ready to be sent
	if (file->dataBufferNumFilled > 0) {
		DBG_SPAM_printf("WritingData -> SendingData");
		return FS_File_GotoState(file, FILE_SendingData, &FS_File_ProcessSendingData);
	}
	// Check is file is requesting cloes
	if (file->requestClose) {
		if (file->dataBufferPos > 0) {
			DBG_SPAM_printf("WritingData -> SendingData (partial block, request close)");
			// Send last block - and zero the rest of the block
			memset(file->dataBuffer[file->dataBufferWrite]+file->dataBufferPos,
					0, file->fs->bytesPerSector - file->dataBufferPos);
			DBG_SPAM_printf("Block remainder zeroed");
			return FS_File_GotoState(file, FILE_SendingData, &FS_File_ProcessSendingData);
		} else {
			DBG_SPAM_printf("WritingData -> TerminatingData (request close)");
			return FS_File_GotoState(file, FILE_TerminatingData, &FS_File_ProcessTerminatingData);
		}
	}
	// Otherwise, we're idle
	return FS_IDLE;
}

/**
 * Periodically called when sending a data block to the storage medium.
 *
 * @pre /a file is in the FILE_SendingData state.
 * @param file File.
 * @param sdresult Result of the SD Card operation relevant to this function.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessSendingData(FS_File *file) {
	if (file->state != FILE_SendingData) {
		DBG_ERR_printf("File operation failed: file not in the SendingData state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	sd_result_t sdresult;

	if (file->subState == 0) {
		DBG_SPAM_printf("Beginning send block at LBA %lu", file->currLBA);
		sdresult = SD_DMA_MBW_SendBlock(file->fs->card, &file->fs->card->DataBlocks[file->dataBufferWrite + 1]);
		file->subState = 1;
	} else {
		sdresult = SD_DMA_MBW_GetSendBlockResult(file->fs->card);
	}

	if (sdresult == SD_BUSY) {
		return FS_BUSY;
	} else if (sdresult == SD_SUCCESS) {
		DBG_SPAM_printf("Block sent");

		if (file->requestClose && file->dataBufferNumFilled == 0) {
			file->position += file->dataBufferPos;
			file->dataBufferPos = 0;
		} else {
			file->position += file->dataBufferSize;
			file->dataBufferNumFilled--;
		}

		file->dataBufferWrite++;
		if (file->dataBufferWrite >= FS_NUM_DATA_BUFFERS) {
			file->dataBufferWrite = 0;
		}

		file->currLBA++;
		file->currLBAClusterOffset++;
		if (file->currLBAClusterOffset >= file->fs->sectorsPerCluster) {
			file->currLBAClusterOffset = 0;
			file->currCluster++;
		}

		DBG_SPAM_printf("SendingData -> WritingData");

		file->state = FILE_WritingData;
		file->subState = 1;
		return FS_File_ProcessWritingData(file);
	} else {
		DBG_ERR_printf("Block send failed: LBA %lu, unexpected result from card: 0x%02x", file->currLBA, sdresult);
		FS_File_GotoStateNoInvoke(file, FILE_TerminatingData, &FS_File_ProcessTerminatingData);;
		return FS_PHY_ERR;
	}
}

/**
 * Periodically called when terminating a data write operation
 *
 * @pre /a file is in the FILE_TerminatingData state.
 * @param file File.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessTerminatingData(FS_File *file) {
	if (file->state != FILE_TerminatingData) {
		DBG_ERR_printf("File operation failed: file not in the TerminatingData state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	sd_result_t sdresult;

	if (file->subState == 0) {
		sdresult = SD_DMA_MBW_Terminate(file->fs->card);
		file->subState = 1;
	} else {
		sdresult = SD_DMA_MBW_GetTerminateStatus(file->fs->card);
	}

	if (sdresult == SD_BUSY) {
		return FS_BUSY;
	} else if (sdresult == SD_SUCCESS) {
		DBG_SPAM_printf("Terminate data write");
		return FS_File_GotoState(file, FILE_Idle, &FS_File_ProcessIdle);
	} else {
		DBG_ERR_printf("Data write terminate failed: unexpected result from card: 0x%02x", sdresult);
		FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
		return FS_PHY_ERR;
	}
}

/**
 * Periodically called when writing the FAT to the storage medium.
 *
 * @pre /a file is in the FILE_WritingFAT state.
 * @param file File.
 * @param sdresult Result of the SD Card operation relevant to this function.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessWritingFAT(FS_File *file) {
	if (file->state != FILE_WritingFAT) {
		DBG_ERR_printf("File operation failed: file not in the WritingFAT state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	sd_result_t sdresult;

	if (file->subState == 0) {
		if (file->requestClose && file->dataBufferNumFilled == 0 && file->dataBufferPos == 0) {
			// Write termination block
			DBG_SPAM_printf("Write termination block");
			FAT32_TerminateFATBlock(file, file->currFATData);
			memcpy(file->fsBuffer, file->currFATData, file->fs->bytesPerSector);
			file->subState = 2;
		} else if (file->currFATLBA == GetClusterFATLBA(file->fs, file->currCluster)) {
			// Access FAT from cache, if it's there
			DBG_SPAM_printf("Allocate FAT Block from cache");
			FAT32_AllocateFATBlock(file, file->currFATData);
			memcpy(file->fsBuffer, file->currFATData, file->fs->bytesPerSector);
			file->subState = 2;
		}
	}
	if (file->subState == 0 || file->subState == 1) {
		if (file->subState == 0) {
			// Read FAT from disk otherwise
			DBG_SPAM_printf("Read FAT");
			sdresult = SD_DMA_SingleBlockRead(file->fs->card,
					GetClusterFATLBA(file->fs, file->currCluster), &file->fs->card->DataBlocks[0]);
			file->subState = 1;
		} else {
			sdresult = SD_DMA_GetSingleBlockReadResult(file->fs->card);
		}

		if (sdresult == SD_BUSY) {
			return FS_BUSY;
		} else if (sdresult == SD_SUCCESS) {
			DBG_SPAM_printf("Allocate FAT Block");
			FAT32_AllocateFATBlock(file, file->fsBuffer);
			memcpy(file->currFATData, file->fsBuffer, file->fs->bytesPerSector);
			file->subState = 2;
		} else {
			DBG_ERR_printf("Read FAT: unexpected result from card: 0x%02x", sdresult);
			FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
			return FS_PHY_ERR;
		}
	}
	if (file->subState == 2 || file->subState == 3) {
		if (file->subState == 2) {
			DBG_SPAM_printf("Write FAT at LBA %lu", file->currFATLBA);
			sdresult = SD_DMA_SingleBlockWrite(file->fs->card,
					file->currFATLBA, &file->fs->card->DataBlocks[0]);
			file->subState = 3;
		} else {
			sdresult = SD_DMA_GetSingleBlockWriteResult(file->fs->card);
		}
		
		if (sdresult == SD_BUSY) {
			return FS_BUSY;
		} else if (sdresult == SD_SUCCESS) {
			if (file->startCluster == 0x0000) {
				file->startCluster = file->currCluster;
				FAT32_WriteDirectoryTableEntry(file, file->dirTableBlockData);
				file->dirTableDirty = 1;
			}
			if (file->currFATClusterEnd == FAT32_CLUSTER_EOC) {
				FAT32_UpdateDirectoryTableEntry(file, file->dirTableBlockData);
				file->dirTableDirty = 1;				
			}

			DBG_SPAM_printf("WritingFAT -> Idle");
			return FS_File_GotoState(file, FILE_Idle, &FS_File_ProcessIdle);
		} else {
			DBG_ERR_printf("Write FAT: LBA %lu, unexpected result from card: 0x%02x", file->currFATLBA, sdresult);
			FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
			return FS_PHY_ERR;
		}
	}
	
	DBG_ERR_printf("Write FAT: unexpected substate: 0x%02x", file->subState);
	return FS_FAILED;
}

/**
 * Periodically called when writing the FS Information Sector to the storage
 * medium.
 *
 * @pre /a file is in the FILE_WritingFSInformation state.
 * @param file File.
 * @param sdresult Result of the SD Card operation relevant to this function.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessWritingFSInformation(FS_File *file) {
	if (file->state != FILE_WritingFSInformation) {
		DBG_ERR_printf("File operation failed: file not in the WritingFSInformation state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	sd_result_t sdresult;

	if (file->subState == 0) {
		DBG_SPAM_printf("Write FS Information");
		FAT32_FillFSInformationSector(file->fs, file->fsBuffer);
		sdresult = SD_DMA_SingleBlockWrite(file->fs->card,
			file->fs->FS_info_LBA, &file->fs->card->DataBlocks[0]);
		file->subState = 1;
	} else {
		sdresult = SD_DMA_GetSingleBlockWriteResult(file->fs->card);
	}

	if (sdresult == SD_BUSY) {
		return FS_BUSY;
	} else if (sdresult == SD_SUCCESS) {
		file->fs->fsInfoDirty = 0;
		DBG_SPAM_printf("WritingFSInformation -> Idle");
		return FS_File_GotoState(file, FILE_Idle, &FS_File_ProcessIdle);
	} else {
		DBG_ERR_printf("Write FS Information: LBA %lu, unexpected result from card: 0x%02x", file->fs->FS_info_LBA, sdresult);
		FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
		return FS_PHY_ERR;
	}
}

/**
 * Periodically called when writing the Directory Table to the storage
 * medium.
 *
 * @pre /a file is in the FILE_WritingDirTable state.
 * @param file File.
 * @param sdresult Result of the SD Card operation relevant to this function.
 * @return Result of the operation.
 */
fs_result_t FS_File_ProcessWritingDirTable(FS_File *file) {
	if (file->state != FILE_WritingDirTable) {
		DBG_ERR_printf("File operation failed: file not in the WritingDirTable state, state is 0x%02x", file->state);
		return FS_FAILED;
	}
	sd_result_t sdresult;

	if (file->subState == 0) {
		DBG_SPAM_printf("Write Directory Table");
		FAT32_UpdateDirectoryTableEntry(file, file->dirTableBlockData);
		memcpy(file->fsBuffer, file->dirTableBlockData, file->fs->bytesPerSector);
		sdresult = SD_DMA_SingleBlockWrite(file->fs->card,
			file->dirTableLBA, &file->fs->card->DataBlocks[0]);
		file->subState = 1;
	} else {
		sdresult = SD_DMA_GetSingleBlockWriteResult(file->fs->card);
	}

	if (sdresult == SD_BUSY) {
		return FS_BUSY;
	} else if (sdresult == SD_SUCCESS) {
		file->dirTableDirty = 0;
		DBG_SPAM_printf("WritingDirTable -> Idle");
		return FS_File_GotoState(file, FILE_Idle, &FS_File_ProcessIdle);
	} else {
		DBG_ERR_printf("Write Directory Table: LBA %lu, unexpected result from card: 0x%02x", file->dirTableLBA, sdresult);
		FS_File_GotoStateNoInvoke(file, FILE_Idle, &FS_File_ProcessIdle);
		return FS_PHY_ERR;
	}
}

fs_result_t FS_FileTasks(FS_File *file) {
	if (file->state == FILE_Idle) {
		return FS_File_ProcessIdle(file);
	} else if (file->state == FILE_WritingData) {
		return FS_File_ProcessWritingData(file);
	} else if (file->state == FILE_SendingData) {
		return FS_File_ProcessSendingData(file);
	} else if (file->state == FILE_TerminatingData) {
		return FS_File_ProcessTerminatingData(file);
	} else if (file->state == FILE_WritingFAT) {
		return FS_File_ProcessWritingFAT(file);
	} else if (file->state == FILE_WritingFSInformation) {
		return FS_File_ProcessWritingFSInformation(file);
	} else if (file->state == FILE_WritingDirTable) {
		return FS_File_ProcessWritingDirTable(file);
	} else if (file->state == FILE_Closed) {
		return FS_CLOSED;
	} else {
		// Code should never reach this
		DBG_ERR_printf("Failed: Bad state 0x%02x", file->state);
		return FS_FAILED;
	}
}

void FS_RequestFileClose(FS_File *file) {
	file->requestClose = 1;
}
