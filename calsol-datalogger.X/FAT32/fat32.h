 /*
 * File:   fat32.h
 * Author: Ducky
 *
 * Created on July 28, 2011, 11:55 AM
 *
 * Revision History
 * Date			Author	Change
 * 29 Jul 2011	Ducky	Initial implementation
 *
 * @file
 * FAT32 file system library.
 */

#ifndef FAT32_H
#define FAT32_H

#include "../types.h"

#include "../SD-SPI-DMA/sd-spi-dma.h"

#define FAT32_CLUSTER_EOC	0x0fffffff		// Last cluster in file

typedef enum {
	FS_UNINITIALIZED,		/// File system not initialized.
	FS_INITIALIZING,		/// File system being initialized in the background.
	FS_INITIALIZED			/// File system initialized and ready for use.
} FS_State;

/**
 * Data structure holding relevant information for a FAT32 directory.
 * When initialized, it should hold all the information necessary to do directory access.
 */
typedef struct {
	fs_addr_t directoryTableBeginCluster;		/// Cluster number of the beginning of the directory table.

	fs_addr_t directoryTableAvailableCluster;	/// Cluster number of the first available entry in the directory table.
	fs_addr_t directoryTableAvailableClusterOffset;	// Cluster offset of the first available entry of the directory table.
	fs_addr_t directoryTableAvailableLBA;		/// LBA of the first available entry in the directory table
} FS_Directory;

/**
 * Data structure holding relevant information for a FAT32 filesystem.
 * When intiailized, it should hold all the information necessary to do file opens, ...
 * Note that the entire file table should NOT be read - data reads are done on demand.
 */
typedef struct {
	// Storage medium
	SD_Card *card;						/// SD Card struct holding this filesystem.

	// State variables
	FS_State State;						/// FS state.
	uint8_t SubState;					/// Sub-state within the fs-state.

	// Filesystem information
	uint16_t bytesPerSector;			/// Bytes in a sector, almost always 512.
	uint8_t sectorsPerCluster;			/// Number of sectors in a cluster.
	uint16_t numberOfReservedSectors;
	uint8_t numberOfFATs;
	uint32_t sectorsPerFAT;
	FS_Directory rootDirectory;
	fs_addr_t FS_info_LBA;				/// LBA of the FS Information Sector.

	uint8_t clusterPointerSize;			/// Size, in bytes, of a cluster pointer (FAT entry).

	fs_addr_t Partition_LBA_Begin;		/// LBA where the partition begins
	fs_addr_t FAT_LBA_Begin;			/// LBA where FAT #1 begins.
	fs_addr_t Cluster_LBA_Begin;		/// LBA where the Clusters (holding files and directories) section begins.

	uint32_t numFreeClusters;			/// Number of free clusters, as indicated by the FS Information Sector.
	uint32_t mostRecentCluster;			/// Most recently allocated cluster, as indicated by the FS Information Sector.
	uint8_t fsInfoDirty;				/// Whether FS Information Sector data has been changed and needs to be committed to disk.
} FS_FAT32;

#define FS_SUCCESS					0x00
#define FS_IDLE						0x01
#define FS_CLOSED					0x10

#define FS_UNREADY					0xe0

#define FS_FAILED					0xf0
#define FS_PHY_ERR					0xf1

#define FS_BUSY						0xff

/**
 * Initializes the FAT32 file system struct.
 * Loads any important information about the file system into the struct.
 * After this function returns successfully, it should be possible to create,
 * read, and find files.
 *
 * @param[in,out] fs Filesystem struct to initialize.
 * @param[in] card SD Card structure.
 * @return Result of the initialize operation
 * @retval FS_SUCCESS Filesystem initialized successfully and is ready to use.
 * @retval FS_PHY_ERR Storage medium access error.
 * @retval FS_FAILED General failure.
 * @retval FS_INIT_UNRECOGNIZED File system on medium unrecognized.
 * @retval FS_INIT_UNSUPPORTED File system on medium recognized but not supported.
 * @retval FS_BUSY Initialize operation is not yet complete and will continue
 * in the background.
 */
fs_result_t FAT32_Initialize(FS_FAT32 *fs, SD_Card *card);
#define FS_INIT_UNRECOGNIZED		0x10	/// Unrecognized file system
#define FS_INIT_UNSUPPORTED			0x11	/// Unsupported file system (like FAT16)

/*
 * Gets the result of the current FAT32 intialize operation in progress.
 *
 * @param[out] fs Filesystem struct to initialize.
 * @return Result of the initialize operation
 * @retval FS_SUCCESS Filesystem initialized successfully and is ready to use.
 * @retval FS_PHY_ERR Storage medium access error.
 * @retval FS_FAILED General failure.
 * @retval FS_INIT_UNRECOGNIZED File system on medium unrecognized.
 * @retval FS_INIT_UNSUPPORTED File system on medium recognized but not supported.
 * @retval FS_BUSY Initialize operation is not yet complete and will continue
 * in the background.
 */
fs_result_t FAT32_GetInitializeResult(FS_FAT32 *fs);

#endif
