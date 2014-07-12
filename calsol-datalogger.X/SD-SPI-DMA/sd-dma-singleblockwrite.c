/*
 * File:   sd-singleblockwrite.c
 * Author: Ducky
 *
 * Created on July 26, 2011, 4:58 PM
 *
 * Revision History
 * Date			Author	Change
 * 26 Jul 2011	Ducky	Initial implementation.
 *
 * TODOs
 * 26 Jul 2011	Ducky	SDHC Support.
 *
 * Single Block Write operation functionality.
 */

#include "sd-defs.h"
#include "sd-spi-dma.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
#define DBG_MODULE "SD/SBW"
#include "../debug-common.h"
#include "../debug-log.h"

#define SD_SBW_SUB_BLOCKSEND	0	// Currently sending block
#define SD_SBW_SUB_BLOCKBUSY	1	// Waiting for end of busy signal

sd_result_t SD_DMA_SingleBlockWrite(SD_Card *card, sd_block_t addr, SD_Data_Block *data) {
	uint8_t result;
	uint8_t args[4];

	if (card->State != SD_IDLE) {
		DBG_ERR_printf("SBW failed: Card not in idle state");
		return SD_FAILED;
	}

	if (!card->SDHC) {
		addr = addr * card->BlockSize;
	}

	args[0] = (uint8_t)((addr >> 24) & 0xff);
	args[1] = (uint8_t)((addr >> 16) & 0xff);
	args[2] = (uint8_t)((addr >> 8) & 0xff);
	args[3] = (uint8_t)((addr >> 0) & 0xff);

	SD_SPI_Open(card);
	result = SD_SendCommand(card, SD_CMD_WRITE_BLOCK, args, 0x00);
	if (result != 0x00) {
		DBG_ERR_printf("SBW failed: Bad response to WRITE_BLOCK - got 0x%02x", result);

		SD_DMA_OnError();

		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		return SD_PHY_ERR;
	}

	// send block
	data->StartOffset = 1;
	data->BlockLen = 516;
	data->Data[1] = SD_TOKEN_START_BLOCK;
	data->Data[card->BlockSize + 2] = 0x00;
	data->Data[card->BlockSize + 3] = 0x00;
	data->Data[card->BlockSize + 4] = 0xff;
	SD_DMA_SendBlock(card, data);

	SD_DMA_OnBlockWrite();

	card->State = SD_DMA_SBW;
	card->SubState = 0;

	return SD_BUSY;
}

sd_result_t SD_DMA_GetSingleBlockWriteResult(SD_Card *card) {
	if (card->State != SD_DMA_SBW) {
		DBG_ERR_printf("SBW failed: Card not in Single Block Write state");
		return SD_FAILED;
	}

	if (card->SubState == 0) {
		if (SD_DMA_GetTransferComplete(card)) {
			uint8_t result;

			result = *card->RXBuffer;
			while ((result & 0b00010001) != 0b00000001) {
				WriteDebugLog(DBG_LOG_OP_SBW_LATEDATARESP, 0, NULL);
				result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			}

			if ((result & 0b00001110) == 0b00000100) {
				card->SubState = 1;
			} else {
				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				card->State = SD_IDLE;
				
				DBG_ERR_printf("SBW failed: Bad data response token - got 0x%02x", result);

				SD_DMA_OnError();

				return SD_PHY_ERR;
			}

		} else {
			return SD_BUSY;
		}
	}
	if (card->SubState == 1) {
		uint8_t result = 0x01;
		while ((result != SD_IDLE_BYTE) && (result != SD_BUSY_BYTE)) {
			result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
		}
		if (result == SD_IDLE_BYTE) {
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			card->State = SD_IDLE;
			
			return SD_SUCCESS;
		} else {
			return SD_BUSY;
		}
	}

	// Code should never reach this
	DBG_ERR_printf("SBW failed: Bad substate 0x%02x", card->SubState);
	return SD_FAILED;
}
