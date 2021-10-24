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
 * @file xmc_acmp.h
 * @date 16 Feb, 2015
 * @version 1.0.2
 *
 * 
 *
 * <b>Detailed description of file</b> <br>
 * APIs provided in this file mainly cover the following functionality of ACMP: <br>
 * ---- Filter, Hysteresis, Output inversion
 *
 * History<br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.2 Removed unused declarations<br> 
 */
 
#ifndef XMC_ACMP_H
#define XMC_ACMP_H
 
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup XMClib XMC Peripheral Library
 * @{
 */

/**
 * @addtogroup ACMP
 * @brief Analog Comparator(ACMP) low level driver for XMC family of microcontrollers. <br>
 *
 * The ACMP module consists of 3 analog comparators. Each analog comparator has two inputs, INP and INN. 
 * Input INP is compared with input INN in the pad voltage domain.
 * It generates a digital comparator output signal. The digital comparator output signal is shifted down from VDDP 
 * power supply voltage level to VDDC core voltage level. The ACMP module provides the following functionalities.\n
 * -# Monitor external voltage level
 * -# Operates in low power mode
 * -# Provides Inverted ouput option\n

 * \par The ACMP low level driver funtionalities\n
 * <OL>
 * <LI>Initializes an instance of analog comparator module with the @ref XMC_ACMP_CONFIG_t configuration structure 
 * using the API XMC_ACMP_Init().</LI>
 * <LI>Programs the source of input(INP) specified by @ref XMC_ACMP_INP_SOURCE_t parameter using the API 
 * XMC_ACMP_SetInput(). </LI>
 * <LI>Sets the low power mode of operation using XMC_ACMP_SetLowPowerMode() API.</LI>
 * </OL>
 * @{
 */
 
/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_common.h>

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* If ACMP is available*/
#if defined (COMPARATOR)

#define XMC_ACMP_MAJOR_VERSION (1U) /**< Major number of the driver version. Format \<major\>.\<minor\>.\<patch\>*/
#define XMC_ACMP_MINOR_VERSION (0U) /**< Minor number of the driver version. Format \<major\>.\<minor\>.\<patch\>*/
#define XMC_ACMP_PATCH_VERSION (2U) /**< Patch number of the driver version. Format \<major\>.\<minor\>.\<patch\>*/

#define XMC_ACMP_MAX_INSTANCES (3U) /* Maximum number of Analog Comparators available*/

#define XMC_ACMP_SLICE_0        (0U) /**< Instance number for Slice-0 */
#define XMC_ACMP_SLICE_1        (1U) /**< Instance number for Slice-1 */
#define XMC_ACMP_SLICE_2        (2U) /**< Instance number for Slice-2 */

/* Checks if the pointer being passed is valid*/
#define XMC_ACMP_CHECK_MODULE_PTR(PTR)  (((PTR)== COMPARATOR))

/* Checks if the instance being addressed is valid*/
#define XMC_ACMP_CHECK_INSTANCE(INST)   (((INST)< XMC_ACMP_MAX_INSTANCES))

/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/
/**
 * Defines the analog comparator module.
 */
typedef COMPARATOR_Type XMC_ACMP_t;

/**
 * Defines the return value of an API.
 */ 
typedef enum XMC_ACMP_STATUS
{
  XMC_ACMP_STATUS_SUCCESS = 0U, /**< API completes the execution successfully */
  XMC_ACMP_STATUS_ERROR       , /**< API cannot fulfill the request */
} XMC_ACMP_STATUS_t;

/**
 * Defines the hysteresis voltage levels to reduce noise sensitivity.
 */ 
typedef enum XMC_ACMP_HYSTERESIS
{
  XMC_ACMP_HYSTERESIS_OFF = 0, /**< No hysteresis */
  XMC_ACMP_HYSTERESIS_10     , /**< Hysteresis = 10mv */
  XMC_ACMP_HYSTERESIS_15     , /**< Hysteresis = 15mv */
  XMC_ACMP_HYSTERESIS_20       /**< Hysteresis = 20mv */
} XMC_ACMP_HYSTERESIS_t;

/**
 *  Defines the Comparator output status.
 */ 
typedef enum XMC_ACMP_COMP_OUT
{
  XMC_ACMP_COMP_OUT_NEG_HIGHER = 0,  /**< Input Negative(INN) greater than Input Positive(INP). Vminus > Vplus*/
  XMC_ACMP_COMP_OUT_POS_HIGHER       /**< Input Positive(INP) greater than Input Negative(INN). Vminus < Vplus */
} XMC_ACMP_COMP_OUT_t;

/**
 *  Defines the analog comparator input connection method.
 */ 
typedef enum XMC_ACMP_INP_SOURCE
{
  XMC_ACMP_INP_SOURCE_STANDARD_PORT = 0,  /**< Input is connected to port */
  XMC_ACMP_INP_SOURCE_REF_DIV          ,  /**< Input is connected to Reference Divider */
  XMC_ACMP_INP_SOURCE_ACMP1_INP_PORT      /**< Input is connected to ACMP-1 INP */
} XMC_ACMP_INP_SOURCE_t;

/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/


/*Anonymous structure/union guard start*/
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__TASKING__)
  #pragma warning 586
#endif

/**
 *  Structure for initializing the ACMP module. It configures the ANACMP register of the respective input.
 */
typedef struct XMC_ACMP_CONFIG
{
  union
  {
    struct
    {
	  uint32_t                  : 1;
	  uint32_t filter_disable   : 1; /**< Comparator filter option for removing glitches. By default this option
	                                      is selected in ANACMP register. Setting this option disables the filter */
	  uint32_t                  : 1;
	  uint32_t output_invert    : 1; /**< Option to invert the comparator output. */
	  uint32_t hysteresis       : 2; /**< Hysteresis voltage to reduce noise sensitivity. Select the voltage levels
	                                      from the values defined in @ref XMC_ACMP_HYSTERESIS_t. */
	  uint32_t                  : 26;
    };
    uint32_t anacmp;
  };
} XMC_ACMP_CONFIG_t;

/*Anonymous structure/union guard end*/
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__TASKING__)
  #pragma warning restore
#endif

/*********************************************************************************************************************
 * API Prototypes
 ********************************************************************************************************************/

/**
 * @return Data structure @ref XMC_DRIVER_VERSION_t storing driver version
 *
 * \par<b>Description: </b><br>
 * Return the version of the low level driver <br>
 *
 * \par
 * The function can be used to check application software compatibility with a specific version of the low level driver.
 *
 * \par<b>Related APIs:</b><br>
 * None
 */
XMC_DRIVER_VERSION_t XMC_ACMP_GetDriverVersion(void);

/**
 * @param peripheral Constant pointer to ACMP instance, of @ref XMC_ACMP_t type.
 * @param instance ACMP instance Number. Use one of the Macros @ref XMC_ACMP_SLICE_0/ @ref XMC_ACMP_SLICE_1/ 
                   @ref XMC_ACMP_SLICE_2 <BR>
 *                 Range: [0x0 to 0x2]
 * @param config Pointer to configuration data. Refer data structure @ref XMC_ACMP_CONFIG_t for details.
 * @return
 *   @ref XMC_ACMP_STATUS_t returns \a XMC_ACMP_STATUS_SUCCESS , if succeeded else returns \a XMC_ACMP_STATUS_FAILURE
 *
 * \par<b>Description:</b><br>
 *  Initializes an instance of analog comparator module.<BR>\n
 *  Configures the ANACMP resister \a instance with hysteresis, comparator filter and inverted comparator output
 *  specified in the \a config structure. It internally calls XMC_ACMP_EnableComparator() to enable the analog
 *  comparator before setting the configurations.
 *
 * \par<b>Related APIs:</b><br>
 *  None.
 */
XMC_ACMP_STATUS_t XMC_ACMP_Init(XMC_ACMP_t *const peripheral, uint32_t instance, const XMC_ACMP_CONFIG_t *const config);

/**
 * @param peripheral Constant pointer to ACMP instance, of @ref XMC_ACMP_t type..
 * @param instance  ACMP instance Number
 *                  Use one of the Macros @ref XMC_ACMP_SLICE_0/ @ref XMC_ACMP_SLICE_1/ @ref XMC_ACMP_SLICE_2 <BR>
 *                  Range: [0x0 to 0x2]
 * @return
 *    None<BR>
 *
 * \par<b>Description:</b><br>
 * Enables an instance of ACMP module.<BR>\n
 * Enables a specific analog comparator for operation. The \a instance number determines which analog comparator to be
 * switched on. Sets the CMP_EN bit of respective ANACMP register specified in the \a instance number passed. Call this
 * API before accessing any ANACMP related Hardware functionalities.
 *
 * \par<b>Related APIs:</b><br>
 * XMC_ACMP_Init().<BR>
 * XMC_ACMP_DisableComparator().<BR>
 */
void XMC_ACMP_EnableComparator(XMC_ACMP_t *const peripheral, uint32_t instance);


/**
 * @param peripheral Constant pointer to analog comparator instance, of @ref XMC_ACMP_t type.
 * @param instance  ACMP instance Number.
 *                  Use one of the Macros @ref XMC_ACMP_SLICE_0/ @ref XMC_ACMP_SLICE_1/ @ref XMC_ACMP_SLICE_2 <BR>
 *                  Range: [0x0 to 0x2]
 * @return
 *    None<BR>
 * \par<b>Description:</b><br>
 * Disables an instance of ACMP module.<BR>\n
 * Disables a specific analog comparator for operation. The \a instance number determines which analog comparator to be
 * switched off. Resets the CMP_EN bit of respective ANACMP register specified in the \a instance number passed.
 *
 * \par<b>Related APIs:</b><br>
 * XMC_ACMP_EnableComparator().
 */
void XMC_ACMP_DisableComparator(XMC_ACMP_t *const peripheral, uint32_t instance);

/**
 * @param peripheral Constant pointer to analog comparator instance, of @ref XMC_ACMP_t type.
 * @param instance analog comparator instance Number.
 *                 Use one of the Macros @ref XMC_ACMP_SLICE_0/ @ref XMC_ACMP_SLICE_1/ @ref XMC_ACMP_SLICE_2<BR>
 *                 Range: [0x0 to 0x2]
 * @param source Input source. Refer @ref XMC_ACMP_INP_SOURCE_t for possible values<BR>
 * @return
 *    None<BR>
 *
 * \par<b>Description:</b><br>
 * Programs the source of INP.<BR>\n
 * INP can be driven by either an internal reference voltage or by an analog port input. Selects the Input for the
 * specific \a instance of the analog comparator. Directly accessed registers are  ANACMP0, ANACMP1, ANACMP2 according
 * to the instance number passed.
 *
 * \par<b>Related APIs:</b><br>
 * None.
 */
void XMC_ACMP_SetInput(XMC_ACMP_t *const peripheral, uint32_t instance, const XMC_ACMP_INP_SOURCE_t source);


/**
 * @param None
 * @return
 *    None<BR>
 *
 * \par<b>Description:</b><br>
 * Sets up low power mode.<BR>\n
 * The low power mode is controlled by analog comparator module0. It is necessary to request low power mode of
 * operation for all instances of ACMP for the feature to be turned on. Sets LPWR bit of ANACMP0 register.
 *
 * \par<b>Related APIs:</b><br>
 * XMC_ACMP_ClearLowPowerMode().
 */
__STATIC_INLINE void XMC_ACMP_SetLowPowerMode(void)
{
  COMPARATOR->ANACMP0 |= COMPARATOR_ANACMP0_CMP_LPWR_Msk;
}

/**
 * @param None 
 * @return
 *    None<BR>
 *
 * \par<b>Description:</b><br>
 * Exits the low power mode.<BR>\n
 * The low power mode is controlled by ACMP0 module. Turning off the low power feature of any single ACMP instance
 * disables other instances also. Blanking time will be introduce to ensure that the output would remain stable.
 * Resets LPWR bit of ANACMP0 register.
 *
 * \par<b>Related APIs:</b><br>
 * XMC_ACMP_ClearLowPowerMode().
 */
__STATIC_INLINE void XMC_ACMP_ClearLowPowerMode(void)
{
  COMPARATOR->ANACMP0 &= (uint16_t)(~COMPARATOR_ANACMP0_CMP_LPWR_Msk);
}

#endif /* #ifdef ACMP_AVAILABLE */

/**
 * @}
 */

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif
 
#endif /* XMC_ACMP_H */
