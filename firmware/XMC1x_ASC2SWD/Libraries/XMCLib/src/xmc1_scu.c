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
 * @file xmc1_scu.c
 * @date 16 Feb, 2014
 * @version 1.0.0
 *
 * @brief SCU low level driver API prototype definition for XMC1 family of microcontrollers <br>
 *
 * <b>Detailed description of file</b> <br>
 * APIs provided in this file cover the following functional blocks of SCU: <br>
 * -- GCU (APIs prefixed with XMC_SCU_GEN_) <br>
 * ----Temperature Monitoring, Voltage Monitoring, CCU Start etc
 *
 * -- CCU (APIs prefixed with XMC_SCU_CLOCK_)<br>
 * ---- Clock initialization, Clock Gating, Sleep Management etc
 *
 * -- RCU (APIs prefixed with XMC_SCU_RESET_) <br>
 * ---- Reset Init, Cause, Manual Reset Assert/Deassert etc
 *
 * -- INTERRUPT (APIs prefixed with XMC_SCU_INTERRUPT_)<br>
 * ---- Initialization, Manual Assert/Deassert, Acknowledge etc
 *
 * History
 *
 * Version 1.0.0 Initial <br>
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_scu.h>

#if UC_FAMILY == XMC1

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/

#define SCU_GCU_PASSWD_PROT_ENABLE  (195UL) /**< Password for enabling protection */
#define SCU_GCU_PASSWD_PROT_DISABLE (192UL) /**< Password for disabling protection */
#define XMC_SCU_DELAY_20US          (200UL) /**< 20us delay count with CPU ticking at 32Mhz */

#define XMC_SCU_CHECK_RTCCLKSRC(source)       ( (source == XMC_SCU_CLOCK_RTCCLKSRC_DCO2) || \
                                                (source == XMC_SCU_CLOCK_RTCCLKSRC_ERU_IOUT0) || \
                                                (source == XMC_SCU_CLOCK_RTCCLKSRC_ACMP0_OUT) || \
                                                (source == XMC_SCU_CLOCK_RTCCLKSRC_ACMP1_OUT) || \
                                                (source == XMC_SCU_CLOCK_RTCCLKSRC_ACMP2_OUT) ) /**< Used to verify
                                                                                                whether provided RTC 
                                                                                                clock source is 
                                                                                                correct. */

#define XMC_SCU_EVENT_IRQ0_MASK     (XMC_SCU_INTERRUPT_EVENT_FLASH_ERROR | \
                                     XMC_SCU_INTERRUPT_EVENT_FLASH_COMPLETED | \
                                     XMC_SCU_INTERRUPT_EVENT_PESRAM | \
                                     XMC_SCU_INTERRUPT_EVENT_PUSIC | \
                                     XMC_SCU_INTERRUPT_EVENT_LOCI)

#define XMC_SCU_EVENT_IRQ1_MASK     (XMC_SCU_INTERRUPT_EVENT_STDBYCLKFAIL | \
                                     XMC_SCU_INTERRUPT_EVENT_VDDPI | \
                                     XMC_SCU_INTERRUPT_EVENT_VDROP | \
                                     XMC_SCU_INTERRUPT_EVENT_VCLIP | \
                                     XMC_SCU_INTERRUPT_EVENT_TSE_DONE | \
                                     XMC_SCU_INTERRUPT_EVENT_TSE_HIGH | \
                                     XMC_SCU_INTERRUPT_EVENT_TSE_LOW | \
                                     XMC_SCU_INTERRUPT_EVENT_WDT_WARN | \
                                     XMC_SCU_INTERRUPT_EVENT_RTC_PERIODIC | \
                                     XMC_SCU_INTERRUPT_EVENT_RTC_ALARM | \
                                     XMC_SCU_INTERRUPT_EVENT_RTCCTR_UPDATED | \
                                     XMC_SCU_INTERRUPT_EVENT_RTCATIM0_UPDATED | \
                                     XMC_SCU_INTERRUPT_EVENT_RTCATIM1_UPDATED | \
                                     XMC_SCU_INTERRUPT_EVENT_RTCTIM0_UPDATED | \
                                     XMC_SCU_INTERRUPT_EVENT_RTCTIM1_UPDATED)

#if UC_SERIES != XMC11
#define XMC_SCU_EVENT_IRQ2_MASK     (XMC_SCU_INTERRUPT_EVENT_ORC0 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC1 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC2 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC3 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC4 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC5 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC6 | \
                                     XMC_SCU_INTERRUPT_EVENT_ORC7 | \
                                     XMC_SCU_INTERRUPT_EVENT_ACMP0 | \
                                     XMC_SCU_INTERRUPT_EVENT_ACMP1 | \
                                     XMC_SCU_INTERRUPT_EVENT_ACMP2)
#else
#define XMC_SCU_EVENT_IRQ2_MASK     (0U)
#endif                                  
   
#define XMC_SCU_INTERRUPT_EVENT_MAX (32U)
#define XMC_SCU_NUM_IRQ             (3U)
   
/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/
static XMC_SCU_INTERRUPT_EVENT_HANDLER_t event_handler_list[XMC_SCU_NUM_IRQ][XMC_SCU_INTERRUPT_EVENT_MAX];

/*********************************************************************************************************************
 * LOCAL ROUTINES
 ********************************************************************************************************************/
static void                 XMC_SCU_CLOCK_lDivUpdate(uint32_t idiv, uint32_t fdiv);
static void                 XMC_SCU_CLOCK_lFrequencyUpScaling(uint32_t curr_idiv, uint32_t idiv);
static void                 XMC_SCU_CLOCK_lFrequencyDownScaling(uint32_t curr_idiv, uint32_t idiv);

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/
/* API to lock protected bitfields from being modified */
void XMC_SCU_LockProtectedBits(void)
{
  SCU_GENERAL->PASSWD = SCU_GCU_PASSWD_PROT_ENABLE;
}

/* API to make protected bitfields available for modification */
void XMC_SCU_UnlockProtectedBits(void)
{
  SCU_GENERAL->PASSWD = SCU_GCU_PASSWD_PROT_DISABLE;

  while(((SCU_GENERAL->PASSWD)&SCU_GENERAL_PASSWD_PROTS_Msk))
  {
    /* Loop until the lock is removed */
  }
}

/* API to initialize power supply monitoring unit */
void XMC_SCU_SupplyMonitorInit(const XMC_SCU_SUPPLYMONITOR_t *obj)
{
  uint32_t anavdel;
  uint32_t irqmask;

  anavdel = 0UL;
   
  anavdel |= (uint32_t)((obj-> ext_supply_threshold) << SCU_ANALOG_ANAVDEL_VDEL_SELECT_Pos);
  anavdel |= (uint32_t)((obj->ext_supply_monitor_speed) << SCU_ANALOG_ANAVDEL_VDEL_TIM_ADJ_Pos);
   
  if(true == (obj->enable_at_init))
  {
    anavdel |= (uint32_t)SCU_ANALOG_ANAVDEL_VDEL_EN_Msk;
  }
   SCU_ANALOG->ANAVDEL = (uint16_t) anavdel;
   
  irqmask = 0UL;
 
  if(true == (obj->enable_prewarning_int))
  {
    irqmask |= (uint32_t)SCU_INTERRUPT_SRMSK_VDDPI_Msk;
  }
   
  if(true == (obj->enable_vdrop_int))
  {
    irqmask |= (uint32_t)SCU_INTERRUPT_SRMSK_VDROPI_Msk;
  }
   
  if(true == (obj->enable_vclip_int))
  {
    irqmask |= (uint32_t)SCU_INTERRUPT_SRMSK_VCLIPI_Msk;
  }
  SCU_INTERRUPT->SRMSK |= (uint32_t)irqmask;
}
 
/* API to program temperature limits as raw digital values into temperature sensor */
#if (UC_SERIES != XMC11)
void XMC_SCU_SetRawTempLimits(const uint32_t lower_temp, const uint32_t upper_temp)
{
  SCU_ANALOG->ANATSEIH = upper_temp & SCU_ANALOG_ANATSEIH_TSE_IH_Msk;
  SCU_ANALOG->ANATSEIL = lower_temp & SCU_ANALOG_ANATSEIL_TSE_IL_Msk;
}

/* API to start temperature measurement */
XMC_SCU_STATUS_t XMC_SCU_StartTempMeasurement(void)
{
  volatile uint32_t i;
  
  SCU_ANALOG->ANATSECTRL |= (uint32_t)SCU_ANALOG_ANATSECTRL_TSE_EN_Msk;
  /* Spin for about 10000 cycles */
  for (i = 0UL; i < 10000UL; i++)
  {
    /* NOP */
  }
  return XMC_SCU_STATUS_OK;
}

/* API to stop temperature measurement */
void XMC_SCU_StopTempMeasurement(void)
{
  SCU_ANALOG->ANATSECTRL &= (uint32_t)~SCU_ANALOG_ANATSECTRL_TSE_EN_Msk;
}

/* API to check if the temperature has gone past the ceiling */
bool XMC_SCU_HighTemperature(void)
{
  bool ret_val;
  uint32_t high_temp;
   
  high_temp = (SCU_INTERRUPT->SRRAW) & SCU_INTERRUPT_SRRAW_TSE_HIGH_Msk;

  if(high_temp)
  {
    ret_val = true;
  }
  else
  {
    ret_val = false;
  }
   
  return ret_val;
}

/* API to check if the temperature is lower than normal */
bool XMC_SCU_LowTemperature(void)
{
  bool ret_val;
  uint32_t low_temp;
   
  low_temp = (SCU_INTERRUPT->SRRAW) & SCU_INTERRUPT_SRRAW_TSE_LOW_Msk;

  if(low_temp)
  {
    ret_val = true;
  }
  else
  {
    ret_val = false;
  }
   
  return ret_val;
}

/* API to retrieve the ddevice temperature */
uint32_t XMC_SCU_GetTemperature(void)
{
  uint32_t temperature;
  
  temperature = (uint32_t)(SCU_ANALOG->ANATSEMON);
  
  return temperature;
}

#endif

/* API which initializes the clock tree ofthe device */
void XMC_SCU_CLOCK_Init(const XMC_SCU_CLOCK_CONFIG_t *const config)
{
  /* Remove protection */
  XMC_SCU_UnlockProtectedBits();

  /* Update PCLK selection mux. */
  SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~(SCU_CLK_CLKCR_PCLKSEL_Msk | SCU_CLK_CLKCR_RTCCLKSEL_Msk)) | 
                   config->rtc_src |
                   config->pclk_src;

  /* Update the dividers now */
  XMC_SCU_CLOCK_lDivUpdate(config->idiv, config->fdiv);

  SystemCoreClockUpdate();
   
  /*Close the lock opened above. */
  XMC_SCU_LockProtectedBits();
   
}

/* API which selects one of the available parent clock nodes for a given child clock node */
void XMC_SCU_CLOCK_SetRtcClockSource(const XMC_SCU_CLOCK_RTCCLKSRC_t source)
{
  XMC_ASSERT("XMC_SCU_CLOCK_SetRtcSourceClock:Wrong Parent Clock", XMC_SCU_CHECK_RTCCLKSRC(source));
    
  XMC_SCU_UnlockProtectedBits();
  
  SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~SCU_CLK_CLKCR_RTCCLKSEL_Msk) |
                   source;

  XMC_SCU_LockProtectedBits();
}

/* API to program the divider placed between fperiph and its parent */
void XMC_SCU_CLOCK_SetFastPeripheralClockSource(const XMC_SCU_CLOCK_PCLKSRC_t source)
{
  XMC_SCU_UnlockProtectedBits();

  SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~SCU_CLK_CLKCR_PCLKSEL_Msk) | 
                   source;
                   
  XMC_SCU_LockProtectedBits();
}

/* API which gates a clock node at its source */
void XMC_SCU_CLOCK_GatePeripheralClock(const XMC_SCU_PERIPHERAL_CLOCK_t peripheral)
{
  XMC_SCU_UnlockProtectedBits();   
  SCU_CLK->CGATSET0 |= (uint32_t)peripheral;
  XMC_SCU_LockProtectedBits();
}

/* API which ungates a clock note at its source */
void XMC_SCU_CLOCK_UngatePeripheralClock(const XMC_SCU_PERIPHERAL_CLOCK_t peripheral)
{
  XMC_SCU_UnlockProtectedBits();   
  SCU_CLK->CGATCLR0 |= (uint32_t)peripheral;
  XMC_SCU_LockProtectedBits();
}

bool XMC_SCU_CLOCK_IsPeripheralClockGated(const XMC_SCU_PERIPHERAL_CLOCK_t peripheral)
{
  bool retval;
  
  XMC_SCU_UnlockProtectedBits();   
  retval = (bool)(SCU_CLK->CGATSTAT0 & peripheral);
  XMC_SCU_LockProtectedBits();
  
  return retval;
}

/* A utility routine which updates the fractional dividers in steps */
static void XMC_SCU_CLOCK_lDivUpdate(uint32_t idiv, uint32_t fdiv)
{
  /* Find out current and target value of idiv */
  uint32_t curr_idiv;

  /* Take a snapshot of value already programmed into IDIV */
  curr_idiv = (SCU_CLK->CLKCR & SCU_CLK_CLKCR_IDIV_Msk) >> SCU_CLK_CLKCR_IDIV_Pos;
   
  SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~(SCU_CLK_CLKCR_FDIV_Msk | SCU_CLK_CLKCR_CNTADJ_Pos)) |
                   (uint32_t)(fdiv << SCU_CLK_CLKCR_FDIV_Pos) |
                   (uint32_t)(1023UL <<SCU_CLK_CLKCR_CNTADJ_Pos);

  while ((SCU_CLK->CLKCR)& SCU_CLK_CLKCR_VDDC2LOW_Msk)
  {
    /* Spin until the core supply stabilizes */
  }
   
  if(curr_idiv <= idiv)
  {
    /* Requested IDIV is greater than currently programmed IDIV. So downscale the frequency */
    XMC_SCU_CLOCK_lFrequencyDownScaling(curr_idiv, idiv);
  }
  else
  {
    /* Requested IDIV is lower than currently programmed IDIV. So upscale the frequency */
    XMC_SCU_CLOCK_lFrequencyUpScaling(curr_idiv, idiv);
  }

  SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~(SCU_CLK_CLKCR_IDIV_Msk | SCU_CLK_CLKCR_CNTADJ_Msk)) |
                   (uint32_t)(idiv << SCU_CLK_CLKCR_IDIV_Pos) | (uint32_t)(1023UL << SCU_CLK_CLKCR_CNTADJ_Pos);

  while ((SCU_CLK->CLKCR) & SCU_CLK_CLKCR_VDDC2LOW_Msk)
  {
    /* Wait voltage suply stabilization */
  }  

}
 
/* Utility routine to perform frequency upscaling */
static void XMC_SCU_CLOCK_lFrequencyUpScaling(uint32_t curr_idiv, uint32_t target_idiv)
{
  while (curr_idiv > (target_idiv * 4UL))
  {
    curr_idiv = (curr_idiv & 0xFFFFFFFCUL) + 4UL;
    curr_idiv = (uint32_t)(curr_idiv >> 2UL);   /* Divide by 4. */
    
    SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~(SCU_CLK_CLKCR_IDIV_Msk | SCU_CLK_CLKCR_CNTADJ_Msk)) |
                     (uint32_t)(curr_idiv << SCU_CLK_CLKCR_IDIV_Pos) | (uint32_t)(1023UL << SCU_CLK_CLKCR_CNTADJ_Pos);

    while (SCU_CLK->CLKCR & SCU_CLK_CLKCR_VDDC2LOW_Msk)
    {
    /* Wait voltage suply stabilization */
    }
  }
}

/* Utility routine to perform frequency downscaling */
static void XMC_SCU_CLOCK_lFrequencyDownScaling(uint32_t curr_idiv, uint32_t target_idiv)
{

  while ((curr_idiv * 4UL) < target_idiv)
  {
    curr_idiv  = (uint32_t)(curr_idiv << 2UL);   /* Multiply by 4. */
    SCU_CLK->CLKCR = (SCU_CLK->CLKCR & (uint32_t)~(SCU_CLK_CLKCR_IDIV_Msk|SCU_CLK_CLKCR_CNTADJ_Pos)) |
                     (uint32_t)(curr_idiv << SCU_CLK_CLKCR_IDIV_Pos) |
                     (uint32_t)(1023UL << SCU_CLK_CLKCR_CNTADJ_Pos);

    while (SCU_CLK->CLKCR & SCU_CLK_CLKCR_VDDC2LOW_Msk)
    {
    /* Wait voltage suply stabilization */
    }
  }
}  

/*
 * API to retrieve clock frequency of peripherals on the peripheral bus using a shared functional clock
 */
uint32_t XMC_SCU_CLOCK_GetPeripheralClockFrequency(void)
{
  return SystemCoreClock;
}

uint32_t XMC_SCU_CLOCK_GetFastPeripheralClockFrequency(void)
{
  return (SystemCoreClock << ((SCU_CLK->CLKCR & SCU_CLK_CLKCR_PCLKSEL_Msk) >> SCU_CLK_CLKCR_PCLKSEL_Pos));
}

/*
 *
 */
XMC_SCU_STATUS_t XMC_SCU_INTERRUPT_SetEventHandler(XMC_SCU_INTERRUPT_EVENT_t event, XMC_SCU_INTERRUPT_EVENT_HANDLER_t handler)
{
  uint32_t index;
  XMC_SCU_STATUS_t status;
  
  index = 0U;
  status = XMC_SCU_STATUS_OK;
  
  while (((uint32_t)event >> index) != 0x1U)
  {
    index++;
  }
  
  if (index < XMC_SCU_INTERRUPT_EVENT_MAX)
  {
    if (event & XMC_SCU_EVENT_IRQ0_MASK)    
    {
      event_handler_list[0U][index] = handler;
    }
    else if (event & XMC_SCU_EVENT_IRQ1_MASK)
    {
      event_handler_list[1U][index] = handler;
    }
    else if (event & XMC_SCU_EVENT_IRQ2_MASK)
    {
      event_handler_list[2U][index] = handler;
    }
    else 
    {
      status = XMC_SCU_STATUS_ERROR;  
    }    
  }
  else 
  {
    status = XMC_SCU_STATUS_ERROR;
  }
  
  return status;
}

/*
 *
 */
void XMC_SCU_IRQHandler(uint32_t sr_num)
{
  uint32_t index;
  uint32_t status; 
  XMC_SCU_INTERRUPT_EVENT_HANDLER_t event_handler;
  
  index = 0U;
  status = XMC_SCU_INTERUPT_GetEventStatus();
  while (index < XMC_SCU_INTERRUPT_EVENT_MAX)
  {    
    if ((status & (1U << index)) != 0U)
    {
      event_handler = event_handler_list[sr_num][index];
      if (event_handler != NULL)
      {
          event_handler();
      }
      
      XMC_SCU_INTERRUPT_ClearEventStatus(1U << index);
      
      /* break; XMC1: Only PULSE interrupts */
    }    
    index++;
  }
}

#endif /* UC_FAMILY == XMC1 */
