/*
 * File:   configuration_buts.c
 * Author: Ducky
 *
 * Revision History
 * Date			Author	Change
 * 26 May 2012	Ducky	Separated configuration bits from main.c
 *
 * @file
 * Device configuration bits.
 */

#include "hardware.h"

/*
 * Configuration Bits
 */
#if defined (__dsPIC33FJ128MC802__)
	_FBS(RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF);
	_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);
	_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);

	_FOSCSEL(FNOSC_PRIPLL & IESO_OFF);
	_FOSC(FCKSM_CSDCMD & IOL1WAY_OFF & OSCIOFNC_OFF & POSCMD_HS);
	//_FOSCSEL(FNOSC_FRC & IESO_OFF);	//		Configuration for internal 7.37 MHz FRC
	//_FOSC(FCKSM_CSDCMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_NONE);
	_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
	#if defined HARDWARE_RUN_3
		_FPOR(PWMPIN_ON & HPOL_OFF & ALTI2C_OFF & FPWRT_PWR1);
		_FICD(JTAGEN_OFF & ICS_PGD1);
	#elif defined HARDWARE_CANBRIDGE
		_FPOR(PWMPIN_ON & HPOL_OFF & ALTI2C_OFF & FPWRT_PWR1);
		_FICD(JTAGEN_OFF & ICS_PGD3);
	#endif
#elif defined (__dsPIC33EP256MU806__)

// DSPIC33EP256MU806 Configuration Bit Settings

#include <p33Exxxx.h>
    _FGS(
        GWRP_OFF &           // General Segment Write-Protect bit (General Segment may be written)
        GSS_OFF &            // General Segment Code-Protect bit (General Segment Code protect is disabled)
        GSSK_OFF             // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)
    );
    _FOSCSEL(
        FNOSC_PRI &          // Initial Oscillator Source Selection bits (Primary Oscillator (XT, HS, EC))
        IESO_OFF             // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)
    );
    _FOSC(
        POSCMD_HS &          // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
        OSCIOFNC_OFF &       // OSC2 Pin Function bit (OSC2 is clock output)
        IOL1WAY_ON &         // Peripheral pin select configuration (Allow only one reconfiguration)
        FCKSM_CSECMD         // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
    );
    _FWDT(
        WDTPOST_PS32768 &    // Watchdog Timer Postscaler bits (1:32,768)
        WDTPRE_PR128 &       // Watchdog Timer Prescaler bit (1:128)
        PLLKEN_ON &          // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
        WINDIS_OFF &         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
        FWDTEN_OFF           // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)
    );
    _FPOR(
        FPWRT_PWR128 &       // Power-on Reset Timer Value Select bits (128ms)
        BOREN_ON &           // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
        ALTI2C1_ON           // Alternate I2C pins for I2C1 (ASDA1/ASCK1 pins are selected as the I/O pins for I2C1)
    );
    _FICD(
        ICS_PGD1 &           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
        RSTPRI_PF &          // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
        JTAGEN_ON            // JTAG Enable bit (JTAG is enabled)
    );
    _FAS(
        AWRP_OFF &           // Auxiliary Segment Write-protect bit (Aux Flash may be written)
        APL_OFF &            // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
        APLK_OFF             // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)
    );

#else

#errror "No configuration bits set"

#endif
