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
 * @file xmc_uart.c
 * @date 16 Feb, 2015
 * @version 1.0.0
 *
 * @brief UART driver for XMC microcontroller family
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/

#include <xmc_scu.h>
#include <xmc_uart.h>

/*******************************************************************************
 * MACROS
 *******************************************************************************/
 
#define XMC_UART_CH_OVERSAMPLING (16UL)
#define XMC_UART_CH_OVERSAMPLING_MIN_VAL (4UL)

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

 XMC_DRIVER_VERSION_t XMC_UART_GetDriverVersion(void)
{
  XMC_DRIVER_VERSION_t version;

  version.major = (uint8_t)XMC_UART_MAJOR_VERSION;
  version.minor = (uint8_t)XMC_UART_MINOR_VERSION;
  version.patch = (uint8_t)XMC_UART_PATCH_VERSION;

  return version;
}

void XMC_UART_CH_Init(XMC_USIC_CH_t *channel, const XMC_UART_CH_CONFIG_t *const config)
{
  uint32_t oversampling = XMC_UART_CH_OVERSAMPLING;

  /* USIC channel switched on*/
  XMC_USIC_CH_Enable(channel);
  
  if(config->oversampling != 0U)
  {
    oversampling = (uint32_t)config->oversampling;
  }
  
  /* Configure baud rate */
  (void)XMC_USIC_CH_SetBaudrate(channel, config->baudrate, oversampling);
  
  /* Configure frame format
   * Configure the number of stop bits
   * Pulse length is set to 0 to have standard UART signaling, 
   * i.e. the 0 level is signaled during the complete bit time
   * Sampling point set equal to the half of the oversampling period
   * Enable Sample Majority Decision */
  channel->PCR_ASCMode = (uint32_t)(((config->stop_bits - 1UL) << USIC_CH_PCR_ASCMode_STPB_Pos) |
			             (((oversampling >> 1UL) + 1UL) << USIC_CH_PCR_ASCMode_SP_Pos) |
			             USIC_CH_PCR_ASCMode_SMD_Msk);

  /* Set passive data level, high
     Set word length. Data bits - 1
     If frame length is > 0, frame_lemgth-1; else, FLE = WLE (Data bits - 1)
     Transmission Mode: The shift control signal is considered active if it
     is at 1-level. This is the setting to be programmed to allow data transfers */
  channel->SCTR = (uint32_t)((((uint32_t)config->data_bits - 1UL) << USIC_CH_SCTR_WLE_Pos) |
		              ((0x1UL << USIC_CH_SCTR_TRM_Pos) | USIC_CH_SCTR_PDL_Msk));

  if (config->frame_length != 0U)
  {
    channel->SCTR |= (uint32_t)(((uint32_t)config->frame_length - 1UL) << USIC_CH_SCTR_FLE_Pos);
  }
  else
  {
    channel->SCTR |= (uint32_t)(((uint32_t)config->data_bits - 1UL) << USIC_CH_SCTR_FLE_Pos);
  }

  /* Enable transfer buffer */
  channel->TCSR = (0x1UL << USIC_CH_TCSR_TDEN_Pos) |
                  USIC_CH_TCSR_TDSSM_Msk;

  /* Clear protocol status */
  channel->PSCR = 0xFFFFFFFFUL;

  /* Set parity settings */
  channel->CCR = (uint32_t)config->parity_mode;
}

XMC_UART_CH_STATUS_t XMC_UART_CH_SetBaudrate(XMC_USIC_CH_t *const channel, uint32_t rate, uint32_t oversampling)
{
  XMC_UART_CH_STATUS_t status;
  
  status = XMC_UART_CH_STATUS_ERROR;
  
  if ((rate <= (XMC_SCU_CLOCK_GetPeripheralClockFrequency() >> 2U)) && (oversampling >= XMC_UART_CH_OVERSAMPLING_MIN_VAL))
  {
    if (XMC_USIC_CH_SetBaudrate(channel, rate, oversampling) == XMC_USIC_CH_STATUS_OK)
    {
      status = XMC_UART_CH_STATUS_OK;
    }
  } 
  return status;
}

void XMC_UART_CH_Transmit(XMC_USIC_CH_t *const channel, const uint16_t data)
{
  /* Check FIFO size */
  if ((channel->TBCTR & USIC_CH_TBCTR_SIZE_Msk) == 0UL)
  {
    /* Wait till the Transmit Buffer is free for transmission */
    while(XMC_USIC_CH_GetTransmitBufferStatus(channel) == XMC_USIC_CH_TBUF_STATUS_BUSY)
    {
    }
  
    /* Clear the Transmit Buffer indication flag */
    XMC_UART_CH_ClearStatusFlag(channel, (uint32_t)XMC_UART_CH_STATUS_FLAG_TRANSMIT_BUFFER_INDICATION);
  
    /*Transmit data */
    channel->TBUF[0U] = data;
  }
  else
  {
    channel->IN[0U] = data;
  }
}

uint16_t XMC_UART_CH_GetReceivedData(XMC_USIC_CH_t *const channel)
{
  uint16_t retval;

  /* Check FIFO size */
  if ((channel->RBCTR & USIC_CH_RBCTR_SIZE_Msk) == 0U)
  {
    retval = (uint16_t)channel->RBUF;
  }
  else
  {
    retval = (uint16_t)channel->OUTR;
  }

  return retval;
}

XMC_UART_CH_STATUS_t XMC_UART_CH_Stop(XMC_USIC_CH_t *const channel)
{
  XMC_UART_CH_STATUS_t status = XMC_UART_CH_STATUS_OK;

  if ((XMC_UART_CH_GetStatusFlag(channel) & (uint32_t)XMC_UART_CH_STATUS_FLAG_TRANSMITTER_FRAME_FINISHED) != 0U)
  {
    status = XMC_UART_CH_STATUS_BUSY;
  }
  
  /* USIC channel in IDLE mode */
  XMC_USIC_CH_SetMode(channel, XMC_USIC_CH_OPERATING_MODE_IDLE);

  return status;
}

void XMC_UART_CH_EnableEvent(XMC_USIC_CH_t *const channel, const uint32_t event)
{
  if ((event & 0x80000000U) != 0U)
  {
    /* USIC module event */
    channel->CCR |= event & 0x7fffffffU;
  }
  else
  {
    /* Protocol event */
    channel->PCR_ASCMode |= event;
  }
}

void XMC_UART_CH_DisableEvent(XMC_USIC_CH_t *const channel, const uint32_t event)
{
  if ((event & 0x80000000U) != 0U)
  {
    channel->CCR &= ~(event & 0x7fffffffU);
  }
  else
  {
    channel->PCR_ASCMode &= ~event;
  }
}
