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
 * @file xmc_acmp.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief ACMP low level driver API prototype definition for XMC1 family of microcontrollers <br>
 *
 * <b>Detailed description of file</b> <br>
 * APIs provided in this file mainly cover the following functionality of ACMP: <br>
 * ---- Filter, Hysterisis, Output inversion
 *
 * Version 1.0.0 Initial <br>
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_acmp.h>

/* If ACMP is available*/
#if defined (COMPARATOR)

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/

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
 * LOCAL ROUTINES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/

/* API to retrieve driver version */
XMC_DRIVER_VERSION_t XMC_ACMP_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = XMC_ACMP_MAJOR_VERSION;
  version.minor = XMC_ACMP_MINOR_VERSION;
  version.patch = XMC_ACMP_PATCH_VERSION;

  return version;
}

/* API to initialize an instance of ACMP module */
XMC_ACMP_STATUS_t XMC_ACMP_Init(XMC_ACMP_t *const peripheral, uint32_t instance, const XMC_ACMP_CONFIG_t *const config)
{
  
  XMC_ASSERT("XMC_ACMP_Init:NULL Configuration", (config != (XMC_ACMP_CONFIG_t *)NULL))
  XMC_ASSERT("XMC_ACMP_Init:Wrong module pointer", XMC_ACMP_CHECK_MODULE_PTR(peripheral))
  XMC_ASSERT("XMC_ACMP_Init:Wrong instance number", XMC_ACMP_CHECK_INSTANCE(instance) )
  
  if (instance == XMC_ACMP_SLICE_0)
  {
    peripheral->ANACMP0 = (uint16_t)(config->anacmp);
  }
  else if (instance == XMC_ACMP_SLICE_1)
  {
    peripheral->ANACMP1 = (uint16_t)(config->anacmp);
  }
  else
  {
    peripheral->ANACMP2 = (uint16_t)(config->anacmp);
  }
  XMC_ACMP_EnableComparator(peripheral,instance);

  return XMC_ACMP_STATUS_SUCCESS;
}

/* API to enable an instance of ACMP */
void XMC_ACMP_EnableComparator(XMC_ACMP_t *const peripheral, uint32_t instance)
{
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong module pointer", XMC_ACMP_CHECK_MODULE_PTR(peripheral))
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong instance number", XMC_ACMP_CHECK_INSTANCE(instance) )

  if (instance == XMC_ACMP_SLICE_0)
  {
    peripheral->ANACMP0 |= (uint16_t)COMPARATOR_ANACMP0_CMP_EN_Msk;
  }
  else if (instance == XMC_ACMP_SLICE_1)
  {
    peripheral->ANACMP1 |= (uint16_t)COMPARATOR_ANACMP1_CMP_EN_Msk;
  }
  else
  {
    peripheral->ANACMP2 |= (uint16_t)COMPARATOR_ANACMP2_CMP_EN_Msk;
  }
}

/* API to disable an instance of ACMP */
void XMC_ACMP_DisableComparator(XMC_ACMP_t *const peripheral, uint32_t instance)
{
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong module pointer", XMC_ACMP_CHECK_MODULE_PTR(peripheral))
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong instance number", XMC_ACMP_CHECK_INSTANCE(instance) )

  if (instance == XMC_ACMP_SLICE_0)
  {
    peripheral->ANACMP0 &= (uint16_t)(~((uint32_t)COMPARATOR_ANACMP0_CMP_EN_Msk));
  }
  else if (instance == XMC_ACMP_SLICE_1)
  {
    peripheral->ANACMP1 &= (uint16_t)(~((uint32_t)COMPARATOR_ANACMP1_CMP_EN_Msk));
  }
  else
  {
    peripheral->ANACMP2 &= (uint16_t)(~((uint32_t)COMPARATOR_ANACMP2_CMP_EN_Msk));
  }
}

/* API to select INP source */
void XMC_ACMP_SetInput(XMC_ACMP_t *const peripheral, uint32_t instance, XMC_ACMP_INP_SOURCE_t source)
{
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong module pointer", XMC_ACMP_CHECK_MODULE_PTR(peripheral))
  XMC_ASSERT("XMC_ACMP_EnableComparator:Wrong instance number", XMC_ACMP_CHECK_INSTANCE(instance) )
  
  if (instance == XMC_ACMP_SLICE_0)
  {
    XMC_ASSERT("XMC_ACMP_SelectInput:Wrong analog source", ((source == XMC_ACMP_INP_SOURCE_STANDARD_PORT) ||
                                                        (source == XMC_ACMP_INP_SOURCE_ACMP1_INP_PORT)) )
    if (XMC_ACMP_INP_SOURCE_STANDARD_PORT == source)
    {
      /* Program the comparators to receive INP from the PORT PADS */	 
      peripheral->ANACMP0 |= (uint16_t)(COMPARATOR_ANACMP0_ACMP0_SEL_Msk);
    }
    else
    {
      /* Program the comparator to receive INP from ACMP1 INP */
      peripheral->ANACMP0 &= (uint16_t)(~COMPARATOR_ANACMP0_ACMP0_SEL_Msk);
    }
  }
  else if (instance == XMC_ACMP_SLICE_1)
  {
    XMC_ASSERT("XMC_ACMP_SetInput:Wrong analog source", (source < XMC_ACMP_INP_SOURCE_ACMP1_INP_PORT))
    if(source == XMC_ACMP_INP_SOURCE_REF_DIV)
    {
      /* First, enable the divider switch using ANACMP1 register */
      peripheral->ANACMP1 |= (uint16_t)(COMPARATOR_ANACMP1_REF_DIV_EN_Msk);
    }
  }
  else
  {
    XMC_ASSERT("XMC_ACMP_SelectInput:Wrong analog source", ((source == XMC_ACMP_INP_SOURCE_STANDARD_PORT) ||
                                                        (source == XMC_ACMP_INP_SOURCE_ACMP1_INP_PORT)) )

    if (XMC_ACMP_INP_SOURCE_STANDARD_PORT == source)
    {
      /* Program the comparator-2 to receive INP from the PORT PADS */	 
      peripheral->ANACMP2 |= (uint16_t)(COMPARATOR_ANACMP2_ACMP2_SEL_Msk);
    }
    else
    {
      /* Program the comparator-2 to receive INP from ACMP1 INP */
      peripheral->ANACMP2 &= (uint16_t)(~COMPARATOR_ANACMP2_ACMP2_SEL_Msk);
    }
  }
}

#endif /* #ifdef ACMP_AVAILABLE */
