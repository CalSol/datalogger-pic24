/*
 * File:   fat32-file-util.h
 * Author: Ducky
 *
 * Created on July 30, 2011, 9:15 AM
 *
 * Revision History
 * Date			Author	Change
 * 30 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * Utility functions for optimized FAT32 file operations.
 */

#ifndef FAT32_FILE_UTIL_H
#define FAT32_FILE_UTIL_H

#include "fat32.h"
#include "fat32-file.h"

/**
 * Writes the directory table entry for the file.
 *
 * @param file File structure, with the directory table pointers (especially
 * block offset) already initialized.
 * @param data Data block of the sector containing the directory table.
 */
void FAT32_WriteDirectoryTableEntry(FS_File *file, uint8_t *data);

/**
 * Updates the file's directory table entry with current paramters like size.
 *
 * @param file File structure.
 * @param data Data block of the sector containing the directory table.
 */
void FAT32_UpdateDirectoryTableEntry(FS_File *file, uint8_t *data);

/**
 * Allocates the next block of FAT data for a file starting at the file's
 * current cluster.
 * This then updates then file's FAT LBA pointers, the new last allocated
 * cluster, and the FS Information Sector's number of free clusters and
 * most recently allocated cluster.
 *
 * @param file File struct.
 * @param data Data block of the sector containing the FAT entry.
 */
void FAT32_AllocateFATBlock(FS_File *file, uint8_t *data);

/**
 * Terminates the FAT block at the file's current cluster.
 * This updates the file's last allocated cluster, the FS Information Sector's
 * number of free clusters, and most recently allocated cluster
 *
 * @param file File struct.
 * @param data Data block of the sector containing the FAT entry.
 */
void FAT32_TerminateFATBlock(FS_File *file, uint8_t *data);

#endif
