/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * 
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,OR CONSEQUENTIAL DAMAGES, FOR ANY REASON
 * WHATSOEVER.
 */

/**
 * @file xmc_scu.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief SCU driver - API implementation common to all devices <br>
 *
 * <b>Detailed description of file</b> <br>
 * Only the Versioning API is today a common API.
 * 
 * History
 *
 * Version 1.0.0 Initial <br>
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_scu.h>

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/

/*  API to retrieve version of the SCU driver */
XMC_DRIVER_VERSION_t XMC_SCU_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;
  version.major = (uint8_t)XMC_SCU_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_SCU_MINOR_VERSION;
  version.patch = (uint8_t)XMC_SCU_PATCH_VERSION;
   
  return version;
}
