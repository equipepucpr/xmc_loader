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
 * @file xmc1_gpio.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief GPIO low level driver API prototype definition for XMC1 family of microcontrollers <br>
 *
 * History <br>
 *
 * Version 1.0.0  Initial version <br>
 */

#include "xmc_gpio.h"

#if UC_FAMILY == XMC1

/*******************************************************************************
 * MACROS
 *******************************************************************************/

#define PORT_PHCR_Msk             PORT0_PHCR0_PH0_Msk
#define PORT_PHCR_Size            PORT0_PHCR0_PH0_Msk
#define PORT_HWSEL_Msk            PORT0_HWSEL_HW0_Msk

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

void XMC_GPIO_Init(XMC_GPIO_PORT_t *const port, const uint8_t pin, const XMC_GPIO_CONFIG_t *const config)
{
  XMC_ASSERT("XMC_GPIO_Init: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_Init: Invalid mode", XMC_GPIO_CHECK_MODE(config->mode));
  XMC_ASSERT("XMC_GPIO_Init: Invalid input hysteresis", XMC_GPIO_CHECK_INPUT_HYSTERESIS(config->input_hysteresis));
  XMC_ASSERT("XMC_GPIO_Init: Invalid output level", XMC_GPIO_CHECK_OUTPUT_LEVEL(config->output_level));
  
  /* Switch to input */
  port->IOCR[pin >> 2U] &= ~(uint32_t)((uint32_t)PORT_IOCR_PC_Msk << (PORT_IOCR_PC_Size * (pin & 0x3U)));

  /* HW port control is disabled */
  port->HWSEL &= ~(uint32_t)((uint32_t)PORT_HWSEL_Msk << ((uint32_t)pin << 1U));

  /* Set input hysteresis */
  port->PHCR[(uint32_t)pin >> 3U] &= ~(uint32_t)((uint32_t)PORT_PHCR_Msk << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U)));
  port->PHCR[(uint32_t)pin >> 3U] |= (uint32_t)config->input_hysteresis << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U));
    
  /* Enable digital input */
  if (XMC_GPIO_CHECK_ANALOG_PORT(port))
  {    
    port->PDISC &= ~(uint32_t)((uint32_t)0x1U << pin);
  }
  else
  {
    /* Set output level */
    port->OMR = (uint32_t)config->output_level << pin;
  }

  /* Set mode */
  port->IOCR[pin >> 2U] |= (uint32_t)config->mode << (PORT_IOCR_PC_Size * (pin & 0x3U));
}

void XMC_GPIO_SetInputHysteresis(XMC_GPIO_PORT_t *const port, 
                                 const uint8_t pin, 
                                 const XMC_GPIO_INPUT_HYSTERESIS_t hysteresis)
{
  XMC_ASSERT("XMC_GPIO_SetInputHysteresis: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_SetInputHysteresis: Invalid input hysteresis", XMC_GPIO_CHECK_INPUT_HYSTERESIS(hysteresis));

  port->PHCR[(uint32_t)pin >> 3U] &= ~(uint32_t)((uint32_t)PORT_PHCR_Msk << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U)));
  port->PHCR[(uint32_t)pin >> 3U] |= (uint32_t)hysteresis << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U));
}

#endif /* UC_FAMILY == XMC1 */
