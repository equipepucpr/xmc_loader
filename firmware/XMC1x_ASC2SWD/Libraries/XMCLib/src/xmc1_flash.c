/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,OR CONSEQUENTIAL DAMAGES, FOR ANY REASON
 * WHATSOEVER.
 *
 */

/**
 * @file xmc1_flash.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief flash low level driver API prototype definition for XMC1 family of microcontrollers <br>
 *
 * <b>Detailed description of file</b> <br>
 * APIs provided in this file cover the following functional blocks of flash <br>
 *
 * History
 *
 * Version 1.0.0 Initial version<br>
 */

#include "xmc_flash.h"

#if UC_FAMILY == XMC1

/*******************************************************************************
 * MACROS
 *******************************************************************************/
/* FLASH programming / erase options */
typedef enum FLASH_ACTION
{
  FLASH_ACTION_IDLE                        =  (uint32_t)0x00,
  FLASH_ACTION_ONESHOT_WRITE_VERIFY        = ((uint32_t)0x51 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_ONESHOT_WRITE               = ((uint32_t)0x91 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_CONTINUOUS_WRITE_VERIFY     = ((uint32_t)0x61 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_CONTINUOUS_WRITE            = ((uint32_t)0xa1 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_ONESHOT_PAGE_ERASE          = ((uint32_t)0x92 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_CONTINUOUS_PAGE_ERASE       = ((uint32_t)0xa2 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_ONESHOT_VERIFY_ONLY         = ((uint32_t)0xd0 << NVM_NVMPROG_ACTION_Pos),
  FLASH_ACTION_CONTINUOUS_VERIFY_ONLY      = ((uint32_t)0xe0 << NVM_NVMPROG_ACTION_Pos)
} FLASH_ACTION_t;


/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

 /* Returns the Driver major minor patch versionsEach of the XMC low level drivers export a version number.
 * Applications may then audit such a version number to determine compatibility.
 */
XMC_DRIVER_VERSION_t XMC_FLASH_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = (uint8_t)XMC_FLASH_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_FLASH_MINOR_VERSION;
  version.patch = (uint8_t)XMC_FLASH_PATCH_VERSION;

  return version;
}

/*
 * This API shall clear the ECC and VERIFICATION error status.
 */
void XMC_FLASH_ClearStatus(void)
{
  NVM->NVMPROG |= (uint16_t)((uint16_t)NVM_NVMPROG_RSTVERR_Msk | (uint16_t)NVM_NVMPROG_RSTECC_Msk);
}

/*
 * This API shall return the status of NVM.
 */
uint32_t XMC_FLASH_GetStatus(void)
{
  return NVM->NVMSTATUS;
}

/*
 * This API shall enable the the flash interrupt event.
 */
void XMC_FLASH_EnableEvent(const uint32_t event_msk)
{
  NVM->NVMCONF |= (uint16_t)event_msk;
}

/*
 * This API shall disable the the flash interrupt event.
 */
void XMC_FLASH_DisableEvent(const uint32_t event_msk)
{
  NVM->NVMCONF &= (uint16_t)(~(uint16_t)event_msk);
}

void XMC_FLASH_ErasePage(uint32_t *address)
{
  (void)XMC1000_NvmErasePage(address);
}

void XMC_FLASH_ProgramVerifyPage(uint32_t *address, const uint32_t *data)
{
  (void)XMC1000_NvmProgVerify(data, address);
}

/* Write blocks of data into flash*/
void XMC_FLASH_WriteBlocks(uint32_t *address, const uint32_t *data, uint32_t num_blocks, bool verify)
{
  uint32_t word;
  uint32_t block;

  XMC_ASSERT("XMC_FLASH_WriteBlocks: Starting address not aligned to Block",
                                                                   ((uint32_t)address & FLASH_BLOCK_ADDR_MASK) == 0U)

  /* Configure the continuous Write option command and reset the NVM error / verification status*/
  NVM->NVMPROG &= (uint16_t)(~(uint16_t)NVM_NVMPROG_ACTION_Msk);
  NVM->NVMPROG |= (uint16_t)(NVM_NVMPROG_RSTVERR_Msk | NVM_NVMPROG_RSTECC_Msk);

  if (verify == true)
  {
    NVM->NVMPROG |= (uint16_t)FLASH_ACTION_CONTINUOUS_WRITE_VERIFY;
  }
  else
  {
    NVM->NVMPROG |= (uint16_t)FLASH_ACTION_CONTINUOUS_WRITE;
  }

  for (block = 0U; block < num_blocks; ++block)
  {
    for (word = 0U; word < XMC_FLASH_WORDS_PER_BLOCK; ++word)
    {
      *address = *data;
      data++;
      address++;
    }
      
    while (XMC_FLASH_IsBusy() == true)
    {
    }
  }

  /* Stop continuous write operation */
  NVM->NVMPROG &= (uint16_t)(~(uint16_t)NVM_NVMPROG_ACTION_Msk);
}

/* Erase flash pages */
void XMC_FLASH_ErasePages(uint32_t *address, uint32_t num_pages)
{
  uint32_t page;

  XMC_ASSERT("XMC_FLASH_ErasePages: Starting address not aligned to Page",
                                                                    ((uint32_t)address & FLASH_PAGE_ADDR_MASK) == 0U)

  /* Configure the continuous erase option command and reset the NVM error / verification status*/
  NVM->NVMPROG &= (uint16_t)(~(uint16_t)NVM_NVMPROG_ACTION_Msk);
  NVM->NVMPROG |= (uint16_t)((uint16_t)NVM_NVMPROG_RSTVERR_Msk | 
                             (uint16_t)NVM_NVMPROG_RSTECC_Msk | 
	                         (uint16_t)FLASH_ACTION_CONTINUOUS_PAGE_ERASE);

  for (page = 0U; page < num_pages; ++page)
  {
    /* A write access to the starting memory location of the page triggers the erase operation*/
    *address = 0;

    while (XMC_FLASH_IsBusy() == true)
    {
    }

    /* Increment the page address for the next erase */
    address += XMC_FLASH_WORDS_PER_PAGE;

  }

  /* Stop continuous write operation */
  NVM->NVMPROG &= (uint16_t)(~(uint16_t)NVM_NVMPROG_ACTION_Msk);
}

/* Write multiple data blocks and verify the written data */
void XMC_FLASH_VerifyBlocks(uint32_t *address, const uint32_t *data, uint32_t num_blocks)
{
  uint32_t word;
  uint32_t block;

  XMC_ASSERT("XMC_FLASH_VerifyBlocks: Starting address not aligned to Block",
                                                                   ((uint32_t)address & FLASH_BLOCK_ADDR_MASK) == 0U)

  /* Configure the Continuous write with verify option command and reset the NVM error / verification status*/
  NVM->NVMPROG &= (uint16_t)~NVM_NVMPROG_ACTION_Msk;
  NVM->NVMPROG |= (uint16_t)((uint16_t)NVM_NVMPROG_RSTVERR_Msk | 
                             (uint16_t)NVM_NVMPROG_RSTECC_Msk | 
                             (uint16_t)FLASH_ACTION_CONTINUOUS_VERIFY_ONLY);

  for (block = 0U; block < num_blocks; ++block)
  {
    for (word = 0U; word < XMC_FLASH_WORDS_PER_BLOCK; ++word)
    {
      *address = *data;
      data++;
      address++;
    }

    while (XMC_FLASH_IsBusy() == true)
    {
    }
  }

  /* Stop continuous verify operation */
  NVM->NVMPROG &= (uint16_t)(~(uint16_t)NVM_NVMPROG_ACTION_Msk);
}

/* Read data blocks from flash */
void XMC_FLASH_ReadBlocks(uint32_t *address, uint32_t *data, uint32_t num_blocks)
{
  uint32_t word;
  uint32_t block;

  XMC_ASSERT("XMC_FLASH_ReadBlocks: Starting address not aligned to Block",
                                                                  ((uint32_t)address & FLASH_BLOCK_ADDR_MASK) == 0U)

  for (block = 0U; block < num_blocks; ++block)
  {
    for (word = 0U; word < XMC_FLASH_WORDS_PER_BLOCK; ++word)
    {
      *data = *address;
      data++;
      address++;
    }
  }
}

/* Erase single sector */
void XMC_FLASH_EraseSector(uint32_t *address)
{
  XMC_ASSERT("XMC_FLASH_EraseSector: Starting address not aligned to Sector",
                                                                 ((uint32_t)address & FLASH_SECTOR_ADDR_MASK) == 0U)
  XMC_FLASH_ErasePages(address, XMC_FLASH_PAGES_PER_SECTOR);
}

/* Program single page */
void XMC_FLASH_ProgramPage(uint32_t *address, const uint32_t *data)
{
  XMC_FLASH_ProgramVerifyPage(address, data);
}

#endif
