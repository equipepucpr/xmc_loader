
/**************************************************************************//**
 *
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon <Microcontroller name, step>                           **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** MODIFICATION DATE : June 16, 2014                                          **
**                                                                            **
*******************************************************************************/

/**
 * @file  DAVE.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes
 *
 * Revision History
 * 16 June 2014 v0.3.0 Initial Version
 *
 */

#ifndef _DAVE_H_
#define _DAVE_H_

/*******************************************************************************
**                      @Project Includes                                     **
*******************************************************************************/

/** #include DAVE App Header files. */

#include "xmc_common.h"  
	

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
typedef enum DAVE_STATUS
{
  DAVE_STATUS_SUCCESS = 0,
  DAVE_STATUS_FAILURE,
  DAVE_STATUS_ALREADY_INITIALIZED
} DAVE_STATUS_t;

/*******************************************************************************
**                      @Prototypes Of Global Functions                       **
*******************************************************************************/

DAVE_STATUS_t DAVE_Init(void);

#endif  /** ifndef _DAVE_H_ */

