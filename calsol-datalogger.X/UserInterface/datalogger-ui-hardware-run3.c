/*
 * File:   datalogger-ui-hardware-run3.c
 * Author: Ducky
 *
 * Created on June 26, 2011, 2:17 PM
 *
 * 21 Jul 2011	Ducky	Added this change history box,
 *						separated Run 2/3 UI code.
 *
 * @file
 * UI hardware abstraction functions for the revision 1.2-rc1 (run 3) board.
 */

#include "../hardware.h"

#include "datalogger-ui-hardware.h"
#include "../I2CDevices/mcp23018.h"

#ifdef HARDWARE_RUN_3

#define DEBUG_UART
//#define DEBUG_UART_DATA
#include "../debug-common.h"

const uint8_t OLATA_Status_Err_Mask = 0b10000000;
const uint8_t OLATA_Status_Oper_Mask = 0b01000000;
const uint8_t OLATA_Status_Wait_Mask = 0b00100000;
const uint8_t OLATB_CAN_Err_Mask = 0b00000100;
const uint8_t OLATB_CAN_TX_Mask = 0b00000001;
const uint8_t OLATB_CAN_RX_Mask = 0b00000010;
const uint8_t OLATB_SD_Err_Mask = 0b00001000;
const uint8_t OLATB_SD_Write_Mask = 0b00100000;
const uint8_t OLATB_SD_Read_Mask = 0b00010000;

/*	Bindings for the 8mm LEDs temporarily used
const uint8_t OLATA_Status_Err_Mask = 0b01000000;
const uint8_t OLATA_Status_Oper_Mask = 0b00100000;
const uint8_t OLATA_Status_Wait_Mask = 0b10000000;
const uint8_t OLATB_CAN_Err_Mask = 0b00000010;
const uint8_t OLATB_CAN_TX_Mask = 0b00000100;
const uint8_t OLATB_CAN_RX_Mask = 0b00000001;
const uint8_t OLATB_SD_Err_Mask = 0b00010000;
const uint8_t OLATB_SD_Write_Mask = 0b00001000;
const uint8_t OLATB_SD_Read_Mask = 0b00100000;
*/

const uint8_t GPIOA_CardDetect_Mask = 0b00000001;
const uint8_t GPIOA_WriteProtect_Mask = 0b00000010;

const uint8_t GPIOB_Unmount_Mask = 0b01000000;
const uint8_t GPIOB_Test_Mask = 0b10000000;

uint8_t GPIO_OLATA = 0;		// Current value of OLATA
uint8_t GPIO_OLATA_Old = 0;	// Last written value of OLATA

uint8_t GPIO_OLATB = 0;		// Current value of OLATB
uint8_t GPIO_OLATB_Old = 0;	// Last written value of OLATB

uint8_t GPIO_GPIOA = 0;		// Last read value of GPA
uint8_t GPIO_GPIOB = 0;		// Last read value of GPB

/**
 * Initializes everything for the user interface, such as setting pin direction
 * and enabling pull-ups.
 */
inline void UI_HW_Initialize() {

	if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_IODIRA, 0b00011111)) {
		DBG_ERR_printf("I2C MCP23018 IODIRA failed");
	}
	if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_IODIRB, 0b11000000)) {
		DBG_ERR_printf("I2C MCP23018 IODIRB failed");
	}

	if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_GPPUA, 0b11111111)) {
		DBG_ERR_printf("I2C MCP23018 GPPUA failed");
	}
	if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_GPPUB, 0b11111111)) {
		DBG_ERR_printf("I2C MCP23018 GPPUB failed");
	}

	LED_FAULT_IO = 0;
	LED_FAULT_TRIS = 0;
}

/**
 * Updates LED states.
 * If the LEDs are controlled through a GPIO expander, this writes the data
 * to the expander.
 * If the LED is directly controlled by the MCU, this does nothing.
 */
inline void UI_HW_LED_Update() {
	if (GPIO_OLATA != GPIO_OLATA_Old) {
		if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_OLATA, ~GPIO_OLATA)) {
			DBG_ERR_printf("I2C MCP23018 OLATA update failed");
		}
		DBG_DATA_printf("I2C MCP23018 OLATA update to %02x", GPIO_OLATA);
		GPIO_OLATA_Old = GPIO_OLATA;
	}


	if (GPIO_OLATB != GPIO_OLATB_Old) {
		if (!MCP23018_SingleRegisterWrite(0b000, MCP23018_ADDR_OLATB, ~GPIO_OLATB)) {
			DBG_ERR_printf("I2C MCP23018 OLATB update failed");
		}
		DBG_DATA_printf("I2C MCP23018 OLATB update to %02x", GPIO_OLATB);
		GPIO_OLATB_Old = GPIO_OLATB;
	}

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
	GPIO_OLATA |= OLATA_Status_Err_Mask;
}

/**
 * Turns off the Status - Error LED.
 */
inline void UI_LED_Status_Error_Off() {
	GPIO_OLATA &= ~OLATA_Status_Err_Mask;
}

/**
 * Turns on the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_On() {
	GPIO_OLATA |= OLATA_Status_Oper_Mask;
}
/**
 * Turns off the Status - Operating (normal condition) LED.
 */
inline void UI_LED_Status_Operate_Off() {
	GPIO_OLATA &= ~OLATA_Status_Oper_Mask;
}

/**
 * Turns on the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_On() {
	GPIO_OLATA |= OLATA_Status_Wait_Mask;
}
/**
 * Turns off the Status - Waiting LED.
 */
inline void UI_LED_Status_Waiting_Off() {
	GPIO_OLATA &= ~OLATA_Status_Wait_Mask;
}

/**
 * Turns on the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_On() {
	GPIO_OLATB |= OLATB_CAN_Err_Mask;
}
/**
 * Turns off the CAN - Error LED.
 */
inline void UI_LED_CAN_Error_Off() {
	GPIO_OLATB &= ~OLATB_CAN_Err_Mask;
}

/**
 * Turns on the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_On() {
	GPIO_OLATB |= OLATB_CAN_RX_Mask;
}
/**
 * Turns off the CAN - RX LED.
 */
inline void UI_LED_CAN_RX_Off() {
	GPIO_OLATB &= ~OLATB_CAN_RX_Mask;
}

/**
 * Turns on the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_On() {
	GPIO_OLATB |= OLATB_CAN_TX_Mask;
}
/**
 * Turns off the CAN - TX LED.
 */
inline void UI_LED_CAN_TX_Off() {
	GPIO_OLATB &= ~OLATB_CAN_TX_Mask;
}

/**
 * Turns on the SD - Error LED.
 */
inline void UI_LED_SD_Error_On() {
	GPIO_OLATB |= OLATB_SD_Err_Mask;
}
/**
 * Turns off the SD - Error LED.
 */
inline void UI_LED_SD_Error_Off() {
	GPIO_OLATB &= ~OLATB_SD_Err_Mask;
}

/**
 * Turns on the SD - Read LED.
 */
inline void UI_LED_SD_Read_On() {
	GPIO_OLATB |= OLATB_SD_Read_Mask;
}
/**
 * Turns off the SD - Read LED.
 */
inline void UI_LED_SD_Read_Off() {
	GPIO_OLATB &= ~OLATB_SD_Read_Mask;
}

/**
 * Turns on the SD - Write LED.
 */
inline void UI_LED_SD_Write_On() {
	GPIO_OLATB |= OLATB_SD_Write_Mask;
}
/**
 * Turns off the SD - Write LED.
 */
inline void UI_LED_SD_Write_Off() {
	GPIO_OLATB &= ~OLATB_SD_Write_Mask;
}

/**
 * Updates switch states.
 * If the switches are controlled through a GPIO expander, this reads the data
 * from the expander.
 * If the switch is directly controlled by the MCU, this does nothing.
 */
inline void UI_Switch_Update() {
	if (!MCP23018_SingleRegisterRead(0b000, MCP23018_ADDR_GPIOA, &GPIO_GPIOA)) {
		DBG_ERR_printf("I2C MCP23018 GPIOA read failed");
	}
	if (!MCP23018_SingleRegisterRead(0b000, MCP23018_ADDR_GPIOB, &GPIO_GPIOB)) {
		DBG_ERR_printf("I2C MCP23018 GPIOB read failed");
	}
}

/**
 * @return The state of the Card Dismount button.
 * @retval 0 Card Dismount button is not pressed.
 * @retval 1 Card Dismount button is pressed.
 */
inline uint8_t UI_Switch_GetCardDismount() {
	return ((GPIO_GPIOB & GPIOB_Unmount_Mask) == 0) ? 1 : 0;
}

/**
 * @return The state of the Test button.
 * @retval 0 Test button is not pressed.
 * @retval 1 Test button is pressed.
 */
inline uint8_t UI_Switch_GetTest() {
	return ((GPIO_GPIOB & GPIOB_Test_Mask) == 0) ? 1 : 0;
	return 0;
}

/**
 * @return The state of the Card Detect switch.
 * @retval 0 There is no card inserted.
 * @retval 1 There is a card inserted.
 */
inline uint8_t UI_Switch_GetCardDetect() {
	return ((GPIO_GPIOA & GPIOA_CardDetect_Mask) == 0) ? 1 : 0;
}

/**
 * @return The state of the Write Protect switch.
 * @retval 0 Write protect is not enabled.
 * @retval 1 Write protect is enabled.
 */
inline uint8_t UI_Switch_GetCardWriteProtect() {
	return ((GPIO_GPIOA & GPIOA_WriteProtect_Mask) == 0) ? 0 : 1;
}

#endif
