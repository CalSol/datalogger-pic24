/*
 * File:   timing-run2.c
 * Author: Ducky
 *
 * Created on July 9, 2011, 7:34 PM
 *
 * Revision History
 * Date			Author	Change
 * 27 Jul 2011	Ducky	Added this revision history box.
 *						Timing now uses TMR1 with the 32.768 kHz secondary
 *						oscillator.
 * 12 Aug 2011	Ducky	Separated Run 2 and Run 3 timing.
 *
 * @file
 * Hardware abstraction layer for the real-time clock and timer functions.
 */
#include "hardware.h"
#include "timing.h"

#ifdef HARDWARE_RUN_2

seconds_t TimeSeconds;

/**
 * Initializes hardware needed for the timing functions.
 * This starts the seconds counter at the current time.
 */
void Timing_Init() {
	// Initialize variables
	TimeSeconds = 0;

	// Initialize Timer
	T4CONbits.T32 = 1;
	PR4 = 0x2d00;
	PR5 = 0x0131;
	IEC1bits.T5IE = 1;
	T4CONbits.TON = 1;
}

/**
 * @return The number of seconds elapsed since power on, rounded down.
 */
inline seconds_t GetTimeSeconds() {
	return TimeSeconds;
}

/**
 * @return The binary-milliseconds (1/1024 second) offset from the current
 * second.
 */
inline uint16_t GetbmsecOffset() {
	return (TMR5 * 214) >> 6;
}

/**
 * @return The current time, in 32-bit format. The low 10 bits represent
 * the fractions of a second in 1/1024 increments while the upper 22 bits
 * represent the time in seconds.
 */
inline uint32_t Get32bitTime() {
	uint32_t retVal = GetbmsecOffset();
	retVal = retVal | (TimeSeconds << 10);
	return retVal;
}

/**
 * Starts the countdown for the CountdownTimer object.
 *
 * @param timer Timer to start.
 * @param duration Duration of the timer in 1/1024 seconds.
 */
void Timer_StartCountdown(CountdownTimer *timer, uint16_t duration) {
	uint16_t secs = (duration - (duration % 1024)) / 1024;
	timer->ExpirationSeconds = TimeSeconds + secs;
	duration = duration % 1024;
	
	timer->ExpirationFracSecs = TMR5;
	timer->ExpirationFracSecs += (duration * 38) >> 7;

	if (timer->ExpirationFracSecs >= 305) {
		timer->ExpirationSeconds++;
		timer->ExpirationFracSecs -= 305;
	}
}

/**
 * Checks if the CountdownTimer object has expired (time has elapsed).
 *
 * @param timer Timer to check.
 * @return
 */
uint8_t Timer_CountdownExpired(CountdownTimer *timer) {
	if (timer->ExpirationSeconds > TimeSeconds) {
		return 1;
	} else if (timer->ExpirationSeconds == TimeSeconds) {
		if (timer->ExpirationFracSecs > TMR5) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

// Interrupt Handler
void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void) {
	_T5IF = 0;
	TimeSeconds++;
}

#endif
