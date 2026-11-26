/* ============================================================================
 * bsp_timer.h — 软定时器 + 系统节拍（等价 STM32 SysTick 1ms）
 * TIM2 仿真由 hal_compat 完成；此处用 Timer0 1ms 中断驱动 g_sys_ms 与软定时器。
 * ========================================================================== */
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#define TMR_COUNT   4       /* 软件定时器个数（ID 范围 0~3） */

typedef enum {
    TMR_ONCE_MODE = 0,      /* 单次模式 */
    TMR_AUTO_MODE = 1       /* 自动重载模式 */
} TMR_MODE_E;

typedef struct {
    volatile uint8_t  Mode;     /* 定时器模式（0/1） */
    volatile uint8_t  Flag;     /* 定时到达标志 */
    volatile uint32_t Count;    /* 当前计数 */
    volatile uint32_t PreLoad;  /* 预装值 */
} SOFT_TMR;

void bsp_InitTimer(void);
void bsp_DelayMS(uint32_t n);
void bsp_DelayUS(uint32_t n);
void bsp_StartTimer(uint8_t _id, uint32_t _period);
void bsp_StartAutoTimer(uint8_t _id, uint32_t _period);
void bsp_StopTimer(uint8_t _id);
uint8_t bsp_CheckTimer(uint8_t _id);
int32_t bsp_GetRunTime(void);
int32_t bsp_CheckRunTime(int32_t _LastTime);

/* Timer0 1ms 中断服务程序入口（定义见 bsp_timer.c，由硬件向量直接调用，无需在此声明原型）。
   注意：C351 不允许在头文件里用 interrupt 关键字声明中断函数原型，故此处不声明。 */

#endif /* __BSP_TIMER_H */
