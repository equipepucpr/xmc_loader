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
 * @file xmc_adc_map.h
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief XMC pin mapping definitions
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

#ifndef XMC_ADC_MAP_H
#define XMC_ADC_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#if (UC_SERIES == XMC11)

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_40_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_ST1  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_40_ST0  	    XMC_VADC_REQ_GT_D
#define XMC_ERU_0_PDOUT2  	    XMC_VADC_REQ_GT_K
#define XMC_ERU_0_PDOUT3	    XMC_VADC_REQ_GT_L
#define XMC_ERU_0_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_0_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_ERU_0_IOUT2         XMC_VADC_REQ_TR_G
#define XMC_ERU_0_IOUT3         XMC_VADC_REQ_TR_H
#define XMC_ERU_0_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_0_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif


#if (UC_SERIES == XMC12)

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_40_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_ST1  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_40_ST0  	    XMC_VADC_REQ_GT_D
#define XMC_LEDTS_0_FN         	XMC_VADC_REQ_GT_I
#define XMC_LEDTS_1_FN  	    XMC_VADC_REQ_GT_J
#define XMC_ERU_0_PDOUT2  	    XMC_VADC_REQ_GT_K
#define XMC_ERU_0_PDOUT3	    XMC_VADC_REQ_GT_L
#define XMC_ERU_0_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_0_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_BCCU0_TRIGOUT       XMC_VADC_REQ_TR_F
#define XMC_ERU_0_IOUT2         XMC_VADC_REQ_TR_G
#define XMC_ERU_0_IOUT3         XMC_VADC_REQ_TR_H
#define XMC_ERU_0_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_0_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif

#if (UC_SERIES == XMC13)

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_40_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_ST1  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_40_ST0  	    XMC_VADC_REQ_GT_D
#define XMC_CCU_80_ST3_A  	    XMC_VADC_REQ_GT_E
#define XMC_CCU_81_ST3  	    XMC_VADC_REQ_GT_F
#define XMC_ERU_0_PDOUT2  	    XMC_VADC_REQ_GT_K
#define XMC_ERU_0_PDOUT3  	    XMC_VADC_REQ_GT_L
#define XMC_CCU_80_ST0	        XMC_VADC_REQ_GT_M
#define XMC_CCU_80_ST1  	    XMC_VADC_REQ_GT_N
#define XMC_ERU_0_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_0_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_BCCU0_TRIGOUT       XMC_VADC_REQ_TR_F
#define XMC_ERU_0_IOUT2         XMC_VADC_REQ_TR_G
#define XMC_ERU_0_IOUT3         XMC_VADC_REQ_TR_H
#define XMC_CCU_80_SR2         	XMC_VADC_REQ_TR_I
#define XMC_CCU_80_SR3  	    XMC_VADC_REQ_TR_J
#define XMC_ERU_0_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_0_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_POSIF_0_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif

#if ( (UC_SERIES == XMC42)||(UC_SERIES == XMC41) )

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_41_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_SR0  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_41_SR1  	    XMC_VADC_REQ_GT_D
#define XMC_CCU_80_ST3_A  	    XMC_VADC_REQ_GT_E
#define XMC_CCU_80_ST3_B  	    XMC_VADC_REQ_GT_F
#define XMC_DAC_0_SGN         	XMC_VADC_REQ_GT_I
#define XMC_DAC_1_SGN         	XMC_VADC_REQ_GT_I
#define XMC_LEDTS_FN         	XMC_VADC_REQ_GT_J
#define XMC_VADC_G0_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G1_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G0_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G3_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_CCU_80_SR0	        XMC_VADC_REQ_GT_M
#define XMC_CCU_80_SR1  	    XMC_VADC_REQ_GT_N
#define XMC_ERU_1_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_1_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_CCU_41_SR2  	    XMC_VADC_REQ_TR_C
#define XMC_CCU_41_SR3  	    XMC_VADC_REQ_TR_D
#define XMC_CCU_80_SR2         	XMC_VADC_REQ_TR_I
#define XMC_CCU_80_SR3  	    XMC_VADC_REQ_TR_J
#define XMC_ERU_1_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_1_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_POSIF_0_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif

#if ( UC_SERIES == XMC44 )

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_41_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_SR0  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_41_SR1  	    XMC_VADC_REQ_GT_D
#define XMC_CCU_80_ST3_A  	    XMC_VADC_REQ_GT_E
#define XMC_CCU_80_ST3_B  	    XMC_VADC_REQ_GT_F
#define XMC_CCU_81_ST3_A       	XMC_VADC_REQ_GT_G
#define XMC_CCU_81_ST3_B       	XMC_VADC_REQ_GT_H
#define XMC_DAC_0_SGN         	XMC_VADC_REQ_GT_I
#define XMC_DAC_1_SGN         	XMC_VADC_REQ_GT_I
#define XMC_LEDTS_FN         	XMC_VADC_REQ_GT_J
#define XMC_VADC_G0_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G1_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G2_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G3_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G0_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G1_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G2_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G3_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_CCU_80_SR0	        XMC_VADC_REQ_GT_M
#define XMC_CCU_80_SR1  	    XMC_VADC_REQ_GT_N
#define XMC_ERU_1_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_1_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_CCU_41_SR2  	    XMC_VADC_REQ_TR_C
#define XMC_CCU_41_SR3  	    XMC_VADC_REQ_TR_D
#define XMC_CCU_42_SR3  	    XMC_VADC_REQ_TR_E
#define XMC_CCU_43_SR3          XMC_VADC_REQ_TR_F
#define XMC_CCU_80_SR2         	XMC_VADC_REQ_TR_I
#define XMC_CCU_80_SR3  	    XMC_VADC_REQ_TR_J
#define XMC_CCU_81_SR2  	    XMC_VADC_REQ_TR_K
#define XMC_CCU_81_SR3	        XMC_VADC_REQ_TR_L
#define XMC_ERU_1_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_1_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_ERU_1_IOUT2  	    XMC_VADC_REQ_TR_N
#define XMC_POSIF_0_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_POSIF_1_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif

#if ( UC_SERIES == XMC45 )

/*  Group request source Gating input connection mappings */
#define XMC_CCU_40_ST3 	        XMC_VADC_REQ_GT_A
#define XMC_CCU_41_ST2  	    XMC_VADC_REQ_GT_B
#define XMC_CCU_40_SR0  	    XMC_VADC_REQ_GT_C
#define XMC_CCU_41_SR1  	    XMC_VADC_REQ_GT_D
#define XMC_CCU_80_ST3_A  	    XMC_VADC_REQ_GT_E
#define XMC_CCU_80_ST3_B  	    XMC_VADC_REQ_GT_F
#define XMC_CCU_81_ST3_A       	XMC_VADC_REQ_GT_G
#define XMC_CCU_81_ST3_B       	XMC_VADC_REQ_GT_H
#define XMC_DAC_0_SGN         	XMC_VADC_REQ_GT_I
#define XMC_DAC_1_SGN         	XMC_VADC_REQ_GT_I
#define XMC_LEDTS_FN         	XMC_VADC_REQ_GT_J
#define XMC_VADC_G0_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G1_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G2_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G3_BLOUT0  	XMC_VADC_REQ_GT_K
#define XMC_VADC_G0_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G1_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G2_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_VADC_G3_SAMPLE  	XMC_VADC_REQ_GT_L
#define XMC_CCU_80_SR0	        XMC_VADC_REQ_GT_M
#define XMC_CCU_80_SR1  	    XMC_VADC_REQ_GT_N
#define XMC_ERU_1_PDOUT0  	    XMC_VADC_REQ_GT_O
#define XMC_ERU_1_PDOUT1	    XMC_VADC_REQ_GT_P

/* Group request source Trigger input connection mappings */
#define XMC_CCU_40_SR2 	        XMC_VADC_REQ_TR_A
#define XMC_CCU_40_SR3  	    XMC_VADC_REQ_TR_B
#define XMC_CCU_41_SR2  	    XMC_VADC_REQ_TR_C
#define XMC_CCU_41_SR3  	    XMC_VADC_REQ_TR_D
#define XMC_CCU_42_SR3  	    XMC_VADC_REQ_TR_E
#define XMC_CCU_43_SR3          XMC_VADC_REQ_TR_F
#define XMC_CCU_80_SR2         	XMC_VADC_REQ_TR_I
#define XMC_CCU_80_SR3  	    XMC_VADC_REQ_TR_J
#define XMC_CCU_81_SR2  	    XMC_VADC_REQ_TR_K
#define XMC_CCU_81_SR3	        XMC_VADC_REQ_TR_L
#define XMC_ERU_1_IOUT0  	    XMC_VADC_REQ_TR_M
#define XMC_ERU_1_IOUT1  	    XMC_VADC_REQ_TR_N
#define XMC_ERU_1_IOUT2  	    XMC_VADC_REQ_TR_N
#define XMC_POSIF_0_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_POSIF_1_SR1  	    XMC_VADC_REQ_TR_O
#define XMC_REQ_GT_SEL	        XMC_VADC_REQ_TR_P

#endif

#ifdef __cplusplus
}
#endif

#endif
