/*
 * File:   datalogger.h
 * Author: Ducky
 *
 * Created on August 12, 2011, 12:47 AM
 *
 * Revision History
 * Date			Author	Change
 * 12 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger application function prototypes.
 */

#ifndef DATALOGGER_H
#define DATALOGGER_H
#include "../SD-SPI-DMA/sd-hardware.h"

#include "../FAT32/fat32.h"
#include "../FAT32/fat32-file.h"

extern SD_Card card;
extern FS_FAT32 fs;
extern FS_File file;

/**
 * Initializes the Datalogger Application.
 */
void Datalogger_Init();

/**
 * Performs the Datalogger Application tasks. Called every once in a while.
 */
void Datalogger_Loop();

#endif
