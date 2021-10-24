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
 * @file xmc_math.c
 * @date 20 Feb, 2015
 * @version 1.0.2
 *
 * @brief MATH driver - API implementation for XMC13 family MATH libraries. <br>
 * 
 * History <br>
 *
 * Version 1.0.0 Initial version <br>
 * Version 1.0.2 Version is updated due to update in xmc_math.h file <br>
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_math.h>

#if defined (MATH)
/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* Reciprocal of Circular gain in XMC_MATH_Q0_23_t format ((2^23)/1.646760258121) */
#define XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023       (0x4DBA76U)
/* Reciprocal of Hyperbolic gain in XMC_MATH_Q1_22_t format ((2^22)/0.828159360960) */
#define XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22    (0x4D47A1U)
/* Signed division is selected */
#define XMC_MATH_SIGNED_DIVISION                      ((uint32_t) 0 << MATH_DIVCON_USIGN_Pos)
/* Unsigned division is selected */
#define XMC_MATH_UNSIGNED_DIVISION                    ((uint32_t) 1 << MATH_DIVCON_USIGN_Pos)

/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL ROUTINES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * API IMPLEMENTATION - Utility functions
 ********************************************************************************************************************/
/* API to retrieve driver version info */
XMC_DRIVER_VERSION_t XMC_MATH_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = XMC_MATH_MAJOR_VERSION;
  version.minor = XMC_MATH_MINOR_VERSION;
  version.patch = XMC_MATH_PATCH_VERSION;

  return version;
}

/* Utility function to check if the DIV unit is busy */
bool XMC_MATH_DIV_IsBusy(void)
{
  bool status;
  if (MATH->DIVST & MATH_DIVST_BSY_Msk)
  {
    status = true;  /* DIV unit is busy running a division operation */ 
  }
  else
  {
    status = false; /* DIV unit is idle */ 
  }

  return (status);
}

/* Utility function to check if the CORDIC unit is busy */
bool XMC_MATH_CORDIC_IsBusy(void)
{
  bool status;
  if (MATH->STATC & MATH_STATC_BSY_Msk)
  {
    status = true;  /* CORDIC unit is busy running an operation */  
  }
  else
  {
    status = false; /* CORDIC unit is idle */   
  }

  return (status);
}

/* This functions returns the status of a requested event */
bool XMC_MATH_GetEventStatus(const XMC_MATH_EVENT_t event)
{
  bool status;
  if (MATH->EVFR & (uint32_t) event)
  {
    status = true; /* Requested event has been detected */
  }
  else
  {
    status = false; /* Requested event has not been detected */
  }
  return (status);
}

/***********************************************************************************************************************
 * API IMPLEMENTATION - aeabi routines
 **********************************************************************************************************************/
/* This function performs unsigned integer division */
uint32_t __aeabi_uidiv(uint32_t dividend, uint32_t divisor)
{
  MATH->DIVCON  = XMC_MATH_UNSIGNED_DIVISION;
  MATH->DVD     = dividend;
  MATH->DVS     = divisor;

  while(MATH->DIVST) /* Wait as divider unit is busy performing requested operation */
  {
  }
  return ((uint32_t) MATH->QUOT);
}

/* This function performs signed integer division */
int32_t __aeabi_idiv(int32_t dividend, int32_t divisor)
{
  MATH->DIVCON  = XMC_MATH_SIGNED_DIVISION;
  MATH->DVD     = dividend;
  MATH->DVS     = divisor;

  while(MATH->DIVST) /* Wait as divider unit is busy performing requested operation */
  {
  }
  return ((int32_t) MATH->QUOT);
}

/* This function performs unsigned integer division modulo */
uint64_t __aeabi_uidivmod(uint32_t dividend, uint32_t divisor)
{
  uint64_t remainder;

  MATH->DIVCON  = XMC_MATH_UNSIGNED_DIVISION;
  MATH->DVD     = dividend;
  MATH->DVS     = divisor;

  while(MATH->DIVST) /* Wait as divider unit is busy performing requested operation */
  {
  }

  remainder = ((uint64_t) MATH->RMD) << 32U;
  return (remainder | MATH->QUOT);
}

/* This function performs signed integer division modulo */
int64_t __aeabi_idivmod(int32_t dividend, int32_t divisor)
{
  uint64_t remainder;
  uint64_t result;

  MATH->DIVCON  = XMC_MATH_SIGNED_DIVISION;
  MATH->DVD     = dividend;
  MATH->DVS     = divisor;

  while(MATH->DIVST) /* Wait as divider unit is busy performing requested operation */
  {
  }

  remainder = ((uint64_t) MATH->RMD) << 32U;
  result    = (remainder | MATH->QUOT);
  return ((int64_t) result);
}

/***********************************************************************************************************************
 * API IMPLEMENTATION - Blocking functions
 **********************************************************************************************************************/
/* This function computes the cosine of a given angle in radians */
XMC_MATH_Q0_23_t XMC_MATH_CORDIC_Cos(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t) angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U;  /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;

  result      = MATH->CORRX >> MATH_CORRX_RESULT_Pos;
  return ((XMC_MATH_Q0_23_t) result);
}

/* This function computes the sine of a given angle in radians */
XMC_MATH_Q0_23_t XMC_MATH_CORDIC_Sin(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;
  result      = MATH->CORRY >> MATH_CORRY_RESULT_Pos;
  return ((XMC_MATH_Q0_23_t) result);
}

/* This function computes the tangent of a given angle in radians */
XMC_MATH_Q0_11_t XMC_MATH_CORDIC_Tan(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->GLBCON = (uint32_t) XMC_MATH_DIV_DVDRC_CORRY_IS_SOURCE + \
                 (uint32_t) XMC_MATH_DIV_DVSRC_CORRX_IS_SOURCE;      /* Chain the results of CORDIC operation to DIV unit */
  MATH->DIVCON = (uint32_t) 11 << MATH_DIVCON_DVSSRC_Pos;            /* Right Shifts Divisor by 11 places prior to division */
  MATH->STATC  = 0U; /* Clear register */
  MATH->CON    = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                 (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ  = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY  = 0U; /* Clear register */
  MATH->CORDX  = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;
  result       = MATH->QUOT;
  return ((XMC_MATH_Q0_11_t) result);
}

/* This function computes the arc tangent of a given angle in radians */
XMC_MATH_Q0_23_t XMC_MATH_CORDIC_ArcTan(XMC_MATH_Q8_15_t x, XMC_MATH_Q8_15_t y)
{
  uint32_t result;
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR;
  MATH->CORDZ = 0U; /* Clear register */
  MATH->CORDY = ((uint32_t) y) << MATH_CORDY_DATA_Pos;
  MATH->CORDX = ((uint32_t) x) << MATH_CORDX_DATA_Pos;
  result      = MATH->CORRZ >> MATH_CORRZ_RESULT_Pos;
  return ((XMC_MATH_Q0_23_t) result);
}

/* This function computes the hyperbolic cosine of a given angle in radians */
XMC_MATH_Q1_22_t XMC_MATH_CORDIC_Cosh(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t) angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
  result      = MATH->CORRX >> MATH_CORRX_RESULT_Pos;
  return ((XMC_MATH_Q1_22_t) result);
}

/* This function computes the hyperbolic sine of a given angle in radians */
XMC_MATH_Q1_22_t XMC_MATH_CORDIC_Sinh(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
  result      = MATH->CORRY >> MATH_CORRY_RESULT_Pos;
  return ((XMC_MATH_Q1_22_t) result);
}

/* This function computes the hyperbolic tangent of a given angle in radians */
XMC_MATH_Q0_11_t XMC_MATH_CORDIC_Tanh(XMC_MATH_Q0_23_t angle_in_radians)
{
  uint32_t result;
  MATH->GLBCON = (uint32_t) XMC_MATH_DIV_DVDRC_CORRY_IS_SOURCE + \
                 (uint32_t) XMC_MATH_DIV_DVSRC_CORRX_IS_SOURCE;      /* Chain the results of CORDIC operation to DIV unit */
  MATH->DIVCON = (uint32_t) 11 << MATH_DIVCON_DVSSRC_Pos;            /* Right Shifts Divisor by 11 places prior to division */
  MATH->STATC  = 0U; /* Clear register */
  MATH->CON    = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                 (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ  = ((uint32_t) angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY  = 0U; /* Clear register */
  MATH->CORDX  = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
  result       = MATH->QUOT;
  return ((XMC_MATH_Q0_11_t) result);
}

/***********************************************************************************************************************
 * API IMPLEMENTATION - Non blocking functions
 **********************************************************************************************************************/
/* This function computes the cosine of a given angle in radians */
void XMC_MATH_CORDIC_CosNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t) angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U;  /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;
}

/* This function computes the sine of a given angle in radians */
void XMC_MATH_CORDIC_SinNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;
}

/* This function computes the tangent of a given angle in radians */
void XMC_MATH_CORDIC_TanNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->GLBCON = (uint32_t) XMC_MATH_DIV_DVDRC_CORRY_IS_SOURCE + \
                 (uint32_t) XMC_MATH_DIV_DVSRC_CORRX_IS_SOURCE;      /* Chain the results of CORDIC operation to DIV unit */
  MATH->DIVCON = (uint32_t) 11 << MATH_DIVCON_DVSSRC_Pos;            /* Right Shifts Divisor by 11 places prior to division */

  MATH->STATC  = 0U; /* Clear register */
  MATH->CON    = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR + \
                 (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ  = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY  = 0U; /* Clear register */
  MATH->CORDX  = XMC_MATH_RECIPROC_CIRCULAR_GAIN_IN_Q023 << MATH_CORDX_DATA_Pos;
}

/* This function computes the arc tangent of a given value */
void XMC_MATH_CORDIC_ArcTanNB(XMC_MATH_Q8_15_t x, XMC_MATH_Q8_15_t y)
{
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_CIRCULAR;
  MATH->CORDZ = 0U; /* Clear register */
  MATH->CORDY = ((uint32_t) y) << MATH_CORDY_DATA_Pos;
  MATH->CORDX = ((uint32_t) x) << MATH_CORDX_DATA_Pos;
}

/* This function computes the hyperbolic cosine of a given angle in radians */
void XMC_MATH_CORDIC_CoshNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
}

/* This function computes the hyperbolic sine of a given angle in radians */
void XMC_MATH_CORDIC_SinhNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->STATC = 0U; /* Clear register */
  MATH->CON   = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ = ((uint32_t)angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY = 0U; /* Clear register */
  MATH->CORDX = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
}

/* This function computes the hyperbolic tangent of a given angle in radians */
void XMC_MATH_CORDIC_TanhNB(XMC_MATH_Q0_23_t angle_in_radians)
{
  MATH->GLBCON = (uint32_t) XMC_MATH_DIV_DVDRC_CORRY_IS_SOURCE + \
                 (uint32_t) XMC_MATH_DIV_DVSRC_CORRX_IS_SOURCE;      /* Chain the results of CORDIC operation to DIV unit */
  MATH->DIVCON = (uint32_t) 11 << MATH_DIVCON_DVSSRC_Pos;            /* Right Shifts Divisor by 11 places prior to division */
  MATH->STATC  = 0U; /* Clear register */
  MATH->CON    = (uint32_t) XMC_MATH_CORDIC_OPERATING_MODE_HYPERBOLIC + \
                 (uint32_t) XMC_MATH_CORDIC_ROTVEC_MODE_ROTATION;
  MATH->CORDZ  = ((uint32_t) angle_in_radians) << MATH_CORDZ_DATA_Pos;
  MATH->CORDY  = 0U; /* Clear register */
  MATH->CORDX  = XMC_MATH_RECIPROC_HYPERBOLIC_GAIN_IN_Q1_22 << MATH_CORDX_DATA_Pos;
}

/* This function performs division for given two unsigned arguments */
void XMC_MATH_DIV_UnsignedDivNB(uint32_t dividend, uint32_t divisor)
{
  MATH->DIVCON = XMC_MATH_UNSIGNED_DIVISION;
  MATH->DVD    = dividend;
  MATH->DVS    = divisor;
}

/* This function performs division for given two signed arguments */
void XMC_MATH_DIV_SignedDivNB(int32_t dividend, int32_t divisor)
{
  MATH->DIVCON = XMC_MATH_SIGNED_DIVISION;
  MATH->DVD    = dividend;
  MATH->DVS    = divisor;
}

/* This function performs modulo operation for given two unsigned arguments */
void XMC_MATH_DIV_UnsignedModNB(uint32_t dividend, uint32_t divisor)
{
  MATH->DIVCON = XMC_MATH_UNSIGNED_DIVISION;
  MATH->DVD    = dividend;
  MATH->DVS    = divisor;
}

/* This function performs modulo operation for given two signed arguments */
void XMC_MATH_DIV_SignedModNB(int32_t dividend, int32_t divisor)
{
  MATH->DIVCON = XMC_MATH_SIGNED_DIVISION;
  MATH->DVD    = dividend;
  MATH->DVS    = divisor;
}

#endif /* end of #if defined (MATH) */
