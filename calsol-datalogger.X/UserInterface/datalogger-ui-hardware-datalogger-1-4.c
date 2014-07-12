/*
 * File:   datalogger-ui-hardware-datalogger-1-4.c
 * Author: Ducky
 *
 * 02 Jun 2012	Ducky	Added UI code for the 1.4 board.
 *
 * @file
 * UI hardware abstraction functions for the revision 1.4-rc1 (run 4) board.
 */

#include "../hardware.h"

#include "datalogger-ui-hardware.h"

#ifdef HARDWARE_DATALOGGER_1_4

const uint8_t Stat_RX_Mask = 0b00000001;
const uint8_t Stat_TX_Mask = 0b00000010;

uint8_t CAN_Stat = 0;
uint8_t SD_Stat = 0;

inline void UI_HW_Initialize() {
    LED_STAT_RED_TRIS = 0;
    LED_STAT_GRN_TRIS = 0;
    LED_STAT_BLU_TRIS = 0;
    LED_CAN_RED_TRIS = 0;
    LED_CAN_GRN_TRIS = 0;
    LED_SD_RED_TRIS = 0;
    LED_SD_GRN_TRIS = 0;

    BTN_TEST_TRIS = 1;
    BTN_TEST_CNPU = 1;
    BTN_DISMOUNT_TRIS = 1;
    BTN_DISMOUNT_CNPU = 1;

    SD_CD_TRIS = 1;
    SD_CD_CNPU = 1;
    SD_WP_TRIS = 1;
    SD_WP_CNPU = 1;
}

inline void UI_HW_LED_Update() {
    // Does nothing - LED IO's are on-chip.
}

inline void UI_LED_Fault_On() {
    // 1.4 board has no fault LED
}

inline void UI_LED_Fault_Off() {
    // 1.4 board has no fault LED
}

inline void UI_LED_Status_Error_On() {
    LED_STAT_RED_IO = LED_ON;
}

inline void UI_LED_Status_Error_Off() {
    LED_STAT_RED_IO = LED_OFF;
}

inline void UI_LED_Status_Operate_On() {
    LED_STAT_GRN_IO = LED_ON;
}

inline void UI_LED_Status_Operate_Off() {
    LED_STAT_GRN_IO = LED_OFF;
}

inline void UI_LED_Status_Waiting_On() {
    LED_STAT_BLU_IO = LED_ON;
}

inline void UI_LED_Status_Waiting_Off() {
    LED_STAT_BLU_IO = LED_OFF;
}

inline void UI_LED_CAN_Error_On() {
    LED_CAN_RED_IO = LED_ON;
}

inline void UI_LED_CAN_Error_Off() {
    LED_CAN_RED_IO = LED_OFF;
}

inline void UI_LED_CAN_RX_On() {
    CAN_Stat |= Stat_RX_Mask;
    LED_CAN_GRN_IO = LED_ON;
}

inline void UI_LED_CAN_RX_Off() {
    CAN_Stat &= ~Stat_RX_Mask;
    if (CAN_Stat == 0) {
        LED_CAN_GRN_IO = LED_OFF;
    }
}

inline void UI_LED_CAN_TX_On() {
    CAN_Stat |= Stat_TX_Mask;
    LED_CAN_GRN_IO = LED_ON;
}

inline void UI_LED_CAN_TX_Off() {
    CAN_Stat &= ~Stat_TX_Mask;
    if (CAN_Stat == 0) {
        LED_CAN_GRN_IO = LED_OFF;
    }
}

inline void UI_LED_SD_Error_On() {
    LED_SD_RED_IO = LED_ON;
}

inline void UI_LED_SD_Error_Off() {
    LED_SD_RED_IO = LED_OFF;
}

inline void UI_LED_SD_Read_On() {
    SD_Stat |= Stat_RX_Mask;
    LED_SD_GRN_IO = LED_ON;
}

inline void UI_LED_SD_Read_Off() {
    SD_Stat &= ~Stat_RX_Mask;
    if (SD_Stat == 0) {
        LED_SD_GRN_IO = LED_OFF;
    }
}

inline void UI_LED_SD_Write_On() {
    SD_Stat |= Stat_TX_Mask;
    LED_SD_GRN_IO = LED_ON;
}

inline void UI_LED_SD_Write_Off() {
    SD_Stat &= ~Stat_TX_Mask;
    if (SD_Stat == 0) {
        LED_SD_GRN_IO = LED_OFF;
    }
}

inline void UI_Switch_Update() {
    // Does nothing - button IO's are on-chip.
}

inline uint8_t UI_Switch_GetCardDismount() {
    return !BTN_DISMOUNT_IO;
}

inline uint8_t UI_Switch_GetTest() {
    return !BTN_TEST_IO;
}

inline uint8_t UI_Switch_GetCardDetect() {
    return !SD_CD_IO;
}

inline uint8_t UI_Switch_GetCardWriteProtect() {
    return !SD_WP_IO;
}

#endif
