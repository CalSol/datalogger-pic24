/*
 * File:   types.h
 * Author: Ducky
 *
 * Created a really long time ago.
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box,
 *						separated Run 2/3 hardware.
 *
 * @file
 * Global typedefs.
 */

#ifndef TYPES_H
#define TYPES_H

#ifndef NULL
	#define NULL	0
#else
	#if NULL != 0
		#error "NULL not defined to be 0!"
	#endif
#endif

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint16_t;
typedef signed int int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef uint8_t sd_result_t;
typedef uint8_t fs_result_t;

typedef uint32_t sd_block_t;

typedef uint32_t fs_addr_t;		/// Integer type used for addressing files (either by byte or by block).
typedef uint32_t fs_size_t;		/// Integer type for specifying file size (in bytes).
typedef uint16_t fs_length_t;	/// Integer size used for specifying read/write length. This is limited by the size of the MCU memory.
								/// This is NOT the same as fs_size_t, and is likely to be smaller.
#endif
