/*
 * File:   timing.h
 * Author: Ducky
 *
 * Creation time unknown
 *
 * Revision History
 * Date			Author	Change
 * 27 Jul 2011	Ducky	Added this revision history box.
 *
 * @file
 * Hardware abstraction interface for the real-time clock and timer functions.
 */

#ifndef TIMING_H
#define TIMING_H

#include "types.h"

typedef uint32_t seconds_t;		/// Type to represent seconds.
typedef uint16_t fracsec_t;		/// Type to represent fractions of a second - heavily platform dependent.
								/// The current fractions of a second should be directly read from timer registers.

typedef struct {
	seconds_t ExpirationSeconds;	/// Second at which the countdown expires.
	fracsec_t ExpirationFracSecs;	/// The fraction of a second at which the countdown expires.
} CountdownTimer;

void Timing_Init();

inline seconds_t GetTimeSeconds();
inline uint16_t GetbmsecOffset();
inline uint32_t Get32bitTime();

void Timer_StartCountdown(CountdownTimer *timer, uint16_t duration);
uint8_t Timer_CountdownExpired(CountdownTimer *timer);

#endif
