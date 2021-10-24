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
 * @file xmc1_usic.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief Template driver for XMC microcontroller family.
 *
 * History <br>
 *
 * Version 1.0.0  Initial <br>
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "xmc_usic.h"
#include "xmc_scu.h"

/*******************************************************************************
 * API Implementation
 *******************************************************************************/

#if UC_FAMILY == XMC1
/**
 * @brief API to enable the USIC driver
 * @retval void
 *
 */
void XMC_USIC_Enable(XMC_USIC_t *const usic)
{
  if (usic == XMC_USIC0)
  {
	XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC0);
  }
#if defined(USIC1)  
  else if (usic == XMC_USIC1)
  {
    XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC1);
  }
#endif  
#if defined(USIC2)  
  else if (usic == XMC_USIC2)
  {
	XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC2);
  }
#endif  
  else
  {
	XMC_ASSERT("USIC module not available", 0/*Always*/);
  }
}

/**
 * @brief API to Disable the USIC driver
 * @retval void
 *
 */
void XMC_USIC_Disable(XMC_USIC_t *const usic)
{
  if (usic == (XMC_USIC_t *)USIC0)
  {
    XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC0);
  }
#if defined(USIC1)  
  else if (usic == (XMC_USIC_t *)USIC1)
  {
    XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC1);
  }
#endif  
#if defined(USIC2)  
  else if (usic == (XMC_USIC_t *)USIC2)
  {
	XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC2);
  }
#endif  
  else
  {
    XMC_ASSERT("USIC module not available", 0/*Always*/);
  }
  
}

#endif
