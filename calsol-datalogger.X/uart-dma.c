/*
 * File:   uart-dma.c
 * Author: Ducky
 *
 * Created on May 30, 2011, 5:41 PM
 */
#include <string.h>
#include <libpic30.h>

#include <dma.h>
#include <uart.h>

#include "types.h"
#include "hardware.h"

#include "uart.h"
#include "uart-dma.h"

char UART_DMA_Buffer[UART_DMA_BUFFER_SIZE] __attribute__((space(dma)));
volatile uint16_t UART_DMA_Active = 0;				/// Whether the DMA module is transferring data.
volatile uint16_t UART_DMA_bufStart = 0;			/// Index of the start of the buffer - the position of the start of the next DMA block transfer.
													/// This should ONLY be modified by the DMA ISR.
uint16_t UART_DMA_bufEnd = 0;				/// Index of the end of the buffer - the position to store the next byte written.
													/// This should ONLY be modified by the user program.
volatile uint16_t UART_DMA_TransferringSize = 0;	/// Number of bytes currently being transferred by the DMA module.

/** 
 * Initialize the UART module and DMA for UART.
 */
void UART_DMA_Init() {
	// Initialize UART  
    OpenUART2(
            UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE
            & UART_MODE_SIMPLEX & UART_UEN_00 & UART_DIS_WAKE
            & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_NO_PAR_8BIT
            & (UART_DMA_BRGH? UART_BRGH_FOUR : UART_BRGH_SIXTEEN)
            & UART_1STOPBIT,
            UART_INT_TX & UART_TX_ENABLE & UART_RX_OVERRUN_CLEAR,
            UART_DMA_BRG
            );
    U2STAbits.UTXINV = 0;

	// Initialize DMA
    OpenDMA7(
            DMA7_MODULE_ON & DMA7_SIZE_BYTE & DMA7_TO_PERIPHERAL
            & DMA7_INTERRUPT_BLOCK & DMA7_NORMAL & DMA7_REGISTER_POST_INCREMENT
            & DMA7_ONE_SHOT,
            DMA7_MANUAL,
            __builtin_dmaoffset(UART_DMA_Buffer),
            __builtin_dmaoffset(UART_DMA_Buffer),
            (unsigned int)&U2TXREG,
            0
            );
    UART_DMAREQbits.IRQSEL = UART_IRQSEL_VAL;

	// Enable interrupts
    EnableIntDMA7;
	UART_DMAIF = 0;
}

/**
 * Writes a string to the UART DMA buffer.
 * This either succeeds (the entire string is written) or fails (nothing is written,
 * if there is not enough space in the buffer). This will NOT do a partial write.
 *
 * @param data Null-terminated string to write to the UART DMA buffer.
 * @return Number of bytes written to the UART DMA buffer.
 */
uint16_t UART_DMA_WriteAtomicS(char* string) {
	return UART_DMA_WriteAtomic(string, strlen(string));
}

/**
 * Writes a string to the UART DMA buffer.
 * This either succeeds (the entire string is written) or fails (nothing is written,
 * if there is not enough space in the buffer). This will NOT do a partial write.
 *
 * @param data String to write to the UART DMA buffer.
 * @param dataLen Number of bytes to write to the UART DMA buffer.
 * @return Number of bytes written to the UART DMA buffer.
 */
uint16_t UART_DMA_WriteAtomic(char* data, uint16_t dataLen) {
	uint16_t localBufStart = UART_DMA_bufStart;		// Take a local copy to avoid parallelism bugs
	uint16_t bufSize;

	// Compute current buffer size to determine if there is enough room
	if (UART_DMA_bufEnd < localBufStart) {	// Buffer wraps around
		bufSize = UART_DMA_BUFFER_SIZE - localBufStart + UART_DMA_bufEnd;
	} else {
		bufSize = UART_DMA_bufEnd - localBufStart;
	}

	if ((bufSize + dataLen) < (UART_DMA_BUFFER_SIZE - 1)) {	// Enough space in buffer
		// Write data to buffer and atomically update buffer end
		uint16_t dataPtr;
		uint16_t localBufEnd = UART_DMA_bufEnd;
		for (dataPtr = 0; dataPtr < dataLen; dataPtr++) {
			UART_DMA_Buffer[localBufEnd] = data[dataPtr];
			localBufEnd ++;
			if (localBufEnd >= UART_DMA_BUFFER_SIZE) {
				localBufEnd = 0;
				if (localBufEnd == localBufStart) {
					while(1);
				}
			}
		}

		UART_DMA_bufEnd = localBufEnd;

		UART_DMA_SendBlock();

		return dataLen;
	} else {	// Not enough space in buffer
		return 0;
	}
}

/**
 * Writes a string to the UART DMA buffer.
 * This blocks until the entire string is entered into the buffer. Partial writes
 * will NOT happen.
 *
 * @param data Null-terminated string to write to the UART DMA buffer.
 */
void UART_DMA_WriteBlockingS(char* string) {
	uint16_t localBufEnd = UART_DMA_bufEnd;
	uint16_t currBufEnd;

	while (*string != 0) {
		UART_DMA_Buffer[localBufEnd] = *string;

		currBufEnd = localBufEnd;
		localBufEnd++;
		if (localBufEnd == UART_DMA_BUFFER_SIZE) {
			localBufEnd = 0;
		}
		
		if (localBufEnd == UART_DMA_bufStart) {		// Full buffer
			UART_DMA_bufEnd = currBufEnd;
			while (localBufEnd == UART_DMA_bufStart){	// Wait for empty buffer location
				UART_DMA_SendBlock();
			}
		}
		string++;
	}
	UART_DMA_bufEnd = localBufEnd;
	UART_DMA_SendBlock();
}

/**
 * Writes a string to the UART DMA buffer.
 * This blocks until the entire string is entered into the buffer. Partial writes
 * will NOT happen.
 *
 * @param data Null-terminated string to write to the UART DMA buffer.
 * @param dataLen Number of bytes to write to the UART DMA buffer.
 */
void UART_DMA_WriteBlocking(char* string, uint16_t dataLen) {
	uint16_t localBufEnd = UART_DMA_bufEnd;
	uint16_t currBufEnd;

	while (dataLen > 0) {
		UART_DMA_Buffer[localBufEnd] = *string;

		currBufEnd = localBufEnd;
		localBufEnd++;
		if (localBufEnd == UART_DMA_BUFFER_SIZE) {
			localBufEnd = 0;
		}

		if (localBufEnd == UART_DMA_bufStart) {		// Full buffer
			UART_DMA_bufEnd = currBufEnd;
			while (localBufEnd == UART_DMA_bufStart){	// Wait for empty buffer location
				UART_DMA_SendBlock();
			}
		}
		string++;
		dataLen--;
	}
	UART_DMA_bufEnd = localBufEnd;
	UART_DMA_SendBlock();
}

/**
 * Sets the DMA module to transfer the next block of data.
 *
 * @return Number of bytes to be transferred.
 */
uint16_t UART_DMA_SendBlock() {
	// Check that there is data and there isn't a transfer ongoing
	if (!UART_DMA_Active && (UART_DMA_bufStart != UART_DMA_bufEnd)) {
		UART_DMA_Active = 1;

		UART_DMASTA = __builtin_dmaoffset(UART_DMA_Buffer) + UART_DMA_bufStart;
		// Calculate transfer size
		if (UART_DMA_bufEnd < UART_DMA_bufStart) {	// Buffer wraps around, transfer to end
			UART_DMA_TransferringSize = UART_DMA_BUFFER_SIZE - UART_DMA_bufStart;
		} else {					// Buffer does not wrap, transfer all
			UART_DMA_TransferringSize = UART_DMA_bufEnd - UART_DMA_bufStart;
		}
		// Upper bound the transfer size to keep the pipe full
		if (UART_DMA_TransferringSize > UART_DMA_BUFFER_SIZE / 2) {
			UART_DMA_TransferringSize = UART_DMA_BUFFER_SIZE / 2;
		}
        uint16_t transferSize = UART_DMA_TransferringSize - 1;
        Nop();  // this fixes a compiler error
		UART_DMACNT = transferSize;

		UART_DMACONbits.CHEN = 1;
		UART_DMAREQbits.FORCE = 1;

		return UART_DMA_TransferringSize;
	} else {
		return 0;
	}
    return 0;
}

void __attribute__((interrupt, no_auto_psv)) UART_DMAInterrupt(void) {
	UART_DMAIF = 0;

	// Set new buffer starting position
	uint16_t localBufStart = UART_DMA_bufStart;
	localBufStart += UART_DMA_TransferringSize;
	if (localBufStart >= UART_DMA_BUFFER_SIZE) {
		localBufStart = 0;
	}
	UART_DMA_bufStart = localBufStart;

	// Check if there is more data
	uint16_t localBufEnd = UART_DMA_bufEnd;
	if (localBufStart != localBufEnd) {
		UART_DMASTA = __builtin_dmaoffset(UART_DMA_Buffer) + localBufStart;
		// Calculate transfer size
		if (localBufEnd < localBufStart) {	// Buffer wraps around, transfer to end
			UART_DMA_TransferringSize = UART_DMA_BUFFER_SIZE - localBufStart;
		} else {					// Buffer does not wrap, transfer all
			UART_DMA_TransferringSize = localBufEnd - localBufStart;
		}
		// Upper bound the transfer size to keep the pipe full
		if (UART_DMA_TransferringSize > UART_DMA_BUFFER_SIZE / 2) {
			UART_DMA_TransferringSize = UART_DMA_BUFFER_SIZE / 2;
		}
        uint16_t transferSize = UART_DMA_TransferringSize - 1;
        Nop();  // this fixes a compiler error
		UART_DMACNT = transferSize;

		while (UART_USTAbits.UTXBF);

		UART_DMACONbits.CHEN = 1;
		UART_DMAREQbits.FORCE = 1;
	} else {
		UART_DMA_Active = 0;
	}
}
