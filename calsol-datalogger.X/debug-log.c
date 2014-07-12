/*
 * File:   debug-log.c
 * Author: Ducky
 *
 * Created on July 26, 2011, 6:30 PM
 *
 * Revision History
 * Date			Author	Change
 * 26 Jul 2011	Ducky	Initial implementation.
 *
 * TODOs
 * 26 Jul 2011	Ducky	Debug logging to NVM.
 *
 * Functions for logging for debugging.
 */

#include "debug-log.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#define DEBUG_UART_SPAM
#include "debug-common.h"

void WriteDebugLog(uint8_t opcode, uint8_t dataLen, uint8_t *data) {
	DBG_ERR_printf("LOG DATA: 0x%02x, length %u", opcode, dataLen);
}
