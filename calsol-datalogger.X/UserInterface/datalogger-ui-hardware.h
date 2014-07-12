/**
 * datalogger-ui.h
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box.
 *
 * @file
 * This contains functions to abstract away the user interface hardware
 * (like LEDs and switches).
 */

#ifndef DATALOGGER_UI_HARDWARE_H
#define DATALOGGER_UI_HARDWARE_H

#include "../types.h"

/**
 * Initializes everything for the user interface, such as setting pin direction
 * and enabling pull-ups.
 */
inline void UI_HW_Initialize();

/**
 * Updates LED states.
 * If the LEDs are controlled through a GPIO expander, this writes the data
 * to the expander.
 * If the LED is directly controlled by the MCU, this does nothing.
 */
inline void UI_HW_LED_Update();

/**
 * Turns on the Fault LED.
 */
inline void UI_LED_Fault_On();
/**
 * Turns off the Fault LED.
 */
inline void UI_LED_Fault_Off();

/**
 * The status LEDs are:
 * Red - Error
 * Green - Operating normally
 * Blue - Waiting for user
 * Combination of Error and Operating: Warning
 */

/**
 * Turns on the Status - Error LED.
 */
inline void UI_LED_Status_Error_On();
/**
 * Turns off the Status - Error LED.
 */
inline void UI_LED_Status_Error_Off();

/**
 * Turns on the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_On();
/**
 * Turns off the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_Off();

/**
 * Turns on the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_On();
/**
 * Turns off the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_Off();

/**
 * The data activity LEDs are:
 * Red - Error
 * Green - Receiving data
 * Blue - Transmitting data
 * ... and both Receiving and Transmitting can be on at once
 */

/**
 * Turns on the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_On();
/**
 * Turns off the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_Off();

/**
 * Turns on the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_On();
/**
 * Turns off the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_Off();

/**
 * Turns on the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_On();
/**
 * Turns off the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_Off();

/**
 * Turns on the SD - Error LED.
 */
inline void UI_LED_SD_Error_On();
/**
 * Turns off the SD - Error LED.
 */
inline void UI_LED_SD_Error_Off();

/**
 * Turns on the SD - Read LED.
 */
inline void UI_LED_SD_Read_On();
/**
 * Turns off the SD - Read LED.
 */
inline void UI_LED_SD_Read_Off();

/**
 * Turns on the SD - Write LED.
 */
inline void UI_LED_SD_Write_On();
/**
 * Turns off the SD - Write LED.
 */
inline void UI_LED_SD_Write_Off();

/**
 * Switches
 */

/**
 * Updates switch states.
 * If the switches are controlled through a GPIO expander, this reads the data
 * from the expander.
 * If the switch is directly controlled by the MCU, this does nothing.
 */
inline void UI_Switch_Update();

/**
 * @return The state of the Card Dismount button.
 * @retval 0 Card Dismount button is not pressed.
 * @retval 1 Card Dismount button is pressed.
 */
inline uint8_t UI_Switch_GetCardDismount();
/**
 * @return The state of the Test button.
 * @retval 0 Test button is not pressed.
 * @retval 1 Test button is pressed.
 */
inline uint8_t UI_Switch_GetTest();

/**
 * @return The state of the Card Detect switch.
 * @retval 0 There is no card inserted.
 * @retval 1 There is a card inserted.
 */
inline uint8_t UI_Switch_GetCardDetect();
/**
 * @return The state of the Write Protect switch.
 * @retval 0 Write protect is not enabled.
 * @retval 1 Write protect is enabled.
 */
inline uint8_t UI_Switch_GetCardWriteProtect();

#endif
