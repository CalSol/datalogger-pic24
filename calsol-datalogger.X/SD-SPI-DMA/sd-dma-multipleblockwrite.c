/*
 * File:   sd-dma-multipleblockwrite.c
 * Author: Ducky
 *
 * Created on July 26, 2011, 8:08 PM
 *
 * Revision History
 * Date			Author	Change
 * 26 Jul 2011	Ducky	Initial implementation.
 *
 * TODOs
 * 26 Jul 2011	Ducky	SDHC Support.
 * 25 Jul 2011	Ducky	More robust error handling on errors.
 *
 * Multiple Block Write operation functionality.
 */

#include "sd-defs.h"
#include "sd-spi-dma.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
#define DBG_MODULE "SD/MBW"
#include "../debug-common.h"
#include "../debug-log.h"

sd_result_t SD_DMA_MBW_Begin(SD_Card *card, sd_block_t addr) {
	uint8_t result;
	uint8_t args[4];

	if (card->State != SD_IDLE) {
		DBG_ERR_printf("MBW Begin failed: Card not in idle state");
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
	result = SD_SendCommand(card, SD_CMD_WRITE_MULTIPLE_BLOCK, args, 0x00);
	if (result != 0x00) {
		DBG_ERR_printf("MBW failed: Bad response to WRITE_MULTIPLE_BLOCK - got 0x%02x", result);

		SD_DMA_OnError();

		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		return SD_PHY_ERR;
	}

	// send block
	card->State = SD_DMA_MBW_IDLE;
	card->SubState = 0;

	return SD_SUCCESS;
}

sd_result_t SD_DMA_MBW_SendBlock(SD_Card *card, SD_Data_Block *data) {
	if (card->State != SD_DMA_MBW_IDLE) {
		DBG_ERR_printf("MBW Send Block failed: Card not in MBW Idle state");
		return SD_FAILED;
	}

	// send block
	data->StartOffset = 0;
	data->BlockLen = 517;
	data->Data[0] = SD_IDLE_BYTE;
	data->Data[1] = SD_TOKEN_MBW_START_BLOCK;
	data->Data[card->BlockSize + 2] = 0x00;
	data->Data[card->BlockSize + 3] = 0x00;
	data->Data[card->BlockSize + 4] = SD_IDLE_BYTE;
	SD_DMA_SendBlock(card, data);

	SD_DMA_OnBlockWrite();

	card->State = SD_DMA_MBW_SENDING;
	card->SubState = 0;

	return SD_BUSY;
}

sd_result_t SD_DMA_MBW_GetSendBlockResult(SD_Card *card) {
	if (card->State != SD_DMA_MBW_SENDING) {
		DBG_ERR_printf("MBW Send Block failed: Card not in MBW Sending state");
		return SD_FAILED;
	}

	if (card->SubState == 0) {
		if (SD_DMA_GetTransferComplete(card)) {
			uint8_t result;
			uint16_t timeout = 0;

			result = *card->RXBuffer;

			while ((result & 0b00010001) != 0b00000001) {
				if (timeout == 0) {	
					WriteDebugLog(DBG_LOG_OP_MBW_LATEDATARESP, 0, NULL);
					DBG_ERR_printf("MBW Send Block: Late data response token, got 0x%02x", result);
				} else if (timeout > 1024) {
					card->State = SD_DMA_MBW_IDLE;

					DBG_ERR_printf("MBW Send Block failed: No data response token (timeout)");

					SD_DMA_OnError();

					return SD_PHY_ERR;
				}
				timeout++;
				result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			}

			if ((result & 0b00001110) == 0b00000100) {
				card->SubState = 1;
			} else {
				card->State = SD_DMA_MBW_IDLE;

				DBG_ERR_printf("MBW Send Block failed: Bad data response token - got 0x%02x", result);

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
			card->State = SD_DMA_MBW_IDLE;

			return SD_SUCCESS;
		} else {
			return SD_BUSY;
		}
	}

	// Code should never reach this
	DBG_ERR_printf("MBW failed: Bad substate 0x%02x", card->SubState);
	return SD_FAILED;
}

sd_result_t SD_DMA_MBW_Terminate(SD_Card *card) {
	if (card->State != SD_DMA_MBW_IDLE) {
		DBG_ERR_printf("MBW Terminate failed: Card not in MBW Idle state");
		return SD_FAILED;
	}

	SD_SPI_Transfer(card, SD_TOKEN_MBW_STOP_TRAN);

	card->State = SD_DMA_MBW_TERMINATING;

	return SD_BUSY;
}

sd_result_t SD_DMA_MBW_GetTerminateStatus(SD_Card *card) {
	uint8_t result = 0x01;

	if (card->State != SD_DMA_MBW_TERMINATING) {
		DBG_ERR_printf("MBW Terminate failed: Card not in MBW Terminating state");
		return SD_FAILED;
	}

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
