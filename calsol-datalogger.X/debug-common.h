/*
 * File:   debug-common.h
 * Author: Ducky
 *
 * Creation time unknown.
 *
 * Revision History
 * Date			Author	Change
 * 25 Jul 2011	Ducky	Added this change history box.
 *						Added support for hex data dumping.
 *
 * @file
 * Debugging console features.
 */

//	#define DBG_BLOCK

#if defined(DEBUG_UART) && !defined(DEBUG_UART_DISABLE)
	// This file should win an award for most complicated preprocessor statements
	#include <stdio.h>
	#include "uart-dma.h"

	#define NUM_SWIRLY 4
	#ifndef DBG_MODULE
		#define DBG_MODULE __FILE__
	#endif

	#ifdef DBG_BLOCK
		#define DBG_BLOCKFN()	while (UART_DMA_Active);
	#else
		#define DBG_BLOCKFN()	;
	#endif

	extern char DBG_buffer[128];
	extern char DBG_swirly[];
	extern char next;
	extern volatile uint16_t UART_DMA_Active;
	#define STR_HELPER(x) #x
	#define STR(x) STR_HELPER(x)

	#define SH_printf(f, ...)		sprintf(DBG_buffer, f, ## __VA_ARGS__);													\
									UART_DMA_WriteBlockingS(DBG_buffer);													\
									UART_DMA_WriteBlockingS("\23337m\r\n");													\
									DBG_BLOCKFN();

	#define DBG_printf(f, ...)		UART_DMA_WriteBlockingS("\23336m[");													\
									UART_DMA_WriteBlocking(DBG_swirly+next, 1);												\
									UART_DMA_WriteBlockingS(" Info]\23337m " DBG_MODULE " " STR(__LINE__) ": ");			\
									next++; if (next >= NUM_SWIRLY) next=0;													\
									sprintf(DBG_buffer, f, ## __VA_ARGS__);													\
									UART_DMA_WriteBlockingS(DBG_buffer);													\
									UART_DMA_WriteBlockingS("\r\n");														\
									DBG_BLOCKFN();

	#define DBG_ERR_printf(f, ...)	UART_DMA_WriteBlockingS("\23331m[");													\
									UART_DMA_WriteBlocking(DBG_swirly+next, 1);												\
									UART_DMA_WriteBlockingS(" Err ]\23337m " DBG_MODULE " " STR(__LINE__) ": ");			\
									next++; if (next >= NUM_SWIRLY) next=0;													\
									sprintf(DBG_buffer, f, ## __VA_ARGS__);													\
									UART_DMA_WriteBlockingS(DBG_buffer);													\
									UART_DMA_WriteBlockingS("\r\n");														\
									DBG_BLOCKFN();

	#ifdef DEBUG_UART_DATA
	void DBG_hexdump(uint8_t *buf, uint16_t len, uint8_t breakLen, uint8_t lineLen);
	#define DBG_DATA_printf(f, ...)	UART_DMA_WriteBlockingS("\23333m[");													\
									UART_DMA_WriteBlocking(DBG_swirly+next, 1);												\
									UART_DMA_WriteBlockingS(" Data]\23337m " DBG_MODULE " " STR(__LINE__) ": ");			\
									next++; if (next >= NUM_SWIRLY) next=0;													\
									sprintf(DBG_buffer, f, ## __VA_ARGS__);													\
									UART_DMA_WriteBlockingS(DBG_buffer);													\
									UART_DMA_WriteBlockingS("\r\n");														\
									DBG_BLOCKFN();

	#define DBG_DATA_hexdump(data, len, breakLen, lineLen)	DBG_hexdump(data, len, breakLen, lineLen);
	#else
		#define DBG_DATA_printf(f, ...)
		#define DBG_DATA_hexdump(data)
	#endif
	#ifdef DEBUG_UART_SPAM
	#define DBG_SPAM_printf(f, ...)	UART_DMA_WriteBlockingS("\23335m[");													\
									UART_DMA_WriteBlocking(DBG_swirly+next, 1);												\
									UART_DMA_WriteBlockingS(" Spam]\23337m " DBG_MODULE " " STR(__LINE__) ": ");			\
									next++; if (next >= NUM_SWIRLY) next=0;													\
									sprintf(DBG_buffer, f, ## __VA_ARGS__);													\
									UART_DMA_WriteBlockingS(DBG_buffer);													\
									UART_DMA_WriteBlockingS("\r\n");														\
									DBG_BLOCKFN();

	#else
		#define DBG_SPAM_printf(f, ...)
	#endif
#else
	#define DBG_printf(f, ...)			;
	#define DBG_ERR_printf(f, ...)		;
	#define DBG_DATA_printf(f, ...)		;
	#define DBG_DATA_hexdump(data, len, breakLen, lineLen)	;
	#define DBG_SPAM_printf(f, ...)		;
#endif
