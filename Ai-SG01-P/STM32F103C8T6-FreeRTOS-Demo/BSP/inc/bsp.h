/**
  ******************************************************************************
  * @file    bsp.h
  * @brief   Board support package header for the STM32F103C8T6 + FreeRTOS port
  *          of the Ai-SG01 PAN312x AT-command firmware.
  *
  * @note    This is the ported version of the original Ai-SG01 bsp.h. The only
  *          structural change is that the ST HAL/CubeMX layer (stm32f1xx_hal.h)
  *          is replaced by the minimal compatibility shim (hal_compat.h) which
  *          provides the small subset of HAL symbols the firmware and PAN312x
  *          driver actually use, implemented on top of the StdPeriph register
  *          structs already supplied by stm32f10x.h.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H_
#define __BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 全局中断控制的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */
	
/* 打印输出重定向到串口1 */
#define BSP_Printf		printf

#define EXAMPLE_DATE	"2025-09-25"
#define DEMO_VER		"0.0.1"

/* Includes ------------------------------------------------------------------*/
#include "hal_compat.h"              /* <-- port shim, replaces stm32f1xx_hal.h */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/* 中断优先级分组 */
#define NVIC_PREEMPT_PRIORITY	4

/* Private includes ----------------------------------------------------------*/
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_led.h"
#include "bsp_flash.h"

#include "PAN312x_Hal.h"
#include "PAN312x_Driver.h"


/* 提供给C文件里使用的函数 */
void bsp_Init(void);
void bsp_Idle(void);

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H_ */
