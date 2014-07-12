/*
 * File:   sd-hardware.c
 * Author: Ducky
 *
 * Created on July 21, 2011, 12:39 PM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Initial version and implementation for the dsPIC33
 *						microcontroller.
 * 24 Jul 2011	Ducky	Added GetTransferComplete(...) function, changed
 *						send DMA transfers to do receive counting.
 *						Major bug fixes after initial testing.
 *
 * @file
 * Hardware abstraction function prototypes and defines.
 */

#include "sd-hardware.h"
#include "sd-defs.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
#define DBG_MODULE "SD/Hardware"
#include "../debug-common.h"
#include "../debug-log.h"

// Buffer definitions
#define RX_DMACON		DMA5CON
#define RX_DMACONbits	DMA5CONbits
#define RX_DMAREQ		DMA5REQ
#define RX_DMAREQbits	DMA5REQbits
#define RX_DMAPAD		DMA5PAD
#define RX_DMACNT		DMA5CNT
#define RX_DMASTA		DMA5STAL
#define RX_DMAIE		IEC2bits.DMA5IE
#define RX_DMAIF		IFS2bits.DMA5IF

#define TX_DMACON		DMA6CON
#define TX_DMACONbits	DMA6CONbits
#define TX_DMAREQ		DMA6REQ
#define TX_DMAREQbits	DMA6REQbits
#define TX_DMAPAD		DMA6PAD
#define TX_DMACNT		DMA6CNT
#define TX_DMASTA		DMA6STAL
#define TX_DMAIE		IEC1bits.DMA6IE
#define TX_DMAIF		IFS1bits.DMA6IF

#define SD_DMAREQ		0x21

#define SD_SPICON1		SPI2CON1
#define SD_SPICON1bits	SPI2CON1bits
#define SD_SPICON2		SPI2CON2
#define SD_SPICON2bits	SPI2CON2bits
#define SD_SPISTAT		SPI2STAT
#define SD_SPISTATbits	SPI2STATbits
#define SD_SPIBUF		SPI2BUF

uint8_t SD_DMA_Buffer0[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));
uint8_t SD_DMA_Buffer1[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));
uint8_t SD_DMA_Buffer2[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));
uint8_t SD_DMA_Buffer3[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));
uint8_t SD_DMA_Buffer4[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));
uint8_t SD_DMA_Buffer5[SD_DATA_BLOCK_LENGTH] __attribute__((space(dma)));

volatile uint8_t SD_DMA_TXBuffer __attribute__((space(dma)));
volatile uint8_t SD_DMA_RXBuffer __attribute__((space(dma)));

SD_Card SD_CreateCard()
{
	SD_Card newCard;

	newCard.State = SD_UNINITIALIZED;
	newCard.SubState = 0;

	newCard.NumDataBlocks = SD_NUM_DATA_BLOCKS;
	
	newCard.DataBlocks[0].Data = SD_DMA_Buffer0;
	newCard.DataBlocks[0].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer0);
	newCard.DataBlocks[1].Data = SD_DMA_Buffer1;
	newCard.DataBlocks[1].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer1);
	newCard.DataBlocks[2].Data = SD_DMA_Buffer2;
	newCard.DataBlocks[2].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer2);
	newCard.DataBlocks[3].Data = SD_DMA_Buffer3;
	newCard.DataBlocks[3].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer3);
	newCard.DataBlocks[4].Data = SD_DMA_Buffer4;
	newCard.DataBlocks[4].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer4);
	newCard.DataBlocks[5].Data = SD_DMA_Buffer5;
	newCard.DataBlocks[5].DMAOffset = __builtin_dmaoffset(SD_DMA_Buffer5);

	newCard.TXBuffer = &SD_DMA_TXBuffer;
	newCard.RXBuffer = &SD_DMA_RXBuffer;
	newCard.TXBufferOffset = __builtin_dmaoffset(&SD_DMA_TXBuffer);
	newCard.RXBufferOffset = __builtin_dmaoffset(&SD_DMA_RXBuffer);

	return newCard;
}

void SD_DMA_Initialize(SD_Card *card) {
	// Initialize SPI stuff
	SD_SPISTATbits.SPIEN = 0;
	SD_SPICON1bits.MSTEN = 1;
	SD_SPISTATbits.SPIROV = 0;

	SD_SPICON1bits.CKE = 1;
	SD_SPICON1bits.CKP = 0;

	SD_SPICON1bits.SPRE = 0b111;
	SD_SPICON1bits.PPRE = 0b00;

	SD_SPISTATbits.SPIEN = 1;

	// Iniitalize DMA stuff
	// DMA AMODE and MODE bits will be initialized during the transfer operation
	TX_DMACONbits.SIZE = 1;		// byte transfers
	TX_DMACONbits.DIR = 1;		// RAM to peripheral transfers
	TX_DMAREQ = SD_DMAREQ;
	TX_DMAPAD = (volatile unsigned int) &SD_SPIBUF;

	RX_DMACONbits.SIZE = 1;		// byte transfers
	RX_DMACONbits.DIR = 0;		// peripheral to RAM transfer
	RX_DMAREQ = SD_DMAREQ;
	RX_DMAPAD = (volatile unsigned int) &SD_SPIBUF;
}

void SD_DMA_InitializeFast(SD_Card *card, uint8_t speedMHz) {
	SD_SPISTATbits.SPIEN = 0;
	SD_SPICON1bits.MSTEN = 1;
	SD_SPISTATbits.SPIROV = 0;
	if (speedMHz > 10) {				// 6:1 (minimum) prescale
		SD_SPICON1bits.SPRE = 0b010;
		SD_SPICON1bits.PPRE = 0b11;
	} else {							// anything else - low speed mode
		SD_SPICON1bits.SPRE = 0b111;
		SD_SPICON1bits.PPRE = 0b00;
	}
	SD_SPISTATbits.SPIEN = 1;
}

inline void SD_SPI_Open(SD_Card *card) {
	SD_SPISTATbits.SPIROV = 0;
	SD_SPISTATbits.SPIEN = 1;		// Enable SPI
	SD_SPI_CS_IO = 0;				// Bring CS pin low
}

inline void SD_SPI_Terminate(SD_Card *card) {
	SD_SPI_Transfer(card, SD_IDLE_BYTE);
}

inline void SD_SPI_Close(SD_Card *card) {
	SD_SPI_CS_IO = 1;				// Bring CS pin high
	SD_SPISTATbits.SPIEN = 0;
}

inline uint8_t SD_SPI_Transfer(SD_Card *card, uint8_t data) {
	while (SD_SPISTATbits.SPITBF);	// wait for empty buffer location
	SD_SPIBUF = data;
	while (!SD_SPISTATbits.SPIRBF);	// wait until data is received
	data = SD_SPIBUF;

	return data;
}

uint8_t SD_SendCommand(SD_Card *card, uint8_t command, uint8_t* args, uint8_t crc) {
	uint8_t response = 0xff;
	uint16_t i = 0;

	SD_SPI_Transfer(card, 0b01000000 | command);
	SD_SPI_Transfer(card, args[0]);
	SD_SPI_Transfer(card, args[1]);
	SD_SPI_Transfer(card, args[2]);
	SD_SPI_Transfer(card, args[3]);
	SD_SPI_Transfer(card, crc | 0b00000001);

	// Wait for a proper received response
	while (response & 0x80 && i < SD_CMD_TIMEOUT) {
		response = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
		i++;
	}
	return response;
}

inline void SD_DMA_SendBlock(SD_Card *card, SD_Data_Block *data) {
	TX_DMACNT = data->BlockLen-1;
	TX_DMASTA = data->DMAOffset + data->StartOffset;
	TX_DMACONbits.AMODE = 0b00;		// register indirect with post-increment
	TX_DMACONbits.MODE = 0b01;		// one-shot without ping-pong

	RX_DMACONbits.AMODE = 0b01;		// register indirect without post-increment
	RX_DMACONbits.MODE = 0b01;		// one-shot without ping-pong
	RX_DMACNT = data->BlockLen-1;
	RX_DMASTA = card->RXBufferOffset;

	TX_DMACONbits.CHEN = 1;
	RX_DMACONbits.CHEN = 1;

	TX_DMAREQbits.FORCE = 1;
}

inline void SD_DMA_ReceiveBlock(SD_Card *card, SD_Data_Block *data) {
	SD_DMA_TXBuffer = SD_DUMMY_BYTE;
	
	TX_DMACNT = data->BlockLen-1;
	TX_DMASTA = card->TXBufferOffset;
	TX_DMACONbits.AMODE = 0b01;		// register indirect without post-increment
	TX_DMACONbits.MODE = 0b01;		// one-shot without ping-pong

	RX_DMACONbits.AMODE = 0b00;		// register indirect with post-increment
	RX_DMACONbits.MODE = 0b01;		// one-shot without ping-pong
	RX_DMACNT = data->BlockLen-1;
	RX_DMASTA = data->DMAOffset + data->StartOffset;

	TX_DMACONbits.CHEN = 1;
	RX_DMACONbits.CHEN = 1;

	TX_DMAREQbits.FORCE = 1;
}

inline uint8_t SD_DMA_GetTransferComplete(SD_Card *card) {
	return !RX_DMACONbits.CHEN;
}
