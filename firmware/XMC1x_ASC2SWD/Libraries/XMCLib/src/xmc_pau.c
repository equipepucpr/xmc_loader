
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
 */

/**
 * @file xmc_pau.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief PAU driver for XMC1 microcontroller family.
 *
 * History <br>
 *
 * Version 1.0.0  Initial <br>
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "xmc_pau.h"

#if defined(PAU)

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

/*
 * Retrieve version of the PAU driver
 */
XMC_DRIVER_VERSION_t XMC_PAU_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = (uint8_t)XMC_PAU_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_PAU_MINOR_VERSION;
  version.patch = (uint8_t)XMC_PAU_PATCH_VERSION;

  return version;
}

/*
 * Enable peripheral access
 */
void XMC_PAU_EnablePeripheralAccess(XMC_PAU_PERIPHERAL_t peripheral)
{
  uint32_t reg_num;
  
  reg_num = ((uint32_t)peripheral & 0xf0000000U) >> 28U;
  XMC_PAU->PRIVDIS[reg_num] &= (uint32_t)~((uint32_t)peripheral & 0x0fffffffUL);
}

/*
 * Disable peripheral access
 */
void XMC_PAU_DisablePeripheralAccess(XMC_PAU_PERIPHERAL_t peripheral)
{
  uint32_t reg_num;

  reg_num = ((uint32_t)peripheral & 0xf0000000U) >> 28U;
  XMC_PAU->PRIVDIS[reg_num] |= (uint32_t)((uint32_t)peripheral & 0x0fffffffUL);
}

/*
 * Check if peripheral access is enabled 
 */
bool XMC_PAU_IsPeripheralAccessEnabled(XMC_PAU_PERIPHERAL_t peripheral)
{
  uint32_t reg_num;

  reg_num = ((uint32_t)peripheral & 0xf0000000U) >> 28U;
  return (bool)(XMC_PAU->PRIVDIS[reg_num] & ((uint32_t)peripheral & 0x0fffffffUL));
}

/*
 * Check if peripheral is available
 */
bool XMC_PAU_IsPeripheralAvailable(XMC_PAU_PERIPHERAL_t peripheral)
{
  uint32_t reg_num;

  reg_num = ((uint32_t)peripheral & 0xf0000000U) >> 28U;
  return (bool)(XMC_PAU->AVAIL[reg_num] & ((uint32_t)peripheral & 0x0fffffffUL));
}

#endif /* defined(PAU) */
