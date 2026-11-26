/* ============================================================================
 * bsp.h — AI8051U-34K64 板级支持包入口（替代 STM32 的 stm32f1xx_hal.h）
 * ---------------------------------------------------------------------------
 * 集中包含：基础类型 / HAL 垫片 / 各 bsp 子模块 / PAN312x 驱动头。
 * 注意：本头被 PAN312x_Hal.h / PAN312x_Driver.h 间接依赖，但其自身又包含它们；
 *       依赖环形由 include 守卫与类型前置（ai8051_port.h + hal_compat.h 先包含）打破。
 * ========================================================================== */
#ifndef __BSP_H_
#define __BSP_H_

/* 全局中断开关（替代 Cortex-M 的 __set_PRIMASK） */
#define ENABLE_INT()    EA = 1
#define DISABLE_INT()   EA = 0

#define BSP_Printf      printf

#define EXAMPLE_DATE    "2025-09-25"
#define DEMO_VER        "0.0.1"

#define NVIC_PREEMPT_PRIORITY   4

/* 基础定宽类型 / EA 宏 / 主频常量 */
#include "ai8051_port.h"
/* STM32 HAL 子集垫片（GPIO_EXTI / NVIC / TIM2 / Delay / Reset） */
#include "hal_compat.h"

#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_led.h"
#include "bsp_flash.h"

/* PAN312x 驱动（其内部 #include "bsp.h" 会被本守卫跳过，类型已由上方提供） */
#include "PAN312x_Hal.h"
#include "PAN312x_Driver.h"

void bsp_Init(void);
void bsp_Idle(void);
void Error_Handler(void);

#endif /* __BSP_H_ */
