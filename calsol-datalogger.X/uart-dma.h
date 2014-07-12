#include "types.h"
#include "hardware.h"

#ifndef _UART_DMA_H_
#define _UART_DMA_H_

/**
 * The UART baud rate, in bits/sec. The BRG is calculated at compile time from this number.
 */
#define UART_DMA_BAUD		115200

// BRGH formula: ( Fcy / ( 4 * baud ) ) - 1
// BRG  formula: ( Fcy / ( 16 * baud ) ) - 1
#if (((Fcy / 4) / UART_DMA_BAUD) - 1) < 255
	#define UART_DMA_BRG	(((Fcy / 4) / UART_DMA_BAUD) - 1)
	#define UART_DMA_BRGH	1
#else
	#define UART_DMA_BRG	(((Fcy / 16) / UART_DMA_BAUD) - 1)
	#define UART_DMA_BRGH	0
#endif
//TODO Add compile-time baud error percentage check

#define UART_DMA_BUFFER_SIZE	256

#define UART_UMODEbits			U2MODEbits
#define UART_UBRG				U2BRG
#define UART_USTAbits			U2STAbits

#define UART_IRQSEL_VAL			0b0011111
#define UART_DMAPAD_VAL			(uint16_t)&U2TXREG

#define UART_DMACON				DMA7CON
#define UART_DMACONbits			DMA7CONbits
#define	UART_DMAREQbits			DMA7REQbits
#define UART_DMASTA				DMA7STAL
#define UART_DMAPAD				DMA7PAD
#define UART_DMACNT				DMA7CNT

#define UART_DMAInterrupt		_DMA7Interrupt
#define UART_DMAIF				_DMA7IF
#define UART_DMAIE				_DMA7IE

void UART_DMA_Init();
uint16_t UART_DMA_WriteAtomicS(char* string);
uint16_t UART_DMA_WriteAtomic(char* data, uint16_t dataLen);
void UART_DMA_WriteBlockingS(char* string);
void UART_DMA_WriteBlocking(char* string, uint16_t dataLen);
uint16_t UART_DMA_SendBlock();

#endif
