/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY
 * REASON WHATSOEVER.
 */

/**
 * @file xmc_wdt.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief WDT driver for XMC microcontroller family
 *
 * History <br>
 *
 * Version 1.0.0 Initial version<br>
 */
 
/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "xmc_wdt.h"

/*********************************************************************************************************************
 * API IMPLEMENTATION
  ********************************************************************************************************************/
/* Return version (major, minor and patch number) of the driver. */
XMC_DRIVER_VERSION_t XMC_WDT_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = XMC_WDT_MAJOR_VERSION;
  version.minor = XMC_WDT_MINOR_VERSION;
  version.patch = XMC_WDT_PATCH_VERSION;

  return version;
}

/* Enables watchdog clock and releases watchdog reset. */
void XMC_WDT_Enable(void)
{
#if (UC_SERIES != XMC45)
  XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_WDT);
#endif
#if (UC_FAMILY == XMC4)
  XMC_SCU_RESET_DeassertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_WDT);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_WDT);
#endif  
}

/* Disables watchdog clock and resets watchdog. */
void XMC_WDT_Disable(void)
{
#if (UC_FAMILY == XMC4)
  XMC_SCU_CLOCK_DisableClock(XMC_SCU_CLOCK_WDT);
  XMC_SCU_RESET_AssertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_WDT);
#endif  
#if (UC_SERIES != XMC45)
  XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_WDT); 
#endif
}
/* Initializes and configures watchdog with configuration data pointed by \a config. */
void XMC_WDT_Init(const XMC_WDT_CONFIG_t *const config)
{
  XMC_WDT_Enable();
  WDT->CTR = config->wdt_ctr;
  WDT->WLB = config->window_lower_bound;
  WDT->WUB = config->window_upper_bound;
}
