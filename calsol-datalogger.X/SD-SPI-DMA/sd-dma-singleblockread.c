/*
 * File:   sd-dma-singleblockread.c
 * Author: Ducky
 *
 * Created on July 25, 2011, 4:38 PM
 *
 * Revision History
 * Date			Author	Change
 * 25 Jul 2011	Ducky	Initial implementation.
 *
 * TODOs
 * 25 Jul 2011	Ducky	Wait for start block token in background.
 *						SDHC Support.
 *
 * Single Block Read operation functionality.
 */

#include "sd-defs.h"
#include "sd-spi-dma.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
#define DBG_MODULE "SD/SBR"
#include "../debug-common.h"

sd_result_t SD_DMA_SingleBlockRead(SD_Card *card, sd_block_t addr, SD_Data_Block *data) {
	uint8_t result;
	uint8_t args[4];
	uint16_t i=0;

	if (card->State != SD_IDLE) {
		DBG_ERR_printf("SBR failed: Card not in idle state, state is 0x%02x", card->State);
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
	result = SD_SendCommand(card, SD_CMD_READ_SINGLE_BLOCK, args, 0x00);
	if (result != 0x00) {
		DBG_ERR_printf("SBR failed: Bad response to READ_SINGLE_BLOCK - got 0x%02x", result);

		SD_DMA_OnError();

		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		return SD_PHY_ERR;
	}

	// wait for the start block token
	result = 0xff;
	while (result != SD_TOKEN_START_BLOCK && i < SD_BLOCK_TIMEOUT) {
		result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
		i++;
	}
	if (result != SD_TOKEN_START_BLOCK) {
		DBG_ERR_printf("SBR failed: Card did not send block, got 0x%02x", result);

		SD_DMA_OnError();

		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		return SD_PHY_ERR;
	}

	data->StartOffset = 2;
	data->BlockLen = 514;
	SD_DMA_ReceiveBlock(card, data);

	SD_DMA_OnBlockRead();

	card->State = SD_DMA_SBR;
	card->SubState = 0;

	return SD_BUSY;
}

sd_result_t SD_DMA_GetSingleBlockReadResult(SD_Card *card) {
	if (card->State != SD_DMA_SBR) {
		DBG_ERR_printf("SBR failed: Card not in Single Block Read state");
		return SD_FAILED;
	}

	if (SD_DMA_GetTransferComplete(card)) {
		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		card->State = SD_IDLE;

		return SD_SUCCESS;
	} else {
		return SD_BUSY;
	}
}
