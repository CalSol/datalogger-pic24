/*
 * File:   fat32-file.h
 * Author: Ducky
 *
 * Created on July 29, 2011, 7:16 PM
 *
 * Revision History
 * Date			Author	Change
 * 29 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * File operations for the FAT32 filesystem.
 */

#ifndef FAT32_FILE_H
#define FAT32_FILE_H

#include "fat32.h"

typedef enum {
	FILE_Uninitialized,				/// Uninitialized file

	FILE_Creating,					/// File being created

	FILE_Idle,						/// File not doing anything, either do what is mentioned in nextOperation or write data

	FILE_WritingData,				/// Writing data but no blocks currently being sent
	FILE_SendingData,				/// Sending data blocks to the card
	FILE_TerminatingData,			/// Terminating the MBW operation

	FILE_WritingFAT,				/// Writing (updating) the FAT entry
	FILE_WritingFSInformation,		/// Writing (updating) the FS Information sector
	FILE_WritingDirTable,			/// Writing (updating) the FS Information sector

	FILE_Closed,					/// File is closed
} FileState;

#define FS_NUM_DATA_BUFFERS	5
#define FS_SECTOR_SIZE		512
/**
 * Holds data for files specific to optimizing large contigious writes.
 */
typedef struct {
	char name[8];						/// 8.3 file name, limited to 8 characters, note that LFN is not supported.
	char ext[3];						/// 8.3 extension, limited to 3 characters

	uint8_t nameMatchChars;				/// For sequential file naming, this is the number of characters in the prefix.
	uint8_t nameNumDigits;				/// For sequential file naming, this is the length of hex digits post-prefix.

	FS_FAT32 *fs;						/// Filesystem object for this file.

	/* File operation state
	 */
	FileState state;					/// What the file is doing.
	uint8_t subState;					/// File substate.
	uint8_t requestClose;				/// Whether the file should close.

	/* Directory entry variables
	 */
	FS_Directory *dir;					/// Directory this file is in.
	
	uint8_t dirTableBlockData[FS_SECTOR_SIZE];		/// Cache for the directory table block.
	uint32_t dirTableCluster;			/// Cluster of the directory table entry containing this file.
	fs_addr_t dirTableLBA;				/// Block address of the directory table entry containing this file.
	uint8_t dirTableLBAClusterOffset;	/// LBA offset of the directory table block from the beginning of the cluster.
	uint16_t dirTableBlockOffset;		/// Byte offset (from block beginning) of the directory table entry containing this file.
	uint8_t dirTableDirty;				/// Whether the directory table has been changed and needs to be committed to disk.

	/* File allocation table caches
	 * Caching is required in case the last data block needs to be changed
	 * without reading data from the disk.
	 */
	uint8_t currFATDataAlloc[FS_SECTOR_SIZE];		/// This actually allocates the cache.
	uint8_t *currFATData;				/// Cache for the FAT block containing the current position.
	fs_addr_t currFATLBA;				/// Block address of the FAT block containing the current position.
	uint16_t currFATBlockOffset;		/// Byte offset in currFATData containing the last cluster entry of the file.

	uint32_t currFATClusterEnd;			/// Last cluster allocated in currFATData. This will be equal to FAT32_CLUSTER_EOC if the file's FAT has terminated.

	/* File allocation variables
	 */
	uint32_t startCluster;				/// Starting cluster number of the file.
	fs_size_t position;					/// Size of the data committed to disk.
	fs_size_t size;						/// Allocated size of the file, in bytes. This should be consistent with the number of allocated clusters
										/// and should be committed to disk when the clusters are alloated.

	uint32_t currCluster;				/// Cluster number of the cluster containing the current byte position.
	fs_addr_t currLBA;					/// Block number of the next block to be written.
	uint8_t currLBAClusterOffset;		/// Block offset from the beginning of the current cluster.
	
	/* Data buffering variables
	 */
	fs_length_t dataBufferSize;				/// Size, in bytes, of each data buffer. This is storage-medium dependent.
	uint8_t *dataBuffer[FS_NUM_DATA_BUFFERS];	/// Dual DMA buffers holding data to be written to disk.
	uint8_t dataBufferWrite;				/// The next DMA buffer to be written to disk.
	uint8_t dataBufferFill;					/// The data buffer being filled with user data.
	uint8_t dataBufferNumFilled;			/// Number of completely filled data buffers.
	uint16_t dataBufferPos;					/// Next byte in the data buffer that is to be filled with user data.

	uint8_t *fsBuffer;						/// DMA buffer holding filesystem information to be written to disk.
} FS_File;

/**
 * Creates and opens a file. This allocates a block for the file in FAT
 * (updating the FS information sector in the process), and writes the directory
 * table entry.
 * After the file creation operation is complete, the file may be written.
 *
 * @param fs[in] FAT32 filesystem in which to write the file.
 * @param dir[in] Directory in which to write the file.
 * @param file[in,out] File struct which will be used for this file.
 * @param name[in] File name, in 8.3 format.
 * @param ext[in] File extension, in 8.3 format.
 * @return Status of the operation.
 * @retval FS_SUCCESS Operation complete, file is ready for writing.
 * @retval FS_BUSY Operation in progress, continuing in the background.
 * @retval FS_PHY_ERR Storage medium access error.
 * @retval FS_FAILED General failure.
 */
fs_result_t FS_CreateFile(FS_FAT32 *fs, FS_Directory *dir, FS_File *file, char *name, char *ext);

/**
 * Creates and opens a file. This allocates a block for the file in FAT
 * (updating the FS information sector in the process), and writes the directory
 * table entry.
 * After the file creation operation is complete, the file may be written.
 * This also allocates sequential file names, that is, if a file with a matching
 * prefix already exists, then it creates a file name which has the postfix
 * hex-incremented by one of the largest existing matching file.
 *
 * @param fs[in] FAT32 filesystem in which to write the file.
 * @param dir[in] Directory in which to write the file.
 * @param file[in,out] File struct which will be used for this file.
 * @param name[in] File name, in 8.3 format.
 * @param ext[in] File extension, in 8.3 format.
 * @param prefixLength[in] Length of the name prefix.
 * @param prefixLength[in] Number of hex digits following the prefix.
 * @return Status of the operation.
 * @retval FS_SUCCESS Operation complete, file is ready for writing.
 * @retval FS_BUSY Operation in progress, continuing in the background.
 * @retval FS_PHY_ERR Storage medium access error.
 * @retval FS_FAILED General failure.
 */
fs_result_t FS_CreateFileSeqName(FS_FAT32 *fs, FS_Directory *dir, FS_File *file,
		char *name, char *ext, uint8_t prefixLength, uint8_t digitLength);

/**
 * Gets the result of the current file creation operation in progress.
 * This should be called periodically until success is returned.
 *
 * @param file File being created.
 * @return Status of the operation.
 * @retval FS_SUCCESS Operation complete, file is ready for writing.
 * @retval FS_BUSY Operation in progress, continuing in the background.
 * @retval FS_PHY_ERR Storage medium access error.
 * @retval FS_FAILED General failure.
 */
fs_result_t FS_GetCreateFileResult(FS_File *file);

/**
 * Writes data to a file.
 * More correctly, this buffers data and initializes a write operation only
 * when a whole block of data is ready.
 *
 * @param file File to write to.
 * @param data Data to write.
 * @param dataLen Length of the data, in bytes, to write.
 * @return Number of bytes written. If this is equal to /a dataLen, then all the
 * data will be written to disk. If this is equal to 0, then none of the data
 * will be written to disk - the buffers are currently full. If this is
 * something in between, then some of the data will be written to disk, and
 * the buffers are now full.
 */
fs_length_t FS_WriteFile(FS_File *file, uint8_t *data, fs_length_t dataLen);

/**
 * This should be periodically called on a file being written. This handles
 * tasks like sending blocks to the storage medium.
 *
 * @return Status.
 * @retval FS_IDLE File is idle, no blocks are being sent to the storage medium
 * because not enough data is available for a write yet.
 * @retval FS_BUSY File is busy.
 * @retval FS_PHY_ERR Storage medium access error. File may be corrupt.
 * @retval FS_CLOSED File closed.
 * @retval FS_FAILED General failure.
 */
fs_result_t FS_FileTasks(FS_File *file);

/**
 * Requests that a file be closed.
 *
 * @param file File to close.
 */
void FS_RequestFileClose(FS_File *file);

#endif
