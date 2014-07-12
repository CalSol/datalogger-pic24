/*
 * File:   fat32-util.h
 * Author: Ducky
 *
 * Created on July 28, 2011, 11:56 AM
 *
 * Revision History
 * Date			Author	Change
 * 28 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * Helper funcitons for the FAT32 library. These are all simple calculation
 * functions and do not involve reading from the card.
 */

#ifndef FAT32_UTIL_H
#define FAT32_UTIL_H

#include "../types.h"

#include "fat32.h"

/**
 * Converts a 2-byte piece of data from the FAT boot sector into a 16-bit
 * integer.
 *
 * @param[in] data Data source, 2 bytes long starting at this pointer.
 */
inline uint16_t FATDataToInt16(uint8_t *data);

/**
 * Converts a 4-byte piece of data from the FAT boot sector into a 32-bit
 * integer.
 * @param[in] data Data source, 4 bytes long starting at this pointer.
 */
inline uint32_t FATDataToInt32(uint8_t *data);

/**
 * Converts a non-contiguous 4-byte piece of data from the FAT boot sector
 * into a 32-bit integer.
 *
 * @param[in] dataHigh High 2 bytes of data source.
 * @param[in] dataLow Low 2 bytes of data source.
 */
inline uint32_t FATSplitDataToInt32(uint8_t *dataHigh, uint8_t *dataLow);

/**
 * Converts a 16-bit integer to a 2-byte little-endian format data for FAT.
 *
 * @param[out] dest Data destination.
 * @param[in] data 16-bit integer to covert.
 */
inline void Int16ToFATData(uint8_t *dest, uint16_t data);

/**
 * Converts a 32-bit integer to a 4-byte little-endian format data for FAT.
 *
 * @param[out] dest Data destination, 4 bytes long starting at this pointer.
 * @param[in] data 32-bit integer to covert.
 */
inline void Int32ToFATData(uint8_t *dest, uint32_t data);

/**
 * Converts a 32-bit integer to a non-contiguous 4-byte little-endian format
 * data for FAT.
 *
 * @param[out] destHigh High part 2 bytes of the data destination.
 * @param[out] destLow Low part 2 bytes of the data destination.
 * @param[in] data 32-bit integer to covert.
 */
inline void Int32ToFATSplitData(uint8_t *destHigh, uint8_t *destLow, uint32_t data);

/**
 * @return The LBA (block address) of the block of the FAT containing the
 * cluster pointer.
 */
inline fs_addr_t GetClusterFATLBA(FS_FAT32 *fs, uint32_t clusterNumber);

/**
 * @return The byte offset from the block beginning containing the cluster
 * number in the FAT.
 */
inline uint16_t GetClusterFATOffset(FS_FAT32 *fs, uint32_t clusterNumber);

/**
 * @return The LBA (block address) of the first block of cluster.
 */
inline fs_addr_t GetClusterLBA(FS_FAT32 *fs, uint32_t clusterNumber);

/**
 * @return The number of cluster pointers in a single block.
 */
inline uint16_t GetClustersPerBlock(FS_FAT32 *fs);

/**
 * Writes the updated FAT32 FS Information Sector to a buffer in memory.
 * The data is generated from the information stored in the filesystem struct.
 *
 * @param file File.
 * @param data The location in memory to write it to.
 */
void FAT32_FillFSInformationSector(FS_FAT32 *fs, uint8_t *data);

#endif
