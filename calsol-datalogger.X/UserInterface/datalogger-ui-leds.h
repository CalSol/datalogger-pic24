/*
 * File:   datalogger-ui-leds.h
 * Author: Ducky
 *
 * Created on July 23, 2011, 4:53 PM
 *
 * Revision History
 * 23 Jul 2011	Ducky	Initial implementation
 *
 * @file
 * State-based LED code, including functionality for pulsing and blinking.
 */

#ifndef DATALOGGER_UI_LEDS_H
#define DATALOGGER_UI_LEDS_H

#include "../types.h"

typedef enum {
	LED_Off,			/// LED is off.
	LED_On,				/// LED is on.
	LED_Blink,			/// LED is continuously blinking.
	LED_BlinkInvert,	/// LED is continuously blinking with inverted polarity.
	LED_PulseOn,		/// LED is pulsing on, but will return to the off state.
	LED_PulseOff,		/// LED is pulsing off, but will return to the on state.
} UI_LED_State;

typedef struct {
	UI_LED_State State;		/// Assigned state of the LED.
	uint16_t Period;		/// Blink period, in milliseconds.
	uint16_t OnTime;		/// On time during a blink period, in milliseconds.
							/// Also the pulse duration, in milliseconds.
	uint8_t PulseRequest;	/// Contains 0x80 if a pulse is requested,
							/// Contains 0x40 is a pulse is armed.

	void (*LEDOnFunction)();	/// Pointer to the function to turn on the LED.
	void (*LEDOffFunction)();	/// Pointer to the function to turn off the LED.
} UI_LED;

extern UI_LED UI_LED_Fault;

extern UI_LED UI_LED_Status_Error;
extern UI_LED UI_LED_Status_Operate;
extern UI_LED UI_LED_Status_Waiting;

extern UI_LED UI_LED_CAN_Error;
extern UI_LED UI_LED_CAN_TX;
extern UI_LED UI_LED_CAN_RX;

extern UI_LED UI_LED_SD_Error;
extern UI_LED UI_LED_SD_Read;
extern UI_LED UI_LED_SD_Write;

extern uint8_t UI_LED_Count;
extern UI_LED *UI_LED_List[];

/**
 * Initializes the UI LEDs.
 */
void UI_LED_Initialize();

/**
 * Updates the LEDs: this writes changes to the GPIO expander (where necessary)
 * and changes states for blinking LEDs.
 * This should be called periodically for proper blinking / pulsing behavior.
 * Ideally, this would be called several (> 8) times during a LED blink period.
 */
void UI_LED_Update();

/**
 * Sets the LED state
 * @param led UI_LED struct.
 * @param state State to set the LED into. Only LED_On, LED_Off, and LED_Blink.
 * Note that blinking is synchronous, and as such, LED changes may or may not
 * start immediately.
 * Pulsing is not done here, and should be requested through UI_LED_Pulse.
 * are valid states.
 */
void UI_LED_SetState(UI_LED *led, UI_LED_State state);

/**
 * Pulses a LED.
 * Note that LED pulses (as with blinking) is synchronous, and the beginning
 * of a pulse may be delayed until clock alignment.
 * @param led UI_LED struct.
 */
void UI_LED_Pulse(UI_LED *led);

/**
 * Sets a LED's blinking (or pulsing) period.
 * @param led UI_LED struct.
 * @param period Blink period, in milliseconds. For proper operation, this must
 * be evenly divisible into one second.
 */
void UI_LED_SetBlinkPeriod(UI_LED *led, uint16_t period);

/**
 * Sets a LED's active time when blinking.
 * @param led UI_LED struct.
 * @param onTime On time, in milliseconds.
 */
void UI_LED_SetOnTime(UI_LED *led, uint16_t onTime);

#endif
