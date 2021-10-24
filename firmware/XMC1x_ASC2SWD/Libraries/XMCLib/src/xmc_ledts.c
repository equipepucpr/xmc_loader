/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file xmc_ledts.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief LEDTS low level driver for XMC1 and XMC4 microcontrollers
 *
 * <b>Detailed description of file:</b><br>
 * APIs for the functional blocks of LEDTS have been defined:<br>
 * -- GLOBAL (APIs prefixed with LEDTS_GLOBAL_) <br>
 * -- Clock configuration, Function/Event configuration, Interrupt configuration
 *
 * History
 *
 * Version 1.0.0 Initial version <br>
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_ledts.h>

#if defined(LEDTS0)

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define XMC_LEDTS_CLOCK_NOT_RUNNING 0U

/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL/UTILITY ROUTINES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/
/**
  * API to retrieve the version of the LEDTS driver
  */
XMC_DRIVER_VERSION_t XMC_LEDTS_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = XMC_LEDTS_MAJOR_VERSION;
  version.minor = XMC_LEDTS_MINOR_VERSION;
  version.patch = XMC_LEDTS_PATCH_VERSION;

  return version;
}

/**
  * Initialization of global register
  */
XMC_LEDTS_STATUS_t XMC_LEDTS_InitGlobal(XMC_LEDTS_t *const ledts, const XMC_LEDTS_GLOBAL_CONFIG_t *config)
{
  XMC_ASSERT("XMC_LEDTS_InitGlobal:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));
  XMC_ASSERT("XMC_LEDTS_InitGlobal:Null Pointer", (config != (XMC_LEDTS_GLOBAL_CONFIG_t *)NULL));

#if(UC_SERIES == XMC12)

  if(ledts == XMC_LEDTS0)
  {
    XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_LEDTS0);
  }
  else
  {
    XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_LEDTS1);
  }

#elif(UC_SERIES == XMC45)
  XMC_SCU_RESET_DeassertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_LEDTS0);

#elif(UC_SERIES !=  XMC45)
  XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_LEDTS0);
  XMC_SCU_RESET_DeassertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_LEDTS0);

#endif

  if((ledts->GLOBCTL & LEDTS_GLOBCTL_CLK_PS_Msk) != XMC_LEDTS_CLOCK_NOT_RUNNING)
  {
    return XMC_LEDTS_STATUS_RUNNING;
  }

  ledts->GLOBCTL = config->globctl;

  return XMC_LEDTS_STATUS_SUCCESS;
}

/**
  * Initialization of registers for LED-driving function
  */
XMC_LEDTS_STATUS_t XMC_LEDTS_InitLED(XMC_LEDTS_t *const ledts, const XMC_LEDTS_LED_CONFIG_t *config)
{
  XMC_ASSERT("XMC_LEDTS_LED_Init:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));
  XMC_ASSERT("XMC_LEDTS_LED_Init:Null Pointer", (config != (XMC_LEDTS_LED_CONFIG_t *)NULL));

  if((ledts->GLOBCTL & LEDTS_GLOBCTL_CLK_PS_Msk) != XMC_LEDTS_CLOCK_NOT_RUNNING)
  {
    return XMC_LEDTS_STATUS_RUNNING;
  }

  ledts->FNCTL &= ~(LEDTS_FNCTL_COLLEV_Msk | LEDTS_FNCTL_NR_LEDCOL_Msk);
  ledts->FNCTL |= (config->fnctl);

  /* Enable LED function */
  ledts->GLOBCTL |= LEDTS_GLOBCTL_LD_EN_Msk;

  return XMC_LEDTS_STATUS_SUCCESS;
}

/**
  * Initialization of registers for basic Touch-Sense control function
  */
XMC_LEDTS_STATUS_t XMC_LEDTS_InitTSBasic(XMC_LEDTS_t *const ledts, const XMC_LEDTS_TS_CONFIG_BASIC_t *config)
{
  uint32_t reg;

  XMC_ASSERT("XMC_LEDTS_TS_Basic_Init:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));
  XMC_ASSERT("XMC_LEDTS_TS_Basic_Init:Null Pointer", (config != (XMC_LEDTS_TS_CONFIG_BASIC_t *)NULL));

  if((ledts->GLOBCTL & LEDTS_GLOBCTL_CLK_PS_Msk) != XMC_LEDTS_CLOCK_NOT_RUNNING)
  {
    return XMC_LEDTS_STATUS_RUNNING;
  }

  reg = ~(LEDTS_FNCTL_ACCCNT_Msk | LEDTS_FNCTL_TSCCMP_Msk | LEDTS_FNCTL_TSCTRR_Msk | LEDTS_FNCTL_TSCTRSAT_Msk |
		 LEDTS_FNCTL_NR_TSIN_Msk);
  ledts->FNCTL &= (reg);
  ledts->FNCTL |= (config->fnctl);

  /* Enable TS function */
  ledts->GLOBCTL |= LEDTS_GLOBCTL_TS_EN_Msk;

  return XMC_LEDTS_STATUS_SUCCESS;
}

/**
  * Initialization of registers for advanced Touch-Sense control function
  */
XMC_LEDTS_STATUS_t XMC_LEDTS_InitTSAdvanced (XMC_LEDTS_t *const ledts, const XMC_LEDTS_TS_CONFIG_ADVANCED_t *config)
{
  uint32_t reg;

  XMC_ASSERT("XMC_LEDTS_TS_Advanced_Init:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));
  XMC_ASSERT("XMC_LEDTS_TS_Advanced_Init:Null Pointer", (config != (XMC_LEDTS_TS_CONFIG_ADVANCED_t *)NULL));

  if((ledts->GLOBCTL & LEDTS_GLOBCTL_CLK_PS_Msk) != XMC_LEDTS_CLOCK_NOT_RUNNING)
  {
    return XMC_LEDTS_STATUS_RUNNING;
  }

  reg = ~(LEDTS_GLOBCTL_MASKVAL_Msk | LEDTS_GLOBCTL_FENVAL_Msk);
  ledts->GLOBCTL &= (reg);
  ledts->GLOBCTL |= (config->globctl);

  reg = ~(LEDTS_FNCTL_PADT_Msk | LEDTS_FNCTL_PADTSW_Msk | LEDTS_FNCTL_EPULL_Msk | LEDTS_FNCTL_TSOEXT_Msk);
  ledts->FNCTL &= (reg);
  ledts->FNCTL |= (config->fnctl);

  return XMC_LEDTS_STATUS_SUCCESS;
}

/**
  * Starts LEDTS-counter
  */
void XMC_LEDTS_StartCounter(XMC_LEDTS_t *const ledts, const uint16_t prescaler)
{
  XMC_ASSERT("XMC_LEDTS_Start_Counter:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  ledts->GLOBCTL |= prescaler<<16U;
}

/**
  * Stops LEDTS-counter
  */
void XMC_LEDTS_StopCounter(XMC_LEDTS_t *const ledts)
{
  XMC_ASSERT("XMC_LEDTS_Stop_Counter:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  ledts->GLOBCTL &= 0x0000FFFF;
}

/**
  * Reads time interrupt flags
  */
uint32_t XMC_LEDTS_ReadInterruptFlag(XMC_LEDTS_t *const ledts)
{
  XMC_ASSERT("XMC_LEDTS_ReadInterruptFlag:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  return (ledts->EVFR & 0xF);
}

/**
  * Clears interrupt indication flags
  */
void XMC_LEDTS_ClearInterruptFlag(XMC_LEDTS_t *const ledts, uint32_t interrupt_mask)
{
  XMC_ASSERT("XMC_LEDTS_ClearInterruptFlag:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  ledts->EVFR = (interrupt_mask << LEDTS_EVFR_CTSF_Pos);
}

/**
  * Programming of registers to output pattern on an LED column in LED matrix
  */
void XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS_t *const ledts, XMC_LEDTS_LED_COLUMN_t column, const uint8_t pattern)
{
  uint32_t reg;
  uint8_t reg_index = ((uint8_t)column) >> 2;
  uint8_t bit_shift_count = ((uint8_t)column & 0x03) * 8;

  XMC_ASSERT("XMC_LEDTS_Set_LED_Line_Pattern:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  reg = ledts->LINE[reg_index];
  reg &= (~(0xff << bit_shift_count));
  reg |= pattern << bit_shift_count;
  ledts->LINE[reg_index] = reg;

}

/**
  * Programming of registers to adjust brightness of an LED column in LED matrix
  */
void XMC_LEDTS_SetColumnBrightness(XMC_LEDTS_t *const ledts, XMC_LEDTS_LED_COLUMN_t column, const uint8_t brightness)
{
  uint32_t reg;
  uint8_t reg_index = ((uint8_t)column) >> 2;
  uint8_t bit_shift_count = ((uint8_t)column & 0x03) * 8;

  XMC_ASSERT("XMC_LEDTS_Set_Column_Brightness:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

	reg = ledts->LDCMP[reg_index];
	reg &= (~(0xff << bit_shift_count));
	reg |= brightness << bit_shift_count;
	ledts->LDCMP[reg_index] = reg;
}

/**
  * Programming of registers to set common oscillation window size for touch-sense inputs
  */
void XMC_LEDTS_SetCommonOscillationWindow(XMC_LEDTS_t *const ledts, const uint8_t common_size)
{
  uint32_t reg;

  XMC_ASSERT("XMC_LEDTS_Set_Common_Oscillation_Window:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  reg = ledts->LDCMP[1];
  reg &= ~LEDTS_LDCMP1_CMP_LDA_TSCOM_Msk;
  reg |= (common_size << LEDTS_LDCMP1_CMP_LDA_TSCOM_Pos);
  ledts->LDCMP[1] = reg;
}

/**
  * Checking the previous active function or LED column status
  */
uint32_t XMC_LEDTS_ReadFNCOL(XMC_LEDTS_t *const ledts)
{
  uint32_t fncol_read;

  XMC_ASSERT("XMC_LEDTS_Read_FNCOL:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  fncol_read = ledts->FNCTL & LEDTS_FNCTL_FNCOL_Msk;
  fncol_read >>= LEDTS_FNCTL_FNCOL_Pos;

  return fncol_read;
}

/**
  * Set the number of LED column Enabled
  */
void XMC_LEDTS_SetNumOfLEDColumns(XMC_LEDTS_t *const ledts, uint8_t count)
{

  XMC_ASSERT("XMC_LEDTS_SetNumOfLEDColumns:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  ledts->FNCTL &= ~(LEDTS_FNCTL_NR_LEDCOL_Msk);
  ledts->FNCTL |= (count << LEDTS_FNCTL_NR_LEDCOL_Pos);
}

/**
  * Reading recorded number of oscillation counts
  */
uint16_t XMC_LEDTS_ReadTSVAL(XMC_LEDTS_t *const ledts)
{
  uint16_t no_of_oscillations;

  XMC_ASSERT("XMC_LEDTS_Read_TSVAL:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

  no_of_oscillations = (ledts->TSVAL & 0xFFFF);

  return no_of_oscillations;
}

/**
  * Programming of registers to adjust the size of oscillation window
  */
void XMC_LEDTS_SetOscillationWindow(XMC_LEDTS_t *const ledts, XMC_LEDTS_NUMBER_TS_INPUT_t touchpad, const uint8_t size)
{
  uint32_t reg;
  uint8_t reg_index = ((uint8_t)touchpad) >> 2;
  uint8_t bit_shift_count = ((uint8_t)touchpad & 0x03) * 8;

  XMC_ASSERT("XMC_LEDTS_Set_Oscillation_Window:Wrong Module Pointer", XMC_LEDTS_CHECK_KERNEL_PTR(ledts));

	reg = ledts->TSCMP[reg_index];
	reg &= (~(0xff << bit_shift_count));
	reg |= size << bit_shift_count;
	ledts->TSCMP[reg_index] = reg;
}

#endif /* LEDTS0 */

