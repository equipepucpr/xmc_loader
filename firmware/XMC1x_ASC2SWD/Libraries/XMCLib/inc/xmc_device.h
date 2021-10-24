/****************************************************************************
 *
 * @file     xmc_device.h
 *           Infineon XMC Device Series
 * @version  V1.0.0
 * @date     16 Feb 2015
 *
   Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 *
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with 
 * Infineon's microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED AS IS.  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

/* Family definitions  */
#define    XMC4       (4)
#define    XMC1       (1)

/* Series definitions  */
#define    XMC45      (45)
#define    XMC44      (44)
#define    XMC42      (42)
#define    XMC41      (41)
#define    XMC13      (13)
#define    XMC12      (12)
#define    XMC11      (11)

/* Device definitions  */
#define    XMC4500    (4500)
#define    XMC4502    (4502)
#define    XMC4504    (4504)
#define    XMC4400    (4400)
#define    XMC4402    (4402)
#define    XMC4200    (4200)
#define    XMC4100    (4100)
#define    XMC4104    (4104)
#define    XMC4108    (4108)
#define    XMC1300    (1300)
#define    XMC1301    (1301)
#define    XMC1302    (1302)
#define    XMC1200    (1200)
#define    XMC1201    (1201)
#define    XMC1202    (1202)
#define    XMC1203    (1203)
#define    XMC1100    (1100)

/* Package definitions */
#define    BGA144     (1)
#define    LQFP144    (2)
#define    LQFP100    (3)
#define    BGA64      (4)
#define    LQFP64     (5)
#define    VQFN48     (6)
#define    TSSOP38    (7)
#define    TSSOP28    (8)
#define    TSSOP16    (9) 
#define    VQFN24     (10)
#define    VQFN40     (11)


#if defined(XMC4500_E144x1024)	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4500
#define UC_PACKAGE   BGA144
#define UC_FLASH     (1024UL)

#elif defined(XMC4500_F144x1024) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4500
#define UC_PACKAGE   LQFP144
#define UC_FLASH     (1024UL)

#elif defined(XMC4500_F100x1024)	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4500
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (1024UL)

#elif defined(XMC4500_F144x768) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4500
#define UC_PACKAGE   LQFP144
#define UC_FLASH     (768UL)

#elif defined(XMC4500_F100x768) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4500
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (768UL)

#elif defined(XMC4502_F100x768) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4502
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (768UL)

#elif defined(XMC4504_F100x512) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4504
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (512UL)

#elif defined(XMC4504_F144x512) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC45
#define UC_DEVICE    XMC4504
#define UC_PACKAGE   LQFP144
#define UC_FLASH     (512UL)

#elif defined(XMC4400_F100x512) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4400
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (512UL)

#elif defined(XMC4400_F64x512) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4400
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (512UL)

#elif defined(XMC4400_F100x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4400
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (256UL)

#elif defined(XMC4400_F64x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4400
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (256UL)

#elif defined(XMC4402_F100x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4402
#define UC_PACKAGE   LQFP100
#define UC_FLASH     (256UL)

#elif defined(XMC4402_F64x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC44
#define UC_DEVICE    XMC4402
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (256UL)

#elif defined(XMC4200_E64x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC42
#define UC_DEVICE    XMC4200
#define UC_PACKAGE   BGA64
#define UC_FLASH     (256UL)

#elif defined(XMC4200_F64x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC42
#define UC_DEVICE    XMC4200
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (256UL)

#elif defined(XMC4200_Q48x256) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC42
#define UC_DEVICE    XMC4200
#define UC_PACKAGE   VQFN48
#define UC_FLASH     (256UL)

#elif defined(XMC4100_E64x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4100
#define UC_PACKAGE   BGA64
#define UC_FLASH     (128UL)

#elif defined(XMC4100_F64x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4100
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (128UL)

#elif defined(XMC4100_Q48x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4100
#define UC_PACKAGE   VQFN48
#define UC_FLASH     (128UL)

#elif defined(XMC4104_E64x64) 	    
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   BGA64
#define UC_FLASH     (64UL)

#elif defined(XMC4104_F64x64) 	    
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (64UL)

#elif defined(XMC4104_Q48x64) 	    
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   VQFN48
#define UC_FLASH     (64UL)

#elif defined(XMC4104_E64x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   BGA64
#define UC_FLASH     (128UL)

#elif defined(XMC4104_F64x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (128UL)

#elif defined(XMC4104_Q48x128) 	
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4104
#define UC_PACKAGE   VQFN48
#define UC_FLASH     (128UL)

#elif defined(XMC4108_Q48x64)
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4108
#define UC_PACKAGE   VQFN48
#define UC_FLASH     (64UL)

#elif defined(XMC4108_F64x64)
#define UC_FAMILY    XMC4
#define UC_SERIES    XMC41
#define UC_DEVICE    XMC4108
#define UC_PACKAGE   LQFP64
#define UC_FLASH     (64UL)

#elif defined(XMC1100_Q024x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (8UL)

#elif defined(XMC1100_Q024x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (16UL)

#elif defined(XMC1100_Q024x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (32UL)

#elif defined(XMC1100_Q024x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (64UL)

#elif defined(XMC1100_Q040x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (16UL)

#elif defined(XMC1100_Q040x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (32UL)

#elif defined(XMC1100_Q040x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (64UL)

#elif defined(XMC1100_T016x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (8UL)

#elif defined(XMC1100_T016x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (16UL)

#elif defined(XMC1100_T016x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (32UL)

#elif defined(XMC1100_T016x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (64UL)

#elif defined(XMC1100_T038x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (16UL)

#elif defined(XMC1100_T038x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (32UL)

#elif defined(XMC1100_T038x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC11
#define UC_DEVICE    XMC1100
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (64UL)

#elif defined(XMC1201_Q040x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (16UL)

#elif defined(XMC1201_Q040x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (32UL)

#elif defined(XMC1201_Q040x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (64UL)

#elif defined(XMC1201_Q040x0128)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (128UL)

#elif defined(XMC1201_Q040x0200)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (200UL)

#elif defined(XMC1201_T038x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (16UL)

#elif defined(XMC1201_T038x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (32UL)

#elif defined(XMC1201_T038x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (64UL)

#elif defined(XMC1201_T038x0128)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (128UL)

#elif defined(XMC1201_T038x0200)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1201
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (200UL)

#elif defined(XMC1202_Q024x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (16UL)

#elif defined(XMC1202_Q024x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (32UL)

#elif defined(XMC1202_Q040x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (16UL)

#elif defined(XMC1202_Q040x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (32UL)

#elif defined(XMC1202_T016x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (16UL)

#elif defined(XMC1202_T016x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (32UL)

#elif defined(XMC1202_T028x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   TSSOP28
#define UC_FLASH     (16UL)

#elif defined(XMC1202_T028x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1202
#define UC_PACKAGE   TSSOP28
#define UC_FLASH     (32UL)

#elif defined(XMC1200_T038x0200)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC12
#define UC_DEVICE    XMC1200
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (200UL)

#elif defined(XMC1301_Q024x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (8UL)

#elif defined(XMC1301_Q024x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (16UL)

#elif defined(XMC1301_Q040x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (8UL)

#elif defined(XMC1301_Q040x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (16UL)

#elif defined(XMC1301_Q040x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (32UL)

#elif defined(XMC1301_T016x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (8UL)

#elif defined(XMC1301_T016x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (16UL)

#elif defined(XMC1301_T038x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (8UL)

#elif defined(XMC1301_T038x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (16UL)

#elif defined(XMC1301_T038x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1301
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (32UL)

#elif defined(XMC1302_Q024x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (16UL)

#elif defined(XMC1302_Q024x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (32UL)

#elif defined(XMC1302_Q024x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN24
#define UC_FLASH     (64UL)

#elif defined(XMC1302_Q040x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (16UL)

#elif defined(XMC1302_Q040x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (32UL)

#elif defined(XMC1302_Q040x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (64UL)

#elif defined(XMC1302_Q040x0128)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   VQFN40
#define UC_FLASH     (128UL)

#elif defined(XMC1302_T038x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (16UL)

#elif defined(XMC1302_T038x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (32UL)

#elif defined(XMC1302_T038x0064)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (64UL)

#elif defined(XMC1302_T038x0128)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (128UL)

#elif defined(XMC1302_T038x0200)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP38
#define UC_FLASH     (200UL)

#elif defined(XMC1302_T016x0008)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (8UL)

#elif defined(XMC1302_T016x0016)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (16UL)

#elif defined(XMC1302_T016x0032)
#define UC_FAMILY    XMC1
#define UC_SERIES    XMC13
#define UC_DEVICE    XMC1302
#define UC_PACKAGE   TSSOP16
#define UC_FLASH     (32UL)

#else
#error "xmc_device.h: device not supported"
#endif 	    

#if UC_SERIES == XMC45
#include "XMC4500.h"

#elif UC_SERIES == XMC44
#include "XMC4400.h"

#elif UC_SERIES == XMC42
#include "XMC4200.h"

#elif UC_SERIES == XMC41
#include "XMC4100.h"

#elif UC_SERIES == XMC11
#include "XMC1100.h"

#elif UC_SERIES == XMC12
#include "XMC1200.h"

#elif UC_SERIES == XMC13
#include "XMC1300.h"

#endif
