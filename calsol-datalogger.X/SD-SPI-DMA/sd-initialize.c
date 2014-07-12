/*
 * File:   sd-initialize.c
 * Author: Ducky
 *
 * Created on July 18, 2011, 12:27 AM
 *
 * Revision History
 * Date			Author	Change
 * 24 Jul 2011	Ducky	Initial implementation.
 * 25 Jul 2011	Ducky	Added CSD/CID parsing and dynamic bus speed config.
 *
 * TODOs
 * 25 Jul 2011	Ducky	Wait for start block token in background.
 *						SDHC Support.
 *
 * Card initialization and related (reading CSD, etc) functionality.
 */

#include "sd-defs.h"
#include "sd-spi-dma.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "SD/Init"
#include "../debug-common.h"

const uint8_t SD_Init_NumBytes = 32;	/// Number of idle bytes to send the
										/// card at power-on

#define SD_INIT_SUB_CLOCK	0			/// Sending clocks on power-on
#define SD_INIT_SUB_INIT	1			/// Waiting for card init (ACMD41)
#define SD_INIT_SUB_CID		2			/// Reading card CID
#define SD_INIT_SUB_CSD		3			/// Reading card CSD

uint8_t SD_Null_Argument[4] = {0x00, 0x00, 0x00, 0x00};
uint8_t SD_IfCond_Argument[4] = {0x00, 0x00, 0x01, 0xaa};
uint8_t SD_ACMD41_HCS_Argument[4] = {0x40, 0x00, 0x00, 0x00};

uint16_t SD_TRAN_SPEED_LUT[] = {
	0,	10,	12,	13,
	15,	20,	25,	30,
	35,	40,	45,	50,
	55,	60,	70,	80
};
char *SD_MONTH_LUT[] = {
	"Unk",
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec"
};

// Known MIDs:
// 3 SanDisk
//
//

uint8_t SD_ParseCID(SD_Card *card, SD_Data_Block *csdBlock);
uint8_t SD_ParseCSD(SD_Card *card, SD_Data_Block *csdBlock);

sd_result_t SD_Initialize(SD_Card *card) {
	uint8_t i=0;

	card->State = SD_INITIALIZING;
	card->SubState = 0;

	SD_DMA_Initialize(card);

	// Send the required 74 clock cycles for power on through DMA
	uint8_t *ptr = card->DataBlocks[0].Data;
	for (i=0;i<SD_Init_NumBytes;i++) {
		*ptr = SD_IDLE_BYTE;
		ptr++;
	}
	card->DataBlocks[0].StartOffset = 0;
	card->DataBlocks[0].BlockLen = SD_Init_NumBytes;

	card->TimeoutCount = 0;

	DBG_DATA_printf("Sending clocks on power-on");

	SD_SPI_Open(card);

	SD_DMA_SendBlock(card, &card->DataBlocks[0]);

	return SD_BUSY;
}

sd_result_t SD_GetInitializeResult(SD_Card *card) {
	if (card->State != SD_INITIALIZING) {
		SD_SPI_Close(card);

		card->State = SD_UNINITIALIZED;
		return SD_INITIALIZE_FAILED;
	}

	if (card->SubState == 0) {
		if (SD_DMA_GetTransferComplete(card)) {
			uint8_t result[5];

			if (*card->RXBuffer != SD_IDLE_BYTE) {
				card->TimeoutCount ++;
				if (card->TimeoutCount > SD_INITIALIZE_MAX_TRIES) {
					DBG_ERR_printf("Warning: card did not return idle, got 0x%02x", *card->RXBuffer);
					//SD_SPI_Close(card);
					//card->State = SD_UNINITIALIZED;
					//return SD_INITIALIZE_FAILED;
				} else {
					DBG_DATA_printf("More clocks on power-on");
					SD_DMA_SendBlock(card, &card->DataBlocks[0]);
					return SD_BUSY;
				}
			}

			// Terminate previous operation
			SD_SPI_Close(card);

			// Try CMD0 (GO_IDLE_STATE)
			SD_SPI_Open(card);
			result[0] = SD_SendCommand(card, SD_CMD_GO_IDLE_STATE,
					SD_Null_Argument, 0x95);
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			DBG_DATA_printf("GO_IDLE_STATE -> 0x%02x", result[0]);
			if (result[0] != SD_R1_IDLE_STATE) {
				DBG_ERR_printf("Failure: Bad response to GO_IDLE_STATE, got 0x%02x", result[0]);
				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}

			// Try CMD8 (SEND_IF_COND) to determine if card is Ver2.00 or later
			SD_SPI_Open(card);
			result[0] = SD_SendCommand(card, SD_CMD_SEND_IF_COND,
					SD_IfCond_Argument, 0x87);

			if (result[0] == (SD_R1_ILLEGAL_COMMAND | SD_R1_IDLE_STATE)) {
				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				DBG_DATA_printf("SEND_IF_COND -> 0x%02x", result[0]);
				DBG_DATA_printf("Detected Ver1.xx card");

				// Ver 1.x SD Card
				card->Ver2SDCard = 0;
				card->SDHC = 0;
			} else if (result[0] == SD_R1_IDLE_STATE) {
				result[1] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
				result[2] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
				result[3] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
				result[4] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);

				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				DBG_DATA_printf("SEND_IF_COND -> 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
						result[0], result[1], result[2], result[3], result[4]);
				DBG_DATA_printf("Detected Ver2.00 or later card");

				// Ver 2.00 or later SD Card
				card->Ver2SDCard = 1;
				card->CmdVer = result[1] & SD_R7_B2_COMMAND_VERSION;

				if (result[4] != 0xaa) {
					// Bad check pattern
					DBG_ERR_printf("Failure: Bad check pattern in SEND_IF_COND response, got 0x%02x", result[4]);
					card->State = SD_UNINITIALIZED;
					SD_DMA_OnError();
					return SD_INITIALIZE_FAILED;
				} else if ((result[3] & SD_R7_B4_VOLTAGE_ACCEPTED) != 0x01) {
					// Incompatible voltage range
					DBG_ERR_printf("Failure: Incompatible voltage range in SEND_IF_COND response, got 0x%02x", result[3]);
					card->State = SD_UNINITIALIZED;
					return SD_INITIALIZE_NOSUPPORT;
				}
			} else {
				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				// Bad response, initialization failed
				DBG_DATA_printf("SEND_IF_COND -> 0x%02x", result[0]);
				DBG_ERR_printf("Failure: Bad response to SEND_IF_COND, got 0x%02x", result[0]);

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}

			// Send CMD58 (READ_OCR)
			SD_SPI_Open(card);
			result[0] = SD_SendCommand(card, SD_CMD_READ_OCR,
					SD_Null_Argument, 0x00);
			result[1] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[2] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[3] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[4] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			DBG_DATA_printf("READ_OCR -> 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
					result[0], result[1], result[2], result[3], result[4]);

			if (result[0] != SD_R1_IDLE_STATE) {
				DBG_ERR_printf("Failure: Bad response to READ_OCR, got 0x%02x", result[0]);
				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}
			if ((result[2] & 0b01111000) == 0) {
				DBG_ERR_printf("Failure: Incompatible voltage range in READ_OCR response, got 0x%02x", result[2]);
				card->State = SD_UNINITIALIZED;
				return SD_INITIALIZE_NOSUPPORT;
			}

			DBG_DATA_printf("Awaiting initialization");

			card->SubState = 1;
			card->TimeoutCount = 0;
		} else {
			return SD_BUSY;
		}
	}
	if (card->SubState == 1) {
		uint8_t result;
		uint16_t i=0;
		// Attempt initialization
		SD_SPI_Open(card);
		SD_SendCommand(card, SD_CMD_APP_CMD, SD_Null_Argument, 0x00);
		SD_SPI_Terminate(card);
		result = SD_SendCommand(card, SD_ACMD_SD_SEND_OP_COND,
				card->Ver2SDCard?SD_ACMD41_HCS_Argument:SD_Null_Argument, 0x00);
		SD_SPI_Terminate(card);
		SD_SPI_Close(card);

		if (result == 0x00) {
			DBG_DATA_printf("SD_SEND_OP_COND -> 0x%02x", result);
			// Continue execution past if, read CSD / CID
		} else if (result == SD_R1_IDLE_STATE) {
			DBG_SPAM_printf("SD_SEND_OP_COND -> 0x%02x", result);
			card->TimeoutCount++;
			if (card->TimeoutCount > SD_INITIALIZE_MAX_TRIES) {
				card->State = SD_UNINITIALIZED;
				return SD_INITIALIZE_TIMEOUT;
			} else {
				return SD_BUSY;
			}
		} else {
			DBG_DATA_printf("SD_SEND_OP_COND -> 0x%02x", result);
			DBG_ERR_printf("Failure: Bad response to ACMD41, got 0x%02x", result);
			
			card->State = SD_UNINITIALIZED;
			SD_DMA_OnError();
			return SD_INITIALIZE_FAILED;
		}

		// If a Ver2.0+ card, send Get CCS
		if (card->Ver2SDCard) {
			uint8_t result[5];
			// Send CMD58 to get CCS
			SD_SPI_Open(card);
			result[0] = SD_SendCommand(card, SD_CMD_READ_OCR,
					SD_Null_Argument, 0x00);
			result[1] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[2] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[3] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			result[4] = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			DBG_DATA_printf("READ_OCR (Get CCS) -> 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
					result[0], result[1], result[2], result[3], result[4]);

			if (result[1] & 0b01000000) {
				DBG_DATA_printf("Detected SDHC card");
				card->SDHC = 1;
			} else {
				DBG_DATA_printf("Detected non-SDHC card");
				card->SDHC = 0;
			}
		}

		// Re-initialize SPI in fast mode at 25MHz
		SD_DMA_InitializeFast(card, 25);

		// Read CID after initialization
		SD_SPI_Open(card);
		result = SD_SendCommand(card, SD_CMD_SEND_CID, SD_Null_Argument, 0x00);
		if (result != 0x00) {
			DBG_ERR_printf("Failure: Bad response to SEND_CID, got 0x%02x", result);
			
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			card->State = SD_UNINITIALIZED;
			SD_DMA_OnError();
			return SD_INITIALIZE_FAILED;
		}
		// wait for the start block token
		result = 0xff;
		while (result != SD_TOKEN_START_BLOCK && i < SD_CMD_TIMEOUT) {
			result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
			i++;
		}
		if (result != SD_TOKEN_START_BLOCK) {
			DBG_ERR_printf("Failure: Card did not send CID, got 0x%02x", result);

			SD_SPI_Terminate(card);
			SD_SPI_Close(card);

			card->State = SD_UNINITIALIZED;
			SD_DMA_OnError();
			return SD_INITIALIZE_FAILED;
		}

		card->DataBlocks[0].BlockLen = 32;
		SD_DMA_ReceiveBlock(card, &card->DataBlocks[0]);

		SD_DMA_OnCardDataRead();

		card->SubState = 2;
	}
	if (card->SubState == 2) {
		uint8_t result;
		uint16_t i=0;
		if (SD_DMA_GetTransferComplete(card)) {
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);
			
			if (SD_ParseCID(card, &card->DataBlocks[0])) {
				DBG_DATA_printf("Parsed CID:");
				DBG_DATA_printf("  > MID: %u, OID: %c%c",
						card->MID, card->OID[0], card->OID[1]);
				DBG_DATA_printf("  > PNM: %c%c%c%c%c, PRV: %u.%u",
						card->PNM[0], card->PNM[1], card->PNM[2], card->PNM[3], card->PNM[4],
						(card->PRV >> 4) & 0b1111, (card->PRV >> 0) & 0b1111);
				DBG_DATA_printf("  > PSN: 0x%08lx, MDT: %s %u",
						card->PSN,
						SD_MONTH_LUT[(card->MDT >> 00) & 0b1111],
						(uint16_t)((card->MDT >> 4) & 0xff) + 2000);
			} else {
				DBG_ERR_printf("Failure: Unable to parse CID");

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}

			// Read CSD
			SD_SPI_Open(card);
			result = SD_SendCommand(card, SD_CMD_SEND_CSD, SD_Null_Argument, 0x00);
			if (result != 0x00) {
				DBG_ERR_printf("Failure: Bad response to SEND_CSD, got 0x%02x", result);

				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}
			// wait for the start block token
			result = 0xff;
			while (result != SD_TOKEN_START_BLOCK && i < SD_CMD_TIMEOUT) {
				result = SD_SPI_Transfer(card, SD_DUMMY_BYTE);
				i++;
			}
			if (result != SD_TOKEN_START_BLOCK) {
				DBG_ERR_printf("Failure: Card did not send CSD, got 0x%02x", result);

				SD_SPI_Terminate(card);
				SD_SPI_Close(card);

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}

			card->DataBlocks[0].BlockLen = 32;
			SD_DMA_ReceiveBlock(card, &card->DataBlocks[0]);

			SD_DMA_OnCardDataRead();

			card->SubState = 3;
		} else {
			return SD_BUSY;
		}
	}
	if (card->SubState == 3) {
		if (SD_DMA_GetTransferComplete(card)) {
			SD_SPI_Terminate(card);
			SD_SPI_Close(card);
			
			if (SD_ParseCSD(card, &card->DataBlocks[0])) {
				DBG_DATA_printf("Parsed CSD:");
				DBG_DATA_printf("  > Calculated capacity: %lu * %u", card->BlockCapacity, card->BlockSize);
			} else {
				DBG_ERR_printf("Failure: Unable to parse CSD");

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_FAILED;
			}

			// Reinitialize at maximum speed reported by card
			// Get transmission speed in MHz
			uint16_t transSpeed = SD_TRAN_SPEED_LUT[(card->TRAN_SPEED >> 3) & 0b1111];
			switch ((card->TRAN_SPEED >> 0) & 0b111) {
				default:
				case 0:		transSpeed /= 100;		break;
				case 1:		transSpeed /= 10;		break;
				case 2:		;						break;
				case 3:		transSpeed *= 10;		break;
			}
			DBG_DATA_printf("Reinitialize SPI bus at %u MHz", transSpeed);
			SD_DMA_InitializeFast(card, transSpeed);

			if (card->BlockSize > SD_DATA_BLOCK_LENGTH + 4) {
				DBG_ERR_printf("Failed: Card block size exceeds DMA buffer size, block size is %u", card->BlockSize);

				card->State = SD_UNINITIALIZED;
				SD_DMA_OnError();
				return SD_INITIALIZE_NOSUPPORT;
			}
			DBG_DATA_printf("Card block size: %u", card->BlockSize);

			card->State = SD_IDLE;
			return SD_SUCCESS;
		} else {
			return SD_BUSY;
		}
	}

	// Code should never reach this
	DBG_ERR_printf("Failed: Bad substate 0x%02x", card->SubState);
	return SD_FAILED;
}

/**
 * Parse the card's CID block received in a data block.
 * @param card SD Card structure.
 * @param cidBlock SD Data Block containing the received CID.
 * @return Success or failure.
 * @retval 1 Success - CID loaded successfully into /a card.
 * @retval 0 Failure - error parsing CID, data in /a card not valid.
 */
uint8_t SD_ParseCID(SD_Card *card, SD_Data_Block *cidBlock) {
	uint8_t *cidData = cidBlock->Data;

	card->MID = cidData[0];
	
	card->OID[0] = cidData[1];
	card->OID[1] = cidData[2];

	card->PNM[0] = cidData[3];
	card->PNM[1] = cidData[4];
	card->PNM[2] = cidData[5];
	card->PNM[3] = cidData[6];
	card->PNM[4] = cidData[7];

	card->PRV = cidData[8];

	card->PSN = cidData[9];	card->PSN = card->PSN << 8;
	card->PSN |= cidData[10];	card->PSN = card->PSN << 8;
	card->PSN |= cidData[11];	card->PSN = card->PSN << 8;
	card->PSN |= cidData[12];

	card->MDT = cidData[13];	card->MDT = card->MDT << 8;
	card->MDT |= cidData[14];

	return 1;
}

/**
 * Parse the card's CSD block received in a data block.
 * @param card SD Card structure.
 * @param csdBlock SD Data Block containing the received CSD.
 * @return Success or failure.
 * @retval 1 Success - CSD loaded successfully into /a card.
 * @retval 0 Failure - error parsing CSD, data in /a card not valid.
 */
uint8_t SD_ParseCSD(SD_Card *card, SD_Data_Block *csdBlock) {
	uint8_t *csdData = csdBlock->Data;

	if (csdData[0] == 0x00) {
		uint32_t C_SIZE;
		uint8_t C_SIZE_MULT;
		uint8_t READ_BL_LEN;

		card->BlockSize = 512;

		card->TRAN_SPEED = csdData[3];

		C_SIZE = (csdData[6] >> 0) & 0b11;		C_SIZE = C_SIZE << 8;
		C_SIZE |= csdData[7];					C_SIZE = C_SIZE << 2;
		C_SIZE |= (csdData[8] >> 6) & 0b11;

		C_SIZE_MULT = (csdData[9] >> 0) & 0b11;	C_SIZE_MULT = C_SIZE_MULT << 1;
		C_SIZE_MULT |= (csdData[10] >> 7) & 0b1;

		READ_BL_LEN = (csdData[5] >> 0) & 0b1111;

		uint32_t MULT = 1 << (C_SIZE_MULT+2);
		uint32_t BLOCKNR = (C_SIZE + 1) * MULT;
		uint32_t BLOCK_LEN = 1 << READ_BL_LEN;
		
		card->BlockCapacity = BLOCKNR * BLOCK_LEN / card->BlockSize;

		return 1;
	} else if (csdData[0] == 0x40) {
		uint32_t C_SIZE;

		card->BlockSize = 512;

		card->TRAN_SPEED = csdData[3];
		C_SIZE = (csdData[7] >> 0) & 0b111111;	C_SIZE = C_SIZE << 6;
		C_SIZE |= csdData[8];					C_SIZE = C_SIZE << 8;
		C_SIZE |= csdData[9];
		C_SIZE += 1;
		C_SIZE <<= 10;

		card->BlockCapacity = C_SIZE;

		return 1;
	} else {
		DBG_ERR_printf("ParseCSD failed: Unsupported CSD_STRUCTURE version, got 0x%02x", csdData[0])
		return 0;
	}
}
