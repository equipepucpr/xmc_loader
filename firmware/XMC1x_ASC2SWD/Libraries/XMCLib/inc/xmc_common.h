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
 * @file xmc_common.h
 * @date 20 Feb, 2015
 * @version 1.0.2
 *
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.2 Brief section updated <br>
 */

#ifndef XMC_COMMON_H
#define XMC_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "xmc_device.h"

/**
 * @addtogroup XMClib XMC Peripheral Library
 * @{
 */

/**
 * @addtogroup COMMON
 * @brief Common APIs to all peripherals for XMC microcontroller family 
 * @{
 */

/*******************************************************************************
 * MACROS
 *******************************************************************************/
/* Define WEAK attribute */
#if !defined(__WEAK)
#if defined ( __CC_ARM )
#define __WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
#define __WEAK __weak
#elif defined ( __GNUC__ )
#define __WEAK __attribute__ ((weak))
#elif defined ( __TASKING__ )
#define __WEAK __attribute__ ((weak))
#endif
#endif

#ifdef XMC_ASSERT_ENABLE
 #define XMC_ASSERT(msg, exp) { if(!(exp)) {XMC_AssertHandler(msg, __FILE__, __LINE__);} }
#else
 #define XMC_ASSERT(msg, exp) { ; }
#endif

#ifdef XMC_DEBUG_ENABLE
 #include <stdio.h>
 #define XMC_DEBUG(msg) { printf(msg); }
#else
 #define XMC_DEBUG(msg) { ; }
#endif

#define XMC_UNUSED_ARG(x) (void)x

#define XMC_STRUCT_INIT(m) memset(&m, 0, sizeof(m))

#define XMC_PRIOARRAY_DEF(name, size) \
XMC_PRIOARRAY_ITEM_t prioarray_m_##name[size + 2]; \
XMC_PRIOARRAY_t prioarray_def_##name = {(size), (prioarray_m_##name)};

#define XMC_PRIOARRAY(name) \
&prioarray_def_##name

/*******************************************************************************
 * DATA STRUCTURES
 *******************************************************************************/
/*
 *
 */
typedef struct XMC_DRIVER_VERSION 
{
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
} XMC_DRIVER_VERSION_t;

/*
 *
 */
typedef void *XMC_LIST_t;

/*
 *
 */
typedef struct XMC_PRIOARRAY_ITEM
{
  int32_t priority;
  int32_t previous;
  int32_t next;
} XMC_PRIOARRAY_ITEM_t;

/*
 *
 */
typedef struct XMC_PRIOARRAY
{
  uint32_t size;
  XMC_PRIOARRAY_ITEM_t *items;
} XMC_PRIOARRAY_t;

/*******************************************************************************
 * API PROTOTYPES
 *******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 */
void XMC_AssertHandler(const char *const msg, const char *const file, uint32_t line);

/*
 *
 */
void XMC_LIST_Init(XMC_LIST_t *list);

/*
 *
 */
void XMC_LIST_Add(XMC_LIST_t *list, void *const item);

/*
 *
 */
void XMC_LIST_Remove(XMC_LIST_t *list, void *const item);

/*
 *
 */
uint32_t XMC_LIST_GetLength(XMC_LIST_t *list);

/*
 *
 */
void *XMC_LIST_GetHead(XMC_LIST_t *list);

/*
 *
 */
void *XMC_LIST_GetTail(XMC_LIST_t *list);

/*
 *
 */
void XMC_LIST_Insert(XMC_LIST_t *list, void *prev_item, void *new_item);

/*
 *
 */
void XMC_PRIOARRAY_Init(XMC_PRIOARRAY_t *prioarray);

/*
 *
 */
void XMC_PRIOARRAY_Add(XMC_PRIOARRAY_t *prioarray, int32_t item, int32_t priority);

/*
 *
 */
void XMC_PRIOARRAY_Remove(XMC_PRIOARRAY_t *prioarray, int32_t item);

/*
 *
 */
__STATIC_INLINE int32_t XMC_PRIOARRAY_GetHead(XMC_PRIOARRAY_t *prioarray)
{
  XMC_ASSERT("XMC_PRIOARRAY_Init: NULL pointer", prioarray != NULL);
  return prioarray->items[prioarray->size].next;
}

/*
 *
 */
__STATIC_INLINE int32_t XMC_PRIOARRAY_GetTail(XMC_PRIOARRAY_t *prioarray)
{
  XMC_ASSERT("XMC_PRIOARRAY_Init: NULL pointer", prioarray != NULL);
  return prioarray->items[prioarray->size + 1].previous;
}

/*
 *
 */
__STATIC_INLINE int32_t XMC_PRIOARRAY_GetItemPriority(XMC_PRIOARRAY_t *prioarray, int32_t item)
{
  XMC_ASSERT("XMC_PRIOARRAY_GetItemPriority: item out of range", (item >= 0) && (item < prioarray->size));
  return prioarray->items[item].priority;
}

/*
 *
 */
__STATIC_INLINE int32_t XMC_PRIOARRAY_GetItemNext(XMC_PRIOARRAY_t *prioarray, int32_t item)
{
  XMC_ASSERT("XMC_PRIOARRAY_GetItemNext: item out of range", (item >= 0) && (item < prioarray->size));
  return prioarray->items[item].next;
}

/*
 *
 */
__STATIC_INLINE int32_t XMC_PRIOARRAY_GetItemPrevious(XMC_PRIOARRAY_t *prioarray, int32_t item)
{
  XMC_ASSERT("XMC_PRIOARRAY_GetItemPrevious: item out of range", (item >= 0) && (item < prioarray->size));
  return prioarray->items[item].previous;
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */

#endif /* XMC_COMMON_H */
