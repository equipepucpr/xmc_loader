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
 *
 */

 /**
 * @file xmc1_eru.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief ERU driver for XMC microcontroller family.
 *
 * History <br>
 *
 * Version 1.0.0 Initial version <br>
 */

#include "xmc_eru.h"

#if UC_FAMILY == XMC1

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/

void XMC_ERU_Enable(XMC_ERU_t *const eru)
{
  XMC_UNUSED_ARG(eru);
}

void XMC_ERU_Disable(XMC_ERU_t *const eru)
{
  XMC_UNUSED_ARG(eru);
}

#endif /* if( UC_FAMILY == XMC1 ) */
