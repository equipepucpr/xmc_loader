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
 * @file xmc_gpio.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief GPIO driver - API implementation common to all devices <br>
 * 
 * History <br>
 *
 * Version 1.0.0  Initial version <br>
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/

#include <xmc_gpio.h>

/*******************************************************************************
 * MACROS
 *******************************************************************************/

#define PORT_HWSEL_Msk PORT0_HWSEL_HW0_Msk

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

XMC_DRIVER_VERSION_t XMC_GPIO_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = (uint8_t)XMC_GPIO_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_GPIO_MINOR_VERSION;
  version.patch = (uint8_t)XMC_GPIO_PATCH_VERSION;

  return version;
}

void XMC_GPIO_SetMode(XMC_GPIO_PORT_t *const port, const uint8_t pin, const XMC_GPIO_MODE_t mode)
{
  XMC_ASSERT("XMC_GPIO_SetMode: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_SetMode: Invalid mode", XMC_GPIO_CHECK_MODE(mode));

  port->IOCR[(uint32_t)pin >> 2U] &= ~(uint32_t)((uint32_t)PORT_IOCR_PC_Msk << ((uint32_t)PORT_IOCR_PC_Size * ((uint32_t)pin & 0x3U)));
  port->IOCR[(uint32_t)pin >> 2U] |= (uint32_t)mode << ((uint32_t)PORT_IOCR_PC_Size * ((uint32_t)pin & 0x3U));
}

void XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT_t *const port, const uint8_t pin, const XMC_GPIO_HWCTRL_t hwctrl)
{
  XMC_ASSERT("XMC_GPIO_SetHardwareControl: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_SetHardwareControl: Invalid hwctrl", XMC_GPIO_CHECK_HWCTRL(hwctrl));

  port->HWSEL &= ~(uint32_t)((uint32_t)PORT_HWSEL_Msk << ((uint32_t)pin << 1U));
  port->HWSEL |= (uint32_t)hwctrl << ((uint32_t)pin << 1U);
}
