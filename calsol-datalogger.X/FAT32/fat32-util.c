/*
 * File:   fat32-util.c
 * Author: Ducky
 *
 * Created on July 28, 2011, 12:35 PM
 *
 * Revision History
 * Date			Author	Change
 * 28 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * Helper funcitons for the FAT32 library. These are all simple calculation
 * functions and do not involve reading from the card.
 */

#include <string.h>

#include "fat32.h"

inline uint16_t FATDataToInt16(uint8_t *data) {
	uint16_t store;
	uint8_t *storeByte = (uint8_t*)&store;

	storeByte[0] = data[0];
	storeByte[1] = data[1];

	return store;
}

inline uint32_t FATDataToInt32(uint8_t *data) {
	uint32_t store;
	uint8_t *storeByte = (uint8_t*)&store;

	storeByte[0] = data[0];
	storeByte[1] = data[1];
	storeByte[2] = data[2];
	storeByte[3] = data[3];

	return store;
}

inline uint32_t FATSplitDataToInt32(uint8_t *dataHigh, uint8_t *dataLow) {
	uint32_t store;
	uint8_t *storeByte = (uint8_t*)&store;

	storeByte[0] = dataLow[0];
	storeByte[1] = dataLow[1];
	storeByte[2] = dataHigh[0];
	storeByte[3] = dataHigh[1];

	return store;
}

inline void Int16ToFATData(uint8_t *dest, uint16_t data) {
	uint8_t *dataByte = (uint8_t*)&data;

	dest[0] = dataByte[0];
	dest[1] = dataByte[1];
}

inline void Int32ToFATData(uint8_t *dest, uint32_t data) {
	uint8_t *dataByte = (uint8_t*)&data;

	dest[0] = dataByte[0];
	dest[1] = dataByte[1];
	dest[2] = dataByte[2];
	dest[3] = dataByte[3];
}

inline void Int32ToFATSplitData(uint8_t *destHigh, uint8_t *destLow, uint32_t data) {
	uint8_t *dataByte = (uint8_t*)&data;

	destLow[0] = dataByte[0];
	destLow[1] = dataByte[1];
	destHigh[0] = dataByte[2];
	destHigh[1] = dataByte[3];
}

inline uint16_t GetClustersPerBlock(FS_FAT32 *fs) {
	return fs->bytesPerSector / fs->clusterPointerSize;
}

inline fs_addr_t GetClusterFATLBA(FS_FAT32 *fs, uint32_t clusterNumber) {
	return fs->FAT_LBA_Begin + (clusterNumber / GetClustersPerBlock(fs));
}

inline uint16_t GetClusterFATOffset(FS_FAT32 *fs, uint32_t clusterNumber) {
	return (clusterNumber % GetClustersPerBlock(fs)) * fs->clusterPointerSize;
}

inline fs_addr_t GetClusterLBA(FS_FAT32 *fs, uint32_t clusterNumber) {
	return fs->Cluster_LBA_Begin + (clusterNumber - 2) * fs->sectorsPerCluster;
}

void FAT32_FillFSInformationSector(FS_FAT32 *fs, uint8_t *data) {
	data[0x00] = 0x52;
	data[0x01] = 0x52;
	data[0x02] = 0x61;
	data[0x03] = 0x41;
	memset(data+0x04, 0, 0x1e4 - 0x04);
	data[0x1e4] = 0x72;
	data[0x1e5] = 0x72;
	data[0x1e6] = 0x41;
	data[0x1e7] = 0x61;
	Int32ToFATData(data + 0x1e8, fs->numFreeClusters);
	Int32ToFATData(data + 0x1ec, fs->mostRecentCluster);
	memset(data+0x1f0, 0, 0x1fe - 0x1f0);
	data[0x1fe] = 0x55;
	data[0x1ff] = 0xaa;
}
