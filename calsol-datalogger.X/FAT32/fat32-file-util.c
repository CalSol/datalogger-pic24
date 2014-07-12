/*
 * File:   fat32-file-util.c
 * Author: Ducky
 *
 * Created on July 30, 2011, 9:17 AM
 *
 * Revision History
 * Date			Author	Change
 * 30 Jul 2011	Ducky	Initial implementation.
 * 08 Aug 2011	Ducky	Removed the special beginning FAT allocation function.
 *
 * @file
 * Utility functions for optimized FAT32 file operations.
 */

#include <string.h>
#include <ctype.h>

#include "fat32-file.h"
#include "fat32-util.h"

void FAT32_WriteDirectoryTableEntry(FS_File *file, uint8_t *data) {
	uint8_t i=0;
	// Move data to beginning of the file's directory entry
	data += file->dirTableBlockOffset;

	for (i=0;i<8;i++) {
		if (file->name[i] == '\0') {
			break;
		} else {
			data[i] = toupper(file->name[i]);
		}
	}
	for (;i<8;i++) {
		data[i] = ' ';
	}

	for (i=0;i<3;i++) {
		if (file->ext[i] == '\0') {
			break;
		} else {
			data[i+8] = toupper(file->ext[i]);
		}
	}
	for (;i<3;i++) {
		data[i+8] = ' ';
	}

	for (i=0x0b;i<0x20;i++) {
		data[i] = 0x00;
	}

	Int32ToFATSplitData(data+0x14, data+0x1a, file->startCluster);
}

void FAT32_UpdateDirectoryTableEntry(FS_File *file, uint8_t *data) {
	Int32ToFATData(data + file->dirTableBlockOffset + 0x1c, file->size);
}

void FAT32_AllocateFATBlock(FS_File *file, uint8_t *data) {
	uint32_t currCluster = file->currCluster;
	uint16_t pos = GetClusterFATOffset(file->fs, currCluster);

	file->fs->numFreeClusters -= (file->fs->bytesPerSector - pos) /
			file->fs->clusterPointerSize;
	file->currFATLBA = GetClusterFATLBA(file->fs, currCluster);
	
	for (;pos<file->fs->bytesPerSector;pos+=file->fs->clusterPointerSize) {
		currCluster++;
		Int32ToFATData(data+pos, currCluster);
	}
	currCluster--;
	pos -= file->fs->clusterPointerSize;

	file->currFATBlockOffset = pos;
	file->currFATClusterEnd = currCluster;
	file->fs->mostRecentCluster = currCluster;
	file->fs->fsInfoDirty = 1;
}

void FAT32_TerminateFATBlock(FS_File *file, uint8_t *data) {
	uint32_t currCluster = file->currCluster;
	uint16_t pos = GetClusterFATOffset(file->fs, currCluster);
	uint16_t end = GetClusterFATOffset(file->fs, file->currFATClusterEnd);

	file->fs->numFreeClusters -= (end - pos) / file->fs->clusterPointerSize;
	file->currFATLBA = GetClusterFATLBA(file->fs, currCluster);

	Int32ToFATData(data+pos, FAT32_CLUSTER_EOC);
	file->currFATClusterEnd = FAT32_CLUSTER_EOC;

	file->currFATBlockOffset = pos;
	file->fs->mostRecentCluster = currCluster;
	file->fs->fsInfoDirty = 1;

	pos += file->fs->clusterPointerSize;

	for (;pos<=end;pos+=file->fs->clusterPointerSize) {
		Int32ToFATData(data+pos, 0x00000000);
	}
}
