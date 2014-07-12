/*
 * File:   fat32-init.c
 * Author: Ducky
 *
 * Created on July 29, 2011, 2:23 AM
 *
 * Revision History
 * Date			Author	Change
 * 29 Jul 2011	Ducky	Initial implementation.
 *
 * Todo
 * 29 Jul 2011	Ducky	Consider refactoring.
 *
 * @file
 * FAT32 file system initialization subroutine.
 */

#include "fat32.h"
#include "fat32-util.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#define DBG_MODULE "FAT32/Init"
#include "../debug-common.h"
#include "../debug-log.h"

#define FS_INIT_SUB_BEGIN			0
#define FS_INIT_SUB_READSEC0		1	/// Reading sector 0
#define FS_INIT_SUB_READBOOTSEC		2	/// Reading boot sector (if it isn't sector 0)
#define FS_INIT_SUB_READINFOSEC		3	/// Reading FS Information Sector

#define SEC0_MBR		0
#define SEC0_BOOTSEC	1
/**
 * Returns the type of record in sector 0.
 * @param[in] data Contents of Sector 0.
 * @return Type of record contained in sector 0.
 * @retval SEC0_MBR Master Boot Record
 * @retval SEC0_BOOTSEC Boot sector (Volume ID)
 */
uint8_t FAT32_GetSector0Type(uint8_t *data) {
	if (!((data[0] == 0xEB && data[2] == 0x90) || data[0] == 0xE9)) {
		DBG_DATA_printf("Sector 0 is MBR (invalid jump instructions)");
		return SEC0_MBR;
	} else if (!((data[13] != 0) && ((data[13] & (~data[13] + 1)) == data[13]))) {
		DBG_DATA_printf("Sector 0 is MBR (sectors per cluster cannot be a non-power of 2)");
		return SEC0_MBR;
	} else if (data[16] != 2) {
		if (data[16] == 0) {
			DBG_DATA_printf("Sector 0 is MBR (number of FATs cannot be 0)");
			return SEC0_MBR;
		} else {
			DBG_printf("Warning: Number of FATs not 2");
			DBG_DATA_printf("Sector 0 is FAT Boot Table");
			return SEC0_BOOTSEC;
		}
	} else {
		DBG_DATA_printf("Sector 0 is FAT Boot Table");
		return SEC0_BOOTSEC;
	}
}

/**
 * Parses the filesystem data in the master boot record.
 *
 * @param fs Filesystem struct.
 * @param data Contents of the Master Boot Record.
 * @return Result.
 * @retval FS_SUCCESS Data successfully parsed and loaded.
 * @retval FS_FAILED Error occured while parsing.
 */
fs_result_t FAT32_ParseMBR(FS_FAT32 *fs, uint8_t *data) {
	// Check boot record signature
	if (data[510] != 0x55 || data[511] != 0xaa) {
		DBG_DATA_printf("MBR has invalid signature, got 0x%02x%02x", data[510], data[511]);
		return FS_FAILED;
	}
	
	fs->Partition_LBA_Begin = FATDataToInt32(data+446+8);

	DBG_DATA_printf("FAT Boot Sector LBA = 0x%08lx", fs->Partition_LBA_Begin);

	return FS_SUCCESS;
}

/**
 * Parses the filesystem data in the FAT boot sector.
 *
 * @param fs Filesystem struct.
 * @param data Contents of the FAT boot sector.
 * @return Result.
 * @retval FS_SUCCESS Data successfully parsed and loaded.
 * @retval FS_FAILED Error occured while parsing.
 */
fs_result_t FAT32_ParseBootSector(FS_FAT32 *fs, uint8_t *data) {
	// Check boot record signature
	if (data[510] != 0x55 || data[511] != 0xaa) {
		DBG_DATA_printf("FAT boot sector has invalid signature, got 0x%02x%02x", data[510], data[511]);
		return FS_FAILED;
	}

	if (data[0x42] == 0x29 && (data[0x40] == 0x00 || data[0x40] == 0x80)) {
		DBG_DATA_printf("Detected FAT32 filesystem");
		fs->clusterPointerSize = 4;
	} else if (data[0x26] == 0x29 && (data[0x24] == 0x00 || data[0x24] == 0x80)) {
		DBG_ERR_printf("Unsupported filesystem: Detected FAT12/16 filesystem");
		return FS_FAILED;
	} else {
		DBG_ERR_printf("Unsupported filesystem");
		return FS_FAILED;
	}

	fs->bytesPerSector = data[11] + ((uint16_t)data[12] << 8);

	if (fs->bytesPerSector != 512) {
		DBG_DATA_printf("Bytes per sector is not 512.");
		return FS_FAILED;
	}

	fs->sectorsPerCluster = data[13];
	fs->numberOfReservedSectors = FATDataToInt16(data+14);
	fs->numberOfFATs = data[16];

	fs->sectorsPerFAT = FATDataToInt32(data+36);
	fs->rootDirectory.directoryTableBeginCluster = FATDataToInt32(data+44);
	fs->FS_info_LBA = FATDataToInt16(data+0x30) + fs->Partition_LBA_Begin;

	fs->FAT_LBA_Begin = fs->Partition_LBA_Begin + fs->numberOfReservedSectors;
	fs->Cluster_LBA_Begin = fs->FAT_LBA_Begin + fs->numberOfFATs * fs->sectorsPerFAT;

	fs->rootDirectory.directoryTableAvailableCluster = fs->rootDirectory.directoryTableBeginCluster;
	fs->rootDirectory.directoryTableAvailableLBA = GetClusterLBA(fs, fs->rootDirectory.directoryTableAvailableCluster);
	fs->rootDirectory.directoryTableAvailableClusterOffset = 0;

	DBG_DATA_printf("Bytes Per Sector = %u, Sectors Per Cluster = %u", fs->bytesPerSector, fs->sectorsPerCluster);
	DBG_DATA_printf("Number of Reserved Sectors = %u", fs->numberOfReservedSectors);
	DBG_DATA_printf("Number of FATs = %u, Sectors Per FAT = %lu", fs->numberOfFATs, fs->sectorsPerFAT);
	DBG_DATA_printf("Root Cluster Number = 0x%08lx", fs->rootDirectory.directoryTableBeginCluster);

	DBG_DATA_printf("Partition LBA = 0x%08lx, FAT LBA = 0x%08lx, Cluster LBA = 0x%08lx",
			fs->Partition_LBA_Begin, fs->FAT_LBA_Begin, fs->Cluster_LBA_Begin)

	return FS_SUCCESS;
}

/**
 * Parses the filesystem data in the FS Information sector.
 *
 * @param fs Filesystem struct.
 * @param data Contents of the FS Information sector.
 * @return Result.
 * @retval FS_SUCCESS Data successfully parsed and loaded.
 * @retval FS_FAILED Error occured while parsing.
 */
fs_result_t FAT32_ParseFSInfoSector(FS_FAT32 *fs, uint8_t *data) {
	// Check for information sector signatures
	if (data[0x00] != 'R' || data[0x01] != 'R' || data[0x02] != 'a' || data[0x03] != 'A'
			|| data[0x1e4] != 'r' || data[0x1e5] != 'r' || data[0x1e6] != 'A' || data[0x1e7] != 'a'
			|| data[0x1fe] != 0x55 || data[0x1ff] != 0xAA) {
		DBG_ERR_printf("FS Information Sector has invalid signature, got %02x %02x %02x %02x, %02x %02x %02x %02x, %02x %02x",
				data[0x00], data[0x01], data[0x02], data[0x03],
				data[0x1e4], data[0x1e5], data[0x1e6], data[0x1e7],
				data[0x1fe], data[0x1ff]);
		return FS_FAILED;
	}

	// Parse FS Information Sector
	fs->numFreeClusters = FATDataToInt32(data+0x1e8);
	fs->mostRecentCluster = FATDataToInt32(data+0x1ec);

	DBG_DATA_printf("Number of Free Clusters = %lu", fs->numFreeClusters);
	DBG_DATA_printf("Most Recently Allocated Cluster = 0x%08lx", fs->mostRecentCluster);

	return FS_SUCCESS;
}

fs_result_t FAT32_Initialize(FS_FAT32 *fs, SD_Card *card) {
	fs->State = FS_INITIALIZING;
	fs->card = card;

	fs->SubState = FS_INIT_SUB_BEGIN;

	return FAT32_GetInitializeResult(fs);
}

fs_result_t FAT32_GetInitializeResult(FS_FAT32 *fs) {
	uint8_t result = SD_BUSY;
	
	if (fs->State != FS_INITIALIZING) {
		DBG_ERR_printf("Failed: FS not in Initializing state")
		return FS_FAILED;
	}
	
	if (fs->SubState == FS_INIT_SUB_BEGIN) {
		// Begin reading sector 0
		DBG_DATA_printf("Read sector 0");
		fs->SubState = FS_INIT_SUB_READSEC0;
		result = SD_DMA_SingleBlockRead(fs->card, 0, &fs->card->DataBlocks[0]);
		if (result == SD_BUSY) {
			return FS_BUSY;
		}
	}

	if (fs->SubState == FS_INIT_SUB_READSEC0) {
		if (result == SD_BUSY) {
			result = SD_DMA_GetSingleBlockReadResult(fs->card);
		}
		if (result == SD_BUSY) {
			return FS_BUSY;
		} else if (result != SD_SUCCESS) {
			DBG_ERR_printf("Failed: Error reading sector 0, got result 0x%02x", result);
			fs->State = FS_UNINITIALIZED;
			return FS_PHY_ERR;
		}

		// Parse sector 0
		if (FAT32_GetSector0Type(fs->card->DataBlocks[0].Data + 2) == SEC0_MBR) {
			DBG_DATA_printf("Detected sector 0 to be Master Boot Record");
			if (FAT32_ParseMBR(fs, fs->card->DataBlocks[0].Data + 2) != FS_SUCCESS) {
				DBG_DATA_printf("Failed: Error parsing MBR");
				fs->State = FS_UNINITIALIZED;
				return FS_INIT_UNRECOGNIZED;
			}

			// Read boot sector
			DBG_DATA_printf("Read boot sector at LBA 0x%08lx", fs->Partition_LBA_Begin);
			fs->SubState = FS_INIT_SUB_READBOOTSEC;
			result = SD_DMA_SingleBlockRead(fs->card, fs->Partition_LBA_Begin, &fs->card->DataBlocks[0]);
			if (result == SD_BUSY) {
				return FS_BUSY;
			}
		} else {
			DBG_DATA_printf("Detected sector 0 to be FAT Boot Sector (Volume ID)");
			fs->Partition_LBA_Begin = 0;
			
			// Fall through and continue to parsing boot sector
			fs->SubState = FS_INIT_SUB_READBOOTSEC;
		}
	}
	
	if (fs->SubState == FS_INIT_SUB_READBOOTSEC) {
		if (result == SD_BUSY) {
			result = SD_DMA_GetSingleBlockReadResult(fs->card);
		}
		if (result == SD_BUSY) {
			return FS_BUSY;
		} else if (result != SD_SUCCESS) {
			DBG_ERR_printf("Failed: Error reading boot sector, got result 0x%02x", result);
			fs->State = FS_UNINITIALIZED;
			return FS_PHY_ERR;
		}

		if (FAT32_ParseBootSector(fs, fs->card->DataBlocks[0].Data + 2) != FS_SUCCESS) {
			DBG_DATA_printf("Failed: Error parsing MBR");
			fs->State = FS_UNINITIALIZED;
			return FS_INIT_UNRECOGNIZED;
		}

		// Read FS information sector
		DBG_DATA_printf("Read FS information sector at LBA 0x%08lx", fs->FS_info_LBA);
		fs->SubState = FS_INIT_SUB_READINFOSEC;
		result = SD_DMA_SingleBlockRead(fs->card, fs->FS_info_LBA, &fs->card->DataBlocks[0]);
		if (result == SD_BUSY) {
			return FS_BUSY;
		}
	}

	if (fs->SubState == FS_INIT_SUB_READINFOSEC) {
		if (result == SD_BUSY) {
			result = SD_DMA_GetSingleBlockReadResult(fs->card);
		}
		if (result == SD_BUSY) {
			return FS_BUSY;
		} else if (result != SD_SUCCESS) {
			DBG_ERR_printf("Failed: Error reading FS information sector");

			fs->State = FS_UNINITIALIZED;
			return FS_PHY_ERR;
		}

		if (FAT32_ParseFSInfoSector(fs, fs->card->DataBlocks[0].Data + 2) != FS_SUCCESS) {
			DBG_DATA_printf("Failed: Error parsing FS information sector, got result 0x%02x", result);
			fs->State = FS_UNINITIALIZED;
			return FS_INIT_UNRECOGNIZED;
		}

		fs->State = FS_INITIALIZED;
		return FS_SUCCESS;
	}

	// Code should never reach this
	DBG_DATA_printf("Failed: Bad substate 0x%02x", fs->SubState);
	return FS_FAILED;
}
