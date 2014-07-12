/*
 * File:   sd-spi-dma.h
 * Author: Ducky
 *
 * Created on July 18, 2011, 12:24 AM
 *
 * Revision History
 * Date			Author	Change
 * 18 Jul 2011	Ducky	Initial definition.
 * 26 Jul 2011	Ducky	Changed return mechanism to use polling functions.
 *
 * @file
 * sd-spi-dma functions intended to be called by the user and data structure
 * definitions.
 */

#ifndef SD_SPI_DMA_H
#define SD_SPI_DMA_H

#include "..\types.h"

#include "sd-hardware.h"

/**
 * @param card SD Card struct.
 * @return Whether the card detect switch indicates there is a card inserted.
 * @retval 0 No card detected.
 * @retval 1 Card detected, or there is no hardware card-detect switch.
 */
uint8_t SD_DetectCard(SD_Card *card);

/**
 * @param card SD Card struct.
 * @return The state of the parameter SD Card.
 */
SD_State SD_GetState(SD_Card *card);

#define SD_SUCCESS					0x00
#define SD_FAILED					0xf0
#define SD_PHY_ERR					0xf1
#define SD_BUSY						0xff

/**
 * Begins the intialization process on the SD Card.
 *
 * @param card SD Card struct.
 * @return Result of the initialization operation.
 * @retval SD_BUSY Operation not yet complete.
 */
sd_result_t SD_Initialize(SD_Card *card);

/**
 * Gets the result of the current initialization process in progress, or returns
 * a busy signal if the initialization process is not yet complete.
 * @pre /a card has an initialization operation in progress.
 *
 * @param card SD Card struct.
 * @return Result of the initialization operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_SUCCESS Operation complete, card initialized.
 * @retval SD_INITIALIZE_FAILED Operation failed, card not initialized.
 * @retval SD_INITIALIZE_TIMEOUT Operation failed - a timeout occurred during
 * intiailization. This most likely indicates that no card is inserted or the
 * card is damaged.
 * @retval SD_INITIALIZE_NOSUPPORT Operation failed - card not supported.
 */
sd_result_t SD_GetInitializeResult(SD_Card *card);
#define SD_INITIALIZE_FAILED		0x10
#define SD_INITIALIZE_TIMEOUT		0x11
#define SD_INITIALIZE_NOSUPPORT		0x12

/**
 * Begins a single block read at the specified address.
 * 
 * @param card SD Card struct.
 * @param addr Block address on the card to begin the operation on.
 * This should be the byte address of the data divided by 512.
 * @param data SD Data Block structure to hold the read data.
 * @return Result of the read operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_FAILED Read failed, contents of data block are undefined.
 */
sd_result_t SD_DMA_SingleBlockRead(SD_Card *card, sd_block_t addr, SD_Data_Block *data);

/**
 * Gets the result of the current single block read in progress, or returns a
 * busy signal if the operation is not yet complete.
 * 
 * @param card SD Card struct.
 * @return Result of the read operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_SUCCESS Read successful, data block contains the read data.
 * @retval SD_FAILED Read failed, contents of data block are undefined.
 */
sd_result_t SD_DMA_GetSingleBlockReadResult(SD_Card *card);

/**
 * Begins a single block wrire at the specified address.
 *
 * @param card SD Card struct.
 * @param addr Block address on the card to begin the operation on.
 * @param data SD Data Block structure holding the data to be written.
 * @return Result of the write operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_FAILED Write failed.
 */
sd_result_t SD_DMA_SingleBlockWrite(SD_Card *card, sd_block_t addr, SD_Data_Block *data);

/**
 * Gets the result of the current single block write in progress, or returns a
 * busy signal if the operation is not yet complete.
 *
 * @param card SD Card struct.
 * @return Result of the write operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_SUCCESS Write successful.
 * @retval SD_FAILED Write failed.
 */
sd_result_t SD_DMA_GetSingleBlockWriteResult(SD_Card *card);

/**
 * Begins a multiple block wrire at the specified address.
 *
 * @param card SD Card struct.
 * @param addr Block address on the card to begin the operation on.
 * @return Result of the begin multiple block write operation.
 * @retval SD_SUCCESS Multiple Block Write started.
 * @retval SD_FAILED Operation failed, likely still in the card idle state.
 */
sd_result_t SD_DMA_MBW_Begin(SD_Card *card, sd_block_t addr);

/**
 * Gets the result of the current send block in progress, or returns a
 * busy signal if the operation is not yet complete.
 *
 * @param card SD Card struct.
 * @return Result of the write operation, to be written to /a resultPtr.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_SUCCESS Block sent successfully and accepted by card.
 * @retval SD_MBW_BLOCK_ERROR Error sending block, likely meaning some data
 * was not properly written.
 */
sd_result_t SD_DMA_MBW_SendBlock(SD_Card *card, SD_Data_Block *data);
#define SD_MBW_BLOCK_ERROR		0x44

/**
 * Sends a data block to the SD Card during the Multiple Block Write operation.
 *
 * @param card SD Card struct.
 * @param data SD Data Block structure holding the data to be written.
 * @return Result of the write operation, to be written to /a resultPtr.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_MBW_BLOCK_SUCCESS Send block successful.
 * @retval SD_MBW_BLOCK_ERROR Error sending block, likely meaning some data
 * was not properly written.
 */
sd_result_t SD_DMA_MBW_GetSendBlockResult(SD_Card *card);

/**
 * Terminates a Multiple Block Write operation.
 *
 * @param card SD Cards struct.
 * @return Result of the write operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_FAILED Error in termination, likely meaning done data
 * was not properly written.
 */
sd_result_t SD_DMA_MBW_Terminate(SD_Card *card);

/**
 * Gets the result of the current Multiple Block Write Terminate operation
 * in progress, or returns a busy signal if the operation is not yet complete.
 *
 * @param card SD Cards struct.
 * @return Result of the write operation.
 * @retval SD_BUSY Operation not yet complete.
 * @retval SD_SUCCESS Termination successful.
 * @retval SD_FAILED Error in termination, likely meaning done data
 * was not properly written.
 */
sd_result_t SD_DMA_MBW_GetTerminateStatus(SD_Card *card);

/**
 * This function is intended to be user-defined and is called once when
 * card-specific data (CSD or CID blocks) are read.
 * This may be called from within interrupts, and should execute quickly.
 */
inline void SD_DMA_OnCardDataRead();

/**
 * This function is intended to be user-defined and is called once when a
 * block read is started.
 * This may be called from within interrupts, and should execute quickly.
 */
inline void SD_DMA_OnBlockRead();

/**
 * This function is intended to be user-defined and is called once when a
 * block write is started.
 * This may be called from within interrupts, and should execute quickly.
 */
inline void SD_DMA_OnBlockWrite();

/**
 * This function is intended to be user-defined and is called once when an
 * SD Card error is encountered (like an unexpected response from the card).
 * This may be called from within interrupts, and should execute quickly.
 */
inline void SD_DMA_OnError();

#endif
