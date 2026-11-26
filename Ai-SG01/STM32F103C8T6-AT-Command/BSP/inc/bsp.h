/**
  ******************************************************************************
  * 文件名 ：   bsp.h
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H_
#define __BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */
	
/* 这个宏仅用于调试阶段排错 */
#define BSP_Printf		printf


#define EXAMPLE_DATE	"2025-09-25"
#define DEMO_VER		"0.0.1"

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
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

/* 定义优先级分组 */
#define NVIC_PREEMPT_PRIORITY	4

/* Private includes ----------------------------------------------------------*/
/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_led.h"
#include "bsp_flash.h"

#include "PAN312x_Hal.h"
#include "PAN312x_Driver.h"


/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void bsp_Idle(void);

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H_ */
