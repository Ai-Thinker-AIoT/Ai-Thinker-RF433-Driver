/* ============================================================================
 * hal_compat.h
 * ---------------------------------------------------------------------------
 * STM32 HAL 子集在 AI8051U 上的等价垫片。
 *
 * 目的：让 PAN312x_Driver.c / at_command_firmware.c 以「近乎原样」编译，
 *       仅替换其实际调用的少量 HAL 符号（GPIO_EXTI / NVIC / RCC / TIM2
 *       软件仿真 / Delay / SystemReset / GPIO 类型与宏）。
 *
 * 设计要点：
 *   - TIM2 仿真：AI8051U 无经典 Timer2，TIM2 由 bsp_timer 的 Timer0 1ms
 *     节拍驱动（HAL_TIM_Tick_Handler），无需硬件 TIM2 中断。
 *   - DIO8 / 第二路 PAN312x GPIO 中断：映射到 P3.2 / P3.3 的端口中断，
 *     上升沿，经 port_int_vec.a51 中转至 interrupt 13。
 *   - 具体硬件操作由各 bsp_*.c / PAN312x_Hal.c 完成；本文件仅做接口与
 *     调度壳。
 * ========================================================================== */
#ifndef __HAL_COMPAT_H__
#define __HAL_COMPAT_H__

#include "ai8051_port.h"

/* ========================== 状态类型 ========================== */
typedef enum {
    HAL_OK      = 0x00U,
    HAL_ERROR   = 0x01U,
    HAL_BUSY    = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

#define HAL_MAX_DELAY   0xFFFFFFFFUL

typedef uint8_t GPIO_PinState;
#define GPIO_PIN_SET    0x0001U
#define GPIO_PIN_RESET  0x0000U

/* ===================== 伪 GPIO 类型（仅编译兼容） ===================== */
/* 实际引脚由 HAL_GPIO_Init 内部按 Pin 映射到具体 AI8051U 端口。 */
typedef struct { uint32_t dummy; } GPIO_TypeDef;
typedef struct {
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
} GPIO_InitTypeDef;

#define GPIOB           ((GPIO_TypeDef *)0)
#define GPIO_PIN_5      ((uint16_t)0x0020U)
#define GPIO_PIN_0    ((uint16_t)0x0001U)
#define GPIO_PIN_1    ((uint16_t)0x0002U)
#define GPIO_PIN_2    ((uint16_t)0x0004U)
#define GPIO_PIN_3    ((uint16_t)0x0008U)
#define GPIO_PIN_4    ((uint16_t)0x0010U)
#define GPIO_PIN_5    ((uint16_t)0x0020U)
#define GPIO_PIN_6    ((uint16_t)0x0040U)
#define GPIO_PIN_7    ((uint16_t)0x0080U)
#define GPIO_PIN_8    ((uint16_t)0x0100U)
#define GPIO_PIN_9    ((uint16_t)0x0200U)
#define GPIO_PIN_10    ((uint16_t)0x0400U)
#define GPIO_PIN_11    ((uint16_t)0x0800U)
#define GPIO_PIN_12    ((uint16_t)0x1000U)
#define GPIO_PIN_13    ((uint16_t)0x2000U)
#define GPIO_PIN_14    ((uint16_t)0x4000U)
#define GPIO_PIN_15    ((uint16_t)0x8000U)


#define GPIO_MODE_INPUT          0x00000000U
#define GPIO_MODE_OUTPUT_PP      0x00000001U
#define GPIO_MODE_IT_RISING      0x00010000U
#define GPIO_NOPULL              0x00000000U
#define GPIO_PULLUP              0x00000001U
#define GPIO_SPEED_FREQ_LOW      0x00000000U
#define GPIO_SPEED_FREQ_HIGH     0x00000001U

/* ===================== 伪 EXTI / NVIC 中断号 ===================== */
typedef enum {
    EXTI1_IRQn   = 0,   /* DIO8  -> P3.2 端口中断（上升沿） */
    EXTI9_5_IRQn = 1,   /* 第二路 PAN312x GPIO -> P3.3 端口中断 */
    TIM2_IRQn    = 2,   /* 仿真 TIM2（由 Timer0 节拍驱动，非硬件中断） */
    USART1_IRQn  = 3    /* UART1（interrupt 4） */
} IRQn_Type;

/* ===================== 伪 TIM 类型 ===================== */
typedef struct {
    uint32_t Prescaler;
    uint32_t CounterMode;
    uint32_t Period;
    uint32_t ClockDivision;
} TIM_Base_InitTypeDef;

typedef struct {
    uint32_t Instance;
    TIM_Base_InitTypeDef Init;
} TIM_HandleTypeDef;

#define TIM_COUNTERMODE_UP           0x00000000U
#define TIM_CLOCKDIVISION_DIV1       0x00000000U
#define TIM_CLOCKSOURCE_INTERNAL     0x00000000U
#define TIM_TRGO_RESET               0x00000000U
#define TIM_MASTERSLAVEMODE_DISABLE  0x00000000U
#define TIM_IT_UPDATE                0x00000001U
#define TIM2                          2U

typedef struct { uint32_t ClockSource; } TIM_ClockConfigTypeDef;
typedef struct { uint32_t MasterOutputTrigger; uint32_t MasterSlaveMode; } TIM_MasterConfigTypeDef;

/* ===================== TIM2 节拍计数（Timer0 1ms ISR 驱动） ===================== */
extern volatile uint32_t g_tim2_tick;
extern volatile uint32_t g_sys_ms;     /* 系统毫秒节拍（替代 HAL_GetTick） */

/* ===================== HAL 函数声明 ===================== */
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *);
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);
void HAL_TIM_Tick_Handler(void);   /* 由 Timer0 1ms ISR 调用，推进 TIM2 仿真 */

/* 以下由 at_command_firmware.c 实现（HAL 回调 / MspInit） */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(void);
void HAL_GPIO_EXTI_Callback(void);

/* 垫片实现 */
void HAL_GPIO_EXTI_IRQHandler(uint16_t);
void HAL_GPIO_Init(GPIO_TypeDef *, GPIO_InitTypeDef *);
void HAL_Delay(uint32_t ms);
void HAL_NVIC_SetPriority(IRQn_Type, uint32_t, uint32_t);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);

/* ===================== 宏：RCC / EXTI / TIM 清标志 ===================== */
#define __HAL_RCC_GPIOB_CLK_ENABLE()        do {} while(0)
#define __HAL_RCC_TIM2_CLK_ENABLE()         do {} while(0)
#define __HAL_RCC_TIM2_CLK_DISABLE()        do {} while(0)
#define __HAL_GPIO_EXTI_CLEAR_IT(__PIN__)   do {} while(0)
#define __HAL_TIM_CLEAR_IT(__HTIM__, __FLAG__) \
    do { g_tim2_tick = 0; } while(0)

#endif /* __HAL_COMPAT_H__ */
