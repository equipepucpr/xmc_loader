/**************************************************************************
 * @file     xmc1000_flasher.h
 * @brief    Header file for the XMC1000 Bootloader
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

#ifndef __XMC1000_FLASHER_H__
#define __XMC1000_FLASHER_H__

// include common definitions
#include "flasher.h"

// ----------------------------------------------------------------------------
//   public defines
// ----------------------------------------------------------------------------

/* Constants definitions */
#define ROM_FUNCTION_TABLE_START    (0x00000100)				      ///< Start address of the ROM function table

#define _NvmErase	                (ROM_FUNCTION_TABLE_START + 0x00) ///< Pointer to Erase Flash Page routine
#define _NvmProgVerify	          (ROM_FUNCTION_TABLE_START + 0x04) ///< Pointer to Erase, Program & Verify Flash Page routine
#define _BmiInstallationReq	      (ROM_FUNCTION_TABLE_START + 0x08) ///< Pointer to Request BMI installation routine

/* Types definitions */
typedef enum tagNVMStatus
{
    NVM_PASS                              = (signed long) 0x00010000,   ///< the function succeeded
    NVM_E_FAIL                            = (signed long) 0x80010001,   ///< generic error code
    NVM_E_SRC_AREA_EXCCEED                = (signed long) 0x80010003,   ///< source data not in RAM
    NVM_E_SRC_ALIGNMENT                   = (signed long) 0x80010004,   ///< source data is not 4 byte aligned
    NVM_E_NVM_FAIL                        = (signed long) 0x80010005,   ///< NVM module cannot be physically accessed
    NVM_E_VERIFY                          = (signed long) 0x80010006,   ///< verification of written page not successful
    NVM_E_DST_AREA_EXCEED                 = (signed long) 0x80010009,   ///< destination data is not (completely) located in NVM
    NVM_E_DST_ALIGNMENT                   = (signed long) 0x80010010,   ///< destination data is not properly aligned
} NVM_STATUS;


// MACRO:  Device specific defines ------------------------------------------
#define XMC1000_FLASH_PAGE_SIZE   256  // program FLASH page size
#define XMC1000_NvmErasePage (*((NVM_STATUS (**) (unsigned long * )) _NvmErase)) //addr. must be page aligned, pass = 0x00010000
#define  XMC1000_NvmProgVerify	        (*((NVM_STATUS (**) (unsigned long * , unsigned long * )) _NvmProgVerify)) //addr. must be page aligned, pass= 0x00010000
#define  XMC1000_BmiInstallationReq	    (*((unsigned long (**) (unsigned short)) _BmiInstallationReq)) //BMI value to be install, if OK will trigger reset and does not return to calling routine.
//
// --------------------------------------------------------------------------

int XMC1000_FLASH_ProgramPage(unsigned long PageAddr);
int XMC1000_FLASH_EraseSector(unsigned long SectorAddr);
void ASC_Init(void);

#endif  // __XMC1000_FLASHER_H__
