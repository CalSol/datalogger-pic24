/*
 * File:   datalogger-voltagelogger.c
 * Author: Ducky
 *
 * Created on August 13, 2011, 6:59 PM
 *
 * Revision History
 * Date			Author	Change
 * 13 Aug 2011	Ducky	Initial implementation.
 *
 * @file
 * Datalogger voltage logging functions.
 */

#include <stdlib.h>
#include <string.h>

#include "../types.h"

#include "../ecan.h"
#include "../timing.h"

#include "../UserInterface/datalogger-ui-hardware.h"
#include "../UserInterface/datalogger-ui-leds.h"

#include "datalogger-stringutil.h"
#include "datalogger-file.h"
#include "datalogger-applications.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
//#define DEBUG_UART_SPAM
#define DBG_MODULE "DLG/VoltLog"
#include "../debug-common.h"

#if defined(HARDWARE_RUN_3) || defined(HARDWARE_CANBRIDGE)

#define DLG_ANALOG_BUFFER_SIZE 16

uint16_t Datalogger_AnalogBufferA[DLG_ANALOG_BUFFER_SIZE] __attribute__((space(dma)));
uint16_t Datalogger_AnalogBufferB[DLG_ANALOG_BUFFER_SIZE] __attribute__((space(dma)));

void Datalogger_InitVoltageRecorder() {
	AD1CON1bits.ADDMABM = 1;		// write in order of conversion
	AD1CON1bits.AD12B = 1;			// 12-bit operation
	AD1CON1bits.SSRC = 0b010;		// timer 3 compare starts conversion
//	AD1CON1bits.SIMSAM = 1;			// sample simultaneously - no available in 12-bit mode
	AD1CON1bits.ASAM = 1;			// auto-set SAMP bit

	AD1CON2bits.CSCNA = 1;			// scan inputs
	AD1CON2bits.BUFM = 1;			// use dual buffer
	AD1CON2bits.SMPI = 1;			// 2 samples per increment

	AD1CON3bits.ADRC = 1;			// Use ADC internal RC oscillator (4MHz)
//	AD1CON3bits.SAMC = 15;			// 16 Tad auto-sample - not necessary for manual sample
	AD1CON3bits.ADCS = 3;			// 4 Tcy = Tad

	AD1CON4bits.DMABL = 0b011;		// 8 buffer words per analog input
	AD1CSSL = 0;
	AD1CSSL |= (uint16_t)1 << ANA_CH_12VDIV;
//	AD1CSSL |= (uint16_t)1 << ANA_CH_EXTANALOG;

	AD1PCFGL = 0xffff;
	AD1PCFGL &= ~((uint16_t)1 << ANA_CH_12VDIV);
//	AD1PCFGL &= ~((uint16_t)1 << ANA_CH_EXTANALOG);

	// Initialize conversion trigger timer
#if defined(HARDWARE_RUN_3) || defined(HARDWARE_CANBRIDGE)
	// Initialize Timer
	PR3 = 20000;
	TMR3 = 0;
	T3CONbits.TON = 1;
#elif defined(HARDWARE_RUN_2)
	// Initialize Timer
	PR3 = 20000;
	TMR3 = 0;
	T3CONbits.TON = 1;
#endif

	// Initialize DMA
	DMA5CONbits.MODE = 0b10;		// Continuous with ping-pong
	DMA5REQbits.IRQSEL = 0b0001101;	// ADC1 conversion done
	DMA5STA = __builtin_dmaoffset(Datalogger_AnalogBufferA);
	DMA5STB = __builtin_dmaoffset(Datalogger_AnalogBufferB);
	DMA5PAD = (volatile unsigned int) &ADC1BUF0;
	DMA5CNT = DLG_ANALOG_BUFFER_SIZE - 1;
	DMA5CONbits.CHEN = 1;
	
	// Enable ADC
	AD1CON1bits.ADON = 1;
	AD1CON1bits.SAMP = 1;

	DBG_SPAM_printf("Voltage logger initialized");
}

StatisticalMeasurement Voltage12v = {0,0,0,0};
uint16_t currVoltage = 0;

void Datalogger_ProcessVoltageRecorder(DlgFile *dlgFile) {
	static uint8_t lastDMA = 0;
	uint8_t currDMA = DMACS1bits.PPST5;

	static uint16_t lastTime = 0;
	uint16_t currTime = GetbmsecOffset();

	if (lastTime > currTime ) {
		static char buffer[64] = "VS xxxxxxxx +12v ";
		uint8_t bufferPos = 17;

		uint16_t average = ((Voltage12v.runningAverage/Voltage12v.sampleCount)
				* 1015762) >> 18;
		uint16_t high = (((uint32_t)Voltage12v.high) * 1015762) >> 18;
		uint16_t low = (((uint32_t)Voltage12v.low) * 1015762) >> 18;
		DBG_SPAM_printf("+12v measurement: Low %u, Avg %u, High %u, Samp %u", low, average, high, Voltage12v.sampleCount);

		Int32ToString(Get32bitTime(), buffer+3);

		itoa(buffer+bufferPos, Voltage12v.sampleCount, 10);
		bufferPos += strlen(buffer+bufferPos);
		buffer[bufferPos] = ' ';	bufferPos++;
		itoa(buffer+bufferPos, low, 10);
		bufferPos += strlen(buffer+bufferPos);
		buffer[bufferPos] = ' ';	bufferPos++;
		itoa(buffer+bufferPos, average, 10);
		bufferPos += strlen(buffer+bufferPos);
		buffer[bufferPos] = ' ';	bufferPos++;
		itoa(buffer+bufferPos, high, 10);
		bufferPos += strlen(buffer+bufferPos);
		buffer[bufferPos] = '\n';	bufferPos++;
		buffer[bufferPos] = 0;

		DlgFile_WriteAtomic(dlgFile, (uint8_t*)buffer, bufferPos);

		// Reset statistical counters
		Voltage12v.sampleCount = 0;
		Voltage12v.low = 65535;
		Voltage12v.high = 0;
		Voltage12v.runningAverage = 0;
	}
	lastTime = currTime;

	if (lastDMA != currDMA) {
		uint16_t *dataBuffer;
		uint8_t i=0;
		if (lastDMA) {	// STB register relected, read STA register
			dataBuffer = Datalogger_AnalogBufferA;
		} else {		// STA register selected, read STB register
			dataBuffer = Datalogger_AnalogBufferB;
		}
		for (i=0;i<DLG_ANALOG_BUFFER_SIZE;i++) {
			Voltage12v.runningAverage += dataBuffer[0+i];
			if (dataBuffer[0+i] > Voltage12v.high) {
				Voltage12v.high = dataBuffer[0+i];
			}
			if (dataBuffer[0+i] < Voltage12v.low) {
				Voltage12v.low = dataBuffer[0+i];
			}
		}
		Voltage12v.sampleCount += 16;
		currVoltage = dataBuffer[0];
		lastDMA = currDMA;
	}

}

#endif
