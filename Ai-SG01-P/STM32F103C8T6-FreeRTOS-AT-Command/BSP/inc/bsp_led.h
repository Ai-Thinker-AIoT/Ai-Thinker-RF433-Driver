#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"   /* uint8_t / GPIO_TypeDef / RCC */

typedef enum
{
	GREEN_LED = 0,
	BLUE_LED
} COLOUR_LED;

/* 供外部调用的函数 */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

#endif

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
