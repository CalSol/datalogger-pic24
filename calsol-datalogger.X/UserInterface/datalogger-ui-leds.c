/*
 * File:   datalogger-ui-leds.c
 * Author: Ducky
 *
 * Created on July 9, 2011, 9:23 PM
 *
 * Revision History
 * 09 Jul 2011	Ducky	File creation.
 * 23 Jul 2011	Ducky	Initial implementation.
 *
 * @file
 * State-based LED code, including functionality for pulsing.
 */

#include "datalogger-ui-hardware.h"

#include "datalogger-ui-leds.h"

#include "../timing.h"

#define DEBUG_UART
//#define DEBUG_UART_DATA
#include "../debug-common.h"

#define UI_LED_DEFAULT_BLINK	64
#define UI_LED_DEFAULT_ON		32

UI_LED UI_LED_Fault = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_Fault_On, &UI_LED_Fault_Off};

UI_LED UI_LED_Status_Error = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_Status_Error_On, &UI_LED_Status_Error_Off};
UI_LED UI_LED_Status_Operate = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_Status_Operate_On, &UI_LED_Status_Operate_Off};
UI_LED UI_LED_Status_Waiting = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_Status_Waiting_On, &UI_LED_Status_Waiting_Off};

UI_LED UI_LED_CAN_Error = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_CAN_Error_On, &UI_LED_CAN_Error_Off};
UI_LED UI_LED_CAN_RX = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_CAN_RX_On, &UI_LED_CAN_RX_Off};
UI_LED UI_LED_CAN_TX = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_CAN_TX_On, &UI_LED_CAN_TX_Off};

UI_LED UI_LED_SD_Error = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_SD_Error_On, &UI_LED_SD_Error_Off};
UI_LED UI_LED_SD_Read = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_SD_Read_On, &UI_LED_SD_Read_Off};
UI_LED UI_LED_SD_Write = {LED_Off, UI_LED_DEFAULT_BLINK, UI_LED_DEFAULT_ON, 0,
	&UI_LED_SD_Write_On, &UI_LED_SD_Write_Off};

uint8_t UI_LED_Count = 10;
UI_LED *UI_LED_List[] = {
	&UI_LED_Fault,
	
	&UI_LED_Status_Error,
	&UI_LED_Status_Operate,
	&UI_LED_Status_Waiting,

	&UI_LED_CAN_Error,
	&UI_LED_CAN_RX,
	&UI_LED_CAN_TX,

	&UI_LED_SD_Error,
	&UI_LED_SD_Read,
	&UI_LED_SD_Write
};

void UI_LED_Initialize() {
	UI_HW_Initialize();
}

void UI_LED_Update() {
	uint8_t i=0;
	for (i=0;i<UI_LED_Count;i++) {
		UI_LED *led = UI_LED_List[i];

		// Update LED state if blinking
		if (led->State == LED_Blink) {
			if (GetbmsecOffset() % led->Period > led->OnTime) {
				led->LEDOffFunction();
			} else {
				led->LEDOnFunction();
			}
		} else if (led->State == LED_BlinkInvert) {
			if (GetbmsecOffset() % led->Period > led->OnTime) {
				led->LEDOnFunction();
			} else {
				led->LEDOffFunction();
			}
		} else if (led->State == LED_PulseOn) {
			if (GetbmsecOffset() % led->Period > led->OnTime) {
				led->LEDOffFunction();
				led->State = LED_Off;
			}
		} else if (led->State == LED_PulseOff) {
			if (GetbmsecOffset() % led->Period > led->OnTime) {
				led->LEDOnFunction();
				led->State = LED_On;
			}
		}
		
		// Update LED state if there is a pulse request
		if (led->PulseRequest && 
				(led->State == LED_On || led->State == LED_Off)) {
			uint16_t periodMod = GetbmsecOffset() % led->Period;
			if (led->PulseRequest & 0x40			// If pulse is armed & ready
					&& periodMod < led->OnTime) {
				if (led->State == LED_Off) {
					led->LEDOnFunction();
					led->State = LED_PulseOn;
				} else if (led->State == LED_On) {
					led->LEDOffFunction();
					led->State = LED_PulseOff;
				}
				led->PulseRequest = 0;
			} else if (led->PulseRequest & 0x80		// If pulse is requested &
					&& periodMod > led->OnTime) {	// ready to arm
				led->PulseRequest |= 0x40;
			}
		}
	}

	UI_HW_LED_Update();
}

void UI_LED_SetState(UI_LED *led, UI_LED_State state) {
	led->State = state;
	if (state == LED_Off) {
		led->LEDOffFunction();
	} else if (state == LED_On) {
		led->LEDOnFunction();
	}
}

void UI_LED_Pulse(UI_LED *led) {
	led->PulseRequest |= 0x80;
}

void UI_LED_SetBlinkPeriod(UI_LED *led, uint16_t period) {
	led->Period = period;
}

void UI_LED_SetOnTime(UI_LED *led, uint16_t onTime) {
	led->OnTime = onTime;
}
