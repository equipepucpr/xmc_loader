/**************************************************************************
 * @file     xmc1000_flasher.c
 * @brief    Implementation of FLASH programming functions for XMC1000
 *           Cortex M0 family on-chip program FLASH memory devices.
 *           
 * @version  V1.0
 * @date     1 May 2013
 *
 * @note
 * Copyright (C) 2013 Infineon Technologies AG. All rights reserved.
 *
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use 
 * with Infineon’s microcontrollers. This file can be freely distributed 
 * within development tools that are supporting such microcontrollers. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, 
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
 * SOFTWARE.INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, 
 * INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 **************************************************************************/
 
#include "xmc1000_flasher.h"

// ----------------------------------------------------------------------------
//   local prototypes
// ----------------------------------------------------------------------------

extern BYTE* p;

// ----------------------------------------------------------------------------
//   local data
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//   public functions
// ----------------------------------------------------------------------------

int XMC1000_FLASH_ProgramPage(unsigned long PageAddr)
{
	signed long error;

	error = XMC1000_NvmProgVerify((unsigned long *) (p+2), (unsigned long * )PageAddr);
	if (error == BSL_NVM_OK) return FLASHER_SUCCESS;
	else return FLASHER_E_FAILED;

}



int XMC1000_FLASH_EraseSector(unsigned long SectorAddr)
{
	signed long error = 0;
	unsigned int i;

	for (i=0;i<16;i++)
	{
		SectorAddr = SectorAddr + i*256 ;
		error = XMC1000_NvmErasePage((unsigned long *)SectorAddr);

	}
	if (error == BSL_NVM_OK) return FLASHER_SUCCESS;
	else return FLASHER_E_FAILED;

}

