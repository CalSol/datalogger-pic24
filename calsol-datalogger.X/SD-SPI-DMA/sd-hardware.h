/*
 * File:   sd-hardware.h
 * Author: Ducky
 *
 * Created on July 18, 2011, 12:25 AM
 *
 * Revision History
 * Date			Author	Change
 * 18 Jul 2011	Ducky	Initial interface definition.
 * 21 Jul 2011	Ducky	Added some more functions, removed the "write-back"
 *						returns in favor of doing command-specific get result
 *						functions.
 *
 * @file
 * Hardware abstraction interface function prototypes and defines.
 * 
 * The current architecture has the infastructure to support multiple cards
 * per microcontroller (which is why the SD_Card structure is included
 * in every argument list), but currently that functionality is not
 * implemented in the hardware-dependent layer because of performance reasons
 * and lack of necessity.
 */

#ifndef SD_HARDWARE_H
#define SD_HARDWARE_H

#include "../types.h"
#include "../hardware.h"

/**
 * States a SD Card can be in.
 */
typedef enum {
	SD_UNINITIALIZED,	/// Card not initialized
	SD_INITIALIZING,	/// Card initializing

	SD_IDLE,			/// Card idle and ready to accept new commands

	SD_BUSY,			/// General Card Busy state - not to be used

	SD_DMA_SBR,			/// Single Block Read operation
	SD_DMA_SBW,			/// Single Block Write operation

	SD_DMA_MBW_IDLE,	/// Multiple Block Write - idle
	SD_DMA_MBW_SENDING,	/// Multiple Block Write - sending a block
SD_DMA_MBW_TERMINATING,	/// Multiple Block Write - operation terminating
} SD_State;

/**
 * A SD Card data buffer block, used for DMA background transfers.
 *
 * The data block is structured as thus for transfer operations:
 * The first two bytes are reserved (for headers such as the start block token)
 * The last four bytes are reserved (for CRC and response where necessary)
 * The rest is data.
 *
 * For Block Write operations, the start block token starts at byte 1 and
 * the block of data is at bytes 2-513. Byte 514-515 form the CRC.
 */
typedef struct {
	uint16_t DMAOffset;			/// DMA offset / DMA address.

	uint16_t StartOffset;		/// Starting offset for the transfer operation.
	uint16_t BlockLen;			/// Length of the block to send, including.
								/// header (i.e. tokens) and trailer (i.e. CRC).

	uint8_t* Data;		/// Pointer to the actual data block.
} SD_Data_Block;

#define SD_NUM_DATA_BLOCKS		6
#define SD_DATA_BLOCK_LENGTH	518

/**
 * A SD Card structure / object. Each object represents a physical SD Card slot,
 * not a SD Card. On card initialization, the card-specific data is populated
 * in the SD Card structure.
 */
typedef struct {
	// Internal state variables
	SD_State State;				/// Card state
	uint8_t SubState;			/// Sub-state within the card-state
	uint16_t TimeoutCount;		/// State-specific timeout count variable

	// Buffering variables
	uint8_t NumDataBlocks;		/// Number of data blocks
	SD_Data_Block DataBlocks[SD_NUM_DATA_BLOCKS];	/// Array of data blocks

	volatile uint8_t *TXBuffer;			/// Single byte transmit buffer
	volatile uint8_t *RXBuffer;			/// Single byte receive buffer
	
	uint16_t TXBufferOffset;	/// DMA offset for TXBuffer
	uint16_t RXBufferOffset;	/// DMA offset for RXBuffer

	// Card information
	uint8_t Ver2SDCard;			/// Whether the card is Version 2.
	uint8_t CmdVer;				/// Command version of the card.
	uint8_t SDHC;				/// Whether the card is SDHC.

	uint16_t BlockSize;			// Size of a block
	uint32_t BlockCapacity;		/// Size, in number of blocks, of the card.

	// Card-Specific data (CSD)
	uint8_t TRAN_SPEED;	/// Transmission speed

	// Card ID (CID) data
	uint8_t MID;			/// Manufacturer ID
	char OID[2];			/// OEM/Application ID
	char PNM[5];			/// Product name - this string is NOT null terminated
	uint8_t PRV;			/// Product revision
	uint32_t PSN;			/// Product serial number
	uint16_t MDT;			/// Manufacturing date

	// Stuff to support multiple cards below (none yet)
} SD_Card;

/**
 * Creates a new SD Card object.
 * @return a new SD Card object.
 */
SD_Card SD_CreateCard();

/**
 * Initializes the SD DMA hardware to the low speed (400kbit/s) mode.
 */
void SD_DMA_Initialize(SD_Card *card);

/**
 * Initializes the SPI bus to the desired speed.
 * @pre SD_DMA_Initialize has already been called previously.
 *
 * @param card SD Card structure.
 * @param speedkHz Requested operation speed in MHz, rounded down. A value of 0
 * indicates operation in low speed (400kbit/s mode).
 */
void SD_DMA_InitializeFast(SD_Card *card, uint8_t speedMHz);

/**
 * Opens the SPI line (asserts CS low).
 *
 * @param card SD Card structure.
 */
inline void SD_SPI_Open(SD_Card *card);

/**
 * Closes the SPI line (deasserts CS).
 *
 * @param card SD Card structure.
 */
inline void SD_SPI_Close(SD_Card *card);

/**
 * Terminates a SD Card command.
 * @param card SD Card structure.
 */
inline void SD_SPI_Terminate(SD_Card *card);

/**
 * Transmits a data byte @a data over the SPI bus, and returns the response.
 * This is blocking until the transmission completes.
 *
 * @param card SD Card structure.
 * @param data Data byte to be shifted out the SPI bus.
 * @return The response byte from the device.
 */
inline uint8_t SD_SPI_Transfer(SD_Card *card, uint8_t data);

/**
 * Sends a command to the SD Card. This function blocks until the transmission
 * is complete.
 *
 * @param card SD Card structure.
 * @param command Command byte to send.
 * @param args Arguments to send, should be an array of 4 bytes.
 * @param crc The 7-bit CRC to send.
 * @return The first byte of the response, or the busy signal on a timeout.
 */
uint8_t SD_SendCommand(SD_Card *card, uint8_t command, uint8_t* args, uint8_t crc);

/**
 * Requests that a block be sent to the card through DMA.
 * 
 * @param card SD Card structure.
 * @param data SD Data Block structure holding the data to be sent.
 */
inline void SD_DMA_SendBlock(SD_Card *card, SD_Data_Block *data);

/**
 * Requests that a block be received from the card through DMA.
 * 
 * @param card SD Card structure.
 * @param data SD Data Block structure which will hold the received data.
 */
inline void SD_DMA_ReceiveBlock(SD_Card *card, SD_Data_Block *data);

/**
 * @return Whether the current background DMA transfer is complete.
 * @retval 0 False, DMA transfer still ongoing.
 * @retval 1 True, DMA transfer complete.
 */
inline uint8_t SD_DMA_GetTransferComplete(SD_Card *card);

#endif
