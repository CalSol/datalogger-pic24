/*
 * File:   datalogger-ui-hardware-canbridge.c
 * Author: Ducky
 *
 * Created on June 26, 2011, 2:17 PM
 *
 * Revision History
 * Date			Author	Change
 * 24 Sep 2011	Ducky	Added code for CANBridge Datalogger,
 *
 * @file
 * UI hardware abstraction functions for the CANBridge 1.0 board.
 */

#include "../hardware.h"

#include "datalogger-ui-hardware.h"

#ifdef HARDWARE_CANBRIDGE

//#define DEBUG_UART
//#define DEBUG_UART_DATA
#include "../debug-common.h"

const uint8_t Stat_RX_Mask = 0b00000001;
const uint8_t Stat_TX_Mask = 0b00000010;

uint8_t CAN_Stat = 0;
uint8_t SD_Stat = 0;

/**
 * Initializes everything for the user interface, such as setting pin direction
 * and enabling pull-ups.
 */
inline void UI_HW_Initialize() {
	LED_FAULT_IO = 0;
	LED_FAULT_TRIS = 0;

	LED_STAT1_IO = 0;
	LED_STAT1_TRIS = 0;

	LED_STAT2_IO = 0;
	LED_STAT2_TRIS = 0;
}

/**
 * Updates LED states.
 * If the LEDs are controlled through a GPIO expander, this writes the data
 * to the expander.
 * If the LED is directly controlled by the MCU, this does nothing.
 */
inline void UI_HW_LED_Update() {
}

/**
 * Turns on the Fault LED.
 */
inline void UI_LED_Fault_On() {
	LED_FAULT_IO = 1;
}
/**
 * Turns off the Fault LED.
 */
inline void UI_LED_Fault_Off() {
	LED_FAULT_IO = 0;
}

/**
 * Turns on the Status - Error LED.
 */
inline void UI_LED_Status_Error_On() {
}

/**
 * Turns off the Status - Error LED.
 */
inline void UI_LED_Status_Error_Off() {
}

/**
 * Turns on the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_On() {
}
/**
 * Turns off the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_Off() {
}

/**
 * Turns on the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_On() {

}
/**
 * Turns off the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_Off() {

}

/**
 * Turns on the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_On() {
}
/**
 * Turns off the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_Off() {
}

/**
 * Turns on the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_On() {
	CAN_Stat |= Stat_RX_Mask;
	LED_STAT1_IO = 1;
}
/**
 * Turns off the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_Off() {
	CAN_Stat &= ~Stat_RX_Mask;
	if (CAN_Stat == 0) {
		LED_STAT1_IO = 0;
	}
}

/**
 * Turns on the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_On() {
	CAN_Stat |= Stat_TX_Mask;
	LED_STAT1_IO = 1;
}
/**
 * Turns off the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_Off() {
	CAN_Stat &= ~Stat_TX_Mask;
	if (CAN_Stat == 0) {
		LED_STAT1_IO = 0;
	}
}

/**
 * Turns on the SD - Error LED.
 */
inline void UI_LED_SD_Error_On() {
}
/**
 * Turns off the SD - Error LED.
 */
inline void UI_LED_SD_Error_Off() {
}

/**
 * Turns on the SD - Read LED.
 */
inline void UI_LED_SD_Read_On() {
	SD_Stat |= Stat_RX_Mask;
	LED_STAT2_IO = 1;
}
/**
 * Turns off the SD - Read LED.
 */
inline void UI_LED_SD_Read_Off() {
	SD_Stat &= ~Stat_RX_Mask;
	if (SD_Stat == 0) {
		LED_STAT2_IO = 0;
	}
}

/**
 * Turns on the SD - Write LED.
 */
inline void UI_LED_SD_Write_On() {
	SD_Stat |= Stat_TX_Mask;
	LED_STAT2_IO = 1;
}
/**
 * Turns off the SD - Write LED.
 */
inline void UI_LED_SD_Write_Off() {
	SD_Stat &= ~Stat_TX_Mask;
	if (SD_Stat == 0) {
		LED_STAT2_IO = 0;
	}
}

/**
 * Updates switch states.
 * If the switches are controlled through a GPIO expander, this reads the data
 * from the expander.
 * If the switch is directly controlled by the MCU, this does nothing.
 */
inline void UI_Switch_Update() {
}

/**
 * @return The state of the Card Dismount button.
 * @retval 0 Card Dismount button is not pressed.
 * @retval 1 Card Dismount button is pressed.
 */
inline uint8_t UI_Switch_GetCardDismount() {
	return 0;
}

/**
 * @return The state of the Test button.
 * @retval 0 Test button is not pressed.
 * @retval 1 Test button is pressed.
 */
inline uint8_t UI_Switch_GetTest() {
	return 0;
}

/**
 * @return The state of the Card Detect switch.
 * @retval 0 There is no card inserted.
 * @retval 1 There is a card inserted.
 */
inline uint8_t UI_Switch_GetCardDetect() {
	return 1;
}

/**
 * @return The state of the Write Protect switch.
 * @retval 0 Write protect is not enabled.
 * @retval 1 Write protect is enabled.
 */
inline uint8_t UI_Switch_GetCardWriteProtect() {
	return 0;
}

#endif
