/*
 * File:   debug-common.c
 * Author: Ducky
 *
 * Created on April 25, 2011, 1:17 AM
 *
 * Revision History
 * Date			Author	Change
 * 25 Jul 2011	Ducky	Added this change history box.
 *						Added support for hex data dumping.
 *
 * @file
 * Debugging console features.
 */

#include <string.h>

#include "debug-common.h"

#include "uart-dma.h"

char DBG_buffer[128];
char next = 0;
char DBG_swirly[] = {'|', '/', '-', '\\'};

/**
 * Converts signed integer @a n to hexadecimal ASCII characters in @a s.
 * Output string will have a minimum length @a len.
 *
 * @param[in] n Signed integer to convert.
 * @param[out] s Pointer to location to store string.
 * @param[in] len Minimum length of output string.
 *		Output string will be padded with 0's to meet this condition.
 * @returns Pointer to output string.
 */
char* lenhtoa(int n, char s[], unsigned char len)
{
    int i, sign, c, j;

    if ((sign = n) < 0)			// record sign
        n = -n;					// make n positive

    i = 0;
    do {						// generate digits in reverse order
        s[i] = n % 16;		// get next digit
		if (s[i] < 10)
			s[i] += '0';
		else
			s[i] += 'A' - 10;
		i++;
    } while ((n /= 16) > 0);	// delete it

    if (sign < 0)
	{
		while (i < len - 1)	{
			s[i++] = '0';
		}
        s[i++] = '-';
	}	else	{
		while (i < len)	{
			s[i++] = '0';
		}
	}
    s[i] = '\0';

	// reverse the string
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

	// this allows it to be used as a string argument
	return s;
}


/**
 * Dumps a segment of memory to UART displaying both hexadecimal and ASCII.
 *
 * @param[in] buf Pointer to start of the location to dump.
 * @param[in] len Length, in bytes, of the location to dump.
 * @param[in] breakLen Length between each break.
 * @param[in] lineLen Length between each line.
 */
void DBG_hexdump(uint8_t *buf, uint16_t len, uint8_t breakLen, uint8_t lineLen) {
	uint8_t *lineStart = buf;
	char buffer[16];
	int i = 0;

	lenhtoa(0, buffer, 4);
	UART_DMA_WriteBlockingS(buffer);
	UART_DMA_WriteBlockingS(" - ");

	for (i=0;i<len;i++) {
		lenhtoa(*(unsigned char*)buf, buffer, 2);
		UART_DMA_WriteBlockingS(buffer);
		UART_DMA_WriteBlockingS(" ");
		buf++;

		if ((i + 1) % lineLen == 0) {
			UART_DMA_WriteBlockingS(" - ");
			while (lineStart < buf) {
				if (*lineStart >= 32 && *lineStart <= 127) {
					UART_DMA_WriteBlocking((char*)lineStart, 1);
				} else {
					UART_DMA_WriteBlockingS(".");
				}
				lineStart++;
			}
			UART_DMA_WriteBlockingS("\n");
			if (i+1 < len) {
				lenhtoa(i+1, buffer, 4);
				UART_DMA_WriteBlockingS(buffer);
				UART_DMA_WriteBlockingS(" - ");
			}
		} else if ((i + 1) % breakLen == 0) {
			UART_DMA_WriteBlockingS(" ");
		}
	}
}
