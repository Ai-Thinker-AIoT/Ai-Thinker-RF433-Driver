/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "bsp_uart.h"

UART_HandleTypeDef huart1;

// 环形缓冲区
static uint8_t usart_rx_buf[USART_RX_BUF_SIZE];
static volatile uint16_t usart_rx_head = 0;
static volatile uint16_t usart_rx_tail = 0;

/* USART1 init function */

void bsp_InitUart(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	
  // 启用接收中断
	HAL_UART_Receive_IT(&huart1, &usart_rx_buf[usart_rx_head], 1);
	
	// 配置NVIC
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	
	// 初始化缓冲区
	usart_rx_head = 0;
	usart_rx_tail = 0;
	memset(usart_rx_buf, 0, USART_RX_BUF_SIZE);

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance==USART1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
  }
}

#if 1
void USART1_Reinit(void)
{
    // 1. 重新配置GPIO
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    
    // TX引脚 (PA9)
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // RX引脚 (PA10)
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 2. 重新初始化串口
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);

    // 3. 重新启用中断
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
    // 4. 重启接收中断
    HAL_UART_Receive_IT(&huart1, &usart_rx_buf[usart_rx_head], 1);
    
    // 5. 重置缓冲区状态
    usart_rx_head = 0;
    usart_rx_tail = 0;
    memset(usart_rx_buf, 0, USART_RX_BUF_SIZE);
}

void USART1_EnterSleep(void)
{
    // 保存串口状态
    HAL_UART_AbortReceive_IT(&huart1);
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    
    // 关闭串口时钟
    __HAL_RCC_USART1_CLK_DISABLE();
    __HAL_RCC_GPIOA_CLK_DISABLE();
}

#endif

// 发送字符串
void USART1_SendString(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

// 发送数据
void USART1_SendData(uint8_t *data, uint16_t size)
{
    HAL_UART_Transmit(&huart1, data, size, HAL_MAX_DELAY);
}

// 从环形缓冲区获取数据
uint16_t USART1_ReceiveData(uint8_t *buffer, uint16_t max_len)
{
    uint16_t count = 0;
    
    while (usart_rx_tail != usart_rx_head && count < max_len) {
        buffer[count++] = usart_rx_buf[usart_rx_tail];
        usart_rx_tail = (usart_rx_tail + 1) % USART_RX_BUF_SIZE;
    }
    
    return count;
}

// 获取接收缓冲区中的数据量
uint16_t USART1_GetRxCount(void)
{
    if (usart_rx_head >= usart_rx_tail) {
        return usart_rx_head - usart_rx_tail;
    } else {
        return USART_RX_BUF_SIZE - usart_rx_tail + usart_rx_head;
    }
}

// 清空接收缓冲区
void USART1_ClearRxBuffer(void)
{
    usart_rx_head = 0;
    usart_rx_tail = 0;
}

// USART1中断处理函数
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

// HAL库接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        // 更新缓冲区指针
        usart_rx_head = (usart_rx_head + 1) % USART_RX_BUF_SIZE;
        
        // 如果缓冲区满，丢弃最旧的数据
        if (usart_rx_head == usart_rx_tail) {
            usart_rx_tail = (usart_rx_tail + 1) % USART_RX_BUF_SIZE;
        }
        
        // 继续接收下一个字符
        HAL_UART_Receive_IT(huart, &usart_rx_buf[usart_rx_head], 1);
    }
}

/*
*********************************************************************************************************
*	函 数 名: fputc
*	功能说明: 重定义putc函数，这样可以使用printf函数从串口1打印输出
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int fputc(int ch, FILE *f)
{
#if 0	/* 将需要printf的字符通过串口中断FIFO发送出去，printf函数会立即返回 */
	comSendChar(COM1, ch);
	
	return ch;
#else	/* 采用阻塞方式发送每个字符,等待数据发送完毕 */
	/* 写一个字节到USART1 */
//	USART1->DR = ch;
//	
//	/* 等待发送结束 */
//	while((USART1->SR & USART_SR_TC) == 0)
//	{}
    
    uint8_t data = ch;
    
    HAL_UART_Transmit(&huart1, &data, 1, HAL_MAX_DELAY);
	
	return ch;
#endif
}

/*
*********************************************************************************************************
*	函 数 名: fgetc
*	功能说明: 重定义getc函数，这样可以使用getchar函数从串口1输入数据
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int fgetc(FILE *f)
{

#if 0	/* 从串口接收FIFO中取1个数据, 只有取到数据才返回 */
	uint8_t ucData;

	while(comGetChar(COM1, &ucData) == 0);

	return ucData;
#else
	/* 等待接收到数据 */
	while((USART1->SR & USART_SR_RXNE) == 0)
	{}

	return (int)USART1->DR;
#endif
}
/* USER CODE END 1 */
