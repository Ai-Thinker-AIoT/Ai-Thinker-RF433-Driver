/**
  ******************************************************************************
  * @file    bsp_uart.h
  * @brief   USART1 (PA9/PA10 @115200) driver header for the StdPeriph port.
  *
  * @note    Ported from the original Ai-SG01 bsp_uart.h. The HAL UART handle is
  *          no longer used; the public API (ring-buffer based) is unchanged so
  *          the firmware keeps calling USART1_SendString / printf unchanged.
  ******************************************************************************
  */

#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "bsp.h"

// 接收缓冲区大小
#define USART_RX_BUF_SIZE 256

// 对外提供的函数
void bsp_InitUart(void);
void USART1_Reinit(void);
void USART1_EnterSleep(void);
void USART1_SendString(const char *str);
void USART1_SendData(uint8_t *data, uint16_t size);
uint16_t USART1_ReceiveData(uint8_t *buffer, uint16_t max_len);
uint16_t USART1_GetRxCount(void);
void USART1_ClearRxBuffer(void);

#endif

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
