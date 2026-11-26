/* ============================================================================
 * bsp_timer.c — AI8051U-34K64 软定时器 + 系统节拍
 *   用定时器0（16位自动重载 + 1T）产生 1ms 节拍，中断内推进：
 *     - 阻塞延时计数（bsp_DelayMS）
 *     - 4 路软件定时器（bsp_StartTimer 等）
 *     - 系统运行时间 g_iRunTime
 *     - 系统毫秒节拍 g_sys_ms（替代 HAL_GetTick）
 *     - 仿真 TIM2（HAL_TIM_Tick_Handler）
 *   等价于 STM32 的 SysTick 1ms 方案。
 * ========================================================================== */
#include "bsp.h"
#include "bsp_timer.h"
#include "hal_compat.h"

/* 1ms 重装值（1T 模式）：65536 - SYSCLK/1000（四舍五入） */
#define T0_RELOAD_1MS   (65536UL - (AI8051_SYS_CLK_HZ + 500UL) / 1000UL)

/* 阻塞延时计数（bsp_DelayMS 使用） */
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t  s_ucTimeOutFlag = 0;

/* 软件定时器结构数组 */
static SOFT_TMR s_tTmr[TMR_COUNT] = {0};

/* 系统运行时间，单位 1ms（替代 STM32 的 g_iRunTime） */
volatile int32_t g_iRunTime = 0;

static volatile uint8_t g_ucEnableSystickISR = 0;

static void bsp_SoftTimerDec(SOFT_TMR *_tmr);

/*
 * 初始化：配置 Timer0 为 16位自动重载 + 1T，开启中断（EA 由 bsp_Init 末尾统一置1）
 */
void bsp_InitTimer(void)
{
    uint8_t i;

    for (i = 0; i < TMR_COUNT; i++)
    {
        s_tTmr[i].Count   = 0;
        s_tTmr[i].PreLoad = 0;
        s_tTmr[i].Flag    = 0;
        s_tTmr[i].Mode    = TMR_ONCE_MODE;
    }

    TMOD &= 0xF0;                       /* T0 -> 方式0（STC：16位自动重载） */
    AUXR |= T0x12;                      /* T0 1T 模式 */
    TH0  = (uint8_t)(T0_RELOAD_1MS >> 8);
    TL0  = (uint8_t)(T0_RELOAD_1MS & 0xFF);
    TF0  = 0;
    TR0  = 1;                            /* 启动 T0 */
    ET0  = 1;                            /* 允许 T0 中断 */

    g_ucEnableSystickISR = 1;
}

/*
 * Timer0 1ms 中断服务程序
 */
void Timer0_ISR(void) interrupt 1
{
    uint8_t i;

    /* 重装（兼容非自动重载实现，自动重载模式下为冗余但无害） */
    TH0 = (uint8_t)(T0_RELOAD_1MS >> 8);
    TL0 = (uint8_t)(T0_RELOAD_1MS & 0xFF);

    /* 阻塞延时计数递减 */
    if (s_uiDelayCount > 0)
    {
        if (--s_uiDelayCount == 0)
            s_ucTimeOutFlag = 1;
    }

    /* 软件定时器递减 */
    for (i = 0; i < TMR_COUNT; i++)
        bsp_SoftTimerDec(&s_tTmr[i]);

    /* 系统运行时间（1ms++） */
    g_iRunTime++;
    if (g_iRunTime == 0x7FFFFFFF)
        g_iRunTime = 0;

    /* 系统毫秒节拍 */
    g_sys_ms++;

    /* 推进仿真 TIM2（到达周期时回调 HAL_TIM_PeriodElapsedCallback） */
    HAL_TIM_Tick_Handler();
}

static void bsp_SoftTimerDec(SOFT_TMR *_tmr)
{
    if (_tmr->Count > 0)
    {
        if (--_tmr->Count == 0)
        {
            _tmr->Flag = 1;
            if (_tmr->Mode == TMR_AUTO_MODE)
                _tmr->Count = _tmr->PreLoad;
        }
    }
}

void bsp_DelayMS(uint32_t n)
{
    if (n == 0)
        return;
    else if (n == 1)
        n = 2;

    DISABLE_INT();

    s_uiDelayCount  = n;
    s_ucTimeOutFlag = 0;

    ENABLE_INT();

    while (1)
    {
        bsp_Idle();
        if (s_ucTimeOutFlag == 1)
            break;
    }
}

void bsp_DelayUS(uint32_t n)
{
    /* 近似微秒延时：33.1776MHz 1T，每轮约 6 个时钟；循环次数 = n*F/1e6/6 */
    volatile uint32_t loops = (n * (AI8051_SYS_CLK_HZ / 1000000UL)) / 6UL;
    while (loops--);
}

void bsp_StartTimer(uint8_t _id, uint32_t _period)
{
    if (_id >= TMR_COUNT)
    {
        BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, "");
        while (1);
    }

    DISABLE_INT();
    s_tTmr[_id].Count   = _period;
    s_tTmr[_id].PreLoad = _period;
    s_tTmr[_id].Flag    = 0;
    s_tTmr[_id].Mode    = TMR_ONCE_MODE;
    ENABLE_INT();
}

void bsp_StartAutoTimer(uint8_t _id, uint32_t _period)
{
    if (_id >= TMR_COUNT)
    {
        BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, "");
        while (1);
    }

    DISABLE_INT();
    s_tTmr[_id].Count   = _period;
    s_tTmr[_id].PreLoad = _period;
    s_tTmr[_id].Flag    = 0;
    s_tTmr[_id].Mode    = TMR_AUTO_MODE;
    ENABLE_INT();
}

void bsp_StopTimer(uint8_t _id)
{
    if (_id >= TMR_COUNT)
    {
        BSP_Printf("Error: file %s, function %s()\r\n", __FILE__, "");
        while (1);
    }

    DISABLE_INT();
    s_tTmr[_id].Count   = 0;
    s_tTmr[_id].Flag    = 0;
    s_tTmr[_id].Mode    = TMR_ONCE_MODE;
    ENABLE_INT();
}

uint8_t bsp_CheckTimer(uint8_t _id)
{
    if (_id >= TMR_COUNT)
        return 0;

    if (s_tTmr[_id].Flag == 1)
    {
        s_tTmr[_id].Flag = 0;
        return 1;
    }
    return 0;
}

int32_t bsp_GetRunTime(void)
{
    int32_t runtime;
    DISABLE_INT();
    runtime = g_iRunTime;
    ENABLE_INT();
    return runtime;
}

int32_t bsp_CheckRunTime(int32_t _LastTime)
{
    int32_t now_time;
    int32_t time_diff;

    DISABLE_INT();
    now_time = g_iRunTime;
    ENABLE_INT();

    if (now_time >= _LastTime)
        time_diff = now_time - _LastTime;
    else
        time_diff = 0x7FFFFFFF - _LastTime + now_time;

    return time_diff;
}
