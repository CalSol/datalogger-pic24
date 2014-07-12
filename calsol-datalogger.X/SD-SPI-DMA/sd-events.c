/*
 * File:   sd-events.c
 * Author: Ducky
 *
 * Created on July 18, 2011, 1:22 AM
 *
 * Revision History
 * Date			Author	Change
 * 18 Jul 2011	Ducky	Created empty functions.
 * 21 Jul 2011	Ducky	Comment style changes.
 *
 * @file
 * Functions called on certain events, like the beginning of a block read
 * or write operation.
 */

#include "sd-spi-dma.h"

#include "../UserInterface/datalogger-ui-leds.h"

inline void SD_DMA_OnCardDataRead() {
	UI_LED_Pulse(&UI_LED_SD_Read);
}

inline void SD_DMA_OnBlockRead() {
	UI_LED_Pulse(&UI_LED_SD_Read);
}

inline void SD_DMA_OnBlockWrite() {
	UI_LED_Pulse(&UI_LED_SD_Write);
}

inline void SD_DMA_OnError() {
	UI_LED_Pulse(&UI_LED_SD_Error);
}
