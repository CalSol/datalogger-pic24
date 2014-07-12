/*
 * File:   debug-log.h
 * Author: Ducky
 *
 * Created on July 26, 2011, 6:29 PM
 *
 * Revision History
 * Date			Author	Change
 * 26 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * Functions for logging for debugging.
 */

#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include "types.h"

#define DBG_LOG_OP_SBW_LATEDATARESP		0x40		/// Single block write where the data response token did not immediately follow the data block
#define DBG_LOG_OP_MBW_LATEDATARESP		0x41		/// Single block write where the data response token did not immediately follow the data block

/**
 * Writes an entry into the debugging log
 *
 * @param opcode Opcode.
 * @param dataLen Length of the data to write.
 * @param data Pointer to the beginning of data.
 */
void WriteDebugLog(uint8_t opcode, uint8_t dataLen, uint8_t *data);

#endif
