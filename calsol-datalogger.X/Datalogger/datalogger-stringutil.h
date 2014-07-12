/*
 * File:   datalogger-stringutil.h
 * Author: Ducky
 *
 * Created on August 13, 2011, 4:55 PM
 */

#ifndef DATALOGGER_STRINGUTIL_H
#define DATALOGGER_STRINGUTIL_H

#include <time.h>
#include "../types.h"

#define INT8_MAX_CHAR   4   // maximum number of characters to represent a decimal 16-bit integer
#define INT16_MAX_CHAR  6   // maximum number of characters to represent a decimal 16-bit integer
#define INT32_MAX_CHAR  11  // maximum number of characters to represent a decimal 16-bit integer
#define INT64_MAX_CHAR  21  // maximum number of characters to represent a decimal 16-bit integer

#define DLGSTR_MAX_LEN  256
/**
 * DlgStr: Datalogger String - a string builder like struct
 */
typedef struct {
    char string[DLGSTR_MAX_LEN];    /// Contents of string
    char* pos;                      /// Next empty position in string
    char* end;                      /// Pointer to one past the last position in string
} DlgStr;

/**
 * Initializes a DlgStr with the specified string.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[out] dlgstr DlgStr object to initialize.
 * @param[in] str String to initialize with.
 */
inline void DlgStr_Init(DlgStr* dlgstr, char* str);

/**
 * Appends a string to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendStr Null-terminated string to append.
 */
inline void DlgStr_AppendString(DlgStr* dlgstr, char* appendStr);

/**
 * Appends @a len characters from @a string to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendStr String to append.
 * @param[in] len Length of string to append.
 */
inline void DlgStr_AppendStringLen(DlgStr* dlgstr, char* appendStr, uint16_t len);

/**
 * Appends a single character to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendChar Character to append.
 */
inline void DlgStr_AppendChar(DlgStr* dlgstr, char appendChar);

/**
 * Appends a timestamp to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] timestamp 32-bit timestamp to append, partially implementation defined
 */
void DlgStr_AppendTimestamp(DlgStr* dlgstr, uint32_t timestamp);

/**
 * Appends a timestamp to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] time tm struct to append.
 */
void DlgStr_AppendTmStruct(DlgStr* dlgstr, struct tm time);

/**
 * Appends a decimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Signed 32-bit number to append.
 */
void DlgStr_AppendDec32(DlgStr* dlgstr, int32_t appendInt);

/**
 * Appends a fake-floating point decimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Signed 16-bit number to append.
 * @param[in] dec Number of places after the decimal point. If necessary, zeros
 * will be added to make the decimal point show up.
 */
void DlgStr_AppendDec16Dec(DlgStr* dlgstr, int16_t appendInt, uint8_t dec);

/**
 * Appends a minimum-length padded decimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Signed 16-bit number to append.
 * @param[in] minLen Minimum length of the output string, if the output number
 * does not meet this length, it will be front-padded with @a pad
 * @param[in] pad Padding character
 */
void DlgStr_AppendDec16Pad(DlgStr* dlgstr, int16_t appendInt, uint8_t minLen, char pad);

/**
 * Appends an unsigned decimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 16-bit number to append.
 */
void DlgStr_AppendUDec16(DlgStr* dlgstr, uint16_t appendInt);

/**
 * Appends a decimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Signed 16-bit number to append.
 */
void DlgStr_AppendDec16(DlgStr* dlgstr, int16_t appendInt);

/**
 * Appends a hexadecimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * The number will be padded with zeros to make it 8 characters long.
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 32-bit hex number to append.
 */
void DlgStr_AppendHex32(DlgStr* dlgstr, uint32_t appendInt);

/**
 * Appends a hexadecimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 * 
 * The number will be padded with zeros to make it 4 characters long.
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 16-bit hex number to append.
 */
void DlgStr_AppendHex16(DlgStr* dlgstr, uint16_t appendInt);

/**
 * Appends a hexadecimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * The number will be padded with zeros to make it 3 characters long.
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 12-bit hex number to append.
 */
void DlgStr_AppendHex12(DlgStr* dlgstr, uint16_t appendInt);

/**
 * Appends a hexadecimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * The number will be padded with zeros to make it 2 characters long.
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 8-bit hex number to append.
 */
void DlgStr_AppendHex8(DlgStr* dlgstr, uint8_t appendInt);

/**
 * Appends a hexadecimal number to a DlgStr.
 * Overflow behavior is undefined - it may either append nothing or append
 * a partial string, but it will not exceed the array limits.
 * This is a safe function.
 *
 * The number will be padded with zeros to make it 1 character long.
 * @param[in/out] dlgstr DlgStr object to append to.
 * @param[in] appendInt Unsigned 4-bit hex number to append.
 */
void DlgStr_AppendHex4(DlgStr* dlgstr, uint8_t appendInt);

/*
 * Old style functions below
 */

/**
 * Converts a 32-bit integer to a hexadecimal string stored in /a buffer.
 * Output is not null-terminated.
 * @param input Input integer to convert.
 * @param buffer Location to store the output string.
 * @return Pointer to the output string, equal to /a buffer.
 */
char* Int32ToString(uint32_t input, char *buffer);

/**
 * Converts a 16-bit integer to a hexadecimal string stored in /a buffer.
 * Output is not null-terminated.
 * @param input Input integer to convert.
 * @param buffer Location to store the output string.
 * @return Pointer to the output string, equal to /a buffer.
 */
char* Int16ToString(uint16_t input, char *buffer);

/**
 * Converts a 12-bit integer to a hexadecimal string stored in /a buffer.
 * Output is not null-terminated.
 * @param input Input integer to convert.
 * @param buffer Location to store the output string.
 * @return Pointer to the output string, equal to /a buffer.
 */
char* Int12ToString(uint16_t input, char *buffer);

/**
 * Converts a 8-bit integer to a hexadecimal string stored in /a buffer.
 * Output is not null-terminated.
 * @param input Input integer to convert.
 * @param buffer Location to store the output string.
 * @return Pointer to the output string, equal to /a buffer.
 */
char* Int8ToString(uint8_t input, char *buffer);

/**
 * Converts a 4-bit integer to a hexadecimal string stored in /a buffer.
 * Output is not null-terminated.
 * @param input Input integer to convert.
 * @param buffer Location to store the output string.
 * @return Pointer to the output string, equal to /a buffer.
 */
char* Int4ToString(uint8_t input, char *buffer);

#endif
