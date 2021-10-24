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
 * @file xmc1_rtc.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief RTC driver for XMC microcontroller family.
 *
 * History <br>
 *
 * Version 1.0.0  Initial <br>
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include <xmc_rtc.h>
#include <xmc_scu.h>

#if UC_FAMILY == XMC1

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/
/*
 * Initialize the RTC peripheral
 */
XMC_RTC_STATUS_t XMC_RTC_Init(const XMC_RTC_CONFIG_t *const config)
{

  if (XMC_RTC_IsEnabled() == false)
  {
    XMC_RTC_Enable();
    XMC_RTC_SetPrescaler(config->prescaler);

	  while ((XMC_SCU_GetMirrorStatus() & (SCU_GENERAL_MIRRSTS_RTC_TIM0_Msk | SCU_GENERAL_MIRRSTS_RTC_TIM1_Msk)) != 0U)
	  {
      /* check SCU_MIRRSTS to ensure that no transfer over serial interface is pending */
    }
    RTC->TIM0 = config->time.raw0;
    RTC->TIM1 = config->time.raw1;
	
    while ((XMC_SCU_GetMirrorStatus() & (SCU_GENERAL_MIRRSTS_RTC_ATIM0_Msk | SCU_GENERAL_MIRRSTS_RTC_ATIM1_Msk)) != 0U)
    {
      /* check SCU_MIRRSTS to ensure that no transfer over serial interface is pending */
    }
    RTC->ATIM0 = config->alarm.raw0;	
    RTC->ATIM1 = config->alarm.raw1;    
  }
  return XMC_RTC_STATUS_OK;
}

/*
 * Ungates a clock node for RTC
 */ 
void XMC_RTC_Enable(void)
{
  XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_RTC);
}

/*
 * Gates a clock node for RTC
 */ 
void XMC_RTC_Disable(void)
{
  XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_RTC);
}

/*
 * Suspends RTC function during CPU HALT mode
 */ 
void XMC_RTC_SetDebugMode(const XMC_RTC_DEBUG_MODE_t debug_mode)
{
  uint32_t regval;
  regval = (RTC->CTR & (uint32_t)~RTC_CTR_SUS_Msk);
  RTC->CTR = (regval | (uint32_t)debug_mode);
}

/*
 * Enable RTC periodic and alarm event(s)
 */ 
void XMC_RTC_EnableEvent(const uint32_t event)
{
  RTC->MSKSR |= event;
}

/*
 * Disable RTC periodic and alarm event(s)
 */
void XMC_RTC_DisableEvent(const uint32_t event)
{
  RTC->MSKSR &= ~event;
}

/*
 * Clear RTC periodic and alarm event(s)
 */
void XMC_RTC_ClearEvent(const uint32_t event)
{
  RTC->CLRSR |= event;
}

/*
 * Checks RTC peripheral is enabled for programming to its registers
 */
bool XMC_RTC_IsEnabled(void)
{
  return !XMC_SCU_CLOCK_IsPeripheralClockGated(XMC_SCU_PERIPHERAL_CLOCK_RTC);
}

#endif /* UC_FAMILY == XMC1 */
