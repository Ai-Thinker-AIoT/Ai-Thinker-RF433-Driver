/**
  ******************************************************************************
  * 文件名 ：   bsp_uart.h
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/

#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "bsp.h"

// 外部可见的串口句柄
extern UART_HandleTypeDef huart1;

// 环形缓冲区大小
#define USART_RX_BUF_SIZE 256

// 函数声明
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
