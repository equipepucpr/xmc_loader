
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
 * @file xmc_prng.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief PRNG driver for XMC microcontroller family.
 *
 * History <br>
 *
 * Version 1.0.0  Initial <br>
 */ 
 
#include "xmc_prng.h"

#if defined (PRNG)

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/
 
/*
 * Retrieves the version of the PRNG driver
 */
XMC_DRIVER_VERSION_t XMC_PRNG_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = (uint8_t)XMC_PRNG_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_PRNG_MINOR_VERSION;
  version.patch = (uint8_t)XMC_PRNG_PATCH_VERSION;

  return version;
}

/*
 * Initializes the PRNG peripheral with the settings in the
 * initialization structure XMC_PRNG_INIT_t
 */
XMC_PRNG_INIT_STATUS_t XMC_PRNG_Init(const XMC_PRNG_INIT_t *prng)
{
  volatile uint16_t read_warm_up;
  uint16_t reg_val, iter;
  XMC_PRNG_INIT_STATUS_t status = XMC_PRNG_INITIALIZED;
  
  XMC_ASSERT("XMC_PRNG_Init:Null Pointer", (prng != (XMC_PRNG_INIT_t *)NULL));

  /* Configure block size for key loading mode */
  XMC_PRNG_SetRandomDataBlockSize(XMC_PRNG_RDBS_WORD);

  /* Enable key loading mode */
  XMC_PRNG_EnableKeyLoadingMode();

  /* Load key words (80 bits) and wait till RDV is set */
  for (iter = (uint16_t)0UL; iter < (uint16_t)5UL; iter++)
  {
    XMC_PRNG_LoadKeyWords(prng->key_words[iter]);
    while (PRNG_CHK_RDV_Msk != XMC_PRNG_CheckValidStatus());
  }
  
  XMC_PRNG_EnableStreamingMode();

  /* Warm up phase: Read and discard 64 bits */
  read_warm_up = PRNG->WORD;
  read_warm_up = PRNG->WORD;
  read_warm_up = PRNG->WORD;
  reg_val      = PRNG->WORD;
  read_warm_up &= reg_val;

  /* Configure block size either byte (8 bit) or word (16 bit) */
  XMC_PRNG_SetRandomDataBlockSize(prng->block_size);

  /*
   * Checks for reset value for "random data block size". If reset,
   * PRNG is not initialized
   */
  if ((uint16_t)XMC_PRNG_RDBS_RESET == (PRNG->CTRL & (uint16_t)PRNG_CTRL_RDBS_Msk))
  {
    status = XMC_PRNG_NOT_INITIALIZED;
  }

  return status;
}

/*
 * De-initialize the PRNG peripheral 
 */
void XMC_PRNG_DeInit(void)
{
  PRNG->CTRL = (uint16_t)0UL;
  PRNG->WORD = (uint16_t)0UL;
}

#endif /* #if defined (PRNG) */
