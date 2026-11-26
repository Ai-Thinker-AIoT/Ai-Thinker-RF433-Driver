/**
  ******************************************************************************
  * @file    bsp_timer.c
  * @brief   Software timers, runtime counter and delays for the StdPeriph port.
  *
  * @note    Ported from the original Ai-SG01 bsp_timer.c. The original used
  *          SysTick for the 1 ms tick; in this port SysTick is owned by
  *          FreeRTOS, so a hardware TIM3 produces the 1 ms tick that drives the
  *          soft timers and g_iRunTime. Microsecond delays use the DWT cycle
  *          counter (also independent of SysTick). The public API is unchanged.
  ******************************************************************************
  */
#include "bsp.h"

/* 使用 TIM3 作为 1ms 系统时基（TIM2 已被 PAN312x 固件用于射频唤醒去抖） */
#define BSP_TICK_TIM        TIM3

/* 这两个全局变量用于 bsp_DelayMS() */
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t  s_ucTimeOutFlag = 0;

/* 软件定时器结构体数组 */
static SOFT_TMR s_tTmr[TMR_COUNT] = {0};

/*
	全局运行时间，单位1ms
*/
__IO int32_t g_iRunTime = 0;

static __IO uint8_t g_ucEnableTickISR = 0;	/* 等待定时器初始化 */

static void bsp_SoftTimerDec(SOFT_TMR *_tmr);

/*
*********************************************************************************************************
*	函 数 名: bsp_InitTimer
*	功能说明: 初始化 TIM3 为 1ms 时基，并初始化软件定时器
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitTimer(void)
{
	uint8_t i;

	for (i = 0; i < TMR_COUNT; i++)
	{
		s_tTmr[i].Count = 0;
		s_tTmr[i].PreLoad = 0;
		s_tTmr[i].Flag = 0;
		s_tTmr[i].Mode = TMR_ONCE_MODE;
	}

	/* DWT 微秒延时初始化 */
	DWT_Init();

	/* TIM3 时钟使能 (APB1) */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	/* TIM3 时钟 = 2 * APB1 = 72MHz。分频 72 -> 1MHz 计数；自动重装 1000-1 -> 1ms */
	TIM3->PSC = 72u - 1u;
	TIM3->ARR = 1000u - 1u;
	TIM3->CNT = 0u;
	TIM3->DIER |= TIM_DIER_UIE;     /* 更新中断 */
	TIM3->CR1 |= TIM_CR1_CEN;       /* 启动计数 */

	NVIC_SetPriority(TIM3_IRQn, 4u);
	NVIC_EnableIRQ(TIM3_IRQn);

	g_ucEnableTickISR = 1;
}

/*
*********************************************************************************************************
*	函 数 名: SysTick_ISR
*	功能说明: 每毫秒调用一次（由 TIM3 溢出触发），维护软定时器与运行时间
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void SysTick_ISR(void)
{
	uint8_t i;

	/* 每毫秒递减 bsp_DelayMS 的计数器 */
	if (s_uiDelayCount > 0)
	{
		if (--s_uiDelayCount == 0)
		{
			s_ucTimeOutFlag = 1;
		}
	}

	/* 软定时器每毫秒递减 */
	for (i = 0; i < TMR_COUNT; i++)
	{
		bsp_SoftTimerDec(&s_tTmr[i]);
	}

	/* 全局运行时间每毫秒 +1 */
	g_iRunTime++;
	if (g_iRunTime == 0x7FFFFFFF)
	{
		g_iRunTime = 0;
	}
}

/*
*********************************************************************************************************
*	TIM3 中断服务程序：1ms 系统时基
*********************************************************************************************************
*/
void TIM3_IRQHandler(void)
{
	if ((TIM3->SR & TIM_SR_UIF) != 0u)
	{
		TIM3->SR = (uint16_t)~TIM_SR_UIF;   /* 清更新中断标志 */

		HAL_IncTick();                      /* 维护 HAL 的 tick 计数 */
		if (g_ucEnableTickISR != 0)
		{
			SysTick_ISR();
		}
	}
}

static void bsp_SoftTimerDec(SOFT_TMR *_tmr)
{
	if (_tmr->Count > 0)
	{
		if (--_tmr->Count == 0)
		{
			_tmr->Flag = 1;
			if (_tmr->Mode == TMR_AUTO_MODE)
			{
				_tmr->Count = _tmr->PreLoad;
			}
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_DelayMS
*	功能说明: ms 级延时，最小分辨率为 1ms
*	形    参:  n : 延时长度，单位 1 ms
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_DelayMS(uint32_t n)
{
	if (n == 0)
	{
		return;
	}
	else if (n == 1)
	{
		n = 2;
	}

	DISABLE_INT();
	s_uiDelayCount = n;
	s_ucTimeOutFlag = 0;
	ENABLE_INT();

	while (1)
	{
		bsp_Idle();
		if (s_ucTimeOutFlag == 1)
		{
			break;
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_DelayUS
*	功能说明: us 级延时（基于 DWT 周期计数器，与 SysTick 无关）
*	形    参:  n : 延时长度，单位 1 us
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_DelayUS(uint32_t n)
{
	DWT_DelayUS(n);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_StartTimer
*	功能说明: 启动一个定时器
*	形    参:  _id     : 定时器ID
*			   _period : 定时周期，单位 1ms
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_StartTimer(uint8_t _id, uint32_t _period)
{
	if (_id >= TMR_COUNT)
	{
		BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, __FUNCTION__);
		while(1);
	}

	DISABLE_INT();
	s_tTmr[_id].Count = _period;
	s_tTmr[_id].PreLoad = _period;
	s_tTmr[_id].Flag = 0;
	s_tTmr[_id].Mode = TMR_ONCE_MODE;
	ENABLE_INT();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_StartAutoTimer
*	功能说明: 启动一个自动定时器
*	形    参:  _id     : 定时器ID
*			   _period : 定时周期，单位 1ms
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_StartAutoTimer(uint8_t _id, uint32_t _period)
{
	if (_id >= TMR_COUNT)
	{
		BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, __FUNCTION__);
		while(1);
	}

	DISABLE_INT();
	s_tTmr[_id].Count = _period;
	s_tTmr[_id].PreLoad = _period;
	s_tTmr[_id].Flag = 0;
	s_tTmr[_id].Mode = TMR_AUTO_MODE;
	ENABLE_INT();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_StopTimer
*	功能说明: 停止一个定时器
*	形    参:  _id     : 定时器ID
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_StopTimer(uint8_t _id)
{
	if (_id >= TMR_COUNT)
	{
		BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, __FUNCTION__);
		while(1);
	}

	DISABLE_INT();
	s_tTmr[_id].Count = 0;
	s_tTmr[_id].Flag = 0;
	s_tTmr[_id].Mode = TMR_ONCE_MODE;
	ENABLE_INT();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_CheckTimer
*	功能说明: 检测定时器是否超时
*	形    参:  _id     : 定时器ID
*	返 回 值: 返回 0 表示定时未到，1 表示定时到达
*********************************************************************************************************
*/
uint8_t bsp_CheckTimer(uint8_t _id)
{
	if (_id >= TMR_COUNT)
	{
		return 0;
	}

	if (s_tTmr[_id].Flag == 1)
	{
		s_tTmr[_id].Flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_GetRunTime
*	功能说明: 获取 CPU 运行时间，单位 1ms
*	形    参:  无
*	返 回 值: CPU 运行时间，单位 1ms
*********************************************************************************************************
*/
int32_t bsp_GetRunTime(void)
{
	int32_t runtime;

	DISABLE_INT();
	runtime = g_iRunTime;
	ENABLE_INT();

	return runtime;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_CheckRunTime
*	功能说明: 计算当前时间与给定时间的差值，用于主循环计时
*	形    参:  _LastTime : 上次时间
*	返 回 值: 当前时间与过去时间的差值，单位 1ms
*********************************************************************************************************
*/
int32_t bsp_CheckRunTime(int32_t _LastTime)
{
	int32_t now_time;
	int32_t time_diff;

	DISABLE_INT();
	now_time = g_iRunTime;
	ENABLE_INT();

	if (now_time >= _LastTime)
	{
		time_diff = now_time - _LastTime;
	}
	else
	{
		time_diff = 0x7FFFFFFF - _LastTime + now_time;
	}

	return time_diff;
}

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
