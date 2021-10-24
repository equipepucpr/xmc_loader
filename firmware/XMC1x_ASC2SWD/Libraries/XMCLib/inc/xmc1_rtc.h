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
 */

/**
 * @file xmc1_rtc.h
 * @date 20 Feb, 2015
 * @version 1.0.2
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.2  Documentation updates <br>
 */

#ifndef XMC1_RTC_H
#define XMC1_RTC_H

/**
 * @addtogroup XMClib XMC Peripheral Library
 * @{
 */

/**
 * @addtogroup RTC
 * @{
 */
/*******************************************************************************
 * ENUMS
 *******************************************************************************/

/**
 * Debug mode status values
 */
typedef enum XMC_RTC_DEBUG_MODE
{
  XMC_RTC_RUN_IN_DEBUG_MODE  = 0U, /**< RTC is not stopped during halting mode debug */
  XMC_RTC_STOP_IN_DEBUG_MODE = 1U  /**< RTC is stopped during halting mode debug */  
} XMC_RTC_DEBUG_MODE_t;

/*******************************************************************************
 * API PROTOTYPES
 *******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param debug_mode Debug mode value containing in (::XMC_RTC_DEBUG_MODE_t) to be set                 
 * @return None
 *
 * \par<b>Description: </b><br>
 * Configures the RTC into running or stopping mode during halting mode debug <br>
 *
 * \par
 * The function sets the CTR.SUS bitfield to configure the RTC into running 
 * or stopping mode during halting mode debug.
 */   
void XMC_RTC_SetDebugMode(const XMC_RTC_DEBUG_MODE_t debug_mode);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */
 
#endif /* XMC1_RTC_H */
