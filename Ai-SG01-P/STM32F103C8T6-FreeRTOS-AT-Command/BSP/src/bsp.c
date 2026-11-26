/**
  ******************************************************************************
  * @file    bsp.c
  * @brief   Board support package init for the STM32F103C8T6 + FreeRTOS port.
  *
  * @note    Ported from the original Ai-SG01 bsp.c. The clock has already been
  *          configured to 72 MHz (HSE 8 MHz * PLL9) by the startup file
  *          (system_stm32f10x.c, SYSCLK_FREQ_72MHz), so SystemClock_Config() is
  *          intentionally a no-op. This file is the only place that calls the
  *          StdPeriph/compat layer to bring up UART, timers, LEDs and Flash.
  ******************************************************************************
  */
#include "bsp.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化所有的硬件设备。该函数在 FreeRTOS 启动前由 main() 调用一次。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Init(void)
{
    /* 复位所有外设、初始化 Flash 接口（HAL_Init 在本移植中为空实现） */
    HAL_Init();

    /* 时钟已在启动文件中配置为 72MHz，这里无需再配置 */
    SystemClock_Config();

    /* 设置中断优先级分组：4 位抢占，0 位子优先级 */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* 初始化各外设 */
    bsp_InitTimer();
    bsp_InitUart();
    bsp_InitLed();

    /* 初始化 Flash（内部 Flash 读写） */
    if (Flash_Init() != HAL_OK)
    {
        printf("Flash initialization failed!\r\n");
        while (1);
    }
}

/**
  * @brief System Clock Configuration (no-op: 72 MHz already set by startup).
  * @retval None
  */
void SystemClock_Config(void)
{
    /* 启动文件 system_stm32f10x.c 在 SystemInit() 中已根据 SYSCLK_FREQ_72MHz
       把系统时钟配置为 HSE(8MHz) * PLL9 = 72MHz。此处保留空实现，便于与原工程
       保持一致的调用关系。 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 主循环/延时中空闲时执行的函数（目前为空）
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
    /* 空闲时无需特殊处理 */
}
