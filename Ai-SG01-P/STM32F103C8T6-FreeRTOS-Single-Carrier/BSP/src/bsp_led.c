/**
  ******************************************************************************
  * @file    bsp_led.c
  * @brief   LED driver for the Ai-SG01 board (GREEN=PA8, BLUE=PB15).
  *
  * @note    Ported from the original Ai-SG01 bsp_led.c. GPIO is programmed via
  *          registers (no StdPeriph GPIO_Init, which is kept available for the
  *          firmware's HAL-compatible GPIO_InitTypeDef). LED pins are PA8/PB15 —
  *          deliberately different from the FreeRTOS package's PB1 LED so they
  *          do not collide with the PAN312x IRQ line (PB1).
  ******************************************************************************
  */
#include "bsp_led.h"

/* GREEN_LED -> PA8, BLUE_LED -> PB15 */
static GPIO_TypeDef *LedPort[2] =
{
    GPIOA,   /* GREEN_LED */
    GPIOB    /* BLUE_LED  */
};
static const uint16_t LedPin[2] =
{
    GPIO_Pin_8,   /* GREEN_LED */
    GPIO_Pin_15   /* BLUE_LED  */
};

void bsp_InitLed(void)
{
    /* 打开 GPIOA / GPIOB 时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;

    /* PA8: CRH[3:0] = MODE(50MHz)=11, CNF(PP)=00 -> 0x3 */
    GPIOA->CRH &= ~(0xFu << 0);
    GPIOA->CRH |=  (0x3u << 0);

    /* PB15: CRH[31:28] = MODE(50MHz)=11, CNF(PP)=00 -> 0x3 << 28 */
    GPIOB->CRH &= ~(0xFu << 28);
    GPIOB->CRH |=  (0x3u << 28);

    /* 默认熄灭（低电平） */
    GPIOA->BRR = GPIO_Pin_8;
    GPIOB->BRR = GPIO_Pin_15;
}

void bsp_LedOn(uint8_t _no)
{
    if (_no < 2u)
    {
        LedPort[_no]->BSRR = LedPin[_no];
    }
}

void bsp_LedOff(uint8_t _no)
{
    if (_no < 2u)
    {
        LedPort[_no]->BRR = LedPin[_no];
    }
}

void bsp_LedToggle(uint8_t _no)
{
    if (_no < 2u)
    {
        LedPort[_no]->ODR ^= LedPin[_no];
    }
}

uint8_t bsp_IsLedOn(uint8_t _no)
{
    if (_no < 2u)
    {
        return ((LedPort[_no]->ODR & LedPin[_no]) != 0u) ? 1u : 0u;
    }
    return 0u;
}

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
