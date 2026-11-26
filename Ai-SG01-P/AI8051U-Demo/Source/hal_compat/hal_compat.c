/* ============================================================================
 * hal_compat.c
 * ---------------------------------------------------------------------------
 * STM32 HAL 子集在 AI8051U（长缨-I / C351 32位）上的等价实现。
 * 覆盖 PAN312x_Driver.c / at_command_firmware.c 实际调用的 HAL 符号：
 *   - TIM2 仿真（由 bsp_timer 的 Timer0 1ms 节拍驱动，无需硬件 TIM2 中断）
 *   - GPIO_EXTI 中转（DIO8 / 第二路 PAN312x GPIO）
 *   - NVIC 调度（端口中断使能/失能、优先级占位）
 *   - HAL_Delay（基于 g_sys_ms）
 *   - HAL_GPIO_Init（伪 GPIO，仅编译兼容）
 *   - HAL_NVIC_SystemReset（软件复位）
 * ========================================================================== */
#include "hal_compat.h"
#include "ai8051_port.h"
#include "XSFR_STC8051U_8Bit.H"     /* EA / P3IE / P3INTF / P3IM0 / P3IM1 / IAP_* / EAXSFR */

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#pragma warning (disable: 280)
#pragma warning (disable: 275)
#endif
/* ===================== TIM2 仿真全局量 ===================== */
volatile uint32_t g_tim2_tick = 0;   /* TIM2 计数器（毫秒），由 Timer0 ISR 推进 */
volatile uint32_t g_sys_ms   = 0;    /* 系统毫秒节拍（替代 HAL_GetTick） */

static TIM_HandleTypeDef *g_tim2_htim   = 0;
static uint8_t            g_tim2_running = 0;

/* ===================== TIM2 仿真 ===================== */
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)
{
    g_tim2_htim = htim;
    /* 等价 STM32 HAL：HAL_TIM_Base_Init 内部会回调 MspInit（本工程由固件实现，
       完成 TIM2 时钟使能与 NVIC 占位）。 */
    HAL_TIM_Base_MspInit(htim);
    /* 启动 TIM2 仿真（由 Timer0 1ms 节拍驱动，无需硬件 TIM2 中断） */
    g_tim2_running = 0; /* Init must not start the sleep/wakeup timer. */
    g_tim2_tick = 0;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig)
{
    (void)htim; (void)sClockSourceConfig;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *sMasterConfig)
{
    (void)htim; (void)sMasterConfig;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
    g_tim2_htim = htim;
    g_tim2_running = 1;
    g_tim2_tick = 0;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{
    (void)htim;
    g_tim2_running = 0;
    return HAL_OK;
}

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
    if (htim != 0)
        HAL_TIM_PeriodElapsedCallback();
}

/* 由 Timer0 1ms ISR 调用：推进 TIM2 仿真，达到周期时触发回调 */
void HAL_TIM_Tick_Handler(void)
{
    if (!g_tim2_running || (g_tim2_htim == 0))
        return;

    g_tim2_tick++;
    if (g_tim2_tick > g_tim2_htim->Init.Period)
    {
        g_tim2_tick = 0;
        HAL_TIM_PeriodElapsedCallback();
    }
}

/* ===================== GPIO_EXTI 中转 ===================== */
void HAL_GPIO_EXTI_IRQHandler(uint16_t pin)
{
    HAL_GPIO_EXTI_Callback();
}

void HAL_GPIO_Init(GPIO_TypeDef *gpio, GPIO_InitTypeDef *init)
{
    /* 伪 GPIO：AI8051U 实际引脚由 HAL_NVIC_EnableIRQ 处理中断相关配置；
       此处对普通 GPIO 模式仅作占位，不执行硬件动作。 */
    (void)gpio; (void)init;
}

/* ===================== 延时 ===================== */
void HAL_Delay(uint32_t ms)
{
    uint32_t start = g_sys_ms;
    while ((g_sys_ms - start) < ms) { /* 轮询系统毫秒节拍 */ }
}

uint32_t HAL_GetTick(void)
{
    return g_sys_ms;
}

/* ===================== NVIC 调度 ===================== */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    (void)IRQn; (void)PreemptPriority; (void)SubPriority;
}

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    EAXSFR();                                   /* 允许访问 XSFR（端口中断寄存器） */
    if (IRQn == EXTI1_IRQn)                     /* DIO8  -> P3.2 上升沿端口中断 */
    {
        P3IM0 |= 0x04;                          /* P3.2：IM0=1 */
        P3IM1 |= 0x04;                          /* P3.2：IM1=1 -> 仅上升沿触发 */
        P3IE  |= 0x04;                          /* 使能 P3.2 中断 */
    }
    else if (IRQn == EXTI9_5_IRQn)              /* 第二路 PAN312x GPIO -> P3.3 */
    {
        P3IM0 |= 0x08;
        P3IM1 |= 0x08;
        P3IE  |= 0x08;
    }
    /* TIM2_IRQn / USART1_IRQn：无硬件动作（TIM2 由 Timer0 节拍仿真；UART1 已在 UartInit 使能） */
}

void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    EAXSFR();
    if (IRQn == EXTI1_IRQn)
        P3IE &= ~0x04;
    else if (IRQn == EXTI9_5_IRQn)
        P3IE &= ~0x08;
}

void HAL_NVIC_SystemReset(void)
{
    /* AI8051U 软件复位：置 IAP_CONTR 的 SWRST 位（0x20）。
       若芯片型号该位不同，可改为喂狗复位；此处为通用占位。 */
    EAXSFR();
    IAP_CONTR |= 0x20;          /* SWRST：请求软件复位 */
    while (1) { /* 等待复位生效 */ }
}
