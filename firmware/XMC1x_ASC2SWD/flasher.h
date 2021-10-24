/**************************************************************************
 * @file     flasher.h
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
 * with Infineon�s microcontrollers. This file can be freely distributed 
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

#ifndef __FLASHER_H__
#define __FLASHER_H__

// TYPE:   Type definitions ------------------------------------------------


// MACRO:  Return codes ------------------------------------------------
//   Return codes emitted by the flasher functions.
//

#define FLASHER_SUCCESS         0     // operation succeeded
#define FLASHER_E_FAILED        -1		// operation failed


// --------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//   local defines
// ----------------------------------------------------------------------------
#define XMC1000_FLASH_PAGE_START_MASK			0x0FF

//FLASH CONSTANTS
typedef unsigned char   BYTE;
typedef unsigned int    UINT;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned long long QWORD;


//FLASH CONSTANTS

#define PAGE_SIZE        	   256   // program FLASH page size

//BSL CONSTANTS

#define HEADER_BLOCK_SIZE  	   16
#define DATA_BLOCK_SIZE  	   PAGE_SIZE+8

#define HEADER_BLOCK 		   0x00
#define DATA_BLOCK 	 		   0x01
#define EOT_BLOCK			   0x02

#define BSL_PROGRAM_FLASH      0x00
#define BSL_CHANGE_BMI         0x01
#define BSL_ERASE_FLASH        0x03
#define BSL_READ_FLASH         0x04

#define BSL_BLOCK_TYPE_ERROR     0xFF
#define BSL_MODE_ERROR 		     0xFE 
#define BSL_CHKSUM_ERROR 	     0xFD
#define BSL_ADDRESS_ERROR 	     0xFC
#define BSL_ERASE_ERROR		     0xFB
#define BSL_PROGRAM_ERROR	     0xFA
#define BSL_SUCCESS 		     0x55
#define BSL_ERASE_SUCCESS 		 0x50

#define BSL_NVM_OK               0x00010000



#endif  // __FLASHER_H__
