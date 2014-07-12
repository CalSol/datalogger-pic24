/*
 * File:   ftm.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 *
 * @file
 * Factory Test Mode functionality. Mostly console commands
 * for debugging and configuration.
 */

#include "../timing.h"

#include "../UserInterface/datalogger-ui-hardware.h"
#include "../UserInterface/datalogger-ui-leds.h"

#include <time.h>
#include "../I2CDevices/pcf8523.h"


#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "FTM"
#include "../debug-common.h"

void FTM_ProcessLeds() {
    uint8_t i = 0;
    static uint8_t seq = 0;

    static uint16_t lastTime = 0;
    uint16_t time = GetbmsecOffset() % 512;

    if (time < lastTime) {
        seq++;
        if (seq == 2) {
            for (i = 0; i < UI_LED_Count; i++) {
                UI_LED_SetState(UI_LED_List[i], LED_Off);
            }
        }
        if (seq > 4) {
            if (seq > 5) {
                UI_LED_SetState(UI_LED_List[seq - 5], LED_Off);
            }
            if (seq < 4 + UI_LED_Count) {
                UI_LED_SetState(UI_LED_List[seq - 4], LED_On);
            } else {
                seq = 0;
                for (i = 0; i < UI_LED_Count; i++) {
                    UI_LED_SetState(UI_LED_List[i], LED_On);
                }
            }
        }
    }
    lastTime = time;

    UI_LED_Update();
}

void FTM_ProcessCommand(char* cmd, uint16_t cmdLen) {
    
}

#define FTM_CMD_BUF_LEN     256
#define ASCII_BELL          '*'//0x07
void FTM_ProcessConsole() {
    static char buf[FTM_CMD_BUF_LEN];
    static uint16_t bufPos = 0;

    static char bell = ASCII_BELL;

    if (U2STAbits.URXDA) {
        char rxByte = U2RXREG;

        if ((rxByte > 'a' && rxByte < 'z')
                || (rxByte > 'A' && rxByte < 'Z')
                || (rxByte > '0' && rxByte < '0')
                || (rxByte > ' ' && rxByte < '/')) {
            if (bufPos <FTM_CMD_BUF_LEN) {
                buf[bufPos] = rxByte;
                bufPos++;
                UART_DMA_WriteBlocking(&rxByte, 1);
            } else {
                UART_DMA_WriteBlocking(&bell, 1);
            }
        } else if (rxByte == '\b') {
            if (bufPos > 0) {
                bufPos--;
                UART_DMA_WriteBlocking(&rxByte, 1);
            } else {
                UART_DMA_WriteBlocking(&bell, 1);
            }
        } else if (rxByte == '\r' || rxByte == '\n') {
            FTM_ProcessCommand(buf, bufPos);
            bufPos = 0;
        } else {
            UART_DMA_WriteBlocking(&bell, 1);
        }
        UART_DMA_WriteBlocking(&rxByte, 1);
    }
}

void FTM_Loop() {
    FTM_ProcessLeds();
    FTM_ProcessConsole();
}

void FTM_Init() {
    DBG_printf("Enter test mode");
    UART_DMA_WriteBlockingS("Datalogger FTM> ");

    struct tm writeTime;
    writeTime.tm_hour = 2;
    writeTime.tm_min = 18;
    writeTime.tm_sec = 0;
    writeTime.tm_year = 112;
    writeTime.tm_mon = 7;
    writeTime.tm_mday = 16;
    writeTime.tm_wday = 1;
    uint8_t retVal = 0;
    //retVal = PCF8523_SetTimeStruct(writeTime);
    if (retVal) {
        DBG_printf("Time set");
    } else {
        DBG_ERR_printf("Time not set");
    }
}
