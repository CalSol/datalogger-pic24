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

#include <dma.h>
#include <adc.h>

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

#ifdef HARDWARE_DATALOGGER_1_4

#define DLG_ANALOG_BUFFER_SIZE 32

uint16_t Datalogger_AnalogBufferA[DLG_ANALOG_BUFFER_SIZE] __attribute__((space(dma)));
uint16_t Datalogger_AnalogBufferB[DLG_ANALOG_BUFFER_SIZE] __attribute__((space(dma)));

void Datalogger_InitVoltageRecorder(DlgFile *dlgFile) {
	// Initialize conversion trigger timer
	PR3 = 30000;
	TMR3 = 0;
	T3CONbits.TON = 1;

    // Close everything (just in case)
    CloseADC1();
    CloseDMA2();

	// Initialize DMA
    OpenDMA2(
            DMA2_MODULE_ON & DMA2_SIZE_WORD & PERIPHERAL_TO_DMA2
            & DMA2_INTERRUPT_BLOCK & DMA2_NORMAL & DMA2_REGISTER_POST_INCREMENT
            & DMA2_CONTINUOUS_PING_PONG,
            DMA2_AUTOMATIC,
            __builtin_dmaoffset(Datalogger_AnalogBufferA),
            __builtin_dmaoffset(Datalogger_AnalogBufferB),
            (unsigned long) &ADC1BUF0,
            DLG_ANALOG_BUFFER_SIZE-1
            );
    DMA2REQ = 0b0001101;	// ADC1 conversion done

    // Initialize ADC
    OpenADC1(
            ADC_MODULE_ON & ADC_IDLE_STOP & ADC_ADDMABM_ORDER
            & ADC_AD12B_12BIT & ADC_FORMAT_INTG & ADC_SSRC_TMR3
            & ADC_AUTO_SAMPLING_ON & ADC_MULTIPLE & ADC_SAMP_ON,
            ADC_VREF_AVDD_AVSS & ADC_SCAN_ON & ADC_SELECT_CHAN_0
            & ADC_DMA_ADD_INC_4 & ADC_ALT_BUF_OFF & ADC_ALT_INPUT_OFF,
            ADC_SAMPLE_TIME_31 & ADC_CONV_CLK_INTERNAL_RC & ADC_CONV_CLK_64Tcy,
            ADC_DMA_EN & ADC_DMA_BUF_LOC_4,
            0,
            ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA
            | ENABLE_AN8_ANA | ENABLE_AN9_ANA,
            0, 0, 0, 0, 0, 0, 0, 0, 0,
            0,
            ((uint16_t)1 << ANA_CH_5VDIV)
            | ((uint16_t)1 << ANA_CH_12VDIV)
            | ((uint16_t)1 << ANA_CH_VREF)
            | ((uint16_t)1 << ANA_CH_TEMP)
            );

    AD1CSSL = ((uint16_t)1 << ANA_CH_5VDIV)
            | ((uint16_t)1 << ANA_CH_12VDIV)
            | ((uint16_t)1 << ANA_CH_VREF)
            | ((uint16_t)1 << ANA_CH_TEMP);

	DBG_SPAM_printf("Voltage logger initialized");
}

StatMeas16 Voltage12v = {0,0,0,0,0};
StatMeas16 Voltage5v = {0,0,0,0,0};
StatMeas16 VoltageVRef = {0,0,0,0,0};
StatMeas16 VoltageTemp = {0,0,0,0,0};
uint16_t currVoltage = 0;

uint16_t StatMeas16_GetLow(StatMeas16* meas) {
    return meas->low;
}

uint16_t StatMeas16_GetHigh(StatMeas16* meas) {
    return meas->high;
}

uint16_t StatMeas16_GetSampleCount(StatMeas16* meas) {
    return meas->sampleCount;
}

uint16_t StatMeas16_GetAverage(StatMeas16* meas) {
    return meas->sum / meas->sampleCount;
}

/* Integer square root by Halleck's method, with Legalize's speedup */
uint64_t isqrt (uint64_t x) {
  uint64_t   squaredbit, remainder, root;

   if (x<1) return 0;
  
   /* Load the binary constant 01 00 00 ... 00, where the number
    * of zero bits to the right of the single one bit
    * is even, and the one bit is as far left as is consistant
    * with that condition.)
    */
   squaredbit  = (uint64_t) ((((uint64_t) ~0L) >> 1) & 
                        ~(((uint64_t) ~0L) >> 2));
   /* This portable load replaces the loop that used to be 
    * here, and was donated by  legalize@xmission.com 
    */

   /* Form bits of the answer. */
   remainder = x;  root = 0;
   while (squaredbit > 0) {
     if (remainder >= (squaredbit | root)) {
         remainder -= (squaredbit | root);
         root >>= 1; root |= squaredbit;
     } else {
         root >>= 1;
     }
     squaredbit >>= 2; 
   }

   return root;
}

uint16_t StatMeas16_GetStdev(StatMeas16* meas) {
    uint64_t temp1 = meas->squareSum / meas->sampleCount;
    uint64_t temp2 = meas->sum / meas->sampleCount;
    temp2 = temp2 * temp2;
    temp1 = temp1 - temp2;
    temp1 = isqrt(temp1);
    return temp1;
}

void StatMeas16_Clear(StatMeas16* meas) {
    meas->high = 0;
    meas->low = 65535;
    meas->sum = 0;
    meas->squareSum = 0;
    meas->sampleCount = 0;
}

void StatMeas16_Sample(StatMeas16* meas, uint16_t sample) {
    meas->sum += sample;
    meas->squareSum += (uint32_t)sample*sample;
    if (sample > meas->high) {
        meas->high = sample;
    }
    if (sample < meas->low) {
        meas->low = sample;
    }
    meas->sampleCount++;
}

uint16_t GetMv(uint16_t samp, uint16_t resh, uint16_t resl) {
    uint32_t samp32 = samp;
    samp32 *= 3300;
    samp32 *= (uint32_t)(resh + resl);
    samp32 /= 4096;
    samp32 /= resl;
    return (uint16_t)samp32;
}

#define MCP9700_V0  500     // 0C output voltage, mV
#define MCP9700_TC  10.0    // temperature coefficient, mV/C
#define MCP9701_V0  400     // 0C output voltage, mV
#define MCP9701_V0_ADC  49648         // 0C output voltage, 100*ADC
#define MCP9701_TC  19.5    // temperature coefficient, mV/C
#define MCP9701_TC_ADC_NUM  121       // temperature coefficient, numerator ADC/C
#define MCP9701_TC_ADC_DEN  5         // temperature coefficient, denominator ADC/C

double GetMcp9700Temp(uint16_t samp) {
    double sampDbl = samp;
    samp *= 100;
    sampDbl *= 3300.0/4096;
    sampDbl -= MCP9701_V0;
    sampDbl /= MCP9701_TC;
    return sampDbl;
}

uint16_t GetMcp9700TempInt(uint16_t samp) {
    uint32_t samp32 = samp * 100;
    samp32 -= MCP9701_V0_ADC;
    samp *= MCP9701_TC_ADC_NUM;
    samp /= MCP9701_TC_ADC_DEN;
    return samp;
}

void Datalogger_ProcessVoltageRecorder(DlgFile *dlgFile) {
	static uint8_t lastDMA = 0;
	uint8_t currDMA = PingPongStatusDMA2();

	static uint16_t lastSecOffset = 0;
	uint16_t currSecOffset = GetbmsecOffset();

	if (lastSecOffset > currSecOffset) {
        uint16_t sampCount, sampAvg, sampLow, sampHigh, sampStdev;
        uint32_t currTime32 = Get32bitTime();
        DlgStr buf;
        
        sampCount = StatMeas16_GetSampleCount(&Voltage12v);
        sampAvg = GetMv(StatMeas16_GetAverage(&Voltage12v), 68, 18);
        sampLow = GetMv(StatMeas16_GetLow(&Voltage12v), 68, 18);
        sampHigh = GetMv(StatMeas16_GetHigh(&Voltage12v), 68, 18);
        sampStdev = GetMv(StatMeas16_GetStdev(&Voltage12v), 68, 18);

        DlgStr_Init(&buf, "VLT ");
        DlgStr_AppendTimestamp(&buf, currTime32);
        DlgStr_AppendString(&buf, " +12v ");
        DlgStr_AppendDec16(&buf, sampCount);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampAvg, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampLow, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampHigh, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampStdev, 3);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);

        sampCount = StatMeas16_GetSampleCount(&Voltage5v);
        sampAvg = GetMv(StatMeas16_GetAverage(&Voltage5v), 1, 1);
        sampLow = GetMv(StatMeas16_GetLow(&Voltage5v), 1, 1);
        sampHigh = GetMv(StatMeas16_GetHigh(&Voltage5v), 1, 1);
        sampStdev = GetMv(StatMeas16_GetStdev(&Voltage5v), 1, 1);

        DlgStr_Init(&buf, "VLT ");
        DlgStr_AppendTimestamp(&buf, currTime32);
        DlgStr_AppendString(&buf, " +05v ");
        DlgStr_AppendDec16(&buf, sampCount);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampAvg, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampLow, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampHigh, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampStdev, 3);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);

        sampCount = StatMeas16_GetSampleCount(&VoltageVRef);
        sampAvg = GetMv(StatMeas16_GetAverage(&VoltageVRef), 0, 1);
        sampLow = GetMv(StatMeas16_GetLow(&VoltageVRef), 0, 1);
        sampHigh = GetMv(StatMeas16_GetHigh(&VoltageVRef), 0, 1);
        sampStdev = GetMv(StatMeas16_GetStdev(&VoltageVRef), 0, 1);

        DlgStr_Init(&buf, "VLT ");
        DlgStr_AppendTimestamp(&buf, currTime32);
        DlgStr_AppendString(&buf, " Vref ");
        DlgStr_AppendDec16(&buf, sampCount);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampAvg, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampLow, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampHigh, 3);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampStdev, 3);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);

        sampCount = StatMeas16_GetSampleCount(&VoltageTemp);
        sampAvg = GetMcp9700TempInt(StatMeas16_GetAverage(&VoltageTemp));
        sampLow = GetMcp9700TempInt(StatMeas16_GetLow(&VoltageTemp));
        sampHigh = GetMcp9700TempInt(StatMeas16_GetHigh(&VoltageTemp));
        sampStdev = GetMcp9700TempInt(StatMeas16_GetStdev(&VoltageTemp));
        
        DlgStr_Init(&buf, "VLT ");
        DlgStr_AppendTimestamp(&buf, currTime32);
        DlgStr_AppendString(&buf, " Temp ");
        DlgStr_AppendDec16(&buf, sampCount);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampAvg, 2);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampLow, 2);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampHigh, 2);
        DlgStr_AppendChar(&buf, ' ');
        DlgStr_AppendDec16Dec(&buf, sampStdev, 2);
        DlgStr_AppendChar(&buf, '\n');
        DlgFile_WriteAtomicDlgStr(dlgFile, &buf);
		
		// Reset statistical counters
        StatMeas16_Clear(&Voltage12v);
        StatMeas16_Clear(&Voltage5v);
        StatMeas16_Clear(&VoltageVRef);
        StatMeas16_Clear(&VoltageTemp);
	}
	lastSecOffset = currSecOffset;

	if (lastDMA != currDMA) {
		uint16_t *dataBuffer;
		uint8_t i=0;

		if (lastDMA) {	// STB register relected, read STA register
			dataBuffer = Datalogger_AnalogBufferA;
		} else {		// STA register selected, read STB register
			dataBuffer = Datalogger_AnalogBufferB;
		}

		for (i=0;i<DLG_ANALOG_BUFFER_SIZE;i+=4) {
            StatMeas16_Sample(&Voltage12v, dataBuffer[0+i]);
            StatMeas16_Sample(&Voltage5v, dataBuffer[1+i]);
            StatMeas16_Sample(&VoltageVRef, dataBuffer[2+i]);
            StatMeas16_Sample(&VoltageTemp, dataBuffer[3+i]);
		}
		currVoltage = GetMv(dataBuffer[0], 68, 18);
		lastDMA = currDMA;
	}

}

#endif
