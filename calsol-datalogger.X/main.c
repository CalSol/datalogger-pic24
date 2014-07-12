/*
 * File:   main.c
 * Author: Ducky
 *
 * Created on January 15, 2011, 5:22 PM
 *
 * Revision History
 * Date			Author	Change
 * 21 Jul 2011	Ducky	Added this change history box.
 *
 * @file
 * Application level code.
 */

//	#include <p24Hxxxx.h>	// included in hardware.h
#include <string.h>

#include "hardware.h"
#include "version.h"

#include "timing.h"
#include "ecan.h"
#include "uart-dma.h"
#include "Datalogger/datalogger.h"

#include "ftm/ftm.h"

#include "UserInterface/datalogger-ui-hardware.h"
#include "UserInterface/datalogger-ui-leds.h"

#define DEBUG_UART
#define DEBUG_UART_DATA
#include "debug-common.h"

/*
 * Function Prototypes
 */
void OscInit(void);
void AnalogInit(void);
void OutputInit(void);
void PPSInit(void);

int main(void) {
	uint16_t i = 0;

	HW_Init_Clock();
	HW_Init_Analog();
	HW_Init_IO();
	HW_Init_Peripherals();

	Timing_Init();
	UART_DMA_Init();

	UI_LED_Initialize();
	for (i=0;i<UI_LED_Count;i++) {
		UI_LED_SetState(UI_LED_List[i], LED_On);
	}
	UI_LED_Update();

	DBG_printf("\r\n");
	DBG_printf("\2330;36mCalSol Datalogger v%u.%u (alpha)\23337m", VERSION_MAJ, VERSION_MIN);
	DBG_printf("\23336m  Built %s %s with C30 ver %i\23337m", __DATE__, __TIME__, __C30_VERSION__);

	DBG_DATA_printf("\23336mDevice reset:%s%s%s%s%s%s%s%s\23337m",
			(RCONbits.TRAPR? " Trap" : ""),
			(RCONbits.IOPUWR? " IllegalOpcode/UninitializedW" : ""),
			(RCONbits.CM? " ConfigMismatch" : ""),
			(RCONbits.EXTR? " ExternalReset" : ""),
			(RCONbits.SWR? " SoftwareReset" : ""),
			(RCONbits.WDTO? " WatchdogTimeout" : ""),
			(RCONbits.BOR? " BrownOutReset" : ""),
			(RCONbits.POR? " PowerOnReset" : "")
			);

	ECAN_Init();
	ECAN_Config();
	C1FCTRLbits.FSA = 4;	// FIFO starts
	C1FEN1 = 0;
	ECAN_SetStandardFilter(0, 0x00, 0, 15);
	ECAN_SetStandardMask(0, 0x00);
	ECAN_SetMode(ECAN_MODE_OPERATE);
	ECAN_SetupDMA();

	UI_Switch_Update();
	if (UI_Switch_GetTest()) {
        FTM_Init();
        
        while(1) {
            FTM_Loop();
        }
	}

	for (i=0;i<UI_LED_Count;i++) {
		UI_LED_SetState(UI_LED_List[i], LED_Off);
	}

	DBG_printf("Initialization complete");

	Datalogger_Init();

	while(1) {
		Datalogger_Loop();
	}
}
