/*****************************************************************************/
/* Startup_XMC1300.s: Startup file for XMC1300 device series                 */
/*****************************************************************************/

/* ********************* Version History *********************************** */
/* ***************************************************************************
V1.0, Oct, 02, 2012 PKB:Startup file for XMC1  
V1.1, Oct, 19, 2012 PKB:ERU and MATH interrupt handlers  
V1.2, Nov, 02, 2012 PKB:Renamed AllowPLLInitByStartup to AllowClkInitByStartup  
V1.3, Dec, 10, 2012 PKB:Changed attributes of XmcVeneercode section  
V1.4, Dec, 13, 2012 PKB:Removed unwanted interrupts/vectors 
V1.5, Jan, 26, 2013 PKB:SSW support 
V1.6, Feb, 13, 2013 PKB:Relative path to Device_Data.h  
V1.7, Feb, 19, 2013 PKB:Included XMC1300_SCU.inc 
**************************************************************************** */
/**
* @file     Startup_XMC1300.s
*           XMC1300 Device Series
* @version  V1.7
* @date     Feb 2013
*
Copyright (C) 2013 Infineon Technologies AG. All rights reserved.
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


/*#define __Xmc1300_stack 0x80000000 */

/* ================== START OF VECTOR TABLE DEFINITION ====================== */
/* Vector Table - This is indirectly branched to through the veneers */
    .syntax unified   
    .cpu cortex-m0

    .section ".Xmc1300.reset"

    .thumb 
/* ======================================================================== */
/* Reset Handler */

    .thumb_func 
    .globl  __Xmc1300_reset_cortex_m
    .type   __Xmc1300_reset_cortex_m, %function
__Xmc1300_reset_cortex_m:
    .fnstart

    /* C routines are likely to be called. Setup the stack now */
    /* This is already setup by BootROM,hence this step is optional */ 
    LDR R0,=__Xmc1300_stack
    MOV SP,R0


    B       __Xmc1300_Program_Loader 
    
    .pool
    .cantunwind
    .fnend
    .size   __Xmc1300_reset_cortex_m,.-__Xmc1300_reset_cortex_m
/* ======================================================================== */

   __Xmc1300_Program_Loader:
   .fnstart
   /* Memories are accessible now*/
   
   /* DATA COPY */
   /* R0 = Start address, R1 = Destination address, R2 = Size */
   LDR R0, =DataLoadAddr
   LDR R1, =__Xmc1300_sData
   LDR R2, =__Xmc1300_Data_Size

   /* Is there anything to be copied? */
   CMP R2,#0
   BEQ SKIPCOPY
   
   /* For bytecount less than 4, at least 1 word must be copied */
   CMP R2,#4
   BCS STARTCOPY
   
   /* Byte count < 4 ; so bump it up */
   MOVS R2,#4

STARTCOPY:
   /* 
      R2 contains byte count. Change it to word count. It is ensured in the 
      linker script that the length is always word aligned.
   */
   LSRS R2,R2,#2 /* Divide by 4 to obtain word count */

   /* The proverbial loop from the schooldays */
COPYLOOP:
   LDR R3,[R0]
   STR R3,[R1]
   SUBS R2,#1
   BEQ SKIPCOPY
   ADDS R0,#4
   ADDS R1,#4
   B COPYLOOP
    
SKIPCOPY:
   /* BSS CLEAR */
   LDR R0, =__Xmc1300_sBSS     /* Start of BSS */
   LDR R1, =__Xmc1300_BSS_Size /* BSS size in bytes */

   /* Find out if there are items assigned to BSS */   
   CMP R1,#0 
   BEQ SKIPCLEAR

   /* At least 1 word must be copied */
   CMP R1,#4
   BCS STARTCLEAR
   
   /* Byte count < 4 ; so bump it up to a word*/
   MOVS R1,#4

STARTCLEAR:
   LSRS R1,R1,#2            /* BSS size in words */
   
   MOVS R2,#0
CLEARLOOP:
   STR R2,[R0]
   SUBS R1,#1
   BEQ SKIPCLEAR
   ADDS R0,#4
   B CLEARLOOP
    
SKIPCLEAR:

   /* Reset stack pointer before zipping off to user application, Optional */
   LDR R0,=__Xmc1300_stack 
   MOV SP,R0

   MOVS R0,#0
   MOVS R1,#0
   LDR R2, =main
   MOV PC,R2

   .pool
   .cantunwind
   .fnend
   .size   __Xmc1300_Program_Loader,.-__Xmc1300_Program_Loader
/* ======================================================================== */


/* ===== Decision function queried by CMSIS startup for Clock tree setup === */
/* In the absence of DAVE code engine, CMSIS SystemInit() must perform clock 
   tree setup. 
   
   This decision routine defined here will always return TRUE.
   
   When overridden by a definition defined in DAVE code engine, this routine
   returns FALSE indicating that the code engine has performed the clock setup
*/   
     .section ".XmcStartup"
    .weak   AllowClkInitByStartup
    .type   AllowClkInitByStartup, %function
AllowClkInitByStartup:
    MOVS R0,#1
    BX LR
    .size   AllowClkInitByStartup, . - AllowClkInitByStartup

/* ======  Definition of the default weak SystemInit_DAVE3 function =========
If DAVE3 requires an extended SystemInit it will create its own version of
SystemInit_DAVE3 which overrides this weak definition. Example includes
setting up of external memory interfaces.
*/
     .weak SystemInit_DAVE3
     .type SystemInit_DAVE3, %function
SystemInit_DAVE3:
     NOP
     BX LR
     .size SystemInit_DAVE3, . - SystemInit_DAVE3
/* ======================================================================== */
/* ======================================================================== */

/* ======================== Data references =============================== */

    .end
