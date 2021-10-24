/**************************************************************************
 * @file     ASC_Init.c
 * @brief    ASC init file for the XMC1000 Bootloader
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

#include <XMC1300.h>

/* USIC : FIFO DPTR & SIZE MASK and POS Values */ 
#define   USIC_CH_TBCTR_DPTRSIZE_Pos  	(0U)
#define   USIC_CH_TBCTR_DPTRSIZE_Msk  	(0x0700003FU << USIC_CH_TBCTR_DPTRSIZE_Pos)

#define   USIC_CH_RBCTR_DPTRSIZE_Pos  	(0U)
#define   USIC_CH_RBCTR_DPTRSIZE_Msk  	(0x0700003FU << USIC_CH_RBCTR_DPTRSIZE_Pos)

void ASC_Init(void)
{              	         

//********* MODULE USIC CONFIGURATIONS for using P1.3 as RXD *************************
   /*USIC 0 Channel 0 Mux Related SFR/Bitfields Configurations*/ 									  					 				 				 		       				              				  					    					 					   				  					 				 				       				  										 									 					 					  									      					              					  						    					      
 WR_REG(USIC0_CH1->DX0CR, USIC_CH_DX0CR_DSEL_Msk, USIC_CH_DX0CR_DSEL_Pos,0);
	
   // Data Pointer & Buffer Size for Transmitter Buffer Control  
 WR_REG(USIC0_CH1->TBCTR, USIC_CH_TBCTR_DPTRSIZE_Msk, USIC_CH_TBCTR_DPTRSIZE_Pos,0x01000000);		/*    DPTR = 0,  SIZE = 1 */
           
  // Data Pointer & Buffer Size for Receiver Buffer Control  
 WR_REG(USIC0_CH1->RBCTR, USIC_CH_RBCTR_DPTRSIZE_Msk, USIC_CH_RBCTR_DPTRSIZE_Pos,0x01000000);		/*    DPTR = 0,  SIZE = 1 */

 //********* MODULE USIC CONFIGURATIONS for using P0.14 as RXD *************************
    /*USIC 0 Channel 0 Mux Related SFR/Bitfields Configurations*/
//  WR_REG(USIC0_CH0->DX0CR, USIC_CH_DX0CR_DSEL_Msk, USIC_CH_DX0CR_DSEL_Pos,0);

    // Data Pointer & Buffer Size for Transmitter Buffer Control
//  WR_REG(USIC0_CH0->TBCTR, USIC_CH_TBCTR_DPTRSIZE_Msk, USIC_CH_TBCTR_DPTRSIZE_Pos,0x01000000);		/*    DPTR = 0,  SIZE = 1 */

   // Data Pointer & Buffer Size for Receiver Buffer Control
//  WR_REG(USIC0_CH0->RBCTR, USIC_CH_RBCTR_DPTRSIZE_Msk, USIC_CH_RBCTR_DPTRSIZE_Pos,0x01000000);		/*    DPTR = 0,  SIZE = 1 */
				       
}

